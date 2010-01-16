# This is a small problem to be put in MBR to check wheter
# the AH=0x42 function is available for int 13h
.code16
.data
str_installed:
	.string "Installed"
str_installed_end:
str_invalid:
	.string "Invalid"
str_invalid_end:
str_uninstalled:
	.string "uninstalled" 
str_uninstalled_end:
.text
.global main
main:
	ljmpl $0x07c0, $begin
begin:
	movw $0x07c0, %ax # initialize
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss
	xor %eax, %eax
	xor %ebx, %ebx
	xor %ecx, %ecx
	xor %edx, %edx
	movw $0x1000, %sp # use AH=0x41 and BX=0x55AA to test
	movb $0x41, %ah
	movw $0x55AA, %bx
	movb $0x80, %dl
	int $0x13
	jc no_func # CF=1 means the command is invalid (old BIOS)
	cmp $0xAA55, %bx
	je installed # BX==0xAA55 means the disk is installed
	movw $0x1301, %ax
	movw $0x0007, %bx
	movw $11, %cx
	movb $20, %dh
	movb $0, %dl
	movw $str_uninstalled, %bp
	int $0x10
uninstalled_end:
	jmp uninstalled_end
installed:
	movw $0x1301, %ax
	movw $0x0007, %bx
	movw $9, %cx
	movb $20, %dh
	movb $0, %dl
	movw $str_installed, %bp
	int $0x10
installed_end:
	jmp installed_end
no_func:
	movw $0x1301, %ax
	movw $0x0007, %bx
	movw $7, %cx
	movb $20, %dh
	movb $0, %dl
	movw $str_invalid, %bp
	int $0x10
no_func_end:
	jmp no_func_end
	
	
	
	

