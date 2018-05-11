#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 해킹침투코딩 p93, 반복문을 사용해 짝수 홀수를 가려주는 코드 
'''
FINAL_NUM = 503
i = 1
while 1:
    if i > 0 and i < 10:
        i += 5
        continue
    elif i % 2 == 0 :
		print str(i) + ": EVEN"
    elif i % 3 == 0:
		print str(i) + ": ODD"
    elif i % FINAL_NUM == 0:
        break
    i += 1

    
