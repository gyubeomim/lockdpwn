#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 이용해 두 물체의 충돌을 애니메이션해 본 코드
                https://youtu.be/l5IiPG5_Xa0

'''
from visual import *

#------------------------------------------------------------------
# 그래픽 그려주는 코드
#------------------------------------------------------------------

ball_size = 0.05  # 공의 크기

# 그래픽창을 설정합니다
scene = display(width=600, height=600, x=0, y=0, background=(0.5,0.6,0.5))

# 공 2개를 생성합니다. 공의 궤적을 표시합니다
b1 = sphere(radius = ball_size, color=color.yellow, make_trail=True, trail_type="points", interval=100)
b2 = sphere(radius = ball_size, color=color.green, make_trail=True, trail_type="points", interval=100)

# 공의 질량은 1kg
b1.m = 1.0
b2.m = 1.0

# 공의 운동에너지를 표시하는 바를 생성합니다
rod_1 = cylinder(pos=(-0.1,-0.4,0), axis=(0.1,0,0), radius=0.03, opacity=0.7)
rod_2 = cylinder(pos=(-0.1,-0.5,0), axis=(0.1,0,0), radius=0.03, opacity=0.7)
rod_e = cylinder(pos=(-0.1,-0.6,0), axis=(0.1,0,0), radius=0.03, opacity=0.7)

# 텍스트를 표시하는 라벨 객체 생성합니다
label_1 = label(pos=(-0.2,-0.4,0), text='K1')
label_2 = label(pos=(-0.2,-0.5,0), text='K2')
label_e = label(pos=(-0.2,-0.6,0), text='E')


# 두 물체가 충돌하면 물체의 위치에 따라 속도를 반환하는 함수 (왜 이런 공식을 썻지?)
def vcollision(b1, b2):
    v1prime = b1.v - (2*b2.m)/(b1.m+b2.m)*(b1.pos-b2.pos) * dot(b1.v - b2.v, b1.pos-b2.pos) / abs(b1.pos - b2.pos)**2
    v2prime = b2.v - (2*b1.m)/(b1.m+b2.m)*(b2.pos-b1.pos) * dot(b2.v-b1.v, b2.pos-b1.pos)/abs(b2.pos - b1.pos)**2
    return v1prime, v2prime


# 공의 초기 위치와 초기 속도를 지정합니다
b1.pos = vector(0.35, 0.05, 0)
b2.pos = vector(0,0,0)
b1.v = vector(-0.2, 0,0)
b2.v = vector(0,0,0)

label1= label()
label2= label()
label3= label()
label4= label()
label5= label()

#------------------------------------------------------------------
# 애니메이션 코드
#------------------------------------------------------------------

dt= 0.001

while abs(b1.pos-b2.pos) < 2.0:
    rate(300)

    b1.pos += b1.v * dt
    b2.pos += b2.v * dt
    
    # 두 공이 충돌하면 두 공의 속도를 각각 계산합니다
    if abs(b1.pos - b2.pos) <= 2*ball_size and dot(b1.pos-b2.pos, b1.v-b2.v) <= 0:
            b1.v, b2.v = vcollision(b1, b2)

    # 두 공의 운동에너지를 표시합니다
    rod_1.axis.x = 0.5*b1.m*abs(b1.v)**2 * 5
    rod_2.axis.x = 0.5*b2.m*abs(b2.v)**2 * 5
    rod_e.axis.x = rod_1.axis.x + rod_2.axis.x

    label1.pos = rod_1.pos + vector(0.5, 0.15,0)
    label1.text = 'dot : %.2f' % (dot(b1.pos-b2.pos, b1.v-b2.v))

    label2.pos = rod_2.pos + vector(0.5, 0.15,0)
    label2.text = 'b1_pos : %.2f, %.2f, %.2f' % (b1.pos.x, b1.pos.y, b1.pos.z)

    label3.pos = rod_e.pos + vector(0.5, 0.15,0)
    label3.text = 'b2_pos : %.2f, %.2f, %.2f' % (b2.pos.x, b2.pos.y, b2.pos.z)

    label4.pos = rod_e.pos + vector(0.5, 0.075,0)
    label4.text = 'b1_v : %.2f, %.2f, %.2f' % (b1.v.x, b1.v.y, b1.v.z)

    label5.pos = rod_e.pos + vector(0.5, 0,0)
    label5.text = 'b2_v : %.2f, %.2f, %.2f' % (b2.v.x, b2.v.y, b2.v.z)
