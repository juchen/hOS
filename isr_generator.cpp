#define _ISR_C_
#include "isr.h"
#include "printf-stdarg.h"

void timerISR(void)
{
	asm("push %eax\n\t"
	    "push %ebx\n\t"
	    "push %ecx\n\t"
	    "push %edx\n\t"
	    "push %edi\n\t"
	    "push %esi\n\t"
	    "push %ebp\n\t"
	   );
	printf("\n\nTimer Interrupt!\n\n");
	asm(
	    "pop %ebp\n\t"
	    "pop %esi\n\t"
	    "pop %edi\n\t"
	    "pop %edx\n\t"
	    "pop %ecx\n\t"
	    "pop %ebx\n\t"
	    "pop %eax\n\t"
	    "leave\n\t"
	    "iret\n\t");
}

