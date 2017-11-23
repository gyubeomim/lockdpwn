#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> pythonchallenge3, 주석에 있는 데이터를 가져와 양옆에 대문자가 3개씩 있는 단어를 찾는 코드
'''
import re
import urllib

S = urllib.urlopen("http://www.pythonchallenge.com/pc/def/equality.html").read()
data = S[S.index('<!--'):S.index('-->')]

regex = r'[a-z][A-Z][A-Z][A-Z]([a-z])[A-Z][A-Z][A-Z][a-z]'

for result in  re.findall(regex,data):
    print result,

