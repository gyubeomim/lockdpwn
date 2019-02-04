from _winreg import *
import sys

varSubKey = "SOFTWARE\Microsoft\Windows NT\CurrentVersion\ProfileList"
varReg = ConnectRegistry(None, HKEY_LOCAL_MACHINE)
varKey = OpenKey(varReg, varSubKey)

for i in range(1024):                                           
    try:
        varSubKey2 = "%s\\%s"%(varSubKey,keyname)
        varKey2 = OpenKey(varReg, varSubKey2)
        try:
            for j in range(1024):
                n,v,t = EnumValue(varKey2,j)
                if("ProfileImagePath" in n and "Users" in v):
                    print v
        except:
            errorMsg = "Exception Inner:", sys.exc_info()[0]
            #print errorMsg
        CloseKey(varKey2)
    except:                                               
        errorMsg = "Exception Outter:", sys.exc_info()[0]
        break          
CloseKey(varKey)                                                                                 #(9)
CloseKey(varReg)
