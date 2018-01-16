import socket
import threading
import marshal
import numpy as np
from struct import *

class MySocket:
    def __init__(self):
        self.HOST = "127.0.0.1"
        self.PORT = 8080
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.connect((self.HOST, self.PORT))
        self.s.setblocking(True)


    def sendingMsg(self, action):
        data = pack('f', action)

        #print(data)

        self.s.send(data)


    def getStep(self):
       data = self.s.recv(800)
       #print(data)

       # 181개의 센서데이터 + isDone + reward까지 183개의 데이터가 들어온다
       pktFormat = 'ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff'
       pktSize = calcsize(pktFormat)

       #print("pktSize : ", pktSize)

       # 물체에 충돌한 경우 data size가 pktSize보다 작아서 에러가 나므로 아래 코드를 추가한다
       if len(data) < pktSize:
           newLen = pktSize - len(data)
           data += b'\x00' * newLen

       data_unpack = []
       data_unpack = unpack(pktFormat, data[:pktSize])
        
       #print(data_unpack)

       data_unpack = np.array(data_unpack)
       states = data_unpack[:-1]
       #reward = data_unpack[-1]
       isDone = data_unpack[-1]

       #print(len(states))

       if(isDone):
           print(data)
           print(len(data))
           print(isDone)

       data = 0

       #print("-- reward : ", reward)

       return states, 1, isDone

    
