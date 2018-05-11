#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> vpython을 사용해 Spring, Mass System의 운동을 그래픽으로 표현한 코드

                code from https://www.youtube.com/watch?v=9n8XCwCmBho
'''
from __future__ import division, print_function
from visual import *

Lo = 4
Lvec = vector(0,3,0)
Lhat = vector(0,1,0)

Ks = 10
Pi = vector(0,0,0)
Blockm = 1.5  # mass

g = vector(0, -9.8, 0)

t = 0
dt = 0.01

spring = helix(pos=(0,0,0), axis=(0,3,0), radius=.5)
block = box(pos= (0,3,0), size = (1.2,1,1.2), color=color.blue, opacity=0.8)
track = box(pos=(0,-0.5,0), size=(4,1,1))

label1 =label()
label2 =label()

while t < 30:
    rate(100)  # frequency, Hz
    t += dt

    F_earth = Blockm * g   # Force_gravity = m * g
    Lmag = abs(Lvec.y)
    F_s = (-Ks) * (Lmag - Lo) * Lhat
    F_net = F_s + F_earth

    Pf = Pi + (F_net * dt)
    Pi = Pf

    Vavg = Pf / Blockm
    Xf = Lvec + Vavg * dt
    Lvec = Xf

    spring.axis = Xf
    block.pos = Xf

    label1.pos = track.pos + vector(0,0.2,0)
    label1.text = 'm is : %.2f kg' % Blockm
    label2.pos = track.pos + vector(0,-0.3,0)
    label2.text = 'k is : %.2f N/m' % Ks
