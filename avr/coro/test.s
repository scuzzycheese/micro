.data
format:
	.string "hello"

.text
.global _stackPrint
_stackPrint:
	pushl %ebp
	movl %esp,%ebp
	pushl $format
	call _printf
	movl $0,%eax
	leave
	RET
