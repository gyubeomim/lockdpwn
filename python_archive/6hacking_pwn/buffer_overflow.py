#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> 파이썬해킹프로그래밍, access_violation_handler.py와 같이 사용하는 코드
'''
from ctypes import *

msvcrt = cdll.msvcrt

raw_input("Once the debugger is attached, press any key.")
buffer = c_char_p("AAAAA")

overflow = "A" * 100
msvcrt.strcpy(buffer, overflow)
