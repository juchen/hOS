#define _X86FUNCTIONS_CPP_
#include "x86functions.h"

BYTE inb(unsigned int port)
{
	BYTE r;
	asm("mov %1, %%dx\n\t"
	    "inb %%dx, %%al\n\t"
	    "mov %%al, %0\n\t":"=g"(r):"g"(port):"al","dx");
	return r;
}

void outb(unsigned int port, BYTE value)
{
	asm("mov %0, %%dx\n\t"
	    "mov %1, %%al\n\t"
	    "out %%al, %%dx\n\t"::"g"(port), "g"(value):"al","dx");
}

void io_wait(void)
{
	volatile unsigned int i = 100;
	while(i--);
}

