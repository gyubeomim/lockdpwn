#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> dll 안에 있는 특정 함수의 주소를 찾는 코드
'''
import sys
from ctypes import *  
import ctypes  

def usage():
	print "\nGet Function Address  \n"
	print "Usage : %s [dll] [proc]" % sys.argv[0]
	sys.exit()

if len(sys.argv) < 2:
	usage()

target_dll = sys.argv[1]
target_function = sys.argv[2]

dll = windll.LoadLibrary(target_dll)
kernel32 = windll.LoadLibrary('kernel32.dll')

function = kernel32.GetProcAddress( dll._handle, target_function)
print "[##] Find Address %s(%s) : 0x%08x" % (target_dll,target_function,function)
