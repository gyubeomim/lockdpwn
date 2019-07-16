#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 물체의 자유낙하 + 바닥에 탄성충돌 운동을 x,v,a 그래프로 애니메이션해 본 코드

                http://tcjd71.wixsite.com/vpython/blank-1
'''
from visual import *
from visual.graph import *

#------------------------------------------------------------------
# 그래픽 그려주는 코드
#------------------------------------------------------------------

# 그래픽창을 설정하는 코드
scene.range = (5,5,5)
scene.center = (0,1,0)
scene.width = 400
scene.height = 400

size = 0.2  # 공의 반지름 m
g = -9.81   # 중력가속도

# 공을 생성하고 초기 위치를 3m로 설정합니다
ball = sphere(radius=size, color=color.white)
ball.pos = (0,3,0)
ball.v = vector(0,0,0)

# 바닥면을 생성합니다
bottom = box(pos=(0,-1+size,0), length=3, heigth=0.1, width=3, material=materials.wood)

# x-t,v-t,a-t 그래프창을 생성합니다 
gd = gdisplay(width=500, height=300, x=410, y=0, title='y vs t', xtitle='t', ytitle='x', ymax=3, ymin=-3, xmax=10)
gd2 = gdisplay(width=500, height=300, x=410, y=250, title='v vs t', xtitle='t', ytitle='vel', ymax=20, ymin=-20, xmax=10)
gd3 = gdisplay(width=500, height=300, x=410, y=400, title='a vs t', xtitle='t', ytitle='acc', ymax=10, ymin=-10, xmax=10)

# 그래프창에 그려질 그래프 곡선들을 설정합니다
xt = gcurve(gdisplay=gd, color=color.cyan)
vt = gcurve(gdisplay=gd2, color=color.cyan)
at = gcurve(gdisplay=gd3, color=color.cyan)

# 속도 화살표 객체를 생성합니다
vel_arrow = arrow(pos=ball.pos, axis=ball.v, color=color.yellow)



#------------------------------------------------------------------
# 애니메이션 코드
#------------------------------------------------------------------

t = 0
dt = 0.0004   

label1 = label()
label2 = label()

while True:
    rate(2500)  # rate * dt = 1이 되게 설정하면 실제 시간과 같은 루프주기를 얻을 수 있습니다
    t += dt

    # 공이 땅에 닿으면 (y == 0) 공의 속도를 반대로 바꿉니다. 완전탄성충돌
    if ball.pos.y <= 0:
        ball.v.y = abs(ball.v.y)

    # 공의 위치,속도,가속도를 그래프화합니다
    xt.plot(pos=(t, ball.pos.y))
    vt.plot(pos=(t,ball.v.y))
    at.plot(pos=(t,g))

    # 공의 위치와 속도를 업데이트합니다
    ball.pos += ball.v*dt
    ball.v.y += g*dt

    # 속도화살표를 업데이트합니다. 0.3을 곱해서 화살표의 크기를 줄입니다
    vel_arrow.pos = ball.pos
    vel_arrow.axis = ball.v*0.3
    
    # 텍스트 데이터
    label1.pos = bottom.pos + vector(0, -0.5,0)
    label1.text = 'time : %.2f s' % t
    label2.pos = bottom.pos + vector(0, -1.2,0)
    label2.text = 'vel : %.2f m/s' % ball.v.y
