#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> test.txt 파일에 A + 0xff 를 삽입해 생성하는 코드
'''
import  struct

print "[+] create file..."

length = struct.pack('<L', 0xff)
dummy = "A" * 1000 + length
payload = dummy

f = open("test.txt", "w")
f.write(payload)
f.close()
