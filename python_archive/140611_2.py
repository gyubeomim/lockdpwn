#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 
'''
import time

class Date(object):
    def __init__(self,year,month,day):
        self.year = year
        self.month = month
        self.day = day
    @staticmethod
    def now( ):
        t = time.localtime()
        return Date(t.tm_year, t.tm_mon, t.tm_day)
    @staticmethod
    def tomorrow( ):
        t = time.localtime(time.time()+86400)
        return Date(t.tm_year, t.tm_mon, t.tm_day)


class Times(object):

    factor = 1
    @classmethod
    def mul(cls,x):
        return cls.factor*x

class TwoTimes(Times):
    factor = 2

class EuroDate(Date):
    def __str__(self):
                    return "%02d/%02d/%4d" % (self.day , self.month, self.year)
