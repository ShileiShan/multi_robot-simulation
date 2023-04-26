#!/usr/bin/env python

import rospy
from allocation_within_area.msg import allocationResult, one_sequence

def result_publisher():
	rospy.init_node("result_publisher", anonymous = True)
	result_info_pub = rospy.Publisher("/allocation_result", allocationResult, queue_size = 10)

	result_msg = list()
	one_msg = one_sequence()

	one_msg.id = 0
	one_msg.targets = [0,1] #[1,0,5]
	result_msg.append(one_msg)
	
	one_msg = one_sequence()
	one_msg.id = 1
	one_msg.targets = [2,3] #[3,2,7]
	result_msg.append(one_msg)
	
	one_msg = one_sequence()
	one_msg.id = 10
	one_msg.targets = [4,5,6] #[4,6,8]
	result_msg.append(one_msg)

	one_msg = one_sequence()
	one_msg.id = 11
	one_msg.targets = [7,8] #[4,6,8]
	result_msg.append(one_msg)
	n = 250000
	while(n>0):
		result_info_pub.publish(result_msg)
		n -= 1


if __name__ == '__main__':
	try:
		result_publisher()
	except rospy.ROSInterruptException:
		pass
