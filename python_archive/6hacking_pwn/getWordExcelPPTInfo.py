#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 워드, 파포, 엑셀의 최근 문서기록을 레지스트리로부터 가져오는 예제 코드
'''
import os
import sys
import _winreg

def Word():
    _reg = _winreg.ConnectRegistry(None, _winreg.HKEY_CURRENT_USER)
    
    try:
        _key = _winreg.OpenKey(_reg, r"Software\\Microsoft\\Office\\15.0\\Word\\User MRU\\LiveId_1E760FAA55C5054F9D13A24FE9D349E16F885C45D07F281A1EB94290DB8AC76F\\File MRU", 0, _winreg.KEY_ALL_ACCESS)
        count = 0
        while True:
            name, value, type = _winreg.EnumValue(_key, count)
            print name + " : " + value
            count += 1 
    except  WindowsError:
        pass

    try:
        _key2 = _winreg.OpenKey(_reg, r"Software\\Microsoft\\Office\\14.0\\Word\\File MRU", 0, _winreg.KEY_ALL_ACCESS)
        count = 0
        while True:
            name, value, type = _winreg.EnumValue(_key2, count)
            print name + " : " + value
            count += 1 
    except  WindowsError:
        pass




def Excel():
    _reg = _winreg.ConnectRegistry(None, _winreg.HKEY_CURRENT_USER)
    
    try:
        _key = _winreg.OpenKey(_reg, r"Software\\Microsoft\\Office\\15.0\\Excel\\User MRU\\LiveId_1E760FAA55C5054F9D13A24FE9D349E16F885C45D07F281A1EB94290DB8AC76F\\File MRU", 0, _winreg.KEY_ALL_ACCESS)
        count = 0
        while True:
            name, value, type = _winreg.EnumValue(_key, count)
            print name + " : " + value
            count += 1
    except  WindowsError:
        pass

    try:
        _key2 = _winreg.OpenKey(_reg, r"Software\\Microsoft\\Office\\14.0\\Excel\\File MRU", 0, _winreg.KEY_ALL_ACCESS)
        count = 0
        while True:
            name, value, type = _winreg.EnumValue(_key2, count)
            print name + " : " + value
            count += 1 
    except  WindowsError:
        pass



def PowerPoint( ):
    _reg = _winreg.ConnectRegistry(None, _winreg.HKEY_CURRENT_USER)

    try:
        _key = _winreg.OpenKey(_reg, r"Software\\Microsoft\\Office\\15.0\\PowerPoint\\User MRU\\LiveId_1E760FAA55C5054F9D13A24FE9D349E16F885C45D07F281A1EB94290DB8AC76F\\File MRU", 0, _winreg.KEY_ALL_ACCESS)
        count = 0
        while True:
            name, value, type = _winreg.EnumValue(_key, count)
            print name + " : " + value
            count += 1 
    except  WindowsError:
        pass

    try:
        _key2 = _winreg.OpenKey(_reg, r"Software\\Microsoft\\Office\\14.0\\PowerPoint\\File MRU", 0, _winreg.KEY_ALL_ACCESS)
        count = 0
        while True:
            name, value, type = _winreg.EnumValue(_key2, count)
            print name + " : " + value
            count += 1 
    except  WindowsError:
        pass
 
print ""
print ""
print "=============Word============="
Word()
print ""
print ""
print "=============Excel============="
Excel()
print ""
print ""
print "=============PowerPoint============="
PowerPoint()


