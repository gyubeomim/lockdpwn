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
turtle.shape("turtle")
t=turtle.Turtle()
u=turtle.Turtle()
turn_trigger=True

while True:
    if turn_trigger:
        if msvcrt.kbhit():
            c=msvcrt.getch().decode(encoding='UTF-8')
            if c=='j':
                t.left(30)
            if c=='k':
                t.right(30)
        t.forward(20)
        if(t.xcor()>=250 or t.xcor()<=-250 or t.ycor()>=250 or t.ycor()<=-250):
            t.left(180)
        turn_trigger=False
    else:    
        angle=random.random()
        if(angle>0.5):
            angle=(1-angle)*180
            u.right(angle)
        elif(0<angle<0.5):
            angle*=180
            u.left(angle)
        else:
            pass
        u.forward(20)

        if(u.xcor()>=250 or u.xcor()<=-250 or u.ycor()>=250 or u.ycor()<=-250):
            u.backward(50)
        turn_trigger=True

