#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
   python ==> opencv, 이미지를 원하는 크기만큼 잘라서 trim%d.jpg 로 이미지를 저장하는 코드. 
                        비주얼컴퓨팅 Human Detection에서 사용했다
'''
import cv2

# 이미지를 자르는 함수
def im_trim(img):
    iy, ix = img.shape
    cnt = 0
    w = 70
    h = 134

    # 이미지를 w x h 만큼 잘라서 하나하나씩 저장한다
    for y in range(0, iy, h):
        for x in range(0, ix, w):
            img_trim = img[y:y+h, x:x+w]
            cv2.imwrite('./trim'+ str(cnt) + '.jpg', img_trim)
            cnt += 1

    print("[*] Trim Done!")

# 이미지 크기를 줄이는 함수
def im_resize(img, prop):
    iy, ix = img.shape

    thumbnail = cv2.resize(img, (int(ix/prop), int(iy/prop)))

    newiy, newix = thumbnail.shape
    print(newiy, newix)

    cv2.imwrite('./resized_img.jpg', thumbnail)

    print("[*] Resize Done!")


org_img = cv2.imread('PennPed00029.png', 0)
im_trim(org_img)
im_resize(org_img, 2)
