#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> pythonchallange13, xmlrpclib을 사용해서 phone 메소드를 활용해 번호를 알아내는 코드
                먼말인지 모르겠네..
'''

import xmlrpclib

server = xmlrpclib.Server('http://www.pythonchallenge.com/pc/phonebook.php')

print server.system.listMethods()
print server.system.methodHelp('phone')
print server.system.methodSignature('phone')
print server.phone('Bert')
raw_input("wait..")
