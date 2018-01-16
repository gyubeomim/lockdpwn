#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> sentdex pygta5 p.2 코드를 따라해본 코드. 
               Canny() 함수를 사용해서 Edge들을 따오는 코드 
'''
import numpy as np
from PIL import ImageGrab
import cv2
import time

# 이미지에 Canny() 함수를 사용해 윤곽선을 따는 함수
def process_img(original_image):
    processed_img = cv2.cvtColor(original_image, cv2.COLOR_BGR2GRAY)
    processed_img = cv2.Canny(processed_img, threshold1=200, threshold2=300)

    return processed_img


# 무한루프를 돌면서
while(True):
    # (0,40)부터 (800,600)좌표까지 창을 만들어서 데이터를 저장하고 screen 변수에 저장합니다
    screen = np.array(ImageGrab.grab(bbox=(0,40,800,600)))

    # 이미지에 윤곽선만 추출해서 new_screen 변수에 대입합니다
    new_screen = process_img(screen)

    # pygta5-2이라는 이름의 창을 생성하고 이 창에 screen 이미지를 뿌려줍니다
    cv2.imshow('pygta5-2', new_screen)

    # 'q'키를 누르면 종료합니다
    if cv2.waitKey(25) & 0xFF == ord('q'):
        cv2.destroyAllWindows()
        break

