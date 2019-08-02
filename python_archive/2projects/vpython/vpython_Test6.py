#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 구슬이 자유낙하하는 궤적 + 속도를 애니메이션한 코드
                https://youtu.be/H8CzQtx9vds
'''
from visual import *
from math import *

#-----------------------------------------------------------------
# 그래픽 그려주는 코드
#------------------------------------------------------------------

# 공과 바닥을 생성합니다. 공의 위치는 지면으로부터 18 + 9 = 27m 위에 있습니다. (vpython은 y축이 위아래방향입니다)
ball = sphere(pos=(-5,18,0), radius=1, color=color.green)
bottom = box(pos=(0,-9,0), size=(25,0.5,25))

# 초기속도는 x방향으로 0.7 m/s
v = vector(0.7, 0,0)
y = ball.pos
g = vector(0, -9.81, 0)

# 공의 궤적을 그래픽화하고 속도의 크기를 화살표로 그래픽화합니다
ball.trail = curve(color=ball.color)
arrow = arrow(pos=ball.pos, axis=v, color=color.yellow)

label1 = label()

#------------------------------------------------------------------
# 애니메이션 코드 
#------------------------------------------------------------------

dt = 0.005
t = 0.0

while True:
    rate(300)  # 300 Hz의 속도로 루프를 실행합니다

    # 공식을 사용해 속도와 위치를 계산합니다
    v += g*dt   
    y += v*dt + 0.5*g*dt**2

    # 바닥에 닿는 순간 속도의 크기는 그대로하고 방향을 바꿉니다
    # 완전탄성충돌 
    if ball.pos.y < (bottom.pos.y + 1):
        v.y = -v.y

    # 공의 위치와 궤적을 업데이트합니다
    ball.pos = y
    ball.trail.append(pos = ball.pos)

    # 속도 화살표를 설정합니다
    arrow.pos = ball.pos
    arrow.axis = v*0.3

    label1.pos = bottom.pos + vector(0,-0.5,0)
    label1.text = 'v is : %.2f m/s'  % v.y
