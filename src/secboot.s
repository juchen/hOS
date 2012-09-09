	.file	"secboot.c"
.globl SEG_NULL_SELECTOR
	.section	.rodata
	.align 4
	.type	SEG_NULL_SELECTOR, @object
	.size	SEG_NULL_SELECTOR, 4
SEG_NULL_SELECTOR:
	.zero	4
.globl SEG_CODE_SELECTOR
	.align 4
	.type	SEG_CODE_SELECTOR, @object
	.size	SEG_CODE_SELECTOR, 4
SEG_CODE_SELECTOR:
	.long	8
.globl SEG_DATA_SELECTOR
	.align 4
	.type	SEG_DATA_SELECTOR, @object
	.size	SEG_DATA_SELECTOR, 4
SEG_DATA_SELECTOR:
	.long	16
.globl SEG_STACK_SELECTOR
	.align 4
	.type	SEG_STACK_SELECTOR, @object
	.size	SEG_STACK_SELECTOR, 4
SEG_STACK_SELECTOR:
	.long	24
.globl SEG_VIDEO_SELECTOR
	.align 4
	.type	SEG_VIDEO_SELECTOR, @object
	.size	SEG_VIDEO_SELECTOR, 4
SEG_VIDEO_SELECTOR:
	.long	32
#APP
	.code16gcc
.LC0:
	.string	"In second boot loader\n\rNow\n"
#NO_APP
	.text
.globl c_entry
	.type	c_entry, @function
c_entry:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	$21, 8(%esp)
	movl	$27, 4(%esp)
	movl	$.LC0, (%esp)
	call	printString
	movl	SEG_CODE_SELECTOR, %eax
	shrl	$3, %eax
	sall	$3, %eax
	addl	$segDescTable, %eax
	movl	$0, 12(%esp)
	movl	$391, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	SegmentDescriptor_codeSegSetup
	movl	SEG_DATA_SELECTOR, %eax
	shrl	$3, %eax
	sall	$3, %eax
	addl	$segDescTable, %eax
	movl	$0, 12(%esp)
	movl	$8192, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	SegmentDescriptor_dataSegSetup
	movl	SEG_STACK_SELECTOR, %eax
	shrl	$3, %eax
	sall	$3, %eax
	addl	$segDescTable, %eax
	movl	$0, 12(%esp)
	movl	$392, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	SegmentDescriptor_stackSegSetup
	movl	SEG_VIDEO_SELECTOR, %eax
	shrl	$3, %eax
	sall	$3, %eax
	addl	$segDescTable, %eax
	movl	$0, 12(%esp)
	movl	$3, 8(%esp)
	movl	$753664, 4(%esp)
	movl	%eax, (%esp)
	call	SegmentDescriptor_dataSegSetup
	movw	$39, -6(%ebp)
	movl	$segDescTable, %eax
	movl	%eax, -4(%ebp)
	leal	-6(%ebp), %eax
#APP
	lgdt (%eax)
	
	cli
	in $0x92, %al
	or $0x02, %al
	out %al, $0x92
	
	mov %cr0, %eax
	or $1, %eax
	mov %eax, %cr0
	.code32
	ljmpl $0x08, $pm_entry
	.code16gcc
	
#NO_APP
.L2:
	jmp	.L2
	.size	c_entry, .-c_entry
	.type	SegmentDescriptor_codeSegSetup, @function
SegmentDescriptor_codeSegSetup:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	SegmentDescriptor_setBaseLimitDPL
	movl	8(%ebp), %eax
	movzbl	5(%eax), %eax
	movl	%eax, %edx
	orl	$-104, %edx
	movl	8(%ebp), %eax
	movb	%dl, 5(%eax)
	movl	8(%ebp), %eax
	movzbl	6(%eax), %eax
	movl	%eax, %edx
	orl	$-64, %edx
	movl	8(%ebp), %eax
	movb	%dl, 6(%eax)
	leave
	ret
	.size	SegmentDescriptor_codeSegSetup, .-SegmentDescriptor_codeSegSetup
	.type	SegmentDescriptor_setBaseLimitDPL, @function
SegmentDescriptor_setBaseLimitDPL:
	pushl	%ebp
	movl	%esp, %ebp
	movl	16(%ebp), %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movw	%dx, (%eax)
	movl	12(%ebp), %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movw	%dx, 2(%eax)
	movl	12(%ebp), %eax
	shrl	$16, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movb	%dl, 4(%eax)
	movl	12(%ebp), %eax
	shrl	$24, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movb	%dl, 7(%eax)
	movl	20(%ebp), %eax
	andl	$3, %eax
	movl	%eax, %edx
	sall	$5, %edx
	movl	8(%ebp), %eax
	movb	%dl, 5(%eax)
	movl	16(%ebp), %eax
	shrl	$16, %eax
	movl	%eax, %edx
	andl	$15, %edx
	movl	8(%ebp), %eax
	movb	%dl, 6(%eax)
	popl	%ebp
	ret
	.size	SegmentDescriptor_setBaseLimitDPL, .-SegmentDescriptor_setBaseLimitDPL
	.type	SegmentDescriptor_stackSegSetup, @function
SegmentDescriptor_stackSegSetup:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	SegmentDescriptor_setBaseLimitDPL
	movl	8(%ebp), %eax
	movzbl	5(%eax), %eax
	movl	%eax, %edx
	orl	$-106, %edx
	movl	8(%ebp), %eax
	movb	%dl, 5(%eax)
	movl	16(%ebp), %eax
	shrl	$16, %eax
	andl	$15, %eax
	movl	%eax, %edx
	orl	$-64, %edx
	movl	8(%ebp), %eax
	movb	%dl, 6(%eax)
	leave
	ret
	.size	SegmentDescriptor_stackSegSetup, .-SegmentDescriptor_stackSegSetup
	.type	SegmentDescriptor_dataSegSetup, @function
SegmentDescriptor_dataSegSetup:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	SegmentDescriptor_setBaseLimitDPL
	movl	8(%ebp), %eax
	movzbl	5(%eax), %eax
	movl	%eax, %edx
	orl	$-110, %edx
	movl	8(%ebp), %eax
	movb	%dl, 5(%eax)
	movl	16(%ebp), %eax
	shrl	$16, %eax
	andl	$15, %eax
	movl	%eax, %edx
	orl	$-64, %edx
	movl	8(%ebp), %eax
	movb	%dl, 6(%eax)
	leave
	ret
	.size	SegmentDescriptor_dataSegSetup, .-SegmentDescriptor_dataSegSetup
	.comm	segDescTable,40,32
	.ident	"GCC: (GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4)"
	.section	.note.GNU-stack,"",@progbits
