.data
format:
	.string "EBP: %X\nESP: %X\n"

.text
.global _stackPrint
_stackPrint:
	pushl %ebp
	movl %esp, %ebp

	pushl %esp
	pushl %ebp

	pushl $format

	call _printf

	#(leave)set esp = ebp then pop ebp off the stack (esp + 4)
	movl %ebp, %esp
	popl %ebp

	ret
