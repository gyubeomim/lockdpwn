#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> sentdex pygta5 p.9 코드를 따라해본 코드
                기존의 차선인식방법이 어려우므로 머신러닝을 사용하고
                머신러닝의 학습데이터를 만들기 위해 작성한 코드

                기존의 PIL.ImageGrab을 사용해서 영상을 추출할 때는 10Hz 정도가 나와서
                grabscreen을 사용해보니 30Hz정도가 나온다


'''
import numpy as np
import cv2
import time
import os
from grabscreen import grab_screen
from getkeys import key_check


# 어떤 키(전진,좌회전,우회전)이 눌렸는지를 체크하고 행렬형태로 반환하는 함수
def keys_to_output(keys):
    # [A,W,D]
    output = [0,0,0]

    if 'A' in keys:
        output[0] = 1
    elif 'D' in keys:
        output[2] = 1
    else:
        output[1] = 1

    return output


file_name = 'training_data.npy'

# 이미 파일이 존재하면 기존데이터를 불러오고
if os.path.isfile(file_name):
    print('File exist, loading previous data!')
    training_data = list(np.load(file_name))

# 없는 경우는 빈 리스트를 생성한다
else:
    print('File does not exist, starting fresh')
    training_data = []



def main():
    #last_time = time.time()

    # 무한루프를 돌면서
    while(True):
        # (0,40)부터 (800,600)좌표까지 창을 만들어서 데이터를 저장하고 screen 변수에 저장합니다
        screen = grab_screen(region=(0,40,800,600))

        # 추출한 영상을 흑백으로 한 다음 80x60 사이즈로 축소시킨다
        screen = cv2.cvtColor(screen, cv2.COLOR_BGR2GRAY)
        screen = cv2.resize(screen, (80,60))

        # 조작하는 사람이 어떤 키를 누르는지 지켜보다가
        keys = key_check()
        # 특정키를 누르면 [0,1,0] 같은 행렬로 반환한다
        output = keys_to_output(keys)

        # 그리고 학습데이터에 저장한다
        training_data.append([screen, output])

    
        # While 루프의 속도를 체크하는 코드
        #print('Frame took {} seconds'.format(time.time()-last_time))
        #last_time = time.time()


        # 500번의 루프마다 file.npy에 저장한다
        if len(training_data) % 500 == 0:
            print(len(training_data))
            np.save(file_name, training_data)

main()
