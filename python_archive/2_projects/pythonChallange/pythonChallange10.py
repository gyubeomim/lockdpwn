#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> pythonchallange10, 개미수열을 구현해본 코드
'''
ant = ['1']
round = 30

while round:
	ant += '!'
	next = []
	start = 0

	for current in range(len(ant)):
		if ant[current] != ant[start]:
			next.append(str(current-start) + ant[start])
			start = current
	ant = "".join(next)

	round -= 1

print len(ant)
