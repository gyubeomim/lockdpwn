#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 윈도우해킹가이드, 간단한 쉘코드 call+4 방법을 사용해 인코딩을 해보는 예제 코드
'''
import os
import struct

print " * Simple XOR Shell code by edward"

def xor(data):
    key = "\x01\x02\x03\x04"  # XOR Key
    leng = len(key)
    reverse = ""
    for i in range(0, len(data)):
        reverse += struct.pack("B", (ord(data[i]) ^ ord(key[i%leng]))) # XOR
    return reverse

def conv_hex(data):
    hex_str = ""
    for i in range(0, len(data)):
        hex_str += ("0x%02x" % ord(data[i])).replace('0x','\\x')
    return hex_str

org_shellcode = (
        "\x41\x41\x41\x41\x42\x42\x42\x42\x43\x43\x43\x43\x44\x44\x44\x44"
        "\x41\x41\x41\x41\x42\x42\x42\x42\x43\x43\x43\x43\x44\x44\x44\x44"
        "\x41\x41\x41\x41\x42\x42\x42\x42\x43\x43\x43\x43\x44\x44\x44\x44"
        "\x41\x41\x41\x41\x00\x00\x00\x00\x43\x43\x43\x43\x44\x44\x44\x44"
        )

xor_shellcode = ""

decoder = (
    "\xe8\xff\xff\xff\xff"    # call + 4
    "\xc2"                    # ret (\xff\xc2 = nop)
    "\x5e"                    # pop esi
    "\x6A\x20\x59"            # pull 20, pop ecx
    "\xBF\x02\x02\x03\x04"    # mov edi, xor_key
    "\x31\x7E\x12"            # xor [esi+12], edi
    "\x83\xC6\x04"            # add esi, 4
    "\xE2\xF8"                # loop xor
)

xor_shellcode = xor(org_shellcode)
print "Original : " + conv_hex(org_shellcode) + '\n'
print "Encoded : " + conv_hex(decoder) + conv_hex(xor_shellcode) + '\n'



