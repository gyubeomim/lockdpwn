from pydbg import *
from pydbg.defines import *
import struct
import utils
 
processName = "BlazeDVD.exe"                                         #(1)
dbg = pydbg()
 
def handler_av(dbg):                                                 #(2)

    crash_bin = utils.crash_binning.crash_binning()                  #(3)
    crash_bin.record_crash(dbg)                                      #(4)
    print crash_bin.crash_synopsis()                                 #(5)

    dbg.terminate_process()                                          #(6)

for(pid, name) in dbg.enumerate_processes():                         #(7)
    if name == processName:
        print "[information] dbg attach:" + processName
        dbg.attach(pid)
        
print "[information] start dbg"
dbg.set_callback(EXCEPTION_ACCESS_VIOLATION, handler_av)             #(8)
dbg.run()
