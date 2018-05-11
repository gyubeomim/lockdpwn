#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 진자의 원운동을 그래프를 통해 애니메이션한 코드

                http://tcjd71.wixsite.com/vpython/blank-1
'''
from visual import *
from visual.graph import *

#------------------------------------------------------------------
# 그래픽 그려주는 코드
#------------------------------------------------------------------

# 그래픽창과 그래프창을 생성합니다
scene = display(width=600, height=600, fov = 0.01*pi)
gd = gdisplay(x=600, y=0, title='x-t', xtitle='t', ytitle='x', ymax=1, ymin=-1, xmax=10, background=(.3,.3,.3))
xt = gcurve(gdisplay=gd, color=color.orange, size=20, dot=False)

# 벽과 공을 생성합니다
wall = box(pos=(0,1,-2), length=4, height=3, width=0.01)
ball = sphere(pos=(-1,0,0), radius=0.1, make_trail=True)


# 공의 각속도는 3 rad/s로 일정합니다 (불명확합니다. 아래 루프코드를 보세요~)
ball.w = 3


# 공의 움직임을 똑같이 따라가는 그림자를 벽에 생성합니다
shadow = cylinder(axis=(0,0,wall.width), radius=ball.radius, color=(0.1,0.1,0.1))
shadow.pos.z = wall.pos.z


# 텍스트를 표시하는 라벨 객체를 생성합니다
label1 = label()
label2 = label()


# 바닥면의 실린더를 생성합니다
disk = cylinder(axis=(0,0.01,0), radius=1.5, material=materials.silver)
disk.pos.y = -ball.radius


# 공의 궤적을 벽에 표현하기 위한 line 객체를 생성합니다
number = 4000
l = [0]*number
m = [0]*number
line = curve(y=linspace(0,2.5,number), z=-2+0.01, color=color.black)

#------------------------------------------------------------------
# 애니메이션 코드
#------------------------------------------------------------------

label3 = label()
t = 0
dt = 0.01

while True:
    rate(100)   # dt와 rate[Hz]를 사용해 루프시간을 느리게합니다 
    t += dt
    
    # rotate(A,theta,B) ==> rotate(vector=A, angle=theta, axis=B)
    # y축을 기준으로 물체가 회전합니다. 실제 각속도는 ball.w * dt = 0.003 rad/s 입니다
    # 이 부분 코드가 불명확합니다. 0.003 rad/s는 너무 작은 값이기 때문에 :-0..
    # 참고 사이트는 여기 있습니다 http://vpython.org/contents/docs/rotation.html
    ball.pos = rotate(ball.pos, ball.w * dt, (0,1,0))
    shadow.pos.x = ball.pos.x
    
    # 공의 궤적을 그래프창에 표시합니다
    xt.plot(pos=(t,ball.pos.x))

    # 공의 위치를 텍스트로 표시합니다
    label1.pos = ball.pos + vector(0,0.2,0)
    label1.text = '(%1.2f, %1.2f, %1.2f)' % (ball.pos.x, ball.pos.y,ball.pos.z)
    label2.pos = shadow.pos + vector(0,0.2,0)
    label2.text = '(%1.2f)' % (shadow.pos.x)

    label3.pos = wall.pos + vector(0, -0.1 , 0)
    label3.text = 'time : %.2f s' % t

    # 공의 움직임을 궤적으로 벽에 표시하는 코드
    l.append(ball.pos.x)
    l.pop(0)

    for j in range(number):
        m[number-1-j] = l[j]

    line.x = array(m)



