#!/usr/bin/python

import time
import subprocess
from Xlib import X
from Xlib.display import Display

display = Display(':0')
root = display.screen().root
root.grab_pointer(True,
        X.ButtonPressMask | X.ButtonReleaseMask | X.PointerMotionMask,
        X.GrabModeAsync, X.GrabModeAsync, 0, 0, X.CurrentTime)
root.grab_keyboard(True,
        X.GrabModeAsync, X.GrabModeAsync, X.CurrentTime)

subprocess.call('xset dpms force off'.split())
p = subprocess.Popen('gnome-screensaver-command -i'.split())
time.sleep(1)

while True:
    print display.next_event()
    p.terminate()
    break
