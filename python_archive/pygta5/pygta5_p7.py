#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> sentdex pygta5 p.7 코드를 따라해본 코드
                차선을 인식해서 차선의 기울기에 따라 차체를 스크립트로 조종해본 코드

'''
from PIL import ImageGrab
import cv2
import time
import sys, os

import numpy as np
from numpy import ones, vstack
from numpy.linalg import lstsq

from directkeys import PressKey, W, A, S, D
from statistics import mean


# 영상에서 라인(차선)을 인식하고 그려주는 함수
def draw_lines(img, lines, color=[0,255,255], thickness=3):
    try:
        # finds the maximum y value for a lane marker
        # (since we cannot assume the horizon will always be at the same point)
        ys = []
        for i in lines:
            for ii in i:
                ys += [ii[1], ii[3]]

        # 라인중에서 y값이 가장 작은값(화면상 위쪽)을 저장하고
        min_y = min(ys)
        # 가장 큰값은 800x600에서 600이 최대이므로 600을 저장한다
        max_y = 600

        new_lines = []
        line_dict = {}

        for idx, i in enumerate(lines):
            for xyxy in i:
                # These four lines:
                # modified from http://stackoverflow.com/questions/21565994/method-to-return-the-equation-of-a-straight-line-given-two-points 
                # Used to calculate the definition of a line, given two sets of coords.
                x_coords = (xyxy[0], xyxy[2])
                y_coords = (xyxy[1], xyxy[3])

                A = vstack([x_coords, ones(len(x_coords))]).T
                m, b = lstsq(A, y_coords)[0]

                # calculating our new, and improved, xs
                x1 = (min_y - b) / m
                x2 = (max_y - b) / m

                # 기울기, 절편, 실제좌표값을 담는 line_dict[] 리스트를 만듭니다
                line_dict[idx] = [m, b,[int(x1), min_y, int(x2), max_y]]

                new_lines.append([int(x1), min_y, int(x2), max_y])


        final_lanes = {}


        for idx in line_dict:
            final_lanes_copy = final_lanes.copy()
            m = line_dict[idx][0]
            b = line_dict[idx][1]
            line = line_dict[idx][2]

            if len(final_lanes) == 0:
                final_lanes[m] = [ [m,b,line] ]

            else:
                found_copy = False

                for other_ms in final_lanes_copy:
                    if not found_copy:
                        # 다른 기울기의 직선들도 +-20%안에 있으면 같은 직선으로 인식한다
                        # +-20% 보다 차이가 많이나면 새로운 직선으로 인식한다
                        if abs(other_ms*1.2) > abs(m) > abs(other_ms*0.8):
                            if abs(final_lanes_copy[other_ms][0][1]*1.2) > abs(b) > abs(final_lanes_copy[other_ms][0][1]*0.8):
                                final_lanes[other_ms].append([m,b,line])
                                found_copy = True
                                break
                        else:
                            final_lanes[m] = [[m,b,line]]

        line_counter = {}

        for lanes in final_lanes:
            line_counter[lanes] = len(final_lanes[lanes])

        # 여러 차선 후보들 중에서 가장 기울기가 많이 유사하게 검출된 직선들 중
        # 2개를 뽑아서 차선으로 인식한다
        top_lanes = sorted(line_counter.items(), key=lambda item: item[1])[::-1][:2]

        lane1_id = top_lanes[0][0]
        lane2_id = top_lanes[1][0]

        # 기울기가 유사한 직선들의 x,y값들을 평균내서 반환하는 함수
        def average_lane(lane_data):
            x1s = []
            y1s = []
            x2s = []
            y2s = []

            for data in lane_data:
                x1s.append(data[2][0])
                y1s.append(data[2][1])
                x2s.append(data[2][2])
                y2s.append(data[2][3])

            return int(mean(x1s)), int(mean(y1s)), int(mean(x2s)), int(mean(y2s))


        # 최종적으로 2개의 직선의 시작점, 끝점을 알 수 있다. (각각 2개씩 총 4개의 (x,y)좌표이므로 총 8개의 점)
        l1_x1, l1_y1, l1_x2, l1_y2 = average_lane(final_lanes[lane1_id])
        l2_x1, l2_y1, l2_x2, l2_y2 = average_lane(final_lanes[lane2_id])

        return [l1_x1, l1_y1, l1_x2, l1_y2], [l2_x1, l2_y1, l2_x2, l2_y2], lane1_id, lane2_id

    except Exception as e:
        print('1 : ' + str(e))



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
def process_img(image):
    original_image = image

    # convert to gray
    processed_img = cv2.cvtColor(original_image, cv2.COLOR_BGR2GRAY)
    # edge detection
    processed_img = cv2.Canny(processed_img, threshold1=200, threshold2=300)
    processed_img = cv2.GaussianBlur(processed_img, (5,5), 0)

    # 원하는 영역을 만들고
    vertices =  np.array([[10,500], [10,300], [300,200],[500,200], [800,300], [800,500]], np.int32)

    # roi()를 사용해 그 영역만큼 영상을 자릅니다
    processed_img = roi(processed_img, [vertices])

    # more info: http://docs.opencv.org/3.0-beta/doc/py_tutorials/py_imgproc/py_houghlines/py_houghlines.html
    #                                    rho   theta   thresh  min length, max gap:   
    lines = cv2.HoughLinesP(processed_img, 1,np.pi/180, 180,   5,      50)

    # 직선의 기울기를 저장하는 변수 추가
    m1 = 0
    m2 = 0

    # 차선 2개의 직선(직선의방정식)을 얻은 다음 추출영상에 그린다
    try:
        l1, l2, m1, m2 = draw_lines(original_image, lines)
        cv2.line(original_image, (l1[0], l1[1]), (l1[2], l1[3]), [0,255,0], 30)
        cv2.line(original_image, (l2[0], l2[1]), (l2[2], l2[3]), [0,255,0], 30)

    except Exception as e:
        print('2 : ' + str(e))
        pass

    # HoughLinesP() 굵은선을 그려주는 코드
    try:
        for coords in lines:
            coords = coords[0]
            try:
                cv2.line(processed_img, (coords[0], coords[1]), (coords[2], coords[3]), [255,0,0], 3)

            except Exception as e:
                print('3 : ' + str(e))

    except Exception as e:
        pass


    return processed_img, original_image, m1, m2


# 전진하는 함수
def straight():
    PressKey(W)
    ReleaseKey(A)
    ReleaseKey(D)

# 좌측으로 이동하는 함수
def left():
    PressKey(A)
    ReleaseKey(W)
    ReleaseKey(D)

# 우측으로 이동하는 함수
def right():
    PressKey(D)
    ReleaseKey(A)
    ReleaseKey(W)


# 4초의 카운트다운을 가진다
for i in list(range(4))[::-1]:
    print(i+1)
    time.sleep(1)


#last_time = time.time()

# 무한루프를 돌면서
while(True):
    # (0,40)부터 (800,600)좌표까지 창을 만들어서 데이터를 저장하고 screen 변수에 저장합니다
    screen = np.array(ImageGrab.grab(bbox=(0,40,800,600)))

    #print('Frame took {} seconds'.format(time.time()-last_time))
    #last_time = time.time()

    # 이미지에 윤곽선만 추출해서 new_screen 변수에 대입합니다
    new_screen, original_image, m1, m2 = process_img(screen)

    # pygta5-7이라는 이름의 창을 생성하고 이 창에 screen 이미지를 뿌려줍니다
    #cv2.imshow('pygta5-7', new_screen)
    cv2.imshow('pygta5-7-2', cv2.cvtColor(original_image, cv2.COLOR_BGR2RGB))



    # 인식되는 차선의 기울기가 동시에 양이거나 음이면 한쪽으로 치우쳤다는 뜻이므로 반대방향으로 이동하도록 조작한다
    if m1 < 0 and m2 < 0:
        right()
    elif m1 > 0 and m2 > 0:
        left()
    else:
        straight()


    # 'q'키를 누르면 종료합니다
    if cv2.waitKey(25) & 0xFF == ord('q'):
        cv2.destroyAllWindows()
        break
