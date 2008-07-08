.data
format:
	.string "hello"

.text
.global _stackPrint
_stackPrint:
	pushl %ebp
	movl %esp,%ebp
	pushl (format)
#	movl 8(%ebp),%edx
#	addl $10,%edx
	call _printf
	movl $0,%eax
	leave
	RET
