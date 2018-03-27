; asm ==> calc.exe를 32비트 환경에서 실행시키는 코드
; 		  ml.exe /c /coff /Zi calc.asm
;         link.exe /subsystem:windows /debug calc.obj
.386
.model flat,stdcall
option casemap :none

include c:\masm32\include\windows.inc
include c:\masm32\include\user32.inc
include c:\masm32\include\kernel32.inc
includelib c:\masm32\lib\user32.lib
includelib c:\masm32\lib\kernel32.lib

.data
.code

Start:

push ebp
mov ebp,esp
sub esp, 0ch

;calc.exe
mov dword ptr [ebp-0ch], 636c6163h
mov dword ptr [ebp-8h], 6578652Eh
mov dword ptr [ebp-4h], 00000000h

;WinExec("calc.exe", NULL)
xor ecx,ecx
push ecx
lea eax, [ebp-0ch] ; calc.exe
push eax
mov eax, 74E83140h ; WinExec Address
call eax

;ExitProcess(1)
mov eax,1
push eax
mov eax, 74E43CC0h ;ExitProcess Address
call eax

end Start








