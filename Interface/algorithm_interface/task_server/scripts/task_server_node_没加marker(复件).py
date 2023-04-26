#!/usr/bin/env python

import rospy
import numpy as np
#from algorithm_msgs.msg import task_state
from task_server.msg import taskchangeValue
from task_server.srv import taskinquiryValue, taskinquiryValueRequest, taskinquiryValueResponse


task_list = list()
task_id_list = list()


def changeCallback(msg):
	global task_list, task_id_list
		
	if msg.action == 0:
		if msg.task.id not in task_id_list:
			task_list.append(msg.task)
			task_id_list.append(msg.task.id)
			rospy.loginfo("The task ID:%d add successfully", msg.task.id)
		else:
			rospy.logwarn("There has a same id task in the list")

	elif msg.action == 1:
		try:	
			index = task_id_list.index(msg.task.id)
			del task_list[index]
			del task_id_list[index]
			rospy.loginfo("The task ID:%d remove successfully", msg.task.id)
		except ValueError:
			rospy.logwarn("No task id in task list (for DELETE)")
	
	elif msg.action == 2:
		task_list = list()
		task_id_list = list()
		rospy.loginfo("All tasks have been deleted")

	elif msg.action == 3:
		if msg.task.id in task_id_list:
			index = task_id_list.index(msg.task.id)
			task_list[index].complete = True
			rospy.loginfo("The task ID:%d remove successfully", msg.task.id)
		else:
			rospy.logwarn("No task id in task list (for COMPLETE)")

def inquiryCallback(req):
	if req.inquiry == True:
		return taskinquiryValueResponse(task_list)
	else:
		rospy.logwarn("Inquiry False")


def task_server_node():
	rospy.init_node("task_server_node", anonymous = True)
	rospy.Subscriber("/task_change", taskchangeValue, changeCallback)
	rospy.Service("/task_inquiry", taskinquiryValue, inquiryCallback)
	rospy.loginfo("task_server_node run successfully")
	rospy.spin()


if __name__ == '__main__':
	task_server_node()
