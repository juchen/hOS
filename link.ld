MEMORY
{
	ram16 : ORIGIN = 0, LENGTH = 0x1000
	rom16 : ORIGIN = 0, LENGTH = 0x1000
	ram32 : ORIGIN = 0x19000, LENGTH = 0x1FE7000
	rom32 : ORIGIN = 0x1000, LENGTH = 0x1FE7000
}

SECTIONS
{
	.text16 :
	{
		secbootinit.o(.text*)
		secboot.o(.text*)
	} > ram16 AT > rom16

	.data16 . :
	{
		secbootinit.o(.data* .rodata* COMMON)
		secboot.o(.data* .rodata* COMMON)
	} > ram16 AT > rom16

	.bss16 . :
	{
		secbootinit.o(.bss*)
		secboot.o(.bss*)
	} > ram16 AT > rom16

	.stack16 . :
	{
		. = 0x400;
		_stack16 = .;
	} > ram16 AT > rom16

	.text :
	{
		*(.text*)
	} > ram32 AT > rom32

	.ctors . :
	{
		_ctor_start = .;
		*(.ctor*)
		_ctor_end = .;
	} > ram32 AT > rom32

	.data . :
	{
		*(.data*)
		*(.rodata*)
		*(COMMON)
	} > ram32 AT > rom32

	.bss . :
	{
		*.(bss*)
	} > ram32 AT > rom32

	.stack . :
	{
		. = 0x10000;
		_stack = .;
	} > ram32 AT > rom32
}
