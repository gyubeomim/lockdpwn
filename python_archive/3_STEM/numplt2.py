#!/usr/local/bin/python
# -*- coding: utf-8 -*-
'''
    python ==> matplotlib, plot을 이용해 sin(), cos() 그래프를 그리는 예제 코드
'''
import numpy as np
import matplotlib.pyplot as plt

t = np.linspace(0,5*np.pi, 100)
y1 = np.sin(0.5*t)
y2 = np.cos(t)

# 그래프를 그린다
plt.plot(t,y1,t,y2)
plt.grid()
plt.show()
