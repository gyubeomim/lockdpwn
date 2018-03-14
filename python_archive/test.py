#!/usr/bin/env python
#-*- coding: utf-8 -*-

def fridge(function):
    def wrapper(*args, **kwargs):
        print("냉장고를 연다.")
        function(*args, **kwargs)
        print("냉장고를 닫는다.")
    return wrapper


@fridge
def put_fridge(food):
    print("{food}를 냉장고에 넣는다.".format(food = food))

put_fridge("족발")
