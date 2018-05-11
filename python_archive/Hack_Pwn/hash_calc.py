#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 윈도우해킹가이드, 특정 dll의 함수들의 목록과 Hash 값을 확인해보는 코드  
'''
import sys
import pefile

def usage( ):
	print " Usage) %s [dll]" % sys.argv[0]
	print " ex) %s kernel32.dll" % sys.argv[0]

# Hash화 코드
def get_hash(srcstr):
	hashstr = 0
	for i in srcstr:
		hashstr += ord(i)
	return hex(hashstr)

print " # Hash Calculator for Universal Shellcode v1.0"

if len(sys.argv) < 2:
	usage()
	sys.exit()

pe = pefile.PE(sys.argv[1])
print "%-10s\t%-35s\t%-5s\t%-6s" % ("Function Address", "Name", "Ordinal", "Hash")

for exp in pe.DIRECTORY_ENTRY_EXPORT.symbols:
	print "%-10s\t%-35s\t%-5s\t%-6s" %  ( 
		hex(pe.OPTIONAL_HEADER.ImageBase + exp.address),
		exp.name,
		exp.ordinal,
		get_hash(exp.name)
	)

		
	
