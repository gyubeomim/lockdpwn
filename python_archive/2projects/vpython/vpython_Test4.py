#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython에서 2 mass-spring System의 운동을 애니메이션 해 본 코드
                https://youtu.be/H8CzQtx9vds

'''
from visual import *
from math import *

#------------------------------------------------------------------
# 그래픽 그려주는 코드
#------------------------------------------------------------------

# 그래픽창을 생성합니다
scene.range = (15,10,10)
scene.center = (0,0,0)
scene.width = 800
scene.height = 300

# 2개의 물체를 생성합니다. 거리는 5m 간격으로 일정합니다
block1 = box(pos=(-2.5,0,0), size=(2,2,2), color=color.red, opacity=0.8)
block2 = box(pos=(2.5,0,0), size=(2,2,2), color=color.red, opacity=0.8)

# 바닥을 생성합니다
bottom_wall = box(pos=(0,-1.25,0), size=(15.5,0.5,7))

# 벽을 생성합니다. 두 벽의 거리는 15m
wall1 = box(pos=(-7.5,1,0), size=(.5,4,7))
wall2 = box(pos=(7.5,1,0), size=(.5,4,7))

# 스프링을 생성합니다
spring1 = helix(pos=(-7.5,0,0), axis=7, radius=0.5, coils=8, thickness=0.1, color=color.gray(0.5))
spring2 = helix(pos=block1.pos, axis=7, radius=0.5, coils=8, thickness=0.1, color=color.gray(0.5))
spring3 = helix(pos=block2.pos, axis=7, radius=0.5, coils=8, thickness=0.1, color=color.gray(0.5))

x1 = -2  # 초기 위치
x2 = 0.
v1 = 0.  # 초기 속도
v2 = 0.

k = 20.  # 스프링강성
m = 2.   # 질량

#------------------------------------------------------------------
# 애니메이션 코드
#------------------------------------------------------------------
t = 0
dt = 0.01

# 텍스트를 표시할 라벨객체를 생성합니다
label1 = label()
label2 = label()
label3 = label()

while True:
    rate(100) # 100 Hz, 초당 100번씩 루프를 돌고 dt=0.01이므로 시간 t는 실제 시간과 일치합니다
    t += dt

    # 운동방정식을 통해 a1,a2,a3를 구하고 v,x로 적분합니다
    a1 = k/m *(x2 - 2*x1)
    a2 = k/m *(-2*x2 + x1)

    v1 += a1*dt
    v2 += a2*dt

    x1 += v1*dt
    x2 += v2*dt

    # 블락의 실시간 위치를 업데이트합니다
    block1.pos.x = x1 - 2.5
    block2.pos.x = x2 + 2.5

    # 스프링 또한 블락과 같이 위치를 업데이트합니다
    # pos : 스프링 좌측의 좌표
    spring2.pos = block1.pos
    spring3.pos = block2.pos
    
    # axis : 스프링 우측의 좌표
    spring1.axis = block1.pos.x - wall1.pos.x
    spring2.axis = block2.pos.x - block1.pos.x
    spring3.axis = wall2.pos.x - block2.pos.x

    label1.pos = bottom_wall.pos + vector(0,-0.5,0)
    label1.text = 'time : %.2f s' % t
    label2.pos = bottom_wall.pos + vector(0,-1.5,0)
    label2.text = 'mass : %.2f kg' % m
    label3.pos = bottom_wall.pos + vector(0,-2.5,0)
    label3.text = 'k : %.2f N/m' % k
