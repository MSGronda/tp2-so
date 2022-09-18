GLOBAL divError
GLOBAL opCodeError


divError:
	mov rdx, 0
	mov rax, 0
	mov rcx, 0xdead00
	div rdx

opCodeError:
	mov rax, 0 
	mov rcx, 0xbadc0de00
	ud2