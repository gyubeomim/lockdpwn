#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> sympy를 이용해 연립방정식을 푸는 예제 코드
'''
from sympy import Matrix, solve_linear_system
from sympy.abc import x,y

# solve the following system
# x + 4y = 2
# -2x + y = 14
system = Matrix(( (1,4,2) , (-2 ,1 ,14)))
print solve_linear_system(system,x,y)
