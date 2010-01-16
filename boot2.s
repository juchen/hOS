.code16
.text
.global main
.org 0x7c00
main:
	movw $0x000C, %bx
	movW $1, %cx
	movb $9, %ah
	movb $98, %al
	int $0x10
ll:
	jmp ll

