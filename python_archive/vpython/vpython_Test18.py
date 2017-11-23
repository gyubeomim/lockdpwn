#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 반한정계의 2자유도 스프링질량계 애니메이션을 구현한 코드

                음.. 확실한건지 모르겠지만 운동방정식이 맞으니 ㅇ.ㅇ
'''
from visual import *
from math import *
 
#------------------------------------------------------------------
# 그래픽 그려주는 코드
#------------------------------------------------------------------
 
# 그래픽창을 생성합니다
scene.range = (15,12,12)
scene.center = (0,0,0)
scene.width = 800
scene.height = 300
 
# 2개의 물체를 생성합니다. 거리는 5m 간격으로 일정합니다
block1 = box(pos=(-2.5,0,0), size=(2,2,2), color=color.green, opacity=0.8)
block2 = box(pos=(2.5,0,0), size=(2,2,2), color=color.orange, opacity=0.8)
 
# 바닥과 기준면을 생성합니다
bottom_wall = box(pos=(0,-1.25,0), size=(30,0.5,7))
origin_wall = box(pos=(0,0,-4), size=(.2,5,1))
 
# 스프링을 생성합니다
spring = helix(pos=block1.pos, axis=7, radius=0.5, coils=8, thickness=0.1, color=color.gray(0.5))
 
x1 = 2.5  # 초기 위치
x2 = 0.

v1 = 3.  # 초기 속도
v2 = 0.
 
k = 20.  # 스프링강성
m1 = 1.   # 질량
m2 = 2.   
 
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
    a1 = k/m1 *(-x1 + x2)
    a2 = k/m2 *(x1 - x2)
 
    v1 += a1*dt
    v2 += a2*dt
 
    x1 += v1*dt
    x2 += v2*dt
 
    # 블락의 실시간 위치를 업데이트합니다
    block1.pos.x = x1 - 2.5
    block2.pos.x = x2 + 2.5
 
    # 스프링 또한 블락과 같이 위치를 업데이트합니다
    # pos : 스프링 좌측의 좌표
    spring.pos = block1.pos
    
    # axis : 스프링 우측의 좌표
    spring.axis = block2.pos.x - block1.pos.x
 
    label1.pos = bottom_wall.pos + vector(0,-0.5,0)
    label1.text = 'time : %.2f s' % t
    label2.pos = bottom_wall.pos + vector(0,-1.5,0)
    label2.text = 'mass1 : %.2f kg, mass2 : %.2f kg' % (m1,m2)
    label3.pos = bottom_wall.pos + vector(0,-2.5,0)
    label3.text = 'k : %.2f N/m' % k
 
 
