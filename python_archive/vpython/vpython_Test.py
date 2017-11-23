#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 spring의 압축, 인장을 애니메이션해 본 코드
                code from https://www.youtube.com/watch?v=9Hf6kfU9KCg
'''
from visual import *
from random import uniform, random
from visual.controls import *

display(center=(0,0,0), background=(1,1,1), autoscale=False, range=(3,5,3), widt=500, height=600, forward=(-1.4,-1.3,-1))

distant_light(direction=(1,1,1), color = color.red)
spring = helix(pos=(0,2,1), axis=(5,0,0), radius=0.5)

dl =.1

l = 1.

def proses():
    global l,dl
    spring.length = l
    if l > 2:
        l = 2
        dl *= -1
    elif l < .5:
        l = .5
        dl *= -1
    l += dl
    
while 1:
    rate(19)
    proses()
