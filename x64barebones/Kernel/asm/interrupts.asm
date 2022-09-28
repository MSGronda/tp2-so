
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _exception0Handler
GLOBAL _exception6Handler

GLOBAL _swIntHandler

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN swIntDispatcher

EXTERN getRSP				; multitasking.c
EXTERN getSS 				; multitasking.c
EXTERN moveToNextTask		; multitasking.c
EXTERN multitaskingEnabled
EXTERN hasTimeLeft
EXTERN decreaseTimeLeft
EXTERN has_or_decrease_time 

GLOBAL saveAndForceNextTask
GLOBAL forceNextTask
GLOBAL forceCurrentTask

SECTION .data

multi_tasking_enabled db 0

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 			; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro


%macro exceptionHandler 1
	pushState

	mov rsi, rsp				; le paso comienzo del register dump
	mov rdi, %1 				; pasaje de parametro
	call exceptionDispatcher

	popState
	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5


;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

;Invalid Opcode Exception
_exception6Handler:
	exceptionHandler 6

haltcpu:
	cli
	hlt
	ret


; = = = = = Interrupts de software = = = = = ;

_swIntHandler:

	push r9
	mov r9, r8
	mov r8, r10
	mov rcx, rdx
	mov rdx, rsi
	mov rsi, rdi
	mov rdi, rax 

	call swIntDispatcher 
	pop r9

	iretq
; = = = = = = = = = = = = = = = = = = = = = ;

;  = = = = = = Multitasking = = = = = = 

saveAndForceNextTask:
	; ya tiene en rdi y rsi los parametros para moveToNextTask
forceNextTask:		
	call moveToNextTask		; me muevo al proximo
forceCurrentTask:
	call getRSP				; rax tiene el RSP del proximo task
	mov rsp,rax
	call getSS	
	mov ss, rax	
	popState				; popeo los registros para el proximo task
	iretq					; popeo el IP, CS, RSP, SS, FLAGS, .... para el proximo task	


enable_multi_tasking:
	mov BYTE [multi_tasking_enabled], 1
	jmp tickHandle
	
; = = = = = = = = = = = = = = = = = = =

; = = = = = = Timer Tick = = = = = = = =
_irq00Handler:
	pushState

	; check if multitasking is enabled
	cmp BYTE [multi_tasking_enabled], 1
	jne enable_multi_tasking

	call has_or_decrease_time
	cmp eax, 1
	je tickHandle

	switchTask:
		mov rdi, rsp 			; pongo los actuales asi despues puedo volver adonde estaba
		mov rsi, ss
		call moveToNextTask		
		call getRSP				; rax tiene el SP del proximo stack
		mov rsp,rax
		call getSS	
		mov ss, rax	

	tickHandle:
	mov rdi, 0				
	call irqDispatcher

	mov al, 20h	
	out 20h, al 								; signal pic EOI (End of Interrupt)

	popState									
	iretq										

; = = = = = = = = = = = = = = = = = = =

; = = = = = = = = Keyboard = = = = = = = = 
_irq01Handler:
	pushState
	
	mov rdi, 1
	mov rsi, rsp  			; puntero a principio de dump de registros
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
; = = = = = = = = = = = = = = = = = = = = 
