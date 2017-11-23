#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> python receiveICMP.py newfilename 172.30.1.48 850(bytes 크기) 를 사용해 파일을 전송받는 예제 코드
'''
import sys
from scapy.all import *

conf.verb = 0
f = open(sys.argv[1], "w")
host = sys.argv[2]
count = int(sys.argv[3])


filter = "icmp and host " + host
print "sniffing with iflter (%s) for %d bytes" % (filter, int(count))
packets = sniff(count, filter = filter)

for p in packets:
	f.write(p['Raw'].load)

f.close()
print "Data Received"
