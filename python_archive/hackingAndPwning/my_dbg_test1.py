#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> my_debugger.py 를 사용해본 예제 코드
                특정 PID의 레지스터 데이터를 출력한다
'''
import my_debugger

debugger = my_debugger.debugger()

pid = raw_input("Enter the PID of the process to attach to: ")


debugger.attach(int(pid))


list = debugger.enumerate_threads()

for thread in list:

    thread_context = debugger.get_thread_context(thread)
    print "[*] Dumping registers for thread ID : 0x%08x" %  thread
    print "[**] EIP: 0x%08x" % thread_context.Eip
    print "[**] ESP: 0x%08x" % thread_context.Esp
    print "[**] EBP: 0x%08x" % thread_context.Ebp
    print "[**] EAX: 0x%08x" % thread_context.Eax
    print "[**] EBX: 0x%08x" % thread_context.Ebx
    print "[**] ECX: 0x%08x" % thread_context.Ecx
    print "[**] EDX: 0x%08x" % thread_context.Edx
    print "[*] END DUMP"
    

debugger.detach()
    
