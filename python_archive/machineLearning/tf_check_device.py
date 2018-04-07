#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> tensorflow에서 사용가능한 device 목록을 출력하는 코드
'''
from tensorflow.python.client import device_lib

print(device_lib.list_local_devices())

# def get_available_gpus():
#     local_device_protos = device_lib.list_local_devices()
#
#     return [x.name for x in local_device_protos if x.device_type == 'GPU']
# get_available_gpus()
