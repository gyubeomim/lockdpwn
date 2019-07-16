#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 해킹침투코딩 p92, 리눅스에서 자신의 계정권한을 알 수 있는 코드 
'''
import os

myuid = os.getuid()
if myuid == 0:
    print "You are root"

elif myuid  < 500:
    print "You are system account"

else:
    print "You are just a regular user"

