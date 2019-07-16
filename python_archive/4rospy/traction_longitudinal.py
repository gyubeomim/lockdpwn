#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> ROS, barc-project에서 가져온 traction control 관련 코드

                        Publish :    오드로이드 --> 아두이노    motor, state 값을 Publish 한다
                        Subscribe :  오드로이드 <-- 아두이노    encoder, servo 값을 subscribe 한다
                        Subscribe :  오드로이드 <-- IMU 센서    IMU 센서 값을 subscribe 한다 
'''
import rospy
import time
from data_service.msg import TimeData
from barc.msg import Encoder, MOT, STATE, SPEED
from math import pi, sin
import time
import serial
from numpy import zeros, hstack, cos, array, dot, arctan
from input_map import angle_2_servo, servo_2_angle
from pid import PID
from filtering import filteredSignal
from scipy.signal import filtfilt, butter, buttord


###########################################################
# Setup measure callbacks
# imu measurement update
# todo
prevtime = 0
deltatime = 0
vx = 0
sleeptime = 0.01

N             = rospy.get_param("longitudinal/N")
Reff          = rospy.get_param("longitudinal/Reff")
threshold     = rospy.get_param("longitudinal/threshold")
counts        = zeros(N)
times         = zeros(N)
Ww_Reff       = 0
desired_slip_ratio  = 0.04
B             = rospy.get_param("longitudinal/B")
buff          = zeros(B)

(ordin,wn) = buttord(.1,.9, 3, 40)
(b,a) = butter(ordin,wn)


def imu_callback(data):
	global a_x, v_x, delta_time, prev_time, buff, b, a

	(_,_,_,a_x,_,_,_,_,_) = data.value
	buff = hstack(([ax], buff[:-1]))
	filtered_buff = filtfilt(b, a, buff)

	acc_filtered = filtered_buff[B/3]
	current_time = data.timestamp

	delta_time = current_time - prev_time

	if(prev_time <= 0):
		delta_time=0

	v_x += acc_filtered * delta_time
	prev_time = current_time



#encoder measurement update
def encoder_callback(data):
	global counts, times, WwReff

	counts = hstack(([data.FR], counts[:-1]))
	times = hstack(([time.time()], times[:-1]))
	Ww = (counts[0]-counts[-1])/(times[0] - times[-1])
	Ww_Reff = Ww * pi / 2 * Reff



def speed_callback(data):
	global speed
	speed = data.speed



def filter_acc_x(acc_raw, filter_obj):
	filter_obj.update(a_x)
	return filter_obj.getFilteredSignal()


#############################################################
# main code
def main_auto():
	#initializeROSnode
	rospy.init_node('auto_mode', anonymous=True)

	rospy.Subscriber('imu', TimeData, imu_callback)
	rospy.Subscriber('encoder', Encoder, encoder_callback)
	rospy.Subscriber('speed', SPEED, speed_callback)

	nh = rospy.Publisher('mot', MOT, queue_size=10)
	log = rospy.Publisher('state', STATE, queue_size=10)

	# set node rate
	rateHz = 50
	rate = rospy.Rate(rateHz)
	dt = 1.0 / rateHz

	p = rospy.get_param("longitudinal/p")
	i = rospy.get_param("longitudinal/i")
	d = rospy.get_param("longitudinal/d")

	pid = PID(P=p, I=i, D=d)

	#main loop
	while not rospy.is_shutdown():
		global v_x , Ww_Reff, desired_slip_ratio, delta_time, speed

                # 슬립율 구하는 코드
                slip_ratio = (Ww_Reff - v_x) / Ww_Reff
                err = slip_ratio - desired_slip_ratio

                # 모터의 속도를 PID 제어하는 코드인듯
                u = 90 + pid.update(err, dt)

                if err > threshold:
                        motor_PWM = max(min(speed, u),90)
                else:
                        pid.reset()
                        motor_PWM = speed

                # publish data
                nh.publish(MOT(motor_PWM))
                log.publish(STATE(v_x, Ww_Reff, err))

                # wait
                rate.sleep()


#------------------------------------------------------------
if __name__ == '__main__':
	try:
		main_auto()
	except rospy.ROSInterruptException:
		pass
