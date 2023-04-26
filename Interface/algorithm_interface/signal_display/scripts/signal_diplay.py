#!/usr/bin/env python
import rospy
import math
import time
from robot_server.srv import robotinquiryValue
from algorithm_msgs.msg import robot_state_base, robot_state_full
from gazebo_msgs.srv import GetModelState
from visualization_msgs.msg import Marker, MarkerArray

def is_in_area(drones_full_state, robot_positon):
    distance = []
    for drone in drones_full_state:
        dis = math.sqrt((robot_positon.x - drone.pose.x)**2 + (robot_positon.y - drone.pose.y)**2 + (robot_positon.z - drone.pose.z)**2)
        distance.append(dis)
    print(distance)
    if min(distance) >= 10:
        return False
    return True
def signal_display():
    rospy.init_node("signal_display", anonymous = True)
    rospy.loginfo("signal_display_node run successfully")
    while not rospy.is_shutdown():
        rospy.wait_for_service("/robot_inquiry")

        try:
            robots_base_client = rospy.ServiceProxy("/robot_inquiry", robotinquiryValue)
            robots_state_base = robots_base_client(True)
        except rospy.ServiceException, e:
            rospy.logerr("Service call failed: %s",  e)
            continue
        
        wheel_robot_num = 0
        crawer_robot_num = 0
        drone_robot_num = 0
        robots_full_state = list()
        drones_full_state = list()
        for robot in robots_state_base.robot_base:
            if robot.type == 0:
                wheel_robot_num += 1
            elif robot.type == 1:
                crawer_robot_num += 1
            else:
                drone_robot_num += 1
        print(drone_robot_num)
        if drone_robot_num == 0:
            rospy.logerr("no drone robot")
            continue
        if wheel_robot_num + crawer_robot_num == 0:
            continue
        for one_robot_state_base in robots_state_base.robot_base:
            one_robot_state_full = robot_state_full()
            rospy.wait_for_service("/gazebo/get_model_state")
            try:
                one_robot_client = rospy.ServiceProxy("/gazebo/get_model_state", GetModelState)
                print("robot"+str(one_robot_state_base.id))
                full_pose = one_robot_client("robot"+str(one_robot_state_base.id), "map")
		# print(full_pose)
                one_robot_state_full.id = one_robot_state_base.id
                one_robot_state_full.type = one_robot_state_base.type
                one_robot_state_full.energy_consumption = one_robot_state_base.energy_consumption
                one_robot_state_full.max_1 = one_robot_state_base.max_1
                one_robot_state_full.max_2 = one_robot_state_base.max_2
                one_robot_state_full.state = one_robot_state_base.state
                one_robot_state_full.pose = full_pose.pose.position
                one_robot_state_full.twist = full_pose.twist
                if one_robot_state_full.id < 20:
                    robots_full_state.append(one_robot_state_full)
                else:
                    drones_full_state.append(one_robot_state_full)
            except rospy.ServiceException, e:
                rospy.logerr("Service call failed: %s", e)
                break
        print(robots_full_state)
        print("----------------------------------------")
        print(drones_full_state)
        signal_show_marker_topic = []
        robot_marker_msg_list = []
        for i in range(0,20):
            signal_show = rospy.Publisher("/robot" + str(i)+"/visualization_marker", Marker, queue_size = 1)
            signal_show_marker_topic.append(signal_show)
            robot_marker_msg = Marker()
            robot_marker_msg.header.frame_id = "robot"+ str(i)+"_tf/base_link"
            robot_marker_msg.header.stamp = rospy.Time.now()
            robot_marker_msg.ns = "robots"
            robot_marker_msg.id = i
            robot_marker_msg.type = Marker.SPHERE
            robot_marker_msg.action = Marker.ADD
            robot_marker_msg.pose.position.x = 0
            robot_marker_msg.pose.position.y = 0
            robot_marker_msg.pose.position.z = 0
            robot_marker_msg.pose.orientation.w = 1.0

            robot_marker_msg.scale.x = 0.3
            robot_marker_msg.scale.y = 0.3
            robot_marker_msg.scale.z = 0.3

            robot_marker_msg.color.r = 1.0
            robot_marker_msg.color.g = 0.0
            robot_marker_msg.color.b = 0.0
            robot_marker_msg.color.a = 1.0
            robot_marker_msg_list.append(robot_marker_msg)
            signal_show_marker_topic[i].publish(robot_marker_msg_list[i])
        for one_robot_state_full in robots_full_state:
            if is_in_area(drones_full_state, one_robot_state_full.pose):
                robot_marker_msg_list[one_robot_state_full.id].color.r = 0.0
                robot_marker_msg_list[one_robot_state_full.id].color.g = 1.0
                robot_marker_msg_list[one_robot_state_full.id].color.b = 0.0
                robot_marker_msg_list[one_robot_state_full.id].color.a = 1.0
                robot_marker_msg_list[one_robot_state_full.id].action = Marker.MODIFY
                signal_show_marker_topic[one_robot_state_full.id].publish(robot_marker_msg_list[one_robot_state_full.id])
            else:
                robot_marker_msg_list[one_robot_state_full.id].color.r = 1.0
                robot_marker_msg_list[one_robot_state_full.id].color.g = 0.0
                robot_marker_msg_list[one_robot_state_full.id].color.b = 0.0
                robot_marker_msg_list[one_robot_state_full.id].color.a = 1.0
                robot_marker_msg_list[one_robot_state_full.id].action = Marker.MODIFY
                signal_show_marker_topic[one_robot_state_full.id].publish(robot_marker_msg_list[one_robot_state_full.id])
        time.sleep(0.1)
if __name__ == '__main__':
	signal_display()

