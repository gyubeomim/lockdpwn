#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    raspberry ==> 라즈베리파이를 사용해 11,13,15에 있는 LED를 껏다 켰다 하는 코드
'''
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)

GPIO.setup(11,GPIO.OUT)
GPIO.setup(13,GPIO.OUT)
GPIO.setup(15,GPIO.OUT)

flag1 = 1
flag2 = 1
flag3 = 1

while(1):
    control = input("\n\ninput 1(yellow), 2(red), 3(green), 0(quit) : ")
    if control == 1:
        if flag1 == 0:
            GPIO.output(11,False)
            flag1 = 1
        else:
            GPIO.output(11,True)
            flag1 = 0

    elif control == 2:
        if flag2 == 0:
            GPIO.output(13,False)
            flag2 = 1
        else:
            GPIO.output(13,True)
            flag2 = 0

    elif control == 3:
        if flag3 == 0:
            GPIO.output(15,False)
            flag3 = 1
        else:
            GPIO.output(15,True)
            flag3 = 0

    elif control == 0:
        print("quitting..")
        GPIO.cleanup()
        exit(0)


