#!/usr/bin/env python

import rospy
import numpy as np
from environment_radiation.msg import RadiationValue
from environment_radiation.srv import RobotValue, RobotValueRequest, RobotValueResponse

L = 300
W = 200
radiation_list = list(np.zeros((L, W), dtype=np.int))
radiation_object_dict = dict()


def radiationCallback(msg):
	global radiation_list
	global radiation_object_dict
	if msg.M > 0:
		if (msg.x, msg.y) not in radiation_object_dict.keys():
			radiation_object_dict[(msg.x, msg.y)] = msg.M
			radiation_list[msg.x][msg.y] += msg.M
			value = msg.M
			for temp in range(1,msg.M):
				value -= 1
				i = msg.x - temp
				for j in range(msg.y-temp,msg.y+temp+1):
					if i<0 or i>=L or j<0 or j>=W:
						continue
					else:
						radiation_list[i][j] += value
				i = msg.x + temp
				for j in range(msg.y-temp,msg.y+temp+1):
					if i<0 or i>=L or j<0 or j>=W:
						continue
					else:
						radiation_list[i][j] += value
				j = msg.y - temp
				for i in range(msg.x-temp+1,msg.x+temp):
					if i<0 or i>=L or j<0 or j>=W:
						continue
					else:
						radiation_list[i][j] += value
				j = msg.y + temp
				for i in range(msg.x-temp+1,msg.x+temp):
					if i<0 or i>=L or j<0 or j>=W:
						continue
					else:
						radiation_list[i][j] += value
				
			rospy.loginfo("Subscribe Info: x:%d y:%d M:%d", msg.x, msg.y, msg.M)

		else:
			rospy.logwarn("Subscribe Info: x:%d y:%d M:%d", msg.x, msg.y, msg.M)
			rospy.logwarn("There has the object in the postion")
			
		print(radiation_object_dict)
		
	elif msg.M < 0:
		if (msg.x, msg.y) in radiation_object_dict.keys() and radiation_object_dict[(msg.x, msg.y)] == -msg.M:
			radiation_list[msg.x][msg.y] = max(radiation_list[msg.x][msg.y]+msg.M,0)
			del radiation_object_dict[(msg.x, msg.y)]
			print(radiation_object_dict)

			value = abs(msg.M)
			for temp in range(1,abs(msg.M)):
				value -= 1
				i = msg.x - temp
				for j in range(msg.y-temp,msg.y+temp+1):
					if i<0 or i>=L or j<0 or j>=W:
						continue
					else:
						radiation_list[i][j] = max(radiation_list[i][j]-value,0)
				i = msg.x + temp
				for j in range(msg.y-temp,msg.y+temp+1):
					if i<0 or i>=L or j<0 or j>=W:
						continue
					else:
						radiation_list[i][j] = max(radiation_list[i][j]-value,0)
				j = msg.y - temp
				for i in range(msg.x-temp+1,msg.x+temp):
					if i<0 or i>=L or j<0 or j>=W:
						continue
					else:
						radiation_list[i][j] = max(radiation_list[i][j]-value,0)
				j = msg.y + temp
				for i in range(msg.x-temp+1,msg.x+temp):
					if i<0 or i>=L or j<0 or j>=W:
						continue
					else:
						radiation_list[i][j] = max(radiation_list[i][j]-value,0)

			rospy.loginfo("Subscribe Info: x:%d y:%d M:%d", msg.x, msg.y, msg.M)

		else:
			rospy.logwarn("Subscribe Info: x:%d y:%d M:%d", msg.x, msg.y, msg.M)
			rospy.logwarn("No Radiation Object in This Position and Value")


def robotCallback(req):
	global radiation_list
	rospy.loginfo("Service: robot_x:%d robot_y:%d", req.robotx, req.roboty)
	if req.robotx == -1 and req.roboty == -1:
		radiation_list = list(np.zeros((L, W), dtype=np.int))
		radiation_object_dict = dict()
		rospy.logwarn("Clear Environment")
		return -1
	else:
		return RobotValueResponse(radiation_list[req.robotx][req.roboty])


def radiation_subscriber():
	rospy.init_node("environment_radiation", anonymous = True)
	rospy.Subscriber("/radiation_position", RadiationValue, radiationCallback)
	rospy.Service("/robot_radiation", RobotValue, robotCallback)
	rospy.loginfo("node run successfully")
	rospy.spin()


if __name__ == '__main__':
	radiation_subscriber()
