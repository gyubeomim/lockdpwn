#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
    python ==> 직접 제작한 계산기 프로그램 코드
'''
import sys

def calculate(a, operator, b):
	a = int(a)
	b = int(b)

	if operator == '+':
		c = a + b
	elif operator == '-':
		c = a - b
	elif operator == '/':
		c = a / b
	elif operator == '*':
		c = a * b
	else:
		return "That's not an operator"

	return c



def main():
	while True:
		elements = raw_input("type words you want to calculate [ex) 1 + 2]:  ")

		if elements == 'q' or elements == 'Q':
			sys.exit(1)

		try:
			a, operator, b = elements.split(' ')
			result = calculate(a, operator, b)
			print a,operator,b, "= ", result

		except Exception, e:
			print e





if __name__ == '__main__':
	main()
