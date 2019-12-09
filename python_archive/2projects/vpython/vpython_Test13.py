#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 3자유도계 스프링-질량 시스템 운동을 애니메이션해 본 코드

             code from https://youtu.be/oMBohUQz3NI
'''
from visual import *
from math import *

#------------------------------------------------------------------
# 그래픽 그려주는 코드
#------------------------------------------------------------------

# 그래픽창을 생성합니다
scene.range = (16,12,12)
scene.center = (0,0,0)
scene.width = 800
scene.height = 300

# 3개의 물체를 생성합니다. 거리는 5m 간격으로 일정합니다
block1 =box(pos=(-5,0,0), size=(2,2,2), color=color.blue, opacity=0.7)
block2 = box(pos=(0,0,0), size=(2,2,2), color=color.blue, opacity=0.7)
block3 = box(pos=(5,0,0), size=(2,2,2), color=color.blue, opacity=0.7)

# 바닥 생성
bottom = box(pos=(0,-1.25,0), size=(20.5,0.5,7))

# 벽 생성
wall1 = box(pos=(-10,1,0), size=(0.5,4,7))
wall2 = box(pos=(10,1,0), size=(0.5,4,7))

# 스프링 생성
spring1 = helix(pos=(-10,0,0), axis=7, radius=0.5, coils=8, thickness=0.1, color=color.gray(0.5))
spring2 = helix(pos=block1.pos, axis=7, radius=0.5, coils=8, thickness=0.1, color=color.gray(0.5))
spring3 = helix(pos=block2.pos, axis=7, radius=0.5, coils=8, thickness=0.1, color=color.gray(0.5))
spring4 = helix(pos=block3.pos, axis=7, radius=0.5, coils=8, thickness=0.1, color=color.gray(0.5))

x1 = 3.  # 초기 위치
x2 = 0.
x3 = 0.

k = 10.  # 강성
m = .5   # 질량

v1 = 0.  # 초기속도
v2 = 0.
v3 = 0.

#------------------------------------------------------------------
# 애니메이션 코드
#------------------------------------------------------------------
t = 0
dt = 0.01 
label1 = label()
label2 = label()
label3 = label()

while True:
    rate(100) # 100 Hz, 초당 100번씩 루프를 돌고 dt=0.01이므로 시간 t는 실제 시간과 일치합니다
    t += dt
    
    # 운동방정식을 통해 a1,a2,a3를 구하고 v,x로 적분합니다
    a1 = k/m*(x2 - 2*x1)
    a2 = k/m*(x3 - 2*x2 + x1)
    a3 = k/m*(-2*x3 + x2)

    v1 += a1*dt
    v2 += a2*dt
    v3 += a3*dt

    x1 += v1*dt
    x2 += v2*dt
    x3 += v3*dt

    # 블락의 실시간 위치를 갱신합니다
    block1.pos.x = x1-5
    block2.pos.x = x2
    block3.pos.x = x3+5

    # 스프링 또한 블락과 같이 이동합니다
    # pos : 스프링 좌측의 좌표
    spring2.pos = block1.pos
    spring3.pos = block2.pos
    spring4.pos = block3.pos

    # axis : 스프링 우측의 좌표
    spring1.axis = block1.pos.x - wall1.pos.x
    spring2.axis = block2.pos.x - block1.pos.x
    spring3.axis = block3.pos.x - block2.pos.x
    spring4.axis = wall2.pos.x - block3.pos.x

    label1.pos = wall2.pos + vector(0.1,-3,0)
    label1.text = 'time : %.2f s' % t
    label2.pos = wall2.pos + vector(0.1,-4.3,0)
    label2.text = 'mass : %.1f kg' % m
    label3.pos = wall2.pos + vector(0.1,-5.6,0)
    label3.text = 'k : %.2f N/m' % k
