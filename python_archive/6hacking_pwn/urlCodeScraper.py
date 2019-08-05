#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> 원하는 URL의 소스코드를 긁어오는 코드
'''
import socket

# Build a socket and connect to google.com
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

hostName = raw_input("[+] type URL you want to get : ")
s.connect((""+hostName+"",80))

# send a basic http request
s.send("GET / HTTP/1.0\nHost: www.koradb.iptime.org\n\n")
page = ""

# while data is still coming back, append to our page variable
while 1:
    data = s.recv(1024)
    if data =="":
        break
    page += data

# close out socket snd print the results
s.close()
print page


