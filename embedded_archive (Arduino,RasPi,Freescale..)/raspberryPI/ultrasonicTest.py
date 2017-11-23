#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    raspberry ==> 라즈베리파이로 초음파센서를 구동시켜 본 예제 코드
'''
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

TRIG = 11
ECHO = 12

GPIO.setup(TRIG,GPIO.OUT)
GPIO.setup(ECHO,GPIO.IN)

GPIO.output(TRIG,False)

try:
    while True:
        GPIO.output(TRIG,True)
        time.sleep(0.00001)
        GPIO.output(TRIG,False)

        while GPIO.input(ECHO) == 0:
            pulse_start = time.time()

        while GPIO.input(ECHO) == 1:
            pulse_end = time.time()

        pulse_duration = pulse_end - pulse_start

        distance = pulse_duration * 17150
        distance = round(distance, 2)

        if distance > 100:
            distance = 100;

        print "Distance: ", distance, " cm"

except KeyboardInterrupt:
    GPIO.cleanup()

