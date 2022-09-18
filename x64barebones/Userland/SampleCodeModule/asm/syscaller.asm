GLOBAL syscaller

section .text

;ASM: rax - rdi - rsi - rdx
;C:   rdi - rsi - rdx - rcx

syscaller:
    push rbp
    mov rbp, rsp

    mov rax, rdi        ; no hace falta preservar registros
    mov rdi, rsi
    mov rsi, rdx
    mov rdx, rcx


	int 80h

    mov rsp, rbp
    pop rbp
    ret
