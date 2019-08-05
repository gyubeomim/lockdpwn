import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
GPIO.setup(11, GPIO.OUT)

flag = 1

while(1):
    control = input("Press 1 to light LED (0 to quit) : ")
    if control == 1:
        if flag == 0:
            GPIO.output(11,False)
            flag =1
        else:
            GPIO.output(11, True)
            flag = 0

    elif control == 0:
        print("quitting...")
        GPIO.cleanup()
        exit(0)















