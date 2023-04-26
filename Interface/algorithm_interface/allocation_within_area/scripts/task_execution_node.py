#!/usr/bin/env python

import rospy
import actionlib  
from actionlib_msgs.msg import * 

from threading import Thread
#from multiprocessing import Pool
from allocation_within_area.msg import allocationResult
from geometry_msgs.msg import Pose, PoseWithCovarianceStamped, Point, Quaternion, Twist  
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from task_server.msg import taskchangeValue
from task_server.srv import taskinquiryValue, taskinquiryValueRequest, taskinquiryValueResponse  


def positionNav(local_id, local_locations, local_taskids):
	#print(local_id, local_locations)
	# Subscribe to the move_base action server  

	complete_pub = rospy.Publisher("/task_change", taskchangeValue, queue_size = 1)
	move_base = actionlib.SimpleActionClient("robot" + str(local_id) + "/move_base", MoveBaseAction) 
	rospy.loginfo("Waiting for move_base action server...")  

	# Wait 60 seconds for the action server to become available  
	move_base.wait_for_server(rospy.Duration(60))
	rospy.loginfo("Connected to move base server")  

	# Variables
	n_locations = len(local_locations)
	i = 0

	# Begin the main loop and run through a sequence of locations
	while not rospy.is_shutdown():
		# If we've gone through the all sequence, then exit
		if i == n_locations:  
			rospy.logwarn("Now reach all destination, now exit the function {robot: %d}", local_id)
			#rospy.signal_shutdown('Quit')  
			break

		else:
			# Increment the counters  

			# Set up the next goal location 
			goal = MoveBaseGoal()
			goal.target_pose.pose = local_locations[i]  
			goal.target_pose.header.frame_id = 'map'  
			goal.target_pose.header.stamp = rospy.Time.now()  

			# Start the robot toward the next location 
			move_base.send_goal(goal)

			# Allow 10 minutes to get there  
			finished_within_time = move_base.wait_for_result(rospy.Duration(600)) 

			# Check for success or failure  
			if not finished_within_time:  
				move_base.cancel_goal() #move_base.cancle_goal()  
				rospy.logerr("Timed out achieving goal {robot: %d}", local_id)  
			else:  
				state = move_base.get_state() #move_base.get_state()  
				if state == GoalStatus.SUCCEEDED:  
					rospy.loginfo("Goal succeeded {robot: %d}", local_id) 
					complete_msg = taskchangeValue()
					complete_msg.action = 3
					complete_msg.task.id = local_taskids[i]
					complete_pub.publish(complete_msg)
					rospy.sleep(1)     
				else:  
					rospy.logerr("Goal failed with error code: " + str(state))  
			i += 1			


def task_execution_node():
	while not rospy.is_shutdown():
		sequences = rospy.wait_for_message("/allocation_result", allocationResult, timeout=None)
		#print(sequences.robot_sequences[0].targets[0], type(sequences.robot_sequences[0].targets[0]))
		rospy.wait_for_service("/task_inquiry")

		try:
			task_client = rospy.ServiceProxy("/task_inquiry", taskinquiryValue)
		
			task_state = task_client(True)
		except rospy.ServiceException, e:
			rospy.logerr("Service call failed: %s", e)
			continue

		#n_processes = len(sequences.robot_sequences)
		#pool = Pool(processes=n_processes)
		threads = list()

		for one_sequence in sequences.robot_sequences:
			locations = list()
			for target in one_sequence.targets:
				#print(one_sequence.targets)
				for task in task_state.task:
					#print(target, task.id)		
					if target == task.id:
						#locations[str(task.id)] = Pose(task.position, Quaternion(0.000, 0.000, 0.000, 1.000))
						locations.append(Pose(task.position, Quaternion(0.000, 0.000, 0.000, 1.000)))
			#positionNav(task.id, locations)
			#pool.apply_async(positionNav, (one_sequence.id, locations,))
			threads.append(Thread(target=positionNav, args=(one_sequence.id, locations, one_sequence.targets)))
		#pool.close()
		#pool.join()

		for t in threads: t.start()
		for t in threads: t.join()


if __name__ == '__main__':
	rospy.init_node("task_execution_node", anonymous = True)
	rospy.loginfo("task_execution_node run successfully")
	task_execution_node()



