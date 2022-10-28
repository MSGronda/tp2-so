GLOBAL syscaller

section .text

;ASM: rax - rdi - rsi - rdx - r10
;C:   rdi - rsi - rdx - rcx - r8

syscaller:
    push rbp
    mov rbp, rsp

    mov rax, rdi        ; no hace falta preservar registros
    mov rdi, rsi
    mov rsi, rdx
    mov rdx, rcx
    mov r10, r8


	int 80h

    mov rsp, rbp
    pop rbp
    ret
