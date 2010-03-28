.text
.global pm_entry
pm_entry:
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov $0x18, %ax
	mov %ax, %ss
	mov $_stack, %esp
	xor %eax, %eax
	xor %ebx, %ebx
	xor %ecx, %ecx
	xor %edx, %edx
	call pm_c_entry
here:
	jmp here

