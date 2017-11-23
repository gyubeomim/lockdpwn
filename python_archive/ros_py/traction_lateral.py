#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> ROS, barc-project에서 가져온 traction control 관련 코드

                        Publish :   오드로이드 --> 아두이노   servo 모터 값을 PID 계산해서 전송하고
                        Subscribe : IMU --> 오드로이드        IMU 값을 받아서 yaw 값을 계산하는 코드
'''
import rospy
from barc.msg import SERV
from data_service.msg import TimeData
from math import pi,sin
import time
import serial
from numpy import zeros,hstack,cos,array,dot,arctan,sign
from numpy import unwrap
from input_map import angle_2_servo, servo_2_angle
from manuevers import TestSettings, CircularTest, Straight, SineSweep, DoubleLaneChange, CoastDown
from pid import PID

# pid control for constrant yaw angle
yaw0 = 0
read_yaw0 = False
yaw_prev = 0
yaw = 0
err = 0

def imu_callback(data):
	global yaw0, read_yaw0, yaw_prev , yaw, err

	#extract yaw angle
	(_,_,yaw,_,_,_,_,_,_) = data.value

	# same initial measurements
	if not read_yaw0:
		read_yaw0 = True
		yaw0 = yaw
	else:
		temp = unwrap(array([yaw_prev,yaw]))
		yaw = temp[1]
		yaw_prev = yaw
		err = yaw - yaw0


#############################################################
def main_auto():
	#initialize ROS node
	rospy.init_node('auto_mode', anonymous=True)
	nh = rospy.Publisher('serv', SERV, queue_size = 10)
	rospy.Subscriber('imu', TimeData, imu_callback)

	#set node rate
	rateHz = 50
	dt = 1.0 / rateHz
	rate = rospy.Rate(rateHz)

	#use simple pid control to keep steering straight
	p = rospy.get_param("lateral/p")
	i = rospy.get_param("lateral/i")
	d = rospy.get_param("lateral/d")
	pid = PID(P=p, I=i, D=d)

	#main_loop
	while not rospy.is_shutdown():
		#get steering wheel command
		u = pid.update(err, dt)
		servoCMD = angle_2_servo(u)

		#send command signal
                # 위에서 PID 계산한 servoCMD 값을 serv_cmd로 publish한다
		serv_cmd = SERV(servoCMD)
		nh.publish(serv_cmd)

		#wait
		rate.sleep()


#############################################################
if __name__ == '__main__':
	try:
		main_auto()
	except rospy.ROSInterruptException:
		pass
