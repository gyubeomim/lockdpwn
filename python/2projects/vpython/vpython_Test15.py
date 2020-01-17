#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 단진자의 운동을 애니메이션해 본 코드
'''
from visual import *
from math import *

#------------------------------------------------------------------
# 그래픽 그려주는 코드
#------------------------------------------------------------------

# 그래픽창을 설정하는 코드
scene.range = (3.5,3.5,3.5)
scene.center = (0,-1,0)
scene.width = 400
scene.height = 700

# 단진자와 이를 받쳐주는 바닥과 봉, 단진자의 실을 생성합니다
ball = sphere(pos=(0,0,0), radius=0.15, color=color.blue, opacity=0.8)
base = box(pos=(0,-2.5,-1), size=(2,0.1,2))
wall = box(pos=(0,-1,-1), size=(0.1,3,0.1))
bar = cylinder(pos=(0,0,-1), radius=0.05, axis=(0,0,1), color=color.yellow)
line = curve(pos=[(bar.pos),(ball.pos)], color=color.gray(0.5))

# 속도를 가시화하기 위한 화살표객체를 생성합니다
velArrow = arrow(pos=ball.pos, axis=(0,0,0) , color=color.yellow)
velFlag = 1

pi = 3.14159  # pi 값
r = 2.        # 실의 길이 m
theta0 = 60   # 초기각도 (deg)
theta = (180 - theta0)*pi / 180  # 초기각도 (rad)
g = 9.81                        # 중력가속도

omega = 0   # 각속도
alpha = 0   # 각가속도
a = 0       # 가속도
v = 0       # 속도
v_max = sqrt(2*g*r*(-cos(theta)))   # 초기각도에서의 속도의 최대값을 운동에너지 = 위치에너지로 구합니다


#------------------------------------------------------------------
# 애니메이션 코드
#------------------------------------------------------------------

t = 0
dt = 0.01
deg_theta = 0

# 텍스트를 위한 라벨 객체를 생성합니다
label1 = label()
label2 = label()
label3 = label()

while True:
    rate(100)
    t += dt

    # 운동방정식으로 각가속도를 계산하고 이를 적분해 각속도,각도를 얻습니다
    alpha = (g*sin(theta))/r
    omega += alpha*dt
    theta += omega*dt

    # 각도를 deg단위로 변환합니다
    deg_theta = 180 - theta*180./pi


    # x축 방향의 속도를 계산합니다 
    # 실제속도 = 속도의 최대값 - 현재각도에서 속도값(위치에너지에 따른)
    # pi - theta인 이유는 0도가 y축의 양의 방향이고 이 방향이 수직 윗방향이기 때문에 pi를 빼준겁니다. (자세한건 직접해보세요~)
    v = v_max - sqrt(2*g*r*(1-cos(pi - theta)))


    # 줄의 위치와 공의 위치를 업데이트합니다
    line.pos = [(bar.pos)+(0,0,1), (ball.pos)] 
    ball.pos = (r*sin(theta), r*cos(theta), 0)

    # 속도화살표를 업데이트합니다. 각도에 따라 방향이 바뀌어야되므로 조건문을 추가합니다. 또한 속도값이 너무 크므로 0.3배로 화살표를 작게만들어줍니다
    velArrow.pos = ball.pos
    if velFlag == 0:
        velArrow.axis = (v*0.3,0,0)    
    else:
        velArrow.axis = (-v*0.3,0,0)
    
    # 속도화살표의 방향을 바꾸기 위한 조건문
    if deg_theta >= theta0 - 0.01:
            velFlag = 1
    elif deg_theta <= -theta0 + 0.01:
            velFlag = 0

    # 텍스트 데이터
    label1.pos = base.pos + vector(0,-0.5,0)
    label1.text = 'theta : %.2f deg' % (deg_theta)
    label2.pos = base.pos + vector(0,-0.1,0)
    label2.text = 'time : %.2f s' % (t)
    label3.pos = base.pos + vector(0,-0.9,0)
    label3.text = 'vel_x : %.2f m/s' % (v)
