	.file	"pm_c_entry.cpp"
	.section	.text._Z3inbj,"axG",@progbits,_Z3inbj,comdat
	.align 2
	.weak	_Z3inbj
	.type	_Z3inbj, @function
_Z3inbj:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
#APP
	mov 8(%ebp), %dx
	inb %dx, %al
	mov %al, -1(%ebp)
	
#NO_APP
	movzbl	-1(%ebp), %eax
	leave
	ret
	.size	_Z3inbj, .-_Z3inbj
	.section	.text._Z4outbjh,"axG",@progbits,_Z4outbjh,comdat
	.align 2
	.weak	_Z4outbjh
	.type	_Z4outbjh, @function
_Z4outbjh:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4, %esp
	movl	12(%ebp), %eax
	movb	%al, -4(%ebp)
#APP
	mov 8(%ebp), %dx
	mov -4(%ebp), %al
	out %al, %dx
	
#NO_APP
	leave
	ret
	.size	_Z4outbjh, .-_Z4outbjh
	.section	.text._Z7io_waitv,"axG",@progbits,_Z7io_waitv,comdat
	.align 2
	.weak	_Z7io_waitv
	.type	_Z7io_waitv, @function
_Z7io_waitv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$100, -4(%ebp)
.L6:
	movl	-4(%ebp), %eax
	subl	$1, %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	cmpl	$-1, %eax
	setne	%al
	testb	%al, %al
	jne	.L6
	leave
	ret
	.size	_Z7io_waitv, .-_Z7io_waitv
	.text
	.align 2
	.type	_Z13init_IntCtrlrv, @function
_Z13init_IntCtrlrv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$33, (%esp)
	call	_Z3inbj
	movb	%al, -2(%ebp)
	movl	$161, (%esp)
	call	_Z3inbj
	movb	%al, -1(%ebp)
	movl	$17, 4(%esp)
	movl	$32, (%esp)
	call	_Z4outbjh
	call	_Z7io_waitv
	movl	$17, 4(%esp)
	movl	$160, (%esp)
	call	_Z4outbjh
	call	_Z7io_waitv
	movl	$32, 4(%esp)
	movl	$33, (%esp)
	call	_Z4outbjh
	call	_Z7io_waitv
	movl	$40, 4(%esp)
	movl	$161, (%esp)
	call	_Z4outbjh
	call	_Z7io_waitv
	movl	$4, 4(%esp)
	movl	$33, (%esp)
	call	_Z4outbjh
	call	_Z7io_waitv
	movl	$2, 4(%esp)
	movl	$161, (%esp)
	call	_Z4outbjh
	call	_Z7io_waitv
	movl	$1, 4(%esp)
	movl	$33, (%esp)
	call	_Z4outbjh
	call	_Z7io_waitv
	movl	$1, 4(%esp)
	movl	$161, (%esp)
	call	_Z4outbjh
	call	_Z7io_waitv
	movl	$143, 4(%esp)
	movl	$33, (%esp)
	call	_Z4outbjh
	movl	$255, 4(%esp)
	movl	$161, (%esp)
	call	_Z4outbjh
	leave
	ret
	.size	_Z13init_IntCtrlrv, .-_Z13init_IntCtrlrv
	.align 2
	.type	_Z10enable_Intv, @function
_Z10enable_Intv:
	pushl	%ebp
	movl	%esp, %ebp
#APP
	sti
	
#NO_APP
	popl	%ebp
	ret
	.size	_Z10enable_Intv, .-_Z10enable_Intv
	.section	.rodata
.LC0:
	.string	"\n\nTimer Interrupt!\n"
	.text
	.align 2
.globl _Z8timerISRv
	.type	_Z8timerISRv, @function
_Z8timerISRv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
#APP
	push %%eax
	push %%ebx
	push %%ecx
	push %%edx
	push %%edi
	push %%esi
	push %%ebp
	
#NO_APP
	movl	$.LC0, (%esp)
	call	puts
#APP
	pop %%ebp
	pop %%esi
	pop %%edi
	pop %%edx
	pop %%ecx
	pop %%ebx
	pop %%eax
	leave
	iret
	
#NO_APP
	leave
	ret
	.size	_Z8timerISRv, .-_Z8timerISRv
	.section	.text._ZN3Idt10setIntGateEjPFvvE,"axG",@progbits,_ZN3Idt10setIntGateEjPFvvE,comdat
	.align 2
	.weak	_ZN3Idt10setIntGateEjPFvvE
	.type	_ZN3Idt10setIntGateEjPFvvE, @function
_ZN3Idt10setIntGateEjPFvvE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	12(%ebp), %eax
	sall	$3, %eax
	movl	%eax, %edx
	addl	8(%ebp), %edx
	movl	$0, 8(%esp)
	movl	16(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	_ZN7IdtDesc3setEPFvvE11IntGateType
	leave
	ret
	.size	_ZN3Idt10setIntGateEjPFvvE, .-_ZN3Idt10setIntGateEjPFvvE
	.section	.text._ZN3Idt11setTimerISREPFvvE,"axG",@progbits,_ZN3Idt11setTimerISREPFvvE,comdat
	.align 2
	.weak	_ZN3Idt11setTimerISREPFvvE
	.type	_ZN3Idt11setTimerISREPFvvE, @function
_ZN3Idt11setTimerISREPFvvE:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	12(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	$0, 4(%esp)
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3Idt10setIntGateEjPFvvE
	leave
	ret
	.size	_ZN3Idt11setTimerISREPFvvE, .-_ZN3Idt11setTimerISREPFvvE
	.text
	.align 2
	.type	_Z8init_ISRR3Idt, @function
_Z8init_ISRR3Idt:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	%eax, -4(%ebp)
	movl	$_Z8timerISRv, 4(%esp)
	movl	-4(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3Idt11setTimerISREPFvvE
	movl	-4(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3Idt8setToCPUEv
	leave
	ret
	.size	_Z8init_ISRR3Idt, .-_Z8init_ISRR3Idt
	.section	.rodata
.LC1:
	.string	"Booting hOS..."
.LC2:
	.string	"In thread!"
	.text
	.align 2
.globl pm_c_entry
	.type	pm_c_entry, @function
pm_c_entry:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$408, %esp
	leal	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN6ScreenC1Ev
	leal	-16(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN6Screen3clsEv
	movl	$.LC1, (%esp)
	call	puts
	leal	-400(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN3IdtC1Ev
	leal	-400(%ebp), %eax
	call	_Z8init_ISRR3Idt
	call	_Z13init_IntCtrlrv
	call	_Z10enable_Intv
.L22:
	movl	$.LC2, (%esp)
	call	puts
	jmp	.L22
	.size	pm_c_entry, .-pm_c_entry
	.ident	"GCC: (GNU) 4.2.4 (Ubuntu 4.2.4-1ubuntu4)"
	.section	.note.GNU-stack,"",@progbits
