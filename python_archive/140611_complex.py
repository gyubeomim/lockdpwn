#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 실수와 허수를 받는 Complex 클래스를 선언한 코드
'''
class Complex(object):
    def __init__(self,real,imag=0):
        self.real = float(real)
        self.imag = float(imag)

    def __repr__(self):
        return "Complex(%s, %s)" % (self.real, self.imag)

    def __str__(self):
        return "(%g+%gj)" % (self.real, self.imag)

    # self + other
    def __add__(self, other):
        return Complex(self.real + other.real, self.imag + other.imag)

    # self - other
    def __sub_(self,other):
        return Complex(self.real - other.real, self.imag - other.imag)

    def __radd__(self,other):
        return Complex(other.real + self.real, other.imag + self.imag)

    def __rsub__(self,other):
        return Complex(other.real - self.real, other.imag - self.imag)
