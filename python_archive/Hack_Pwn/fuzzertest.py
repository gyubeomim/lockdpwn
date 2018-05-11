#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> A 문자열을 입력해 데이터를 무작위로 변경하는 코드 (퍼저로 사용한다)
'''
import random

def mutate(data, n = 20):
	tmp = [c for c in data]
	for i in xrange(n):
		tmp[random.randint(0, len(tmp) - 1)] = chr(random.randint(0, 255))

	return ''.join(tmp)

print repr(mutate('A' * 50))
print repr(mutate('A' * 50))
print repr(mutate('A' * 50))
print repr(mutate('A' * 50))



