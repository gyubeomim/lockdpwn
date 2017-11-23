#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 스프링 + 질량 시스템을 마찰력을 고려해서 애니메이션한 코드 (T+U = E 전부 그래픽으로 표현했다)

                    https://youtu.be/UoN70GjnBTI
'''
from visual import *

#------------------------------------------------------------------
# 그래픽 그려주는 코드
#------------------------------------------------------------------
m = 0.5         # 질량
k = 20.0        # 강성
v0 = 4.0        # 초기속도

# 마찰력을 고려할 때 사용하는 코드 (현재 사용 안함)
#mu_k = 0.1
#mu_s = 0.5
#g = 9.81

# 그래픽창을 생성하고 벽을 생성합니다
scene = display(width=600, height=600, background=(0.5,0.6,0.5))
bottom = box(length=3, height=0.01, width=1, material=materials.silver)
wall = box(length=0.01, height=0.5, width=1, material=materials.silver)


# 물체와 스프링을 생성합니다. 물체의 초기 위치는 0.2m입니다
square = box(length=0.2, height=0.2, width=0.2, material=materials.wood)
spring = helix(pos=(-bottom.length/2, 0,0), coils=15, radius=0.08,  thickness=0.02)


# 바닥과 벽의 위치를 정해주고 초기속도 v0를 입력합니다
bottom.pos = (0, -square.height/2, 0)
wall.pos = (-bottom.length/2, 0.5/2-square.height/2, 0)
square.vx = v0


# 운동에너지, 탄성에너지, 역학적에너지를 표현하는 바를 생성합니다
rod_k = cylinder(pos=(-bottom.length/2, -0.5,0), axis=(0.1,0,0), radius=0.05, opacity=0.5)
rod_u = cylinder(pos=(-bottom.length/2, -0.7,0), axis=(0.1,0,0), radius=0.05, opacity=0.5)
rod_e = cylinder(pos=(-bottom.length/2, -0.9,0), axis=(0.1,0,0), radius=0.05, opacity=0.5)


# 텍스트 표시용 라벨 객체 생성
label_k = label(pos=(-bottom.length/2-0.1, -0.5, 0), text='K')
label_u = label(pos=(-bottom.length/2-0.1, -0.7, 0), text='U')
label_e = label(pos=(-bottom.length/2-0.1, -0.9, 0), text='E')
label1 = label()
label2 = label()
label3 = label()

#------------------------------------------------------------------
# 애니메이션 코드 
#------------------------------------------------------------------

dt = 0.0001

while True:
    rate(2000)  # 2000 hz의 속도로 루프를 돕니다 (dt가 매우 작으므로 실제로는 조금 더 느리게 루프가 돕니다)

    # 운동방정식을 통해 가속도를 구하고
    square.a = -(k/m) * square.pos.x

# 마찰력을 고려할 때 아래의 코드를 주석해제하면 됩니다
#   if square.vx * (square.vx + square.a*dt) > 0:
#       square.a = (-k/m)*square.pos.x - mu_k*g*abs(square.vx)/square.vx
#   elif abs(k*square.pos.x) > mu_s*m*g:
#       square.a = -(k/m)*square.pos.x
#   else:
#       square.a = 0

    # 속도와 위치도 구합니다
    square.vx += square.a*dt
    square.pos.x += square.vx*dt

    # 스프링의 길이를 계산합니다
    spring.length = (square.pos.x - square.length/2) - spring.pos.x

    # 운동에너지, 탄성에너지, 역학적에너지를 표시합니다
    rod_k.axis.x = 0.5*m*square.vx**2/5    # 왜 5로 나누지? 스케일을 줄이기 위해!
    rod_u.axis.x = 0.5*k*square.pos.x**2/5
    rod_e.axis.x = rod_k.axis.x + rod_u.axis.x

    label1.pos = bottom.pos + vector(0,-0.1,0)
    label1.text = 'box position is : %.2f' % square.pos.x
    label2.pos = bottom.pos + vector(0,-0.3,0)
    label2.text = 'box length is : %.2f ' % square.length
    label3.pos = bottom.pos + vector(1.2,-0.1,0)
    label3.text = 'm : %.2f kg, k : %.2f N/m' % (m,k)
