.data
format:
	.string "EBP: %d\nESP: %d\nEDI: %d\n"

.text
.global _stackPrint
_stackPrint:
	pushl %ebp
	movl %esp, %ebp

	#movl %edi, %eax
	#pushl %eax
	pushl %edi

	#movl %esp, %eax
	#pushl %eax
	pushl %esp

	#movl %ebp, %eax
	#pushl %eax
	pushl %ebp

	pushl $format

	call _printf
	movl $0,%eax
	leave
	RET
