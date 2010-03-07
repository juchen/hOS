#include "printf-stdarg.h"
#include "putchar.h"

extern "C" {
void pm_c_entry(void);
}

void pm_c_entry(void)
{
	Screen s;
	s.cls();
	printf("Booting hOS...\n");
	Gdt gdt;
	Idt ide;
	/*
	Gdt gdt; // Copy original GDT and give more segment descriptor, TSS, user mode segs, etc.
	gdt.initFromCpu();
	Tss tss; // The single TSS that gives SS:SP for every privellege.
#error init tss
	tss.esp0 = ...;
	tss.ss0 = 0x18;
	tss.revAndTrapFlag = 0;
	// other fields are irrelevant in my purpose.
#error	here.
	unsigned int tssSelector;
	{ // This block to make some variable local in local.
		SegDesc tssDesc; // This variable will be released from the stack after leaving this block.
#error init tssDesc
		tssDesc.setTssSeg(&tssDesc, sizeof(tssDesc)-1, 0);
#error	here.
		tssSelector = gdt.push(tssDesc);
	}
#error TSS_SEG_SELECTOR has to be get.
	asm (
			"ltr %0\n\t"
			::"g"(tssSelector)
	    );
	    */
	while(1);
}
