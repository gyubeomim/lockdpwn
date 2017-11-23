#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 스프링 + 질량 + 진자의 운동을 애니메이션한 코드
                https://youtu.be/H8CzQtx9vds
'''
from visual import *
from math import *

scene.range = (8,17,10)
scene.center = (3,-2,0)
scene.width = 800
scene.height = 500
scene.background = (.5,.5,.5)

mass = box(pos=(0,0,0), size=(1,1,1), color=(0,1.0,0), opacity=0.8)
ball = sphere(pos=(0,0,0), radius=.5, color=(1.0,0,0), opacity=0.8)

wall = box(pos=(-3,0,0), size = (1,4,4))
bar = cylinder(pos = (-3,0,0), axis=(12,0,0), radius = 0.1)
spring = helix(pos=(-3,0,0), axis=(7,0,0), radius=.3, coils=15, thickness=0.07, color=color.gray(0.5))
line = curve(pos=[(mass.pos), (ball.pos)], color=color.gray(0.5), radius=.03)

L0 = 3
L = 5.
theta0 = 10.
k = 100.
m1 = 1
m2 = .1
theta = (180-theta0)*pi / 180
g = -9.81
omega= 0.
v = 0.
a = 0.
alpha = 0.
x = 3.3

t = 0.
dt = 0.01

while True:
    rate(60)
    a = (m2*L*sin(theta)*omega**2 - m2*g*L*sin(theta)*cos(theta) - k*(x-L0)) / (m1 + m2 + m2*L*(cos(theta))**2)

    alpha = -g*sin(theta) + a*cos(theta)
    v += a*dt
    x += v*dt
    omega += alpha*dt
    theta += omega*dt

    mass.pos = (x,0,0)
    ball.pos = (x+L*sin(theta), L*cos(theta), 0)
    spring.axis = mass.pos - wall.pos
    line.pos = [(mass.pos), (ball.pos)]


