#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> pythonChallange7, 이미지의 RGB값을 읽어와 아스키코드로 변환해서 키를 뽑아내는 코드
                                  chr() 명령어가 숫자를 아스키코드로 변환해주는 명령어인듯
'''
from PIL import Image
import re

img = Image.open("oxygen.png")

#for x  in range(img.size[0]):
#	print img.getpixel((x,45))

row = [img.getpixel((x,45)) for x in range(0,img.size[0],7)]
AS_list = [r for r,g,b,a in row if r==g==b]

string = "".join(map(chr,AS_list))
print string

num = re.findall(r"[0-9]+", string)
ans = ""

for a in range(0,len(num)):
	num[a] = int(num[a])
	ans += chr(num[a])

print num," is ", ans
