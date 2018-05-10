#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==>  자동차융합실험1, 재료의 인장시험을 파이썬으로 분석한 코드
'''
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# 처음시편
data1 = np.genfromtxt('autodata1.csv', dtype=float, delimiter=',', names=True)
Stress1 = data1['StressMPa']
Strain1 = data1['Strain'] / 100.

# 나중시편
data2 = np.genfromtxt('autodata2.csv', dtype=float, delimiter=',', names=True)
Stress2 = data2['StressMPa']
Strain2 = data2['Strain'] / 100.


# PLOTTING SETTINGS===================================
plt.rc('font', size=20)          # controls default text sizes
plt.rc('axes', titlesize=20)     # fontsize of the axes title
plt.rc('axes', labelsize=20)    # fontsize of the x and y labels
plt.rc('xtick', labelsize=12)    # fontsize of the tick labels
plt.rc('ytick', labelsize=12)    # fontsize of the tick labels
plt.rc('legend', fontsize=16)    # legend fontsize
plt.rc('figure', titlesize=25)  # fontsize of the figure title


# PLOTTING CODE of 처음시편============================
plt.title("Stress-Strain First Graph")
plt.xlabel("Strain [mm/mm]")
plt.ylabel("Stress [MPa]")
plt.xlim([0, 0.35])
plt.plot(Strain1, Stress1, 'b')
plt.grid(True)
plt.show()


# PLOTTING CODE of 나중시편============================
plt.title("Stress-Strain Second Graph")
plt.xlabel("Strain [mm/mm]")
plt.ylabel("Stress [MPa]")
plt.xlim([0, 0.35])
plt.plot(Strain2, Stress2, 'r')
plt.grid(True)
plt.show()


# PLOTTING CODE of 처음시편 + 나중시편=================
plt.title("Stress-Strain First + Second Graph")
plt.xlabel("Strain [mm/mm]")
plt.ylabel("Stress [MPa]")
f1, = plt.plot(Strain1, Stress1, 'b', label="first")
f2, = plt.plot(Strain2, Stress2, 'r', label="second")
plt.legend(handles=[f1,f2])
plt.grid(True)
plt.show()




Stress1.max()  # 최대인장강도
Stress1[-1]    # 파단강도

def frange(x, y, jump):
  while x < y:
    yield x
    x += jump

# 0.2% 오프셋방법으로 항복강도 찾기===================
Stress1[0:200].max() 
# Out[]: 353.0

for i in range(0,200):
    if Stress1[i] == 353.0:
        print(i)
        break
# Out[]: 166


m = Stress[166] / Strain[166]
# Out[]: 153.86

p_x = []
p_y = []
for i in frange(0, 0.03, 0.001):
    p_x.append(i + 0.002)   # offset 0.2%
    p_y.append(100*m* (i))

plt.title("0.2% Offset Graph")
plt.xlabel("Strain [mm/mm]")
plt.ylabel("Stress [MPa]")
plt.plot(p_x, p_y, 'r', Strain1, Stress1, 'b')
plt.grid(True)
plt.show()
#END==================================================

# 진변형률, 진응력 구하기
L0 = 59.5      # [mm]
L  = 59.5      # [mm]
A0 = 11.223    # [mm^2]
A  = 11.223    # [mm^2]
w0  = 0.9      # [mm]
w  = 0.9       # [mm]
h0  = 12.47    # [mm]
h  = 12.47     # [mm]

Stress3 = Stress1.copy()
Strain3 = Strain1.copy()

# 166  : 소성변형이 일어나는 구간
# 1600 : 넥킹구간
# 2232 : 전체 구간 
for i in range(0,len(Strain1)):
    L = L0 + Strain1[i] 
    h = h0 - Strain1[i]
    
    if i > 1600 and i < 2100: # 넥킹구간 시작
        w = w - 0.0002
    elif i > 2100:            # 실제로 끊어지는 구간
        w = w - 0.0015

    A = w * h
    P = Stress1[i] * A0
    Stress3[i] = P / A  
    Strain3[i] = np.log(L/L0)
    # print("{:.2f}, {:.2f}, {}, {:.2f}, {:5}".format(P,A,w,h,i))


plt.title("Real Strain-Stress Graph")
plt.xlabel("Strain [mm/mm]")
plt.ylabel("Stress [MPa]")
plt.ylim([0,700])
plt.grid(True)
plt.plot(Strain3, Stress3, 'r')

#END======================================================

# 가공경화지수 n, 강도계수 k=============================
# np.log(Stress1[i]) = np.log(K) + n * np.log(Strain1[i])
# Stress1[i] = K * Strain1[i] ** n
import sympy as sp
from sympy.solvers import solve

n = sp.Symbol('n')
K = sp.Symbol('K')

i = 400
eq1 = K * Strain3[i] ** n - Stress3[i]
sp.pprint(K * Strain3[i] ** n - Stress3[i])

i = 600
eq2 = K * Strain3[i] ** n - Stress3[i]
sp.pprint(K * Strain3[i] ** n - Stress3[i])

solve([eq1, eq2], [n,K])
#Out[22]: [(0.0655774097512531, 560.774460436661)]




