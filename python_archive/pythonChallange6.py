#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> channel.zip에 있는 설명 컬럼에서 특정 단어를 추출하는 코드
'''
import re
import zipfile

file = "90052"
zip = zipfile.ZipFile("/home/edward/Downloads/channel.zip")
result = ""

while True:
    text = zip.read(file + ".txt")
    file = re.findall("Next nothing is (\d+)",text)

    if file:
        file = "".join(file)
        result += zip.getinfo(file+".txt").comment
    else:
        print result
        exit(0)
    
    
















