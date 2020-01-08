#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> pyttsx를 통해 음성프로그램을 작성한 예제 코드
'''

import pyttsx

engine = pyttsx.init()
engine.say("sally sells seashells by the seashore")
engine.say("the quick brown fox jumped over the lazy dog")
engine.runAndWait()
