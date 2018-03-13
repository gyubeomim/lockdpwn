#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 특정파일을 읽어와 최소값과 최대값을 찾는 예제 코드
'''
import sys

if len(sys.argv) != 2:
    print "Please supply a filename"
    raise SystemExit(1)

with open(sys.argv[1]) as f:
    lines = f.read().splitlines()
f.close()


<<<<<<< HEAD

=======
>>>>>>> c46d972e32e778b694cd19406715fcd77c2c9526
fvalues = [float(line) for line in lines]

print "The minimum values is " , min(fvalues)
print "The maximum values is " , max(fvalues)


