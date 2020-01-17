#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> 연습용 코드 (계속 작성중...)
               연립방정식, 역행렬을 푸는 프로그램
'''
import sys
import subprocess
from scipy.optimize  import fsolve
from sympy  import Matrix, solve_linear_system
from sympy import *
from sympy.abc import x,y
import math

def nmapHostFinder():
	ret = subprocess.check_output("nmap -sP 192.168.24.0/24", shell=True)

	for line in ret:
		if line == '\n':
			continue


def solveODE(a, b):

	return


def solveSimultaneousEq(a,b,c,d,e,f):
	system = Matrix(( (a,b,c) , (d,e,f) ))

	print ""
	print "--------------------------------"
	print solve_linear_system(system, x, y)
	print "--------------------------------"
	print ""


def getInverseMatrix(size,a,b,c,d,e=0,f=0,g=0,h=0,i=0):
	size = int(size)
	a = int(a)
	b = int(b)
	c = int(c)
	d = int(d)
	e = int(e)
	f = int(f)
	g = int(g)
	h = int(h)
	i = int(i)

	if size == 2:
		Z = Matrix(size, size, [a,b,c,d])
		D = Z.det()
		Zi = Z.inv()
		DZi = simplify(D*Zi)

	elif size == 3:
		Z = Matrix(size, size, [a,b,c,d,e,f,g,h,i])
		D = Z.det()
		Zi = Z.inv()
		DZi = simplify(D*Zi)

	if DZi:
		print ""
		print "--------------------------------"
		pprint(DZi)
		print "--------------------------------"
		print ""


def main():
	while True:
		print "1 : Simultaneous Equation"
		print "2 : Inverse Matrix"
		print "q to quit"
		choose = raw_input("Choose Options: ")

		if choose == '1':
			print "solve Simultaneous Equation"
			print "ax + by = c"
			print "dx + ey = f"
			ret = raw_input("type (a,b,c,d,e,f): ")
			a,b,c,d,e,f = ret.split(',')

			solveSimultaneousEq(a,b,c,d,e,f)

		elif choose == '2':
		        print "solve Inverse Matrix"
			print "[ a  b  c ]"
			print "[ d  e  f ]"
			print "[ g  h  i ]"
			ret = raw_input("type (a,b,c,d,e,f,g,h,i): ")
			size = raw_input("choose size: ")

			if len(ret) >= 7 and len(ret) < 17:
				a,b,c,d = ret.split(',')
				getInverseMatrix(size,a,b,c,d)

			elif len(ret) >= 17 and len(ret) < 50:
				a,b,c,d,e,f,g,h,i = ret.split(',')
				getInverseMatrix(size,a,b,c,d,e,f,g,h,i)
			else:
				print "[-] Not Valid"
				print ""


				
		elif choose == 'q' or choose == 'Q' or choose == 'exit' or choose == 'quit':
			sys.exit(1)




if __name__ == '__main__':
	main()

