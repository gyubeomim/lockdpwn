#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> sentdex pygta5 p.1 코드를 따라해본 코드. 
                 gta5의 800x600 이미지를 읽어서 10Hz 정도로 window에 따로 뿌려준다
'''
import numpy as np
from PIL import ImageGrab
import cv2

# 무한루프를 돌면서 
while(True):
    # (0,40)부터 (800,600)좌표까지 창을 만들어서 데이터를 저장하고 screen 변수에 저장합니다
    screen = np.array(ImageGrab.grab(bbox=(0,40,800,600)))

    # pygta5-1이라는 이름의 창을 생성하고 이 창에 screen 이미지를 뿌려줍니다
    cv2.imshow('pygta5-1', cv2.cvtColor(screen, cv2.COLOR_BGR2RGB))

    # 'q'키를 누르면 종료합니다
    if cv2.waitKey(25) & 0xFF == ord('q'):
        cv2.destroyAllWindows()
        break

