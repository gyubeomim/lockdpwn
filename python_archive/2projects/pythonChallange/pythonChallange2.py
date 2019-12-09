#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> pythonChallange2, 복잡한 여러 문자들에서 원하는 정규표현식을 사용해 단어를 추출하는 코드
'''
import re
import string

f1 = open("level2.txt",'r')
pr = ""

while True:
    line = f1.readline()
    if not line:
        break
    pr += line

pattern = re.compile('\s+|([ !@#$%^&*(){}\[\]_+<> ])')
sen = re.sub(pattern, '', pr)

print sen




