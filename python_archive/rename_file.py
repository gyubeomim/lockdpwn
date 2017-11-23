#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 파일이름에 공백을 "_"로 치환해주는 코드
'''
import os


for filename in os.listdir("D:\\gitrepo\\lockdpwn\\python_archive\\ipython\\swConvTech_data"):
    os.rename(filename, filename.replace(" ", "_"))
