#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> my_debugger.py 를 사용해본 예제 코드
                printf의 주소를 출력하고 bp를 건다
'''
import my_debugger

debugger = my_debugger.debugger()


pid = raw_input("Enter the PID of the process to attach to: ")

debugger.attach(int(pid))

printf_address = debugger.func_resolve("msvcrt.dll","printf")

print "[*] Address of printf : 0x%08x" % printf_address

debugger.bp_set(printf_address)
debugger.run()
