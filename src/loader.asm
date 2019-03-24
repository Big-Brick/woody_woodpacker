section .text

loader:
    msg db "....WOODY....", 0xA, 0x0, 0x0

_decrypt:

_loader_ent:
    mov rax, 1 ; write
    mov rdi, 1 ; stdout
    lea rsi, [rel msg]
    mov rdx, 16
    syscall

 jumpaddr:
    mov rax, 0x400430 ; ptr + .text->offset + jumpaddr_off + 1
    jmp rax
