시스템최신기술 과제 제출
모든 코드는 systemNewTechnology 폴더 안에 있습니다

- Youtube URL (Mission 2) :    [https://www.youtube.com/watch?v=grN8DFKpY14]
- Youtube URL (Mission 3):     [https://youtu.be/uU5L1j1SaFw]
- thingspeak URL :             [https://thingspeak.com/channels/248481]

# Mission 2 :
Raspberry Pi에 Python으로 DS18B20 온도세서 구동시키고, Thing Speak에 데이타 전송하여 실시간 온라인 그래프 보는 Public URL제출,  개인 github에 프로그램 올리고, 30초짜리 작동 동영상 만들어 유튜브에 올리고 Github에 링크를 올려둠
```python
#-*- coding: utf-8 -*-
'''
    python ==> 시스템최신기술, ds18b20 센서데이터를 thingspeak api를 이용해 웹에 뿌려주는 코드
'''
import os
import time
import urllib
import json
import httplib

# 5초의 데이터 업데이트 시간을 설정하고 API 값을 저장합니다
sleep = 5
key = 'PC45B10F37HRMZ0P'

# 라즈베리파이가 센서데이터를 받는 경로를 설정합니다.
temp_sensor='/sys/bus/w1/devices/28-0416935fd1ff/w1_slave'

os.system('modprobe w1-gpio')
os.system('modprobe w1-therm')

# 파일의 내용을 읽어오는 함수
def temp_raw():
    f = open(temp_sensor,'r')
    lines = f.readlines()
    f.close()
    return lines

# 읽어온 파일의 구문을 분석해 온도부분만 반환하는 함수
def read_temp():
    lines = temp_raw()
    while lines[0].strip()[-3:] != 'YES':
        time.sleep(0.2)
        lines = temp_raw()

    temp_output = lines[1].find('t=')

    if temp_output != -1:
        temp_string = lines[1].strip()[temp_output+2:]
        temp_c = float(temp_string) / 1000.0
        temp_f = temp_c * 9.0/5.0 + 32.0
        return temp_c, temp_f

# ThingSpeak에 데이터를 전송하는 함수
def thermometer():
    while True:
        temp = read_temp()[0]
        params = urllib.urlencode({'field1': temp, 'key':key })
        headers = {"Content-typZZe": "application/x-www-form-urlencoded","Accept": "text/plain"}
        conn = httplib.HTTPConnection("api.thingspeak.com:80")
        try:
            conn.request("POST", "/update", params, headers)
            response = conn.getresponse()
            print temp
            print response.status, response.reason
            data = response.read()
            conn.close()
        except:
            print "connection failed"
        break


if __name__ == "__main__":
    while True:
        thermometer()
        time.sleep(sleep)
```


# Mission 3-1 :
Raspberry Pi에 Python으로 LED를 10개 연결하여 뱀이 기어가는 형태를 구현하고 동영상 10초 촬영.  Push Button Switch를 붙이고 LED10개를 사용, LED를 킨후 사람이 스위치를 누르는 순발력 측정기 구현, 데모 영상.개인 github에 프로그램 올리고, 30초짜리 작동 동영상 만들어 유튜브에 올리고 Github에 링크를 올려둠
```python
#-*- coding: utf-8 -*-
'''
    python ==> 시스템최신기술, LED 10개를 연쇄적으로 불이 들어왔다 꺼지게 하는 코드
'''
import RPi.GPIO as GPIO
import time

# 핀들의 목록을 생성합니다.
pin=[7,11,12,13,15,18,29,31,32,33]

# BOARD를 초기화하고 16번 핀을 풀다운 인풋으로 설정합니다.
GPIO.setmode(GPIO.BOARD)
GPIO.setup(16, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setwarnings(False)

# setup : 핀들의 초기화를 하는 함수
def setup(p):
    GPIO.setup(pin[p], GPIO.OUT)

# out : 핀들의 HIGH, LOW 값을 변경해주는 함수
def out(p, v):
    GPIO.output(pin[i], v)

for i in range(0, len(pin)):
    setup(i)

for i in range(0, len(pin)):
    out(i, 0)

while True:
    # 0.1초를 주기로 핀들이 순서대로 켜졌다가 순서대로 꺼지는 것을 반복합니다
    for i in range(0, len(pin)):
        out(i, 1);
        time.sleep(0.1)

    for i in range(len(pin)-1, -1, -1):
        out(i, 0);
        time.sleep(0.1)
```

# Mission 3-2 :
```python
#-*- coding: utf-8 -*-
'''
    python ==> 시스템최신기술, LED 1개가 켜진 후 스위치를 누른 시간차이를 계산하는 코드
'''
import RPi.GPIO as GPIO
import time
import random

# 핀들의 목록을 생성합니다.
pin=[7,11,12,13,15,18,29,31,32,33]

# BOARD를 초기화하고 16번 핀을 풀다운 인풋으로 설정합니다.
GPIO.setmode(GPIO.BOARD)
GPIO.setup(16, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setwarnings(False)

# setup : 핀들의 초기화를 하는 함수
def setup(p):
    GPIO.setup(pin[p], GPIO.OUT)

# out : 핀들의 HIGH, LOW 값을 변경해주는 함수
def out(p, v):
    GPIO.output(pin[i], v)

for i in range(0, len(pin)):
    setup(i)

for i in range(0, len(pin)):
    out(i, 0)


while True:
    # 5 ~ 10초의 랜덤시간 안에 LED가 켜지고 현재 시간을 저장합니다.
    rand= random.randint(5,10)
    time.sleep(rand)
    start = time.time()
    out(1,1)

    # 스위치를 누르면 시간차이를 계산해 출력합니다.
    if(GPIO.wait_for_edge(16, GPIO.RISING)):
        out(1,0)
        end = time.time()
        print("%f second spent!" %(end-start))
```


