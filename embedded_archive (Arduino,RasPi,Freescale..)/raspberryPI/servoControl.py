#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    raspberry ==> sg90 서보모터를 돌려본 코드 
                pwm.start, ChangeDutyCycle, stop 함수로 제어한다
'''
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

# 8번에 서보모터 pwm을 연결한다
GPIO.setup(7,GPIO.OUT)
pwm = GPIO.PWM(7, 50)   # 8번핀 50Hz, 20ms

pwm.start(7.5)  # duty cycle을 정한다

try:
    while True:
        pwm.ChangeDutyCycle(7.5)  # 90 deg
        time.sleep(1)
        pwm.ChangeDutyCycle(2.5)  # 0 deg
        time.sleep(1)
        pwm.ChangeDutyCycle(12.5) # 180 deg
        time.sleep(1)


except KeyboardInterrupt:
    pwm.stop()
    GPIO.cleanup()

