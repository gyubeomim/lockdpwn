#-*-coding:utf-8-*-
''' 
    python ==> matplotlib으로 GPS 데이터를 plot하는 코드
'''
import matplotlib.pyplot as plt

# 각 컬럼별로 데이터를 받기 위해 선언합니다
index = []
latitude = []
longitude = []
height = []
speed = []

# 데이터파일을 열면서
with open('./gpsdata.txt','r') as f:
    # 첫번째 라인은 넘어가고
    line = f.readline()
    
    # 나머지 라인들을 숫자화해서 배열에 추가합니다 
    for i in range(0,132):
        line = f.readline()
        line = line.split(',')
        
        index.append(int(line[0]))
        latitude.append(float(line[5]))
        longitude.append(float(line[7]))

        line[9] = line[9].split(' ')
        height.append(float(line[9][0]))

        line[10] = line[10].split(' ')
        speed.append(float(line[10][0]))


# 추가한 데이터들을 plot합니다
plt.subplot(2,2,1)
plt.plot(index,height,'r')
plt.ylabel('HEIGHT')
plt.title('GPS Data')
plt.legend()
plt.grid()

plt.subplot(2,2,2)
plt.plot(index,speed,'g')
plt.ylabel('SPEED (km/h)')
plt.title('GPS Data')
plt.legend()
plt.grid()

plt.subplot(2,2,3)
plt.plot(index,longitude,'b')
plt.ylabel('LONGITUDE')
plt.title('GPS Data')
plt.legend()
plt.grid()

plt.subplot(2,2,4)
plt.plot(index,latitude,'c')
plt.ylabel('LATITUDE')
plt.title('GPS Data')
plt.legend()
plt.grid()
plt.show()


