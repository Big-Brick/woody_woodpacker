section .text

loader_start:
    push rax
    push rdi
    push rsi
    push rdx
    mov rax, 1 ; write
    mov rdi, 1 ; stdout
    lea rsi, [rel msg]
    mov rdx, 16
    syscall
 jumpaddr:
    pop rdx
    pop rsi
    pop rdi
    pop rax
    mov r15, 0x400430 ; ptr + .text->offset + jumpaddr_off + 1
    jmp r15
    msg db "....WOODY....", 0xA, 0x0, 0x0
loader_end:
