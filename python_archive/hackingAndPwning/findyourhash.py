#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 해킹침투코딩 p89, 리눅스에서 passwd 파일을 분석해주는 코드 
'''
import sys
import crypt

f = open(sys.argv[1],"r")
lines = f.readlines()
f.close()
found = []

for line in lines:
    data = line.split(':')

    # Set username and password to first 2 fields
    user,password = data[0:2]
    geco = data[4].split(',')

    # Create password guess using first char of first name and last field
    guess = geco[0][0] + geco[-1]

    # Assign salt as first 2 characters of crypted password
    salt = password[0:2]


if crypt.crypt(guess,salt)  == password:
    userInfo = { "user" : user , "pass" : guess, "home" : data[5],\
                 "uid" : data[2] , "name" : geco[0]}
    found.append(userInfo)


for user in found:
    print "User : %s " % user['user']
    for k in user.keys():
        if k == "user":
            continue
        print "\t%s : %s " % (k,user[k])

