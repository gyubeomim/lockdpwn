#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> tensorflow에서 사용가능한 device 목록을 출력하는 코드
'''
import tensorflow as tf
from tensorflow.python.client import device_lib

print(device_lib.list_local_devices())

# 또는 간단하게

tf.test.is_gpu_available()
tf.test.gpu_device_name()




#START============================================
# def get_available_gpus():
#     local_device_protos = device_lib.list_local_devices()
#
#     return [x.name for x in local_device_protos if x.device_type == 'GPU']
# get_available_gpus()
#END==============================================
