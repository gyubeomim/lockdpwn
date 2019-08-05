#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> ROS로봇프로그래밍, ROS를 사용해 퍼블리셔를 만들어본 코드
'''
import rospy
from std_msgs.msg import Int32

rospy.init_node('topic_publisher')
pub = rospy.Publisher('counter', Int32)
rate = rospy.Rate(2)

count = 0

while not rospy.is_shutdown():
    pub.publish(count)
    count += 1
    rate.sleep()
