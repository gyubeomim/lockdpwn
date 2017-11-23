#-*- coding: utf-8 -*-
'''
    python ==> 파이썬해킹입문, pydbg를 활용해 메모장의 I love you 를 I hate you로 바꾸는 예제 코드
'''
import utils, sys
from pydbg import *
from pydbg.defines import *

'''
BOOL WINAPI WriteFile(
  _In_         HANDLE hFile,
  _In_         LPCVOID lpBuffer,
  _In_         DWORD nNumberOfBytesToWrite,
  _Out_opt_    LPDWORD lpNumberOfBytesWritten,
  _Inout_opt_  LPOVERLAPPED lpOverlapped
);
'''
        
dbg= pydbg()
isProcess = False

orgPattern = "love"
repPattern = "hate"
processName = "notepad.exe"

def replaceString(dbg, args):                                #(1)
    buffer = dbg.read_process_memory(args[1], args[2])       #(2)

    if orgPattern in buffer:                                 #(3)
        print "[APIHooking] Before : %s" % buffer
        buffer = buffer.replace(orgPattern, repPattern)      # (4)
        replace = dbg.write_process_memory(args[1], buffer)  # (5)
        print "[APIHooking] After : %s" % dbg.read_process_memory(args[1], args[2])

    return DBG_CONTINUE

for (pid, name) in dbg.enumerate_processes():                 #(6)
    if name.lower() == processName :
        isProcess = True
        hooks = utils.hook_container()        

        dbg.attach(pid)                                                       #(7)
        print "Saves a process handle in self.h_process of pid[%d]" % pid

        hookAddress = dbg.func_resolve_debuggee("kernel32.dll", "WriteFile")  #(8)

        if hookAddress:
            hooks.add(dbg, hookAddress, 5, replaceString, None)               #(9)
            print "sets a breakpoint at the designated address : 0x%08x" % hookAddress
            break
        else:
            print "[Error] : couldn't resolve hook address"
            sys.exit(-1)

if isProcess: 
    print "waiting for occuring debugger event"
    dbg.run()                                                                  #(10)
else:
    print "[Error] : There in no process [%s]" % processName
    sys.exit(-1)
