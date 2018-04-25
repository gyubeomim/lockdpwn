#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> sympy 시작할 때 변수 선언을 해주는 코드
'''
from __future__ import division
from sympy import *
from sympy import solve

x, y, z, w = symbols('x y z w')
k, m, n = symbols('k m n', integer=True)
f, g, h = symbols('f g h', cls=Function)
a,b,c,d = symbols('a b c d')
init_printing()
