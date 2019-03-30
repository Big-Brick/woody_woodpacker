segment .text
	global _start
	extern xxtea_decrypt

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
    mov rax, 0x7d ; sys_mprotect
text_addr:
    mov rdi, 0x7700550033001100 ; addr
text_len:
    mov rsi, 0x7700550033001100 ; len
    mov rdx, 7
    syscall
    lea rdx, [rel key] ; &key
    call xxtea_decrypt
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
    key db "1234567890abcdef"
loader_end:
