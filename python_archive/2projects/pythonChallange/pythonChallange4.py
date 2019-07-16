#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> pythonchallenge4, nothing=????? 이런식으로 홈페이지 주소를 계속 바꿔가며 들어가야 되는데 이를 자동화해주는 코드
'''
import urllib
import re

num = 8022

while True:
    b = urllib.urlopen("http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=%s" % num)
    cont = b.read()

    str = re.findall("next nothing is (\d+)",cont)

    if str:
        num = "".join(str)
    else:
        print cont
        exit(0)

    print num
    
    

