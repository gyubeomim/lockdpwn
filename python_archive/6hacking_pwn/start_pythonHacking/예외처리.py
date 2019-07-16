try:
    a = 10 / 0                                               #(1)
except:                                                      #(2)   
    print "1.[exception] divided by zero "

print "\n"

try:
    a = 10 / 0
    print "value of a: ", a
except ZeroDivisionError:                                     #(3)
    print "2.[exception] divided by zero "

print "\n"

try:
    a = 10
    b = "a"
    c = a / b
except (TypeError, ZeroDivisionError):                        #(4)
    print "3.[exception] type error occurred"
else:
    print "4.type is proper"                                  #(5)
finally:
    print "5.end of test program"                             #(6)
