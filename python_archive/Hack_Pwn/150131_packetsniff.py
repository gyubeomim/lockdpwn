#-*- coding: utf-8 -*-
'''
    python ==> 파이썬해킹입문, ftp 서버와의 통신 패킷을 읽고 스니핑해주는 예제 코드
                                cmd> ftp ~~ 로 해야지 제대로 패킷이 잡힌다
'''
import socket
import string

HOST = socket.gethostbyname(socket.gethostname())

s = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_IP)
s.bind((HOST,0))
s.setsockopt(socket.IPPROTO_IP,socket.IP_HDRINCL,1)
s.ioctl(socket.SIO_RCVALL, socket.RCVALL_ON)

while True:
    data = s.recvfrom(65565)
    printable = set(string.printable)
    parsedData = ''.join(x if x in printable else '.' for x in data[0])

    if(parsedData.find("USER") > 0):
        print parsedData
    elif(parsedData.find("PASS") >0):
        print parsedData
    elif(parsedData.find("530 User cannot log in") >0):
        print parsedData
    elif(parsedData.find("230 User logged in") > 0):
        print parsedData
