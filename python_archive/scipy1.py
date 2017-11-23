#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> scipy.optimize를 이용해 미분방정식을 푸는 예제 코드
               xy^2 - 4 = 0
               xy + e^x -3 =0
               두 미분방정식의 해를 구한다
'''
from scipy.optimize import fsolve
import math

def equation(p):
    x,y = p
    return (x*y**2-4, math.exp(x) + x*y -3)

x,y = fsolve(equation, (1,1))
print equation((x,y))
