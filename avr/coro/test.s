.data
format:
	.string "EBP: %X\nESP: %X\n"

.text
.global stackPrint
stackPrint:
	pushl %ebp
	movl %esp, %ebp

	pushl %esp
	pushl %ebp

	pushl $format

	call printf

	#(leave)set esp = ebp then pop ebp off the stack (esp + 4)
	movl %ebp, %esp
	popl %ebp

	ret