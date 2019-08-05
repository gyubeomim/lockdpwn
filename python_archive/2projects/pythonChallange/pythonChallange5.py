#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> pythonChallange5, Pickle을 사용해 데이터를 unSerialize해서 cmd창에 뿌려주는 코드
'''
import cPickle

f = open("banner.p",'rb')
result = cPickle.load(f)

for finalresult in  result:
    line = ""
    for tu_ch,tu_cnt in finalresult:
        line += tu_ch * tu_cnt
    print line
