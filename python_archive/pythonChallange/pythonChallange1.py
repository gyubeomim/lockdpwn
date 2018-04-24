#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> pythonChallange1, 아래 문자열에 아스키 코드값을 전부 +2를 더해 해독하는 코드
'''
import string

prstr = "g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."
prstr2 = "map"

# 아스키 코드 값에 + 2를 더해서 해독하는 코드
transtab = string.maketrans(string.ascii_lowercase, string.ascii_lowercase[2:] + string.ascii_lowercase[:2])
prslv = prstr.translate(transtab)
prslv2 = prstr2.translate(transtab)

print prslv
print prslv2
