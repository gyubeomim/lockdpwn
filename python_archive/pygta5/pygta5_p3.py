#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> sentdex pygta5 p.3 코드를 따라해본 코드
            
               python을 사용해 W 키를 눌러서 gta5 캐릭터가 앞으로 가도록 설정하는 코드
               time.sleep(3) 함수 때문에 Window가 제대로 출력되지 않는 문제점이 있다

'''
import numpy as np
from PIL import ImageGrab
import cv2
import time
# python에서 키보드를 사용하기 위해 아래 코드를 추갛나다
from directkeys import PressKey, ReleaseKey, W,A,S,D

#last_time = time.time()

def process_img(original_image):
    processed_img = cv2.cvtColor(original_image, cv2.COLOR_BGR2GRAY)
    processed_img = cv2.Canny(processed_img, threshold1=200, threshold2=300)

    return processed_img

while(True):
    screen = np.array(ImageGrab.grab(bbox=(0,40,800,600)))
    #print("Loop took {} seconds".format(time.time()-last_time))

    new_screen = process_img(screen)

    print('Down')
    PressKey(W)
    time.sleep(3)
    print('Up')
    ReleaseKey(W)

    cv2.imshow('window', new_screen)
    if cv2.waitKey(25) & 0xFF == ord('q'):
        cv2.destroyAllWindwos()
        break

