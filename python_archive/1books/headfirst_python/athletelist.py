#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 헤드퍼스트 파이썬, AthleteList 클래스를 선언한 코드
'''
class AthleteList(list):

    def __init__(self, a_name, a_dob=None, a_times=[]):
        list.__init__([])
        self.name = a_name
        self.dob = a_dob
        self.extend(a_times)

    @staticmethod
    def sanitize(time_string):
        if '-' in time_string:
            splitter = '-'
        elif ':' in time_string:
            splitter = ':'
        else:
            return(time_string)
        (mins, secs) = time_string.split(splitter)
        return(mins + '.' + secs)

    @property
    def top3(self):
        return(sorted(set([self.sanitize(t) for t in self]))[0:3])

    @property
    def clean_data(self):
        return(sorted(set([self.sanitize(t) for t in self])))
