#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
	python ==>  8080 포트에 아주 간단한 서버를 만드는 코드
'''
import socket, select, subprocess

#Create a socket and then bind the socket to all addresses on port 8080
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('localhost',8080))
#Listening for incoming connections
s.listen(10)
input = [s]

while 1:
    #Check for sockets wating read
    reader, output, exceptions = select.select(input,[],[])
	
    for sock in reader:
    #If the socket is our listner, accept a new connection
        if sock == s:
            c, addr = s.accept()
            print "New connection from " , addr
            input.append(c)
    # otherwise, it's a command to execute
        else:
            command = sock.recv(1024)
            if command:
                shell = command.rstrip().split(" ")
                try:
                    out = subprocess.Popen(shell,stdout = subprocess.PIPE).\
                    communicate()[0]
                except:
                    out = "Command failed\n"
                    sock.send(out)
            else:
                sock.close()
                input.remove(sock)
s.close()
