; binsh2.s
BITS 32
global _start

_start:
    mov eax, 11
    jmp buf
setebx:
    pop ebx
    xor ecx, ecx
    xor edx, edx
    int 0x80
	
buf:
    call setebx
    db '/bin/sh', 0
