#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> sympy, 4x4 행렬의 역행렬을 구하는 예제코드
'''
from sympy import *
from sympy.abc import a,b,c,d,e,f,g

# Z = Matrix(4,4,[a,e,0,0,e,b,f,0,0,f,c,g,0,0,g,d])
Z = Matrix(4,4,[1,2,0,0,3,4,6,0,0,7,8,9,0,0,1,2])
D = Z.det()
Zi = Z.inv()
DZi = simplify(D*Zi)
init_printing()
DZi
