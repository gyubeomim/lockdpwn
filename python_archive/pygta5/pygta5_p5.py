#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> sentdex pygta5 p.5 코드를 따라해본 코드
                Canny()로 윤곽선만 영상처리된 영상에서 라인(차선)을 인식하는 코드

'''
import numpy as np
from PIL import ImageGrab
import cv2
import time


# 영상에서 라인(차선)을 인식하고 그려주는 함수
def draw_lines(img, lines):
    try:
        for line in lines:
            coords = line[0]
            cv2.line(img, (coords[0], coords[1]), (coords[2], coords[3]), [255,255,255],3)
    except:
        pass


# Region of Interest : 관심영역을 설정하는 함수
def roi(img, vertices):
    # img 크기만큼의 영행렬을 mask 변수에 저장하고
    mask = np.zeros_like(img)

    # vertices 영역만큼의 Polygon 형상에만 255의 값을 넣습니다
    cv2.fillPoly(mask, vertices, 255)

    # img와 mask 변수를 and (비트연산) 해서 나온 값들을 masked에 넣고 반환합니다
    masked = cv2.bitwise_and(img, mask)
    return masked



# 이미지에 각종 영상처리를 하는 함수
def process_img(original_image):
    processed_img = cv2.cvtColor(original_image, cv2.COLOR_BGR2GRAY)
    processed_img = cv2.Canny(processed_img, threshold1=200, threshold2=300)

    processed_img = cv2.GaussianBlur(processed_img, (5,5), 0)

    # 원하는 영역을 만들고
    vertices =  np.array([[10,500], [10,300], [300,200],[500,200], [800,300], [800,500]])
    # roi()를 사용해 그 영역만큼 영상을 자릅니다
    processed_img = roi(processed_img, [vertices])

    lines = cv2.HoughLinesP(processed_img, 1, np.pi/180, 180,20,15)
    draw_lines(processed_img, lines)

    return processed_img


# 무한루프를 돌면서
while(True):
    # (0,40)부터 (800,600)좌표까지 창을 만들어서 데이터를 저장하고 screen 변수에 저장합니다
    screen = np.array(ImageGrab.grab(bbox=(0,40,800,600)))

    # 이미지에 윤곽선만 추출해서 new_screen 변수에 대입합니다
    new_screen = process_img(screen)

    # pygta5-5이라는 이름의 창을 생성하고 이 창에 screen 이미지를 뿌려줍니다
    cv2.imshow('pygta5-5', new_screen)

    # 'q'키를 누르면 종료합니다
    if cv2.waitKey(25) & 0xFF == ord('q'):
        cv2.destroyAllWindows()
        break


