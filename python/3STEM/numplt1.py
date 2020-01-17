#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> matplotlib, pyplot, animation을 이용해 gif파일을 만드는 예제 코드
                cos(2pi*(x - 0.01t))
'''
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

fig = plt.figure()
ax = plt.axes(xlim=(0,2), ylim=(-2,2))
line, = ax.plot([],[],lw=2)

def init():
    line.set_data([],[])
    return line,

def animate(i):
    x = np.linspace(0,2,1000)
    y = np.cos(2* np.pi * (x - 0.01 * i))
    line.set_data(x,y)
    return line,


anim = animation.FuncAnimation(fig, animate, init_func=init, frames =200, interval = 20, blit=True)
anim.save('animation.gif', writer='imagemagic', fps=30, dpi=100)
plt.grid()
plt.show()
