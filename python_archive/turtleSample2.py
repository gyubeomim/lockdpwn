#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 객체수업시간에 바탕화면에 있는 코드 가져옴 turtle이라는 패키지 사용한다
'''
import turtle
import msvcrt
import time
import random

turtle.setup(500,500,0,0)
t=turtle.Turtle()

while True:
    angle=random.random()
    if(angle>0.5):
        angle=(1-angle)*180
        t.right(angle)
    elif(0<angle<0.5):
        angle*=180
        t.left(angle)
    else:
        pass
    t.forward(20)

    if(t.xcor()>=250 or t.xcor()<=-250 or t.ycor()>=250 or t.ycor()<=-250):
        t.backward(50)
