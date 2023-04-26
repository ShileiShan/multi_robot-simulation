#!/usr/bin/env python

import rospy
import numpy as np
#from algorithm_msgs.msg import task_state
from task_server.msg import taskchangeValue
from task_server.srv import taskinquiryValue, taskinquiryValueRequest, taskinquiryValueResponse
from visualization_msgs.msg import Marker, MarkerArray


task_list = list()
task_id_list = list()

class task_server_subandpub:
    def __init__(self):
        self.__task_marker_pub_ = rospy.Publisher("/task_server/visualization_marker", Marker, queue_size = 1)
        self.__task_change_sub_ = rospy.Subscriber("/task_change", taskchangeValue, self.changeCallback)
 
    def changeCallback(self, msg):
        assert isinstance(msg, taskchangeValue) 
        # To check if get correct msg
      		
	global task_list, task_id_list
	task_marker_msg = Marker()	
	if msg.action == 0:
		if msg.task.id not in task_id_list:
			task_list.append(msg.task)
			task_id_list.append(msg.task.id)
			task_marker_msg.header.frame_id = "map"
			task_marker_msg.header.stamp = rospy.Time.now()
			task_marker_msg.ns = "tasks"
			task_marker_msg.id = msg.task.id
			task_marker_msg.type = Marker.SPHERE
			task_marker_msg.action = Marker.ADD

			task_marker_msg.pose.position = msg.task.position
			task_marker_msg.pose.orientation.w = 1.0
			
			task_marker_msg.scale.x = 0.3
			task_marker_msg.scale.y = 0.3
			task_marker_msg.scale.z = 0.3

			task_marker_msg.color.r = 1.0
			task_marker_msg.color.g = 0.0
			task_marker_msg.color.b = 0.0
			task_marker_msg.color.a = 1.0

			self.__task_marker_pub_.publish(task_marker_msg)
			
			rospy.loginfo("The task ID:%d add successfully", msg.task.id)
		else:
			rospy.logwarn("There has a same id task in the list")

	elif msg.action == 1:
		try:	
			index = task_id_list.index(msg.task.id)
			del task_list[index]
			del task_id_list[index]

			task_marker_msg.ns = "tasks"
			task_marker_msg.id = msg.task.id
			task_marker_msg.action = Marker.DELETE

			self.__task_marker_pub_.publish(task_marker_msg)
			rospy.loginfo("The task ID:%d remove successfully", msg.task.id)
		except ValueError:
			rospy.logwarn("No task id in task list (for DELETE)")
	
	elif msg.action == 2:
		task_list = list()
		task_id_list = list()

		task_marker_msg.action = Marker.DELETEALL

		self.__task_marker_pub_.publish(task_marker_msg)
		rospy.loginfo("All tasks have been deleted")

	elif msg.action == 3:
		if msg.task.id in task_id_list:
			index = task_id_list.index(msg.task.id)
			task_list[index].complete = True

			task_marker_msg.ns = "tasks"
			task_marker_msg.id = msg.task.id
			task_marker_msg.action = Marker.DELETE

			self.__task_marker_pub_.publish(task_marker_msg)
			rospy.loginfo("The task ID:%d complete successfully", msg.task.id)
		else:
			rospy.logwarn("No task id in task list (for COMPLETE)")	


'''def changeCallback(msg):
	global task_list, task_id_list
	task_marker_pub = rospy.Publisher("/visualization_marker", Marker, queue_size = 1)
	task_marker_msg = Marker()	
	if msg.action == 0:
		if msg.task.id not in task_id_list:
			task_list.append(msg.task)
			task_id_list.append(msg.task.id)
			task_marker_msg.header.frame_id = "map"
			task_marker_msg.header.stamp = rospy.Time.now()
			task_marker_msg.ns = "tasks"
			task_marker_msg.id = msg.task.id
			task_marker_msg.type = Marker.SPHERE
			task_marker_msg.action = Marker.ADD

			task_marker_msg.pose.position = msg.task.position
			task_marker_msg.pose.orientation.w = 1.0
			
			task_marker_msg.scale.x = 0.3;	
			task_marker_msg.scale.y = 0.3;
			task_marker_msg.scale.z = 0.3;

			task_marker_msg.color.r = 1.0
			task_marker_msg.color.g = 0.0
			task_marker_msg.color.b = 0.0
			task_marker_msg.color.a = 1.0

			task_marker_pub.publish(task_marker_msg)
			
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
			rospy.loginfo("The task ID:%d complete successfully", msg.task.id)
		else:
			rospy.logwarn("No task id in task list (for COMPLETE)")'''

def inquiryCallback(req):
	if req.inquiry == True:
		return taskinquiryValueResponse(task_list)
	else:
		rospy.logwarn("Inquiry False")


def task_server_node():
	rospy.init_node("task_server_node", anonymous = True)
	rospy.Service("/task_inquiry", taskinquiryValue, inquiryCallback)	
	SAPObject = task_server_subandpub()
	rospy.loginfo("task_server_node run successfully")
	rospy.spin()


if __name__ == '__main__':
	task_server_node()
