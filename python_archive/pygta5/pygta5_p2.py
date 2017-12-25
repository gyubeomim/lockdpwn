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

#last_time = time.time()


def process_img(original_image):
    processed_img = cv2.cvtColor(original_image, cv2.COLOR_BGR2GRAY)
    processed_img = cv2.Canny(processed_img, threshold1=200, threshold2=300)

    return processed_img


while(True):
    screen = np.array(ImageGrab.grab(bbox=(0,40,800,600)))
    #print("Loop took {} seconds".format(time.time()-last_time))

    new_screen = process_img(screen)
    
    cv2.imshow('window', new_screen)
    #cv2.imshow('window2', cv2.cvtColor(screen, cv2.COLOR_BGR2RGB))
    if cv2.waitKey(25) & 0xFF == ord('q'):
        cv2.destroyAllWindwos()
        break

