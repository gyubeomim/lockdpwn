#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> my_debugger.py 를 사용해본 예제 코드
'''
import my_debugger
from my_debugger_defines import *

debugger = my_debugger.debugger()

pid = raw_input("Enter the PID of the process to attach to: ")

debugger.attach(int(pid))

printf = debugger.func_resolve("msvcrt.dll","printf")
print "[*] Address of printf: 0x%08x" % printf
debugger.bp_set_mem(printf,10)

debugger.run()
