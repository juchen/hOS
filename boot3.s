.code16gcc
.text
.global main
main:
	ljmpl $0x07c0, $begin
begin:
	xor %eax, %eax
	xor %ebx, %ebx
	xor %ecx, %ecx
	xor %edx, %edx
	xor %edi, %edi
	xor %esi, %esi
	mov %cs, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	mov $2048, %esp
	call c_entry

	.text
.global printString
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
	
	

