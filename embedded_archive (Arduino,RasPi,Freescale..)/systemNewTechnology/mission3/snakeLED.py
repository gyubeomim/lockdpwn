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
