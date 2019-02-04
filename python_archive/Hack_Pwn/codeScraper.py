#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==> 해킹침투코딩 p103, koradb.iptime.org에 웹페이지 요청을 보내는 코드 
'''
import socket

# Build a socket and connect to google.com
af, type, proto,name,conn = socket.getaddrinfo("koradb.iptime.org",80,0,0,\
                                               socket.SOL_TCP)[0]
s = socket.socket(af,type,proto)
s.connect(conn)

# send a basic http request 보내는 사람
s.send("GET / HTTP/1.0\nHost: aaa.bbb.com\n\n")
page = ""

# while data is still coming back, append to our page variable
while 1:
    data = s.recv(1024)
    if data == "":
        break
    page = page + data

#close our socket and print the results
s.close()

print page

