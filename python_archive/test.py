#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
	python ==> qtconsole로 ros subscribe 함수를 돌려 값을 확인해보는 코드
'''

import rospy
from sensor_msgs.msg import PointCloud2
import sensor_msgs.point_cloud2 as pc2
import numpy as np

velo_np = np.empty(0)
cam_np = np.empty(0)

def grid_data_velo_callback(msg):
    global velo_np
    print("[+] Subscribing Velo...")
    velo = pc2.read_points(msg, skip_nans=False, field_names=("x", "y", "z","intensity"))
    # to convert velo into numpy.ndarray format
    velo_np = np.array(list(velo))

def grid_data_cam_callback(msg):
    global cam_np
    print("[+] Subscribing Cam...")
    cam = pc2.read_points(msg, skip_nans=False, field_names=("x","y","z","rgb"))
    cam_np = np.array(list(cam))


rospy.init_node("test_node")
_sub = rospy.Subscriber("/grid_data_vel", PointCloud2, grid_data_velo_callback, queue_size=1)
_sub2 = rospy.Subscriber("/grid_data_cam", PointCloud2, grid_data_cam_callback, queue_size=1)
