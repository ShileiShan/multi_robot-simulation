#!/usr/bin/env python

import rospy
import numpy as np
#from algorithm_msgs.msg import task_state
from robot_server.msg import robotchangeValue
from robot_server.srv import robotinquiryValue, robotinquiryValueRequest, robotinquiryValueResponse


robot_list = list()
robot_id_list = list()


def changeCallback(msg):
	global robot_list, robot_id_list
		
	if msg.action == 0:
		if msg.robot_base.id not in robot_id_list:
			robot_list.append(msg.robot_base)
			robot_id_list.append(msg.robot_base.id)
			rospy.loginfo("The robot ID:%d add successfully", msg.robot_base.id)
		else:
			rospy.logwarn("There has a same id robot in the list")

	elif msg.action == 1:
		try:	
			index = robot_id_list.index(msg.robot_base.id)
			del robot_list[index]
			del robot_id_list[index]
			rospy.loginfo("The robot ID:%d remove successfully", msg.robot_base.id)
		except ValueError:
			rospy.logwarn("No robot id in task list (for DELETE)")
	
	elif msg.action == 2:
		robot_list = list()
		robot_id_list = list()
		rospy.loginfo("All robots have been deleted")

	elif msg.action == 3:
		if msg.robot_base.id in robot_id_list:
			index = robot_id_list.index(msg.robot_base.id)
			robot_list[index].state = True
			rospy.loginfo("The robot ID:%d validate successfully", msg.robot_base.id)
		else:
			rospy.logwarn("No robot id in robot list (for VALIDATE)")

	elif msg.action == 4:
		if msg.robot_base.id in robot_id_list:
			index = robot_id_list.index(msg.robot_base.id)
			robot_list[index].state = False
			rospy.loginfo("The robot ID:%d invalidate successfully", msg.robot_base.id)
		else:
			rospy.logwarn("No robot id in robot list (for INVALIDATE)")

def inquiryCallback(req):
	if req.inquiry == True:
		return robotinquiryValueResponse(robot_list)
	else:
		rospy.logwarn("Inquiry False")


def robot_server_node():
	rospy.init_node("robot_server_node", anonymous = True)
	rospy.Subscriber("/robot_change", robotchangeValue, changeCallback)
	rospy.Service("/robot_inquiry", robotinquiryValue, inquiryCallback)
	rospy.loginfo("robot_server_node run successfully")
	rospy.spin()


if __name__ == '__main__':
	robot_server_node()
