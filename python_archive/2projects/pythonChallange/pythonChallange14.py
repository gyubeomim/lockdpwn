#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> pythonchallange14, 10000 x 1의 그림을 나선형으로 코딩하는 예제 코드
               난해하다 -_-
'''

from PIL import Image

im = Image.open("wire.png")
new = Image.new(im.mode, [100,100])

doubled_size = 200
directions={'right':(1,0), 'down':(0,1), 'left':(-1,0), 'up':(0,-1)}

x,y,p = -1,0,0
dir_list = ('right','down','left','up')

while doubled_size // 2 > 0:
	for cur_dir in dir_list:
		size = doubled_size // 2

		for s  in range(size):
			x += directions[cur_dir][0]
			y += directions[cur_dir][1]
			new.putpixel( (x,y), im.getpixel((p,0)) )
			p += 1

		doubled_size -= 1
	new.save('level14.jpg')
