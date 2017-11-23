#-*- coding: utf-8 -*-
'''
    raspberry ==> 시스템최신기술, LED 1개가 켜진 후 스위치를 누른 시간차이를 계산하는 코드
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
