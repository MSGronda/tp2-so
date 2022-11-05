GLOBAL readKeyboard
GLOBAL getRTC
GLOBAL _xadd
GLOBAL _xchg


section .text

; returns rsp value before the function call
_rsp:	
	mov rax, rsp
	add rax, 8
	ret



; IMPORTANTE: usar eax y no rax al ser un unsigned int 

_xadd:
	mov rax, rdi
	lock xadd [rsi], eax
	ret

_xchg:
	mov rax, rsi
	xchg [rdi], eax
	ret


readKeyboard:
	push rbp
	mov rbp, rsp

	mov ah, 1  					; 0000 0001
	in al, 64h					; status del teclado/8042
	and al, ah					; ???? bitwise(&)  0001 ; me quedo solo con el ultimo bit
	cmp al, 1 					; para poder recibir, bit 0 de status tiene que estar en 1
	jne no_key_recieved			; sino, sigo esperando hasta que sea 0

	mov rax, 0
	in al, 60h					; leo letra
	jmp end

	no_key_recieved:
		mov rax, -1				; caso letra no leida
		

	end:

	mov rsp, rbp
	pop rbp
	ret

;; hace lo que dice
getRTC:
        push rbp
        mov rbp, rsp

        xor rax, rax            ; Limpio rax

        cli
        mov ax, di              
        out 70h, al             ; Elegimos lo que queremos escribir/leer
        in al, 71h              ; lo leemos
        sti

        mov rsp, rbp
        pop rbp
        ret
        
