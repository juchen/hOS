	.file	"secboot.c"
	.text
.Ltext0:
#APP
	.code16gcc
#NO_APP
	.globl	SEG_NULL_SELECTOR
	.section	.rodata
	.align 4
	.type	SEG_NULL_SELECTOR, @object
	.size	SEG_NULL_SELECTOR, 4
SEG_NULL_SELECTOR:
	.zero	4
	.globl	SEG_CODE_SELECTOR
	.align 4
	.type	SEG_CODE_SELECTOR, @object
	.size	SEG_CODE_SELECTOR, 4
SEG_CODE_SELECTOR:
	.long	8
	.globl	SEG_DATA_SELECTOR
	.align 4
	.type	SEG_DATA_SELECTOR, @object
	.size	SEG_DATA_SELECTOR, 4
SEG_DATA_SELECTOR:
	.long	16
	.globl	SEG_STACK_SELECTOR
	.align 4
	.type	SEG_STACK_SELECTOR, @object
	.size	SEG_STACK_SELECTOR, 4
SEG_STACK_SELECTOR:
	.long	24
	.globl	SEG_VIDEO_SELECTOR
	.align 4
	.type	SEG_VIDEO_SELECTOR, @object
	.size	SEG_VIDEO_SELECTOR, 4
SEG_VIDEO_SELECTOR:
	.long	32
	.comm	segDescTable,40,32
	.text
	.type	SegmentDescriptor_setBaseLimitDPL, @function
SegmentDescriptor_setBaseLimitDPL:
.LFB0:
	.file 1 "secboot.c"
	.loc 1 24 0
	.cfi_startproc
	pushl	%ebp
.LCFI0:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI1:
	.cfi_def_cfa_register 5
	.loc 1 25 0
	movl	16(%ebp), %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movw	%dx, (%eax)
	.loc 1 26 0
	movl	12(%ebp), %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movw	%dx, 2(%eax)
	.loc 1 27 0
	movl	12(%ebp), %eax
	shrl	$16, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movb	%dl, 4(%eax)
	.loc 1 28 0
	movl	12(%ebp), %eax
	shrl	$24, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movb	%dl, 7(%eax)
	.loc 1 29 0
	movl	20(%ebp), %eax
	andl	$3, %eax
	movl	%eax, %edx
	sall	$5, %edx
	movl	8(%ebp), %eax
	movb	%dl, 5(%eax)
	.loc 1 30 0
	movl	16(%ebp), %eax
	shrl	$16, %eax
	movl	%eax, %edx
	andl	$15, %edx
	movl	8(%ebp), %eax
	movb	%dl, 6(%eax)
	.loc 1 31 0
	popl	%ebp
.LCFI2:
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE0:
	.size	SegmentDescriptor_setBaseLimitDPL, .-SegmentDescriptor_setBaseLimitDPL
	.type	SegmentDescriptor_codeSegSetup, @function
SegmentDescriptor_codeSegSetup:
.LFB1:
	.loc 1 37 0
	.cfi_startproc
	pushl	%ebp
.LCFI3:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI4:
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 38 0
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	SegmentDescriptor_setBaseLimitDPL
	.loc 1 39 0
	movl	8(%ebp), %eax
	movzbl	5(%eax), %eax
	movl	%eax, %edx
	orl	$-104, %edx
	movl	8(%ebp), %eax
	movb	%dl, 5(%eax)
	.loc 1 41 0
	movl	8(%ebp), %eax
	movzbl	6(%eax), %eax
	movl	%eax, %edx
	orl	$-64, %edx
	movl	8(%ebp), %eax
	movb	%dl, 6(%eax)
	.loc 1 44 0
	leave
	.cfi_restore 5
.LCFI5:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	SegmentDescriptor_codeSegSetup, .-SegmentDescriptor_codeSegSetup
	.type	SegmentDescriptor_dataSegSetup, @function
SegmentDescriptor_dataSegSetup:
.LFB2:
	.loc 1 50 0
	.cfi_startproc
	pushl	%ebp
.LCFI6:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI7:
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 51 0
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	SegmentDescriptor_setBaseLimitDPL
	.loc 1 52 0
	movl	8(%ebp), %eax
	movzbl	5(%eax), %eax
	movl	%eax, %edx
	orl	$-110, %edx
	movl	8(%ebp), %eax
	movb	%dl, 5(%eax)
	.loc 1 54 0
	movl	16(%ebp), %eax
	shrl	$16, %eax
	andl	$15, %eax
	movl	%eax, %edx
	orl	$-64, %edx
	movl	8(%ebp), %eax
	movb	%dl, 6(%eax)
	.loc 1 57 0
	leave
	.cfi_restore 5
.LCFI8:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	SegmentDescriptor_dataSegSetup, .-SegmentDescriptor_dataSegSetup
	.type	SegmentDescriptor_stackSegSetup, @function
SegmentDescriptor_stackSegSetup:
.LFB3:
	.loc 1 63 0
	.cfi_startproc
	pushl	%ebp
.LCFI9:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI10:
	.cfi_def_cfa_register 5
	subl	$16, %esp
	.loc 1 64 0
	movl	20(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	12(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	SegmentDescriptor_setBaseLimitDPL
	.loc 1 65 0
	movl	8(%ebp), %eax
	movzbl	5(%eax), %eax
	movl	%eax, %edx
	orl	$-106, %edx
	movl	8(%ebp), %eax
	movb	%dl, 5(%eax)
	.loc 1 67 0
	movl	16(%ebp), %eax
	shrl	$16, %eax
	andl	$15, %eax
	movl	%eax, %edx
	orl	$-64, %edx
	movl	8(%ebp), %eax
	movb	%dl, 6(%eax)
	.loc 1 70 0
	leave
	.cfi_restore 5
.LCFI11:
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	SegmentDescriptor_stackSegSetup, .-SegmentDescriptor_stackSegSetup
	.section	.rodata
.LC0:
	.string	"In second boot loader\n\rNow\n"
	.text
	.globl	c_entry
	.type	c_entry, @function
c_entry:
.LFB4:
	.loc 1 100 0
	.cfi_startproc
	pushl	%ebp
.LCFI12:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI13:
	.cfi_def_cfa_register 5
	subl	$40, %esp
	.loc 1 103 0
	movl	$21, 8(%esp)
	movl	$27, 4(%esp)
	movl	$.LC0, (%esp)
	call	printString
	.loc 1 104 0
	movl	SEG_CODE_SELECTOR, %eax
	shrl	$3, %eax
	sall	$3, %eax
	addl	$segDescTable, %eax
	movl	$0, 12(%esp)
	movl	$32, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	SegmentDescriptor_codeSegSetup
	.loc 1 106 0
	movl	SEG_DATA_SELECTOR, %eax
	shrl	$3, %eax
	sall	$3, %eax
	addl	$segDescTable, %eax
	movl	$3, 12(%esp)
	movl	$8192, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	SegmentDescriptor_dataSegSetup
	.loc 1 109 0
	movl	SEG_STACK_SELECTOR, %eax
	shrl	$3, %eax
	sall	$3, %eax
	addl	$segDescTable, %eax
	movl	$0, 12(%esp)
	movl	$33, 8(%esp)
	movl	$0, 4(%esp)
	movl	%eax, (%esp)
	call	SegmentDescriptor_stackSegSetup
	.loc 1 111 0
	movl	SEG_VIDEO_SELECTOR, %eax
	shrl	$3, %eax
	sall	$3, %eax
	addl	$segDescTable, %eax
	movl	$3, 12(%esp)
	movl	$3, 8(%esp)
	movl	$753664, 4(%esp)
	movl	%eax, (%esp)
	call	SegmentDescriptor_dataSegSetup
	.loc 1 113 0
	movw	$39, -14(%ebp)
	.loc 1 114 0
	movl	$segDescTable, %eax
	addl	$98304, %eax
	movl	%eax, -12(%ebp)
	.loc 1 117 0
	leal	-14(%ebp), %eax
	.loc 1 116 0
#APP
# 116 "secboot.c" 1
	lgdt (%eax)
	
# 0 "" 2
	.loc 1 119 0
# 119 "secboot.c" 1
	cli
	in $0x92, %al
	or $0x02, %al
	out %al, $0x92
	
# 0 "" 2
	.loc 1 125 0
# 125 "secboot.c" 1
	mov %cr0, %eax
	or $1, %eax
	mov %eax, %cr0
	ljmpl $0x08, $pm_entry
	
# 0 "" 2
#NO_APP
.L6:
	.loc 1 134 0 discriminator 1
	jmp	.L6
	.cfi_endproc
.LFE4:
	.size	c_entry, .-c_entry
.Letext0:
	.file 2 "types.h"
	.file 3 "secboot.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x2f0
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF28
	.byte	0x1
	.long	.LASF29
	.long	.LASF30
	.long	.Ltext0
	.long	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF0
	.byte	0x2
	.byte	0x4
	.long	0x30
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF2
	.uleb128 0x2
	.long	.LASF1
	.byte	0x2
	.byte	0x5
	.long	0x42
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF3
	.uleb128 0x2
	.long	.LASF4
	.byte	0x2
	.byte	0x6
	.long	0x54
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF5
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF6
	.uleb128 0x2
	.long	.LASF7
	.byte	0x1
	.byte	0x7
	.long	0x6d
	.uleb128 0x4
	.long	.LASF15
	.byte	0x8
	.byte	0x1
	.byte	0x8
	.long	0xce
	.uleb128 0x5
	.long	.LASF8
	.byte	0x1
	.byte	0xa
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x5
	.long	.LASF9
	.byte	0x1
	.byte	0xb
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x5
	.long	.LASF10
	.byte	0x1
	.byte	0xc
	.long	0x25
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x5
	.long	.LASF11
	.byte	0x1
	.byte	0xd
	.long	0x25
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0x5
	.long	.LASF12
	.byte	0x1
	.byte	0xe
	.long	0x25
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0x5
	.long	.LASF13
	.byte	0x1
	.byte	0xf
	.long	0x25
	.byte	0x2
	.byte	0x23
	.uleb128 0x7
	.byte	0
	.uleb128 0x2
	.long	.LASF14
	.byte	0x1
	.byte	0x48
	.long	0xd9
	.uleb128 0x4
	.long	.LASF14
	.byte	0x6
	.byte	0x1
	.byte	0x49
	.long	0x102
	.uleb128 0x6
	.string	"len"
	.byte	0x1
	.byte	0x4b
	.long	0x37
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x5
	.long	.LASF16
	.byte	0x1
	.byte	0x4c
	.long	0x49
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.byte	0
	.uleb128 0x7
	.long	.LASF18
	.byte	0x1
	.byte	0x16
	.byte	0x1
	.long	.LFB0
	.long	.LFE0
	.long	.LLST0
	.long	0x152
	.uleb128 0x8
	.string	"me"
	.byte	0x1
	.byte	0x16
	.long	0x152
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x9
	.long	.LASF16
	.byte	0x1
	.byte	0x17
	.long	0x158
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x9
	.long	.LASF8
	.byte	0x1
	.byte	0x17
	.long	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x9
	.long	.LASF17
	.byte	0x1
	.byte	0x17
	.long	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.long	0x62
	.uleb128 0xb
	.byte	0x4
	.uleb128 0x7
	.long	.LASF19
	.byte	0x1
	.byte	0x23
	.byte	0x1
	.long	.LFB1
	.long	.LFE1
	.long	.LLST1
	.long	0x1aa
	.uleb128 0x8
	.string	"me"
	.byte	0x1
	.byte	0x23
	.long	0x152
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x9
	.long	.LASF16
	.byte	0x1
	.byte	0x24
	.long	0x158
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x9
	.long	.LASF8
	.byte	0x1
	.byte	0x24
	.long	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x9
	.long	.LASF17
	.byte	0x1
	.byte	0x24
	.long	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.byte	0
	.uleb128 0x7
	.long	.LASF20
	.byte	0x1
	.byte	0x30
	.byte	0x1
	.long	.LFB2
	.long	.LFE2
	.long	.LLST2
	.long	0x1fa
	.uleb128 0x8
	.string	"me"
	.byte	0x1
	.byte	0x30
	.long	0x152
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x9
	.long	.LASF16
	.byte	0x1
	.byte	0x31
	.long	0x158
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x9
	.long	.LASF8
	.byte	0x1
	.byte	0x31
	.long	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x9
	.long	.LASF17
	.byte	0x1
	.byte	0x31
	.long	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.byte	0
	.uleb128 0x7
	.long	.LASF21
	.byte	0x1
	.byte	0x3d
	.byte	0x1
	.long	.LFB3
	.long	.LFE3
	.long	.LLST3
	.long	0x24a
	.uleb128 0x8
	.string	"me"
	.byte	0x1
	.byte	0x3d
	.long	0x152
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x9
	.long	.LASF16
	.byte	0x1
	.byte	0x3e
	.long	0x158
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x9
	.long	.LASF8
	.byte	0x1
	.byte	0x3e
	.long	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x9
	.long	.LASF17
	.byte	0x1
	.byte	0x3e
	.long	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.long	.LASF31
	.byte	0x1
	.byte	0x63
	.byte	0x1
	.long	.LFB4
	.long	.LFE4
	.long	.LLST4
	.long	0x272
	.uleb128 0xd
	.long	.LASF32
	.byte	0x1
	.byte	0x65
	.long	0xce
	.byte	0x2
	.byte	0x91
	.sleb128 -22
	.byte	0
	.uleb128 0xe
	.long	.LASF22
	.byte	0x3
	.byte	0xd
	.long	0x284
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	SEG_NULL_SELECTOR
	.uleb128 0xf
	.long	0x49
	.uleb128 0xe
	.long	.LASF23
	.byte	0x3
	.byte	0xe
	.long	0x284
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	SEG_CODE_SELECTOR
	.uleb128 0xe
	.long	.LASF24
	.byte	0x3
	.byte	0xf
	.long	0x284
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	SEG_DATA_SELECTOR
	.uleb128 0xe
	.long	.LASF25
	.byte	0x3
	.byte	0x10
	.long	0x284
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	SEG_STACK_SELECTOR
	.uleb128 0xe
	.long	.LASF26
	.byte	0x3
	.byte	0x11
	.long	0x284
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	SEG_VIDEO_SELECTOR
	.uleb128 0x10
	.long	0x62
	.long	0x2e1
	.uleb128 0x11
	.long	0x54
	.byte	0x4
	.byte	0
	.uleb128 0xe
	.long	.LASF27
	.byte	0x1
	.byte	0x12
	.long	0x2d1
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	segDescTable
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LFB0-.Ltext0
	.long	.LCFI0-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI0-.Ltext0
	.long	.LCFI1-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI1-.Ltext0
	.long	.LCFI2-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI2-.Ltext0
	.long	.LFE0-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST1:
	.long	.LFB1-.Ltext0
	.long	.LCFI3-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI3-.Ltext0
	.long	.LCFI4-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI4-.Ltext0
	.long	.LCFI5-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI5-.Ltext0
	.long	.LFE1-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST2:
	.long	.LFB2-.Ltext0
	.long	.LCFI6-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI6-.Ltext0
	.long	.LCFI7-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI7-.Ltext0
	.long	.LCFI8-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI8-.Ltext0
	.long	.LFE2-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST3:
	.long	.LFB3-.Ltext0
	.long	.LCFI9-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI9-.Ltext0
	.long	.LCFI10-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI10-.Ltext0
	.long	.LCFI11-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI11-.Ltext0
	.long	.LFE3-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
.LLST4:
	.long	.LFB4-.Ltext0
	.long	.LCFI12-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI12-.Ltext0
	.long	.LCFI13-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI13-.Ltext0
	.long	.LFE4-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.value	0
	.value	0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF1:
	.string	"WORD"
.LASF27:
	.string	"segDescTable"
.LASF5:
	.string	"unsigned int"
.LASF19:
	.string	"SegmentDescriptor_codeSegSetup"
.LASF31:
	.string	"c_entry"
.LASF11:
	.string	"ctlLow"
.LASF21:
	.string	"SegmentDescriptor_stackSegSetup"
.LASF26:
	.string	"SEG_VIDEO_SELECTOR"
.LASF32:
	.string	"gdtr"
.LASF18:
	.string	"SegmentDescriptor_setBaseLimitDPL"
.LASF17:
	.string	"priority"
.LASF8:
	.string	"limit"
.LASF6:
	.string	"long long unsigned int"
.LASF10:
	.string	"baseMid"
.LASF7:
	.string	"SegmentDescriptor"
.LASF30:
	.string	"/home/hjchen/works/merkatz.hOS.git/src"
.LASF24:
	.string	"SEG_DATA_SELECTOR"
.LASF2:
	.string	"unsigned char"
.LASF20:
	.string	"SegmentDescriptor_dataSegSetup"
.LASF12:
	.string	"ctlHigh"
.LASF13:
	.string	"baseHigh"
.LASF29:
	.string	"secboot.c"
.LASF9:
	.string	"baseLow"
.LASF28:
	.string	"GNU C 4.6.3"
.LASF3:
	.string	"short unsigned int"
.LASF0:
	.string	"BYTE"
.LASF16:
	.string	"base"
.LASF23:
	.string	"SEG_CODE_SELECTOR"
.LASF22:
	.string	"SEG_NULL_SELECTOR"
.LASF14:
	.string	"GdtReg"
.LASF25:
	.string	"SEG_STACK_SELECTOR"
.LASF4:
	.string	"DWORD"
.LASF15:
	.string	"_SegmentDescriptor"
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
