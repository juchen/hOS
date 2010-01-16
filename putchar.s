	.file	"putchar.cpp"
	.text
	.align 2
.globl _ZN6ScreenC2Ev
	.type	_ZN6ScreenC2Ev, @function
_ZN6ScreenC2Ev:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	$0, (%eax)
	movl	8(%ebp), %eax
	movl	$80, 4(%eax)
	movl	8(%ebp), %eax
	movl	$25, 8(%eax)
	movl	8(%ebp), %eax
	movb	$7, 12(%eax)
	movl	8(%ebp), %eax
	movl	%eax, screen
	popl	%ebp
	ret
	.size	_ZN6ScreenC2Ev, .-_ZN6ScreenC2Ev
	.align 2
.globl _ZN6ScreenC1Ev
	.type	_ZN6ScreenC1Ev, @function
_ZN6ScreenC1Ev:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	$0, (%eax)
	movl	8(%ebp), %eax
	movl	$80, 4(%eax)
	movl	8(%ebp), %eax
	movl	$25, 8(%eax)
	movl	8(%ebp), %eax
	movb	$7, 12(%eax)
	movl	8(%ebp), %eax
	movl	%eax, screen
	popl	%ebp
	ret
	.size	_ZN6ScreenC1Ev, .-_ZN6ScreenC1Ev
	.align 2
.globl _ZN6Screen7setAttrEh
	.type	_ZN6Screen7setAttrEh, @function
_ZN6Screen7setAttrEh:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	12(%ebp), %eax
	movb	%al, -4(%ebp)
	movl	8(%ebp), %edx
	movzbl	-4(%ebp), %eax
	movb	%al, 12(%edx)
	leave
	ret
	.size	_ZN6Screen7setAttrEh, .-_ZN6Screen7setAttrEh
	.align 2
.globl _ZN6Screen7putcharEi
	.type	_ZN6Screen7putcharEi, @function
_ZN6Screen7putcharEi:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	subl	$4, %esp
	movl	12(%ebp), %eax
	cmpb	$10, %al
	jne	.L8
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	addl	%eax, %eax
	movl	%eax, -12(%ebp)
	movl	%edx, %eax
	movl	$0, %edx
	divl	-12(%ebp)
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	imull	%edx, %eax
	addl	%eax, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	jmp	.L11
.L8:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, %ecx
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	imull	%edx, %eax
	addl	%eax, %eax
	movl	%eax, -12(%ebp)
	movl	%ecx, %eax
	movl	$0, %edx
	divl	-12(%ebp)
	movl	%edx, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, %esi
	movl	12(%ebp), %eax
	movl	%eax, %ecx
	movl	8(%ebp), %eax
	movzbl	12(%eax), %edx
#APP
	push %ds
	mov $32, %ax
	mov %ax, %ds
	mov %esi, %ebx
	movb %cl, (%ebx)
	movb %dl, 1(%ebx)
	pop %ds
	
#NO_APP
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	2(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
.L11:
	addl	$4, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	_ZN6Screen7putcharEi, .-_ZN6Screen7putcharEi
	.align 2
.globl _ZN6Screen3clsEv
	.type	_ZN6Screen3clsEv, @function
_ZN6Screen3clsEv:
	jmp .
	pushl	%ebp
	movl	%esp, %ebp
#APP
	mov $0xC0000011, %edx
	
#NO_APP
.L13:
	jmp	.L13
	.size	_ZN6Screen3clsEv, .-_ZN6Screen3clsEv
	.align 2
.globl putchar
	.type	putchar, @function
putchar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	screen, %edx
	movl	8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	_ZN6Screen7putcharEi
	movl	$0, %eax
	leave
	ret
	.size	putchar, .-putchar
	.align 2
.globl puts
	.type	puts, @function
puts:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	$0, -4(%ebp)
	jmp	.L18
.L19:
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al,%eax
	movl	%eax, (%esp)
	call	putchar
	addl	$1, -4(%ebp)
	addl	$1, 8(%ebp)
.L18:
	cmpl	$0, 8(%ebp)
	jne	.L19
	movl	-4(%ebp), %eax
	leave
	ret
	.size	puts, .-puts
	.local	screen
	.comm	screen,4,4
	.ident	"GCC: (GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4)"
	.section	.note.GNU-stack,"",@progbits
