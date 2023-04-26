#!/usr/bin/env python

import rospy
from split_area.msg import drawResult
from algorithm_msgs.msg import robot_state_base, robot_state_full
from task_server.srv import taskinquiryValue, taskinquiryValueRequest, taskinquiryValueResponse
from robot_server.srv import robotinquiryValue, robotinquiryValueRequest, robotinquiryValueResponse
from allocation_within_area.msg import withintaValue
from gazebo_msgs.srv import GetModelState
from geometry_msgs.msg import Point


robots_full_state = list()
tasks_state = list()


def info_collection_node():
	global robots_full_state, tasks_state
	rospy.init_node("info_collection_node", anonymous = True)
	rospy.loginfo("info_collection_node run successfully")
	within_ta_pub = rospy.Publisher("/within_ta_info", withintaValue, queue_size = 1)
	
	while not rospy.is_shutdown():
		robots_full_state = list()
		tasks_state = list()
		rectangle_area = rospy.wait_for_message("/area_result", drawResult, timeout=None)
		rospy.wait_for_service("/task_inquiry")

		try:
			task_client = rospy.ServiceProxy("/task_inquiry", taskinquiryValue)
		
			task_state = task_client(True)
		except rospy.ServiceException, e:
			rospy.logerr("Service call failed: %s", e)
			continue

		for one_task_state in task_state.task:			
				
			if(one_task_state.position.x<rectangle_area.area[0].x 
				or one_task_state.position.x>rectangle_area.area[2].x
				or one_task_state.position.y<rectangle_area.area[0].y
				or one_task_state.position.y>rectangle_area.area[2].y):
				continue
			tasks_state.append(one_task_state)


		rospy.wait_for_service("/robot_inquiry")
		try:
			robots_base_client = rospy.ServiceProxy("/robot_inquiry", robotinquiryValue)
		
			robots_state_base = robots_base_client(True)
		except rospy.ServiceException, e:
			rospy.logerr("Service call failed: %s", e)
			continue

		for one_robot_state_base in robots_state_base.robot_base:
			one_robot_state_full = robot_state_full()
			rospy.wait_for_service("/gazebo/get_model_state")
			try:
				one_robot_client = rospy.ServiceProxy("/gazebo/get_model_state", GetModelState)

				full_pose = one_robot_client("robot"+str(one_robot_state_base.id))
				
				if(full_pose.pose.position.x<rectangle_area.area[0].x 
					or full_pose.pose.position.x>rectangle_area.area[2].x
					or full_pose.pose.position.y<rectangle_area.area[0].y
					or full_pose.pose.position.y>rectangle_area.area[2].y):
					continue

				one_robot_state_full.id = one_robot_state_base.id
				one_robot_state_full.type = one_robot_state_base.type
				one_robot_state_full.energy_consumption = one_robot_state_base.energy_consumption
				one_robot_state_full.max_1 = one_robot_state_base.max_1
				one_robot_state_full.max_2 = one_robot_state_base.max_2
				one_robot_state_full.state = one_robot_state_base.state
				one_robot_state_full.pose = full_pose.pose.position
				one_robot_state_full.twist = full_pose.twist

				robots_full_state.append(one_robot_state_full)
				
			except rospy.ServiceException, e:
				rospy.logerr("Service call failed: %s", e)
				break
		'''i = 0
		full_pose = [[0,0], [5,0], [0,5], [20,20]]
		for one_robot_state_base in robots_state_base.robot_base:
			one_robot_state_full = robot_state_full()
			temp = Point()
			temp.x = full_pose[i][0]
			temp.y = full_pose[i][1]
			
			if(full_pose[i][0]<rectangle_area.area[0].x 
				or full_pose[i][0]>rectangle_area.area[2].x
				or full_pose[i][1]<rectangle_area.area[0].y
				or full_pose[i][1]>rectangle_area.area[2].y):
				continue

			one_robot_state_full.id = one_robot_state_base.id
			one_robot_state_full.type = one_robot_state_base.type
			one_robot_state_full.energy_consumption = one_robot_state_base.energy_consumption
			one_robot_state_full.max_1 = one_robot_state_base.max_1
			one_robot_state_full.max_2 = one_robot_state_base.max_2
			one_robot_state_full.state = one_robot_state_base.state
			one_robot_state_full.pose = temp
			#one_robot_state_full.twist = full_pose.twist

			robots_full_state.append(one_robot_state_full)
			i += 1'''
				

		within_ta_msg = withintaValue()
		within_ta_msg.task = tasks_state
		within_ta_msg.robot_full = robots_full_state	
		within_ta_pub.publish(within_ta_msg)	


if __name__ == '__main__':
	info_collection_node()
