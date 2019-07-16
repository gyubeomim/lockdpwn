import subprocess
import thread
import time

def POD(id):                                                    #(1)
    ret = subprocess.call("ping server -l 65500", shell=True)
    print "%d," % id
      
for i in range(500):                                            #(2)
    thread.start_new_thread(POD, (i,))                          #(3)
    time.sleep(0.8)                                             #(4)
