.data
format:
	.string "EBP: %d\nESP: %d\n"

.text
.global _stackPrint
_stackPrint:
	pushl %ebp
	movl %esp, %ebp

	pushl %esp
	pushl %ebp

	pushl $format

	call _printf
	movl $0,%eax
	leave
	RET
