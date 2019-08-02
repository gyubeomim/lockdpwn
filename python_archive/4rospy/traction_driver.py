#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> ROS, barc-project에서 가져온 traction control 관련 코드
                        
                        Publish : 오드로이드 --> 아두이노    모터의 속도값을 전송하는 코드
'''
# license removed for brevity
import rospy
from dataservice.msg import TimeData
from barc.msg import SPEED
from math import pi, sin
import time
import serial
from numpy import zeros, hstack, cos, array, dot, arctan
from manuevers import TestSettings , StraightBrake

def driver():
	pub = rospy.Publisher('speed', SPEED, queue_size = 10)
	rospy.init_node('driver', anonymous=True)

	rateHz = 50
	dt = 1.0 /rateHz
	rate = rospy.Rate(rateHz)
	t_i  = 0

	speed = rospy.get_param("driver/speed")
	t_0 = rospy.get_param("driver/t_0")
	t_exp = rospy.get_param("driver/t_exp")

	opt = TestSettings(SPD = speed, turn=0, dt =t_exp)
	opt.t_0 = t_0

	while not rospy.is_shutdown():
		(motorCMD, _) = StraightBrake(opt, rateHz, t_i)
		pub.publish(SPEED(motorCMD))
		rate.sleep()
		t_i += 1



if __name__ == '__main__':
	try:
		driver()
	except rospy.ROSInterruptException:
		pass
