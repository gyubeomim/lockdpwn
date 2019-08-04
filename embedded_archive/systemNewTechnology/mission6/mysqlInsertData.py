#-*- coding: utf-8 -*-
'''
    python ==> 시스템최신기술, nodejs 홈페이지를 방문해 mysql에 온도데이터를 삽입하는 코드
'''
import os
import time
import urllib
import json
import httplib
import requests

# 10초의 데이터 업데이트 시간을 설정하고 API 값을 저장합니다
sleep = 10
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

# nodejs에 GET 방식으로 온도 파라미터를 전달하는 역할을 하는 함수
def thermometer():
    while True:
        temp = read_temp()[0]
        headers = {"Content-typZZe": "application/x-www-form-urlencoded","Accept": "text/plain"}

        try:
            # nodejs에 온도데이터를 지속적으로 요청해서 mysql에 데이터를 삽입한다
            print "[+] Node.js"
            r = requests.get('http://localhost:3000/logone', params={'temp':temp})
            print r.status_code

        except:
            print "connection failed"
        break



if __name__ == "__main__":
    while True:
        thermometer()
        time.sleep(sleep)
