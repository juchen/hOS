	.file	"pm_c_entry.cpp"
	.text
	.align 2
.globl pm_c_entry
	.type	pm_c_entry, @function
pm_c_entry:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	leal	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN6ScreenC1Ev
	leal	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN6Screen3clsEv
#APP
	mov $0xC0000010, %edx
	
#NO_APP
.L2:
	jmp	.L2
	.size	pm_c_entry, .-pm_c_entry
	.ident	"GCC: (GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4)"
	.section	.note.GNU-stack,"",@progbits
