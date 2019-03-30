segment .text
	global _start
;	extern _xxtea_decrypt

_start:
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
;    call _xxtea_decrypt
    pop rsi
    pop rdi
    pop rdx
    pop rcx
    pop rbx
    pop rax
 jumpaddr:
    mov r15, 0x40043000400430 ; ptr + .text->offset + jumpaddr_off + 2
    jmp r15
    msg db "....WOODY....", 0xA, 0x0, 0x0
loader_end:
