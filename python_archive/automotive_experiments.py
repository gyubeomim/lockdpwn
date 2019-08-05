#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
    python ==> 자동차융합실험1, 전자전기 회로 이론 및 센서 설계 실험의 그래프를 그리는 코드
'''

import numpy as np
import matplotlib.pyplot as plt

# plt.title('5V, 10V source Voltage [Red, Blue]')
# plt.plot([100, 200, 500], [0.0001, 0.0002, 0.0005], 'ro')
# plt.plot([100, 200, 500], [0.0002, 0.0004, 0.0010], 'bo')
# plt.xlabel('mass [g]')
# plt.ylabel('output Voltage [mV]')
# plt.grid(True)
# plt.show()


plt.plot([11.4, 6.3, 4.34, 3.42], [11.33, 12.52, 12.99, 13.2], 'ro')
plt.plot([11.31,6.26,4.32,3.30], [11.31,12.52,12.96,13.2], 'bo')
plt.ylabel('Voltage [V]')
plt.xlabel('Current [mA]')
plt.grid(True)
plt.show()



