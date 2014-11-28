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
		*/secbootinit.s.o(.text*)
		*secbootinit.o(.text*)
		*/secboot.c.o(.text*)
		*secboot.o(.text*)
	} > ram16 AT > rom16

	.data16 . :
	{
		*/secbootinit.s.o(.data* .rodata* COMMON)
		*secbootinit.o(.data* .rodata* COMMON)
		*/secboot.c.o(.data* .rodata* COMMON)
		*secboot.o(.data* .rodata* COMMON)
	} > ram16 AT > rom16

	.bss16 . :
	{
		*/secbootinit.s.o(.bss*)
		*secbootinit.o(.bss*)
		*/secboot.c.o(.bss*)
		*secboot.o(.bss*)
	} > ram16 AT > rom16

	. = 0x1000;
	.stack16 . :
	{
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

	.note . :
	{
		*(.note*)
	} > ram32 AT > rom32

	. = 0x2000000;
	.stack . :
	{
		_stack = .;
	} > ram32 AT > rom32
}
