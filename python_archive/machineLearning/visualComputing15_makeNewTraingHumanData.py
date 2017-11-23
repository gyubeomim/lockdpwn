#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 비주얼컴퓨팅, 최종 프로젝트 학습용 데이터를 추가로 만들기 위해 im_trim, im_resize 함수를 사용해 neg 데이터를 만드는 코드
'''
import matplotlib.pyplot as plt
import numpy as np
import tensorflow as tf
import scipy.misc
import scipy.io
import random
import cv2
from PIL import Image
import math
import os

#-------------------------------------------------------
# 1,2,3,4,5... jpg 파일을 resizing 한 후 trim 한다
orig_img = cv2.imread('./newTrainImage_forVC/6.jpg', 0)
cols, rows = orig_img.shape

dic = {}  # 딕서녀리 생성
num_images = 0 # 전체 trim 된 이미지의 갯수

# 이미지 사이즈를 70x134로 리사이징하는 함수
def im_resize_to_orig(img):
    thumbnail = cv2.resize(img, (70, 134))
    return thumbnail


# 이미지를 자르는 함수
def im_trim(img, w, h, prefix, trim_prop):
    global num_images, dic
    iy, ix = img.shape
    xcnt = 0
    ycnt = 0

    # 이미지를 w x h 만큼 잘라서 하나하나씩 저장한다
    for y in range(0, iy, int(h*trim_prop)):
        ycnt += 1
        xcnt = 0
        for x in range(0, ix, int(w*trim_prop)):
            img_trim = img[y:y+h, x:x+w]
            
            # 이미지 크기가 70 x 134 보다 작으면 강제로 70x134로 리사이징 후 저장한다
            cols, rows = img_trim.shape
            if(cols < 134 or rows < 70):
                img_trim = im_resize_to_orig(img_trim)

            dic[num_images] = [prefix, xcnt, ycnt]  # 이미지 이름과 정보를 저장한다. keypoint!

            cv2.imwrite('./newTrainImage_forVC/cropped/'+ str(num_images) + '.jpg', img_trim)
            xcnt += 1
            num_images += 1

    print("[*] Trim Done!")



# 이미지 크기를 줄이는 함수
def im_resize(img, prop):
    iy, ix = img.shape
    thumbnail = cv2.resize(img, (int(ix/prop), int(iy/prop)))
    newiy, newix = thumbnail.shape

    # 리사이징한 이미지 rows가 70보다 작으면 trim을 할 수 없으므로 skip한다
    if(newix < 70):
        return False

    print("orig : (", iy, ",", ix, ") ==> (", newiy, ",", newix ,")")

    cv2.imwrite('./newTrainImage_forVC/resized/' + '_' + str(prop) +'.jpg', thumbnail)

    print("[*] Resize Done!")
    return True


# 이미저 전체 크기가 70x134보다 작으면 리사이징할 필요가 없으므로 아래 변수를 사용해 실제 리사이징된 이미지를 카운트한다
num_resize_img = 0

# 이미지를 리사이징한다. 두번째파라미터는 1/n
for i in range(2, 11):
    isOK = im_resize(orig_img, i)
    if isOK == True:
        num_resize_img += 1


img_1 = orig_img

# img_1, img_2 같은 변수를 loop 안에서 다루기 위해 namespace 변수를 추가한다
namespace = globals()
for i in range(2, num_resize_img+2):
    namespace['img_%d' % i] = cv2.imread('./newTrainImage_forVC/resized/_'+str(i) +'.jpg',0)

# 이미지를 잘라서 저장한다
for i in range(1, num_resize_img+2):
    im_trim(namespace['img_%d' %i] , 70, 134, i, 0.25)


