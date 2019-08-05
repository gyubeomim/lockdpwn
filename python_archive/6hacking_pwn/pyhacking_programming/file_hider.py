#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> 파이썬해킹프로그래밍, 파일을 ADS형식으로 해서 숨기는 예제 코드
'''
import sys

# Read in the DLL
fd = open( sys.argv[1], "rb" )
dll_contents = fd.read()
fd.close()

print "[*] Filesize: %d" % len( dll_contents )

# Now write it out to the ADS
fd = open( "%s:%s" % ( sys.argv[2], sys.argv[1] ), "wb" )
fd.write( dll_contents )
fd.close()
