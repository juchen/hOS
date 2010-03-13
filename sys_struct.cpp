#define _SYS_STRUCT_CPP_
#include "sys_struct.h"

void IdtDesc::set(void (*addr)(void), IntGateType t)
{
	offsetLow = (reinterpret_cast<DWORD>(addr)) & 0xFFFF;
	offsetHigh = (reinterpret_cast<DWORD>(addr)) >> 16;
	asm("mov %%cs, %0":"=g"(selector));
	ctrl1 = 0;
	switch(t)
	{
	case INT_GATE:
		ctrl2 = 0x8E;
		break;
	case TRAP_GATE:
		ctrl2 = 0x8F;
		break;
	default:
		ASSERT(false);
		break;
	}
}

struct Idtr
{
	WORD dummy;
	WORD limit;
	IdtDesc *addr;
} __attribute__((aligned(4)));

void Idt::setToCPU()
{
	Idtr idtr;
	idtr.limit = (MAX_INT_NUM - 1);
	idtr.addr = idt;
	asm("lidtl (%0)\n\t"::"g"(&idtr.limit));
}

void defaultIntHandler(void)
{
	ASSERT(false);
}

Idt::Idt()
{
	for(unsigned int i = 0; i < MAX_INT_NUM; i++)
	{
		setIntGate(i, defaultIntHandler);
	}
}


