#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> sentdex pygta5 p.3 코드를 따라해본 코드
            
               python을 사용해 W 키를 눌러서 gta5 캐릭터가 앞으로 가도록 설정하는 코드
               time.sleep(3) 함수 때문에 Window가 제대로 출력되지 않는 문제점이 있다

'''
import time
# python에서 키보드를 사용하기 위해 아래 코드를 추가했다
from directkeys import PressKey, ReleaseKey, W,A,S,D


while(True):

    print('[+] forward, \'w\' key is down')
    PressKey(W)
    time.sleep(3)
    print('[+] stop,    \'w\' key is up')
    ReleaseKey(W)
    time.sleep(3)


