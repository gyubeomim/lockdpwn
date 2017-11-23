#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> CTF, pwn 공격을 할 때 필요한 유용한 코드
'''
import socket
import time
import os
import struct
import telnetlib

def connect(ip,port):
	return socket.create_connection((ip,port))

def p(x):
	return struct.pack('<I', x)

def u(x):
	return struct.unpack('<I', x)[0]

def interact(s):
	print('------- interactive mode ----------')
	t = telnetlib.Telnet()
	t.sock = s
	t.interact()

s = connect('127.0.0.1', 4000)
interact(s)
