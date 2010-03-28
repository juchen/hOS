/* Copyright 2009, Hsuan-Ju Chen */
asm(".code16gcc");
#define _SECBOOT_C_
#include "secboot.h"


typedef struct _SegmentDescriptor SegmentDescriptor;
struct _SegmentDescriptor
{
	WORD limit;
	WORD baseLow;
	BYTE baseMid;
	BYTE ctlLow;
	BYTE ctlHigh;
	BYTE baseHigh;
} __attribute__((packed));

SegmentDescriptor segDescTable[SEG_DESC_NUM];

/// Please note that the priority should less then 3
/// and the limit should less then 0x00100000 (onle 20-bit effective)
static inline void SegmentDescriptor_setBaseLimitDPL(SegmentDescriptor *me,
		void* base, unsigned int limit, unsigned int priority)
{
	me->limit = (limit & 0x0000FFFF);
	me->baseLow = (WORD)(((DWORD)base) & 0x0000FFFF);
	me->baseMid = (BYTE)((((DWORD)base) >> 16) & 0x00FF);
	me->baseHigh = (BYTE)((((DWORD)base) >> 24) & 0x00FF);
	me->ctlLow = (BYTE)((priority & 0x03) << 5);
	me->ctlHigh = (BYTE)((limit >> 16) & 0x0F);
}

/// Please note that the priority should less then 3
/// and the limit should less then 0x00100000 (onle 20-bit effective)
static inline void SegmentDescriptor_codeSegSetup(SegmentDescriptor *me,
		void* base, unsigned int limit, unsigned int priority)
{
	SegmentDescriptor_setBaseLimitDPL(me, base, limit, priority);
	me->ctlLow |= 0x98;
		// P = 1 (present), S = 0 (non-system), type = 1000b (Execute only)
	me->ctlHigh |= 0xC0;
		// G = 1 (use 4K page as the unit of the limit)
		// D = 1 (32-bit code segment)
}

/// Please note that the priority should less then 3
/// and the limit should less then 0x00100000 (onle 20-bit effective)
static inline void SegmentDescriptor_dataSegSetup(SegmentDescriptor *me,
		void* base, unsigned int limit, unsigned int priority)
{
	SegmentDescriptor_setBaseLimitDPL(me, base, limit, priority);
	me->ctlLow |= 0x92;
		// P = 1 (present), S = 0 (non-system), type = 0010b (Read-Write)
	me->ctlHigh = 0xC0 | (limit >> 16) & 0x0F;
		// G = 1 (use 4K page as the unit of the limit)
		// B = 1 (32-bit code segment)
}

/// Please note that the priority should less then 3
/// and the limit should less then 0x00100000 (onle 20-bit effective)
static inline void SegmentDescriptor_stackSegSetup(SegmentDescriptor *me,
		void* base, unsigned int limit, unsigned int priority)
{
	SegmentDescriptor_setBaseLimitDPL(me, base, limit, priority);
	me->ctlLow |= 0x96;
		// P = 1 (present), S = 0 (non-system), type = 0110b (Read-Write expand down)
	me->ctlHigh = 0xC0 | (limit >> 16) & 0x0F;
		// G = 1 (use 4K page as the unit of the limit)
		// B = 1 (32-bit code segment)
}

typedef struct GdtReg GdtReg;
struct GdtReg
{
	WORD len;
	DWORD base;
} __attribute__((packed));

void printString(char *s, unsigned int len, BYTE row);
/*
{
	asm(
			"movw $0x1301, %%ax\n\t"
			"movw $0x0007, %%bx\n\t"
			"movw %1, %%cx\n\t"
			"movb $0, %%dl\n\t"
			"movb %2, %%dh\n\t"
			"movl %0, %%ebp\n\t"
			"int $0x10"
			::"g"(s),"g"(len),"g"(row):"ax","bx","cx","dx","ebp"
	   );
}
*/

void pm_entry(void);

#define SEGS_BASE 0x00000000

void c_entry(void)
{
	GdtReg gdtr;

	printString("In second boot loader\n\rNow\n", 27, 21); 
	SegmentDescriptor_codeSegSetup(&(segDescTable[SEG_CODE_SELECTOR/8]),
			(void *)SEGS_BASE, 0x187, 0x0);
	SegmentDescriptor_dataSegSetup(&(segDescTable[SEG_DATA_SELECTOR/8]),
			(void *)SEGS_BASE, 0x2000, 0x0); // should include the stack segment for manipulation.
	// ^^^ data segment includes all the availble mem (32MB) from 0x18000 to 0x2000000.
	SegmentDescriptor_stackSegSetup(&(segDescTable[SEG_STACK_SELECTOR/8]),
			(void *)SEGS_BASE, 0x188, 0x0);
	SegmentDescriptor_dataSegSetup(&(segDescTable[SEG_VIDEO_SELECTOR/8]),
			(void *)0x000B8000, 0x3, 0x0);
	gdtr.len = sizeof(segDescTable) - 1;
	gdtr.base = SEGS_BASE + ((DWORD)(segDescTable));
	//asm("mov %0, %%edx\n\t"::"g"(&gdtr));
	asm(
			"lgdt (%0)\n\t"::"g"(&gdtr)
	   );
	asm(
			"cli\n\t"
			"in $0x92, %%al\n\t"
			"or $0x02, %%al\n\t"
			"out %%al, $0x92\n\t":::"al"
	   );
	asm(
			"mov %%cr0, %%eax\n\t"
			"or $1, %%eax\n\t"
			"mov %%eax, %%cr0\n\t"     // entered protection mode.
			"ljmpl $0x08, %0\n\t"
			::"g"(pm_entry):"eax"
	   );
	while(1);
}
