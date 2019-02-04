#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
	python ==> fibonacci 수열을 python 코드를 통해 구현한 코드
'''
fibo = {0:0, 1:1}

def fibonacci(n):
	global fibo

	fibo.setdefault(n, 0)
	if n >= 2:
		for i in range(2, n+1):
			fibo[i] = fibo[i-1] + fibo[i-2]


idx = int(input("[+] Please type any integer : "))
fibonacci(idx)

print(fibo[idx])
print(fibo)
