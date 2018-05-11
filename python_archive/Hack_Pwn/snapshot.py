#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> calc.exe 프로그램을 열어서 스냅샷을 찍어서 복구해보는 예제 코드
                calc.exe x86 에서만 가능하다
'''
from pydbg import *
from pydbg.defines import *

import threading
import time
import sys

class snapshotter(object):
    def __init__(self,exe_path):
        self.exe_path = exe_path
        self.pid = None
        self.dbg = None
        self.running = True

        pydbg_thread = threading.Thread(group = None, target = self.start_debugger)
        pydbg_thread.setDaemon(0)
        pydbg_thread.start()

        while self.pid == None:
                time.sleep(1)

        monitor_thread = threading.Thread(target = self.monitor_debugger)
        monitor_thread.setDaemon(0)
        monitor_thread.start()


    def monitor_debugger(self):
        while self.running == True:
            input = raw_input("Enter: 's' is snap 'r' is restore 'q' is quit\n")
            input = input.lower().strip()

            if input == "q":
                print "[*] Exiting the snapshotter."
                self.running == False
                self.dbg.terminate_process()

            elif input == "s":
                print "[*] Supending all threads."
                self.dbg.suspend_all_threads()

                print "[*] Obtaining snapshot."
                self.dbg.process_snapshot()

                print "[*] Resuming operation."
                self.dbg.resume_all_threads()

            elif input == "r":
                print "[*] Suspending all threads."
                self.dbg.suspend_all_threads()

                print "[*] Restoring snapshot."
                self.dbg.process_restore()

                print "[*] Resuming operation."
                self.dbg.resume_all_threads()

    def start_debugger(self):
        self.dbg = pydbg()
        pid = self.dbg.load(self.exe_path)
        self.pid = self.dbg.pid
        self.dbg.run()

exe_path = "C:\\Windows\\SysWOW64\\calc.exe"
snapshotter(exe_path)
