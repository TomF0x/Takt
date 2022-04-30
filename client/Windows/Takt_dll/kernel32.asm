.code

	GetKernel32BaseAddress proc

		mov rax, GS:[60h]
		mov rax, [rax + 18h]
		mov rax, [rax + 20h]
		mov rax, [rax]
		mov rax, [rax]
		mov rax, [rax + 20h]
		ret

	GetKernel32BaseAddress endp

END