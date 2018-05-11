#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 한글파일의 최근 기록을 레지스트리로부터 가져오는 예제 코드
'''
import os
import sys
import _winreg

def main( ):
    _reg = _winreg.ConnectRegistry(None, _winreg.HKEY_CURRENT_USER)
    _key = _winreg.OpenKey(_reg, r"Software\\HNC\\Hwp\\9.0\\HwpFrame_KOR\\RecentFile", 0, _winreg.KEY_ALL_ACCESS)

    try:
        count = 0
        while True:
            name, value, type = _winreg.EnumValue(_key, count)

            if isinstance(value, int):
                print ""
            else:
                print name + " : " + value.decode('UTF-16').encode('cp949')

            count += 1

    except WindowsError:
        pass
    
if __name__ == '__main__':
    main()
