fname = "hello.bmp"

pfile = open(fname, "r+b")                             #(1)
buff = pfile.read()
buff.replace(b'\x2A\x2F',b'\x00\x00')                  #(2)
pfile.close()

pfile = open(fname, "w+b")                             #(3) 
pfile.write(buff)
pfile.seek(2,0)                                        #(4)
pfile.write(b'\x2F\x2A')                               #(5)
pfile.close()

pfile = open(fname, "a+b")                             #(6)
pfile.write(b'\xFF\x2A\x2F\x3D\x31\x3B')               #(7)
pfile.write(open ('hello.js','rb').read())
pfile.close()
