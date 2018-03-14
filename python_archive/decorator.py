#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 장식자 decorator의 예제를 확인해본 코드
                my_function 위에 장식자 @Verbose를 붙여주니 프로그램에서 my_function()을 시작하자마자 Verbose도 같이 시작된다
'''
class Verbose:
    def __init__(self, f):
        print "Initializing Verbose."
        self.func = f;

    def __call__(self):
        print "Begin", self.func.__name__
        self.func();
        print "End", self.func.__name__


@Verbose
def my_function():
    print "hello, world."


print "[+] Program start"
my_function();


