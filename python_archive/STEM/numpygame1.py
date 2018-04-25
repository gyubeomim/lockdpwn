#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
   python ==> numpy, pygame으로 진자운동을 표현한 예제코드 (RK 4차법 사용) 
'''
import pygame
from pygame.locals import *
import numpy as np

h = 0.05
t = v = 0
x = 30*np.pi/180
pen_fm = 0.01
pen_m = 0.1
pen_l = 100*0.01
pen_J = 0.02
pen_g = 9.8
gndCenterX = 150
gndConterY = 20
penLength = pen_l*100*2

def calcODEFunc(tVal, xVal, vVal):
    return -pen_fm / (pen_m*pen_l*pen_l+pen_J) * vVal-pen_m * pen_g * pen_l / (pen_m * pen_l * pen_l+pen_J) * xVal

# 상미분방정식 ==> 초기값이 주어진 경우 사용하는 수치해석방법
# Runge-Kutta, RK 4차법을 활용한 코드인듯
def solveODEusingRK4(t, x, v):
    kx1 = v
    kv1 = calcODEFunc( t, x, v )

    kx2 = v + h*kv1/2
    kv2 = calcODEFunc( t + h/2, x + h*kx1/2, v + h*kv1/2 )

    kx3 = v + h*kv2/2
    kv3 = calcODEFunc( t + h/2, x + h*kx2/2, v + h*kv2/2 )

    kx4 = v + h*kv3
    kv4 = calcODEFunc(t + h, x + h * kx3, v + h * kv3 )

    dx = h*(kx1 + 2*kx2 + 2*kx3 + kx4)/6
    dv = h*(kv1 + 2*kv2 + 2*kv3 + kv4)/6
    return x+dx, v+dv


pygame.init()
srf = pygame.display.set_mode((300,300))
font = pygame.font.SysFont('Vernada.ttf', 25)
aurthorSrf = font.render('by PinkWink', True, (50,50,50))
loopFlag = True

while loopFlag:
    for event in pygame.event.get(QUIT):
        loopFlag = False

    srf.fill((255,255,255))

    t = t + h
    [x, v] = solveODEusingRK4(t,x,v)

    updatedX = gndCenterX + penLength*np.sin(x)
    updatedY = gndConterY + penLength*np.cos(x)
    
    print updatedX, "   " ,updatedY 
    pygame.draw.line(srf, (100,100,100), (gndCenterX, gndConterY), (updatedX, updatedY), 2)
    pygame.draw.circle(srf, (100,100,100), (int(updatedX), int(updatedY)), 10, 0)

    pygame.draw.line(srf, (0,0,0), (10,20), (290,20), 10)
    srf.blit(aurthorSrf, (180,270))

    pygame.time.delay(40)
    pygame.display.flip()
