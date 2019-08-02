#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> pythonchallange12, evil2.gfx 바이너리 값을 5바이트 단위로 읽어서 여러 파일을 생성해본  코드
'''

h = open("evil2.gfx",'rb')
data = h.read()
h.close()

new_data = [[],[],[],[],[]]

for byte  in range(len(data) - 1):
	new_data[byte%5].append(data[byte])

for n,elt  in enumerate(new_data):
	h = open(str(n+1),'wb')
	h.write("".join(elt))
	h.close()
