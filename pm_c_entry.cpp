#include "printf-stdarg.h"
#include "putchar.h"
#include "sys_struct.h"
#include "isr.h"
#include "timer8253.h"
#include "x86functions.h"

extern "C" {
void pm_c_entry(void);
}

static inline void init_ISR(Idt &idt)
{
	idt.setTimerISR(timerISR);
	idt.setToCPU();
}

/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8 and 70, as configured by default */
#define PIC1_COMMAND  0x20
#define PIC1_DATA     0x21
#define PIC2_COMMAND  0xA0
#define PIC2_DATA     0xA1

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

/*
arguments:
	offset1 - vector offset for master PIC
		vectors on the master become offset1..offset1+7
	offset2 - same for slave PIC: offset2..offset2+7
*/
static inline void init_IntCtrlr(void)
{
	unsigned char a1, a2;
	
	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);
	
	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, 0x20 /* offset1 */);                 // define the PIC vectors
	io_wait();
	outb(PIC2_DATA, 0x28 /* offset2 */);
	io_wait();
	outb(PIC1_DATA, 4);                       // continue initialization sequence
	io_wait();
	outb(PIC2_DATA, 2);
	io_wait();
	
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();
	
#warning The mask should be properly configured.
	//outb(PIC1_DATA, a1);   // restore saved masks.
	//outb(PIC2_DATA, a2);
	outb(PIC1_DATA, 0xFE /*a1*/);   // unmask IRQ0 only.
	outb(PIC2_DATA, 0xFF /*a2*/);
}

static inline void enable_Int()
{
	asm("sti\n\t");
}

void pm_c_entry(void)
{
	Screen s;
	s.cls();
	printf("Booting hOS...\n");
	Idt idt;
	Timer8253 timer8253;
	::init_ISR(idt);
	::init_IntCtrlr();
	TRACE_HEX(pm_c_entry);
	//asm("int $0x20\n\t");
  // Before enabling interrupts. TSS has to be setup. 201111271528
	::enable_Int();
	unsigned char i = 0;
	while(1)
	{
		//printf("-> %d \t", i++);
	}
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
