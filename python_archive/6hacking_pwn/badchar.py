#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 
'''
from immlib import *

def main(args):
    imm = Debugger()
    bad_char_found = False
    address = int(args[0],16)
    shellcode = " "
    shellcode_length = len(shellcode)
    debug_shellcode = imm.readMemory(address,shellcode_length)
    debug_shellcode = debug_shellcode.encode("HEX")

    imm.log("Address: 0x%08x" % address)
    imm.log("Shellcode Length : %d" % length)
    imm.log("Attack Shellcode: %s" % canvas_shellcode[:512])
    imm.log("In Memory Shellcode: %s " % id_shellcode[:512])

    count = 0

    while count <= shhellcode_length:
        if debug_shellcode[count] != sellcode[count]:
            imm.log("Bad Char Detected at offset %d" % count)
            bad_char_found = True
            break
        count += 1

    if bad_char_found:
        imm.log("[*****]")
        imm.log("Bad character found: %s" %  debug_shellcode[count])
        imm.log("Bad character original: %s " % shellcode[count])
        imm.log("[*****]")

    return "[*] !badchar finished, check Log window."


