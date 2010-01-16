.code16
.data
row_count:
	.byte 20
dap:
dap_len:
	.byte 0x10
	.byte 0	#reserved
dap_num_blk:
	.word 1
dap_buffer:
	.word 0x8000
	.word 0x07c0
dap_lba:
	.long 0x01
	.long 0x00
str_error_of_42h:
	.string "Error of 42h"
.text
.global main
main:
	ljmpl $0x07c0, $begin
begin:
	movw $0x07c0, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss
	xor %eax, %eax
	xor %ebx, %ebx
	xor %ecx, %ecx
	xor %edx, %edx
	movw $0x1000, %sp

	movb $0x42, %ah # start reading sectors
	movb $0x80, %dl
	movw $dap, %si
	int $0x13
	jc error_of_42h
	movw $0x1301, %ax
	movw $0x0007, %bx
	movw $3, %cx
	movb $20, %dh
	movb $0, %dl
	movw $0x8000, %bp
	int $0x10
no_err_end:
	jmp no_err_end
error_of_42h:
	movw $0x1301, %ax
	movw $0x0007, %bx
	movw $12, %cx
	movb $20, %dh
	movb $0, %dl
	movw $str_error_of_42h, %bp
	int $0x10
error_of_42h_end:
	jmp error_of_42h_end 
	
	
	
	

