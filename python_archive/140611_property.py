#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> @property 장식자를 사용해본 코드
'''
import math

class Circle(object):
    def __init__(self,radius):
        self.radius = radius
    @property
    def area(self):
        return math.pi*self.radius**2
    @property
    def perimeter(self):
        return 2*math.pi*self.radius



