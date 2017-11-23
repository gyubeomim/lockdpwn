#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> 인터넷에서 퍼온 개미수열을 구현한 예제 코드
'''
char = "1"
output = ""
LEN = 10

for i  in range(LEN):
	j = 0
	while j < len(char):
		curr = char[j]
		count = 1

		while j+1 < len(char) and curr == char[j+1]:
			count += 1
			j += 1
		output += curr + str(count)
		j += 1

	print(output)
	char = output
	output = ""
