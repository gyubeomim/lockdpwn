#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> my_debugger.py 를 사용해본 예제 코드
                간단하게 PID에 attach 후 run 했다가 detach 하는 코드
'''
import my_debugger

debugger = my_debugger.debugger()

pid = raw_input("Enter the PID if the process to attach to: ")

debugger.attach(int(pid))
debugger.run()
debugger.detach()

