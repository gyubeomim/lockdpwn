#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 해킹침투코딩 p85, 
			   subnet.py 192.168.1.25/24 를 입력하면 네트워크와 서브넷마스크 등을 구분해서 출력하는 코드
'''
import sys

addrString, cidrString = sys.argv[1].split('/')
addr = addrString.split('.')
cidr = int(cidrString)
mask = [0,0,0,0]

for i in range(cidr):
    mask[i/8] = mask[i/8] + (1 << (7 - i % 8))

net = []
for i in range(4):
    net.append(int(addr[i]) & mask[i])

#Determine broadcast parameters from CIDR address and duplicate the
#netwrok address
broad = list(net)
brange = 32 - cidr

for i in range(brange):
    broad[3 - i/8] = broad[3 - i/8] + (1 << (i % 8))

print "Adress: " , addrString
print "Netmask: " , ".".join(map(str,mask))
print "Network: " , ".".join(map(str,net))
print "Broadcast: ", ".".join(map(str,broad))
