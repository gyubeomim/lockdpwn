#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 활용해 N극과 S극 사이에 놓인 전류의 흐름을 보여주는 애니메이션으로 코드 

                http://tcjd71.wixsite.com/vpython/blank-1
'''
from visual import *

a = 4.
b = 6.
B = vector(0,-1,0)
m = 1.
I = 1.
dt = 0.001
w = 0
theta = 0
d = 0.01

scene = display(width=600, height=600, background=(0.5,0.6,0.5))

N = box(pos=(0,3,0), length=4, height=0.2, width=4, color=color.red)
S = box(pos=(0,-3,0), length=4, height=0.2, width=4, color=color.blue)
re_coil = curve(A=vector(1,0,0), radius=0.02, color=(0.5,0.5,0.5))

v_re_coil_A = arrow(shaftwidth=0.05)
l_re_coil_A = label(text='A')

v_B = arrow(axis=B, shaftwidth=0.05, color=color.black)
l_B = label(pos=1.2*v_B.axis, text='B')

v_I1 = arrow(shaftwidth=0.05, color=color.orange)
v_I2 = arrow(shaftwidth=0.05, color=color.orange)
l_I1= label(text='I')
l_I2= label(text='I')

v_F1 = arrow(shaftwidth=0.05, color=(0,0.5,0))
v_F2 = arrow(shaftwidth=0.05, color=(0,0.5,0))
l_F1= label(text='F')
l_F2= label(text='F')

position = [vector(0, a/2, b/2), vector(0,a/2,-b/2),
        vector(0,-a/2,-b/2), vector(0,-a/2,b/2), vector(0,-a/2,b/2)]

inertia = 2*(a*m / (2*a + 2*b)) *a **2/12 + 2*(b*m / (2*a+2*b))*(a/2)**2

while True:
    rate(100)
    tau = I*cross(a*b*re_coil.A, B)

    alpha = (dot(tau/inertia, (0,0,1)) - dot(tau/inertia, (0,0,1))*w**2*d)
    
    # the second term is similar to friction
    w += alpha*dt
    theta += w*dt

    for i in [0,1,4]:
        position[i].x = -(a/2)*sin(theta)
        position[i].y = (a/2)*cos(theta)

    for i in [2,3]:
        position[i].x = (a/2)*sin(theta)
        position[i].y = -(a/2)*cos(theta)

    if dot(cross(re_coil.A, B), (0,0,1)) < 0:
        I = 1.
        v_I1.axis = (0,0,1)
        v_I2.axis = (0,0,-1)

    if dot(cross(re_coil.A, B), (0,0,1)) > 0:
        I = -1.
        v_I1.axis = (0,0,-1)
        v_I2.axis = (0,0,1)

    re_coil.pos = position
    re_coil.A = vector(cos(theta) , sin(theta) , 0)

    v_re_coil_A.axis = re_coil.A
    l_re_coil_A.pos = 1.2*v_re_coil_A.axis

    v_I1.pos = (position[0]+position[1])/2 - 0.5*v_I1.axis
    v_I2.pos = (position[2]+position[3])/2 + 0.5*v_I1.axis
    v_F1.pos = (position[0]+position[1])/2
    v_F2.pos = (position[2]+position[3])/2
    v_F1.axis = cross(v_I1.axis, B)
    v_F2.axis = cross(v_I2.axis, B)
    l_F1.pos = v_F1.pos + 1.2*v_F1.axis
    l_F2.pos = v_F2.pos + 1.2*v_F2.axis
    l_I1.pos = v_I1.pos + 1.2*v_I1.axis
    l_I2.pos = v_I2.pos + 1.2*v_I2.axis


