	.file	"isr.c"
	.section	.rodata
.LC0:
	.string	"\n\nTimer Interrupt!\n"
	.text
.globl timerISR
	.type	timerISR, @function
timerISR:
#APP
	push %eax
	push %ebx
	push %ecx
	push %edx
	push %edi
	push %esi
#NO_APP
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$.LC0, (%esp)
	call	puts
	leave
#APP
	pop %esi
	pop %edi
	pop %edx
	pop %ecx
	pop %ebx
	pop %eax
	iret
	
	.size	timerISR, .-timerISR
	.ident	"GCC: (GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4)"
	.section	.note.GNU-stack,"",@progbits
