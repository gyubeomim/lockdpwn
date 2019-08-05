#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> pythonchallange11, 이미지의 코드를 조작해서 두 개의 이미지로 분리해본 코드
'''
from PIL import Image

img = Image.open("cave.jpg")
new = Image.new(img.mode, img.size)

for x  in range(0, img.size[0], 2):      # img.size[0] = 640
	for y  in range(0, img.size[1], 2): # img.size[1] = 480
		p = img.getpixel((x,y))
		new.putpixel((x, y), p)

new.save("cave2.jpg")

for x  in range(0, img.size[0], 3):
	for y  in range(0, img.size[1], 3):
		p = img.getpixel((x,y))
		new.putpixel((x, y), p)

new.save("cave3.jpg")
