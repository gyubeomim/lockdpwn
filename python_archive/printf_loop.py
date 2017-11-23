#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> printf() 함수를 사용해본 예제 코드
'''
from ctypes import *
import time

msvcrt = cdll.msvcrt
counter = 0

while 1:
    msvcrt.printf("Loop iteration %d! \n" %counter)
    time.sleep(.5)
    counter += 1
    
