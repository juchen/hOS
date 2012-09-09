	.file	"printf-stdarg.c"
	.text
	.type	printchar, @function
printchar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	cmpl	$0, 8(%ebp)
	je	.L2
	movl	8(%ebp), %eax
	movl	(%eax), %edx
	movl	12(%ebp), %eax
	movb	%al, (%edx)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	jmp	.L5
.L2:
	movl	12(%ebp), %eax
	movl	%eax, (%esp)
	call	putchar
.L5:
	leave
	ret
	.size	printchar, .-printchar
	.type	prints, @function
prints:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$0, -16(%ebp)
	movl	$32, -12(%ebp)
	cmpl	$0, 16(%ebp)
	jle	.L7
	movl	$0, -8(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	jmp	.L9
.L10:
	addl	$1, -8(%ebp)
	addl	$1, -4(%ebp)
.L9:
	movl	-4(%ebp), %edx
	movzbl	(%edx), %eax
	testb	%al, %al
	jne	.L10
	movl	-8(%ebp), %eax
	cmpl	16(%ebp), %eax
	jl	.L12
	movl	$0, 16(%ebp)
	jmp	.L14
.L12:
	movl	-8(%ebp), %edx
	subl	%edx, 16(%ebp)
.L14:
	movl	20(%ebp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L7
	movl	$48, -12(%ebp)
.L7:
	movl	20(%ebp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L20
	jmp	.L18
.L19:
	movl	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	printchar
	addl	$1, -16(%ebp)
	subl	$1, 16(%ebp)
.L18:
	cmpl	$0, 16(%ebp)
	jg	.L19
	jmp	.L20
.L21:
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al,%eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	printchar
	addl	$1, -16(%ebp)
	addl	$1, 12(%ebp)
.L20:
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L21
	jmp	.L23
.L24:
	movl	-12(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	printchar
	addl	$1, -16(%ebp)
	subl	$1, 16(%ebp)
.L23:
	cmpl	$0, 16(%ebp)
	jg	.L24
	movl	-16(%ebp), %eax
	leave
	ret
	.size	prints, .-prints
	.type	printi, @function
printi:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$72, %esp
	movl	$0, -28(%ebp)
	movl	$0, -24(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -20(%ebp)
	cmpl	$0, 12(%ebp)
	jne	.L28
	movb	$48, -12(%ebp)
	movb	$0, -11(%ebp)
	movl	28(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	24(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	prints
	movl	%eax, -40(%ebp)
	jmp	.L30
.L28:
	cmpl	$0, 20(%ebp)
	je	.L31
	cmpl	$10, 16(%ebp)
	jne	.L31
	cmpl	$0, 12(%ebp)
	jns	.L31
	movl	$1, -28(%ebp)
	movl	12(%ebp), %eax
	negl	%eax
	movl	%eax, -20(%ebp)
.L31:
	leal	-12(%ebp), %eax
	addl	$11, %eax
	movl	%eax, -36(%ebp)
	movl	-36(%ebp), %edx
	movb	$0, (%edx)
	jmp	.L35
.L36:
	movl	16(%ebp), %eax
	movl	%eax, -44(%ebp)
	movl	-20(%ebp), %eax
	movl	$0, %edx
	divl	-44(%ebp)
	movl	%edx, %eax
	movl	%eax, -32(%ebp)
	cmpl	$9, -32(%ebp)
	jle	.L37
	movl	32(%ebp), %eax
	subl	$58, %eax
	addl	%eax, -32(%ebp)
.L37:
	subl	$1, -36(%ebp)
	movzbl	-32(%ebp), %eax
	addl	$48, %eax
	movl	-36(%ebp), %edx
	movb	%al, (%edx)
	movl	16(%ebp), %eax
	movl	%eax, -44(%ebp)
	movl	-20(%ebp), %eax
	movl	$0, %edx
	divl	-44(%ebp)
	movl	%eax, -44(%ebp)
	movl	-44(%ebp), %edx
	movl	%edx, -20(%ebp)
.L35:
	cmpl	$0, -20(%ebp)
	jne	.L36
	cmpl	$0, -28(%ebp)
	je	.L40
	cmpl	$0, 24(%ebp)
	je	.L42
	movl	28(%ebp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L42
	movl	$45, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	printchar
	addl	$1, -24(%ebp)
	subl	$1, 24(%ebp)
	jmp	.L40
.L42:
	subl	$1, -36(%ebp)
	movl	-36(%ebp), %eax
	movb	$45, (%eax)
.L40:
	movl	28(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	24(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-36(%ebp), %edx
	movl	%edx, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	prints
	movl	-24(%ebp), %edx
	addl	%eax, %edx
	movl	%edx, -40(%ebp)
.L30:
	movl	-40(%ebp), %eax
	leave
	ret
	.size	printi, .-printi
	.section	.rodata
.LC0:
	.string	"(null)"
	.text
	.type	print, @function
print:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$72, %esp
	movl	$0, -24(%ebp)
	jmp	.L47
.L48:
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$37, %al
	jne	.L49
	addl	$1, 12(%ebp)
	movl	$0, -28(%ebp)
	movl	-28(%ebp), %eax
	movl	%eax, -32(%ebp)
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	je	.L51
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$37, %al
	je	.L49
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$45, %al
	jne	.L56
	addl	$1, 12(%ebp)
	movl	$1, -28(%ebp)
	jmp	.L56
.L57:
	addl	$1, 12(%ebp)
	orl	$2, -28(%ebp)
.L56:
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$48, %al
	je	.L57
	jmp	.L59
.L60:
	movl	-32(%ebp), %eax
	sall	$2, %eax
	addl	-32(%ebp), %eax
	addl	%eax, %eax
	movl	%eax, -32(%ebp)
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al,%eax
	subl	$48, %eax
	addl	%eax, -32(%ebp)
	addl	$1, 12(%ebp)
.L59:
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$47, %al
	jle	.L61
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$57, %al
	jle	.L60
.L61:
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$115, %al
	jne	.L63
	movl	16(%ebp), %edx
	leal	4(%edx), %eax
	movl	%eax, 16(%ebp)
	movl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, -20(%ebp)
	cmpl	$0, -20(%ebp)
	je	.L65
	movl	-20(%ebp), %edx
	movl	%edx, -36(%ebp)
	jmp	.L67
.L65:
	movl	$.LC0, -36(%ebp)
.L67:
	movl	-28(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-32(%ebp), %edx
	movl	%edx, 8(%esp)
	movl	-36(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	prints
	addl	%eax, -24(%ebp)
	jmp	.L68
.L63:
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$100, %al
	jne	.L69
	movl	16(%ebp), %edx
	leal	4(%edx), %eax
	jmp .
	movl	%eax, 16(%ebp)
	movl	%edx, %eax
	movl	(%eax), %eax
	movl	$97, 24(%esp)
	movl	-28(%ebp), %edx
	movl	%edx, 20(%esp)
	movl	-32(%ebp), %edx
	movl	%edx, 16(%esp)
	movl	$1, 12(%esp)
	movl	$10, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	printi
	addl	%eax, -24(%ebp)
	jmp	.L68
.L69:
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$120, %al
	jne	.L71
	movl	16(%ebp), %edx
	leal	4(%edx), %eax
	movl	%eax, 16(%ebp)
	movl	%edx, %eax
	movl	(%eax), %eax
	movl	$97, 24(%esp)
	movl	-28(%ebp), %edx
	movl	%edx, 20(%esp)
	movl	-32(%ebp), %edx
	movl	%edx, 16(%esp)
	movl	$0, 12(%esp)
	movl	$16, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	printi
	addl	%eax, -24(%ebp)
	jmp	.L68
.L71:
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$88, %al
	jne	.L73
	movl	16(%ebp), %edx
	leal	4(%edx), %eax
	movl	%eax, 16(%ebp)
	movl	%edx, %eax
	movl	(%eax), %eax
	movl	$65, 24(%esp)
	movl	-28(%ebp), %edx
	movl	%edx, 20(%esp)
	movl	-32(%ebp), %edx
	movl	%edx, 16(%esp)
	movl	$0, 12(%esp)
	movl	$16, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	printi
	addl	%eax, -24(%ebp)
	jmp	.L68
.L73:
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$117, %al
	jne	.L75
	movl	16(%ebp), %edx
	leal	4(%edx), %eax
	movl	%eax, 16(%ebp)
	movl	%edx, %eax
	movl	(%eax), %eax
	movl	$97, 24(%esp)
	movl	-28(%ebp), %edx
	movl	%edx, 20(%esp)
	movl	-32(%ebp), %edx
	movl	%edx, 16(%esp)
	movl	$0, 12(%esp)
	movl	$10, 8(%esp)
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	printi
	addl	%eax, -24(%ebp)
	jmp	.L68
.L75:
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$99, %al
	jne	.L68
	movl	16(%ebp), %edx
	leal	4(%edx), %eax
	movl	%eax, 16(%ebp)
	movl	%edx, %eax
	movl	(%eax), %eax
	movb	%al, -2(%ebp)
	movb	$0, -1(%ebp)
	movl	-28(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-32(%ebp), %edx
	movl	%edx, 8(%esp)
	leal	-2(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	prints
	addl	%eax, -24(%ebp)
	jmp	.L68
.L49:
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al,%eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	printchar
	addl	$1, -24(%ebp)
.L68:
	addl	$1, 12(%ebp)
.L47:
	movl	12(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L48
.L51:
	cmpl	$0, 8(%ebp)
	je	.L79
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movb	$0, (%eax)
.L79:
	movl	-24(%ebp), %eax
	leave
	ret
	.size	print, .-print
.globl printf
	.type	printf, @function
printf:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	leal	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$0, (%esp)
	call	print
	leave
	ret
	.size	printf, .-printf
.globl sprintf
	.type	sprintf, @function
sprintf:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	leal	16(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	8(%ebp), %eax
	movl	%eax, (%esp)
	call	print
	leave
	ret
	.size	sprintf, .-sprintf
	.ident	"GCC: (GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4)"
	.section	.note.GNU-stack,"",@progbits
