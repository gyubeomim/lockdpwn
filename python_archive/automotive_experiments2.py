#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
    python ==> 자동차융합실험1, 
'''

import numpy as np
import matplotlib.pyplot as plt


# plt.plot([0.00001,0.000022,0.000056,0.00009,0.000111,0.000133], [0.000021,0.000047,0.000118,0.000191,0.000235,0.000280], 'ro')
# plt.plot([0.000008,0.000017,0.000043,0.000069,0.000084,0.0001], [0.000021,0.000047,0.000118,0.000191,0.000235,0.000280], 'bo')
# plt.ylabel('Uout/Uin [mV/V]')
# plt.xlabel('Strain esp')
# plt.grid(True)
# plt.show()
#


# plt.title('5V, 10V source Voltage [Red, Blue]')
plt.plot([0,5,10,15], [0,0.0523,0.1047,0.1221], 'ro')
plt.plot([0,5,10,15], [0,0.0349,0.0872,0.1221], 'bx')
plt.xlabel('weight [N]')
plt.ylabel('delta [rad]')
plt.grid(True)
plt.show()


