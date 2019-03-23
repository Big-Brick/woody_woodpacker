[BITS 64]

global loader:function
global sloader:data
global _loader:data ; offset to loader entry point

section .text

loader:
    msg db "....WOODY....", 0xA, 0x0, 0x0
    sloader dd _loader_end - loader
    _loader dd _loader_ent - loader

_decrypt:

_loader_ent:
    mov rax, 1 ; write
    mov rdi, 1 ; stdout
    lea rsi, [rel msg]
    mov rdx, 16
    syscall
;    mov rax, 60
;    mov rdi, 0
;    syscall

;    lea rax, [rel text]
    jmp 0xffffffff
;    text  dd 0x0 ; .text section
;    stext dd 0x0 ; .text section size
_loader_end:
