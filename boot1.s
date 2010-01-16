	.file	"boot1.c"
#APP
	.code16gcc
#NO_APP
	.text
	.type	printString, @function
printString:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	16(%ebp), %eax
	movb	%al, -8(%ebp)
#APP
	movw $0x1301, %ax
	movw $0x0007, %bx
	movw 12(%ebp), %cx
	movb $0, %dl
	movb -8(%ebp), %dh
	movl 8(%ebp), %ebp
	int $0x10
#NO_APP
	addl	$4, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	printString, .-printString
	.section	.rodata
.LC0:
	.string	"Start loading"
	.text
.globl c_entry
	.type	c_entry, @function
c_entry:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$20, 8(%esp)
	movl	$13, 4(%esp)
	movl	$.LC0, (%esp)
	call	printString
	movl	$21, 8(%esp)
	movl	$3, 4(%esp)
	movl	$32768, (%esp)
	call	printString
	movl	$1, 16(%esp)
	movl	$1, 12(%esp)
	movl	$128, 8(%esp)
	movl	$32768, 4(%esp)
	movl	$1984, (%esp)
	call	__readSectors
	movl	$22, 8(%esp)
	movl	$3, 4(%esp)
	movl	$32768, (%esp)
	call	printString
.L4:
	jmp	.L4
	.size	c_entry, .-c_entry
	.type	__readSectors, @function
__readSectors:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movw	%ax, -24(%ebp)
	movw	%dx, -28(%ebp)
	movl	-8(%ebp), %eax
	movb	$16, (%eax)
	movl	-8(%ebp), %eax
	movb	$0, 1(%eax)
	movl	24(%ebp), %eax
	movl	%eax, %edx
	movl	-8(%ebp), %eax
	movw	%dx, 2(%eax)
	movl	-8(%ebp), %edx
	movzwl	-24(%ebp), %eax
	movw	%ax, 6(%edx)
	movl	-8(%ebp), %edx
	movzwl	-28(%ebp), %eax
	movw	%ax, 4(%edx)
	movl	20(%ebp), %eax
	movl	$0, %edx
	movl	-8(%ebp), %ecx
	movl	%eax, 8(%ecx)
	movl	%edx, 12(%ecx)
#APP
	movl -8(%ebp), %esi
	movb $0x42, %ah
	movb 16(%ebp), %dl
	int $0x13
	
#NO_APP
	addl	$24, %esp
	popl	%esi
	popl	%ebp
	ret
	.size	__readSectors, .-__readSectors
	.ident	"GCC: (GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4)"
	.section	.note.GNU-stack,"",@progbits
