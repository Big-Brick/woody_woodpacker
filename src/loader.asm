section .text

loader_start:
    push rax
    push rbx
    push rcx
    push rdx
    push rdi
    push rsi
    mov rax, 1 ; write
    mov rdi, 1 ; stdout
    lea rsi, [rel msg] ; &msg
    mov rdx, 16 ; size
    syscall
    pop rsi
    pop rdi
    pop rdx
    pop rcx
    pop rbx
    pop rax
 jumpaddr:
    mov r15, 0x400430 ; ptr + .text->offset + jumpaddr_off + 1
    jmp r15
    msg db "....WOODY....", 0xA, 0x0, 0x0
loader_end:
