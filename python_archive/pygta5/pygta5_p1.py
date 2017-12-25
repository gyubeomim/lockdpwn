#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> sentdex pygta5 p.1 코드를 따라해본 코드. 
                 gta5의 800x600 이미지를 읽어서 10Hz 정도로 window에 따로 뿌려준다
'''
import numpy as np
from PIL import ImageGrab
import cv2
import time

last_time = time.time()

while(True):
    screen = np.array(ImageGrab.grab(bbox=(0,40,800,600)))

    cv2.imshow('window2', cv2.cvtColor(screen, cv2.COLOR_BGR2RGB))
    if cv2.waitKey(25) & 0xFF == ord('q'):
        cv2.destroyAllWindwos()
        break

