#!/usr/bin/env pytohn
#-*- coding: utf-8 -*-
'''
	python ==> 파이썬해킹프로그래밍,
'''
from ctypes import *
import sys

# pyemu 의 경로를 설정한다
sys.path.append("C:\Python27\Lib\site-packages\pyemu")
sys.path.append("C:\Python27\Lib\site-packages\pyemu\lib")

from PyEmu import PEPyEmu
# 커맨드라인 파라미터

exename = sys.argv[1]
outputfile = sys.argv[2]

# 에뮬레이터 객체를 초기화 한다
emu = PEPyEmu()

if exename:
    # PyEmu 에 바이너리를 로드한다
    if not emu.load(exename):
        print "[!] Problem loading %s" % exename
        sys.exit(2)

else:
    print "[!] Blank filename specified"
    sys.exit(3)


# 라이브러리 핸들러를 설정한다.
emu.set_library_handler("LoadLibraryA", loadlibrary)

emu.set_library_handler("GetProcAddress", getprocaddress)

emu.set_library_handler("VirtualProtect",virtualprotect)

# 바이너리를 덤프하기 위해 실제 엔트리 포인트에 브레이크 포인트를 설정한다.

emu.set_mnemonic_handler("jmp",jmp_handler)

# 엔트리포인트부터 실행을 시작한다

emu.execute(start=emu.entry_point)

'''
HMODULE WINAPI LoadLibrary(
__in LPCTSTR lpFileName
);

'''

def loadlibrary(name,address):
    # dll 이름을 추출한다.
    dllname= emu.get_memory_string(emu.get_memory(emu.get_register("ESP")+4))

    # 실제 LoadLibrary 함수를 호출하고 핸들을 리턴 값으로 설정한다
    dllhandle = windll.kernel32.LoadLibrary(dllname)
    emu.set_register("EAX",dllhandle)

    # 스택을 정리하고 리턴한다

    return_address = emu.get_memory(emu.get_register("ESP"))
    emu.set_register("ESP",emu.get_register("ESP")+8)
    emu.set_register("EIP",return_address)
    return True
'''
FARPROC WINAPI GetProcAddress(
__in HMODULE hModule,
__in LPCSTR lpProcName
);
'''

def getprocaddress(name,address):
    # 전달 된 파라미터에서 핸들과 함수이름을 추출한다.
    handle = emu.get_memory(emu.get_register("ESP") +4)
    proc_name = emu.get_memory(emu.get_register("ESP")+8)

    # lpProcName 은 이름이나 서수일 수 있다.
    # top word 값이 NULL이면 lpProcName은 서수가 된다.

    if (proc_name >> 16):
        procname = emu.get_memory_string(emu.get_memory(\
            emu.get_register("ESP")+8))
    else:
        procname = arg2

    # 함수를 에뮬레이터에 추가한다.
    emu.os.add_library(handle,procname)
    import_address = emu.os.get_library_address(procname)
    # 임포트 어드레스를 리턴값으로 설정한다.

    emu.set_register("EAX",import_address)

    #스택을 정리하고 리턴한다

    return_address = emu.get_memory(emu.get_register("ESP"))
    emu.set_register("ESP",emu.get_register("ESP")+8)
    emu.set_register("EIP",return_address)
    return True

'''
BOOL WINAPI VirtualProtect(
__in LPVOID lpAddress,
__in SIZE_T dwsize,
__in DWORD flNewProtect,
__out PDWORD lpflOldProtect
);
'''

def virtualprotect(name,address):
    # 리턴값으로 TRUE 를 설정한다
    emu.set_register("EAX",1)
    # 스택을 정리하고 리턴한다.

    return_address = emu.get_memory(emu.get_register("ESP"))
    emu.set_register("ESP", emu.get_register("ESP")+16)
    emu.set_register("EIP",return_address)
    return True

    # 언팩 루틴이 종료되면 oep로의 jmp명령을 처리한다ㅣ


def jmp_handler(emu,mnemonic, eip,op1,op2,op3):
    # UPX1 섹션

    if eip< emu.sections["UPX1"]["base"]:
        print "[*] We are jumping out of the unpacking routine"
        print "[*] OEP = 0x%08x" % eip

        # 언팩 된 바이너리를 디스크에 저장한다
        dump_unpacked(emu)

        # 에뮬레이터를 정지시킨다.
        emu.emulating = False
        return True


def dump_unpacked(eum):
    global outputfile
    fh = open(outputfile, "wb")

    print '[*] Dumping UPX0 Section'
    base = emu.sections["UPX0"]["base"]
    length = emu.sections["UPX0"]["vsize"]

    print "[*] Base: 0x%08x Vsize: %08x" % (base,length)

    for x in range(length):
        fh.write("%c" % emu.get_memory(base +x,1))

    print "[*] Dumping UPX1 Section"

    base = emu.sections["UPX1"]["base"]
    length = emu.sections["UPX1"]["vsize"]

    print "[*] Base: 0x%08x Vsize: %08x" % (base,length)

    for x in range(length):
        fh.write("%c" % emu.get_memory(base+x , 1))
    print "[*] Finished"
