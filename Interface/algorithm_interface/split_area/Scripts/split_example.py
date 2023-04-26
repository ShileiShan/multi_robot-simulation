#!/usr/bin/env python

import rospy
import time
from split_area.msg import drawResult


def split_example():
	rospy.init_node("split_example", anonymous = True)
	result_info_pub = rospy.Publisher("/area_result", drawResult, queue_size = 10)

	result_msg = drawResult()
	result_msg.color = -1
	i = 0
	while(1):
		time.sleep(3.5)
		result_info_pub.publish(result_msg)
		i += 1
		if(i == 1):
			break

	result_msg = drawResult()
	result_msg.color = 1
	result_msg.area[0].x = -20.0
	result_msg.area[0].y = -13.0
	result_msg.area[1].x = -11.0
	result_msg.area[1].y = 0.0
	result_msg.area[2].x = 1.0
	result_msg.area[2].y = 0.0
	result_msg.area[3].x = 1.0
	result_msg.area[3].y = -13.0	
	i = 0
	while(1):
		time.sleep(3.5)
		result_info_pub.publish(result_msg)
		i += 1
		if(i == 1):
			break

	'''n = 25000
	while(n>0):
		result_info_pub.publish(result_msg)
		n -= 1'''

	result_msg.color = 2
	result_msg.area[0].x = 3.0
	result_msg.area[0].y = 2.0
	result_msg.area[1].x = 20.0
	result_msg.area[1].y = 2.0
	result_msg.area[2].x = 20.0
	result_msg.area[2].y = -14.0
	result_msg.area[3].x = 3.0
	result_msg.area[3].y = -14.0
	
	i = 0
	while(1):
		time.sleep(3.5)
		result_info_pub.publish(result_msg)
		i += 1
		if(i == 1):
			break


	result_msg.color = 3
	result_msg.area[0].x = -10.0
	result_msg.area[0].y = 10.0
	result_msg.area[1].x = -10.0
	result_msg.area[1].y = 25.0
	result_msg.area[2].x = 20.0
	result_msg.area[2].y = 25.0	
	result_msg.area[3].x = 20.0
	result_msg.area[3].y = 10.0

	i = 0
	while(1):
		time.sleep(3.5)
		result_info_pub.publish(result_msg)
		i += 1
		if(i == 1):
			break


if __name__ == '__main__':
	try:
		split_example()
	except rospy.ROSInterruptException:
		pass
