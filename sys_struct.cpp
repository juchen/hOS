#define _SYS_STRUCT_CPP_
#include "sys_struct.h"

void GdtReg::loadFromCpu()
{
  asm(
      "mov %0, %%ebx\n\t"
      "sgdtl (%%ebx)\n\t"::"g"(&len):"ebx"
     );
}

void GdtReg::storeToCpu()
{
  asm(
      "mov %0, %%ebx\n\t"
      "lgdtl (%%ebx)\n\t"::"g"(&len):"ebx"
     );
}

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
	idtr.limit = (MAX_INT_NUM * sizeof(IdtDesc) - 1);
	idtr.addr = idt; // + (0x18000/sizeof(IdtDesc));
	TRACE_HEX(idt);
	TRACE_HEX(idtr.limit);
	TRACE_HEX(idtr.addr);
	TRACE_HEX(&idtr.limit);
	asm("lidtl (%0)\n\t"::"g"(&idtr.limit));
}

#define IMPLEMENT_DEF_INT_HANDLER(I) \
void defaultIntHandler##I(void)\
{\
	printf("Int 0x%x occurred\n", I);\
	ASSERT(false);\
}

IMPLEMENT_DEF_INT_HANDLER(0x00)
IMPLEMENT_DEF_INT_HANDLER(0x01)
IMPLEMENT_DEF_INT_HANDLER(0x02)
IMPLEMENT_DEF_INT_HANDLER(0x03)
IMPLEMENT_DEF_INT_HANDLER(0x04)
IMPLEMENT_DEF_INT_HANDLER(0x05)
IMPLEMENT_DEF_INT_HANDLER(0x06)
IMPLEMENT_DEF_INT_HANDLER(0x07)
IMPLEMENT_DEF_INT_HANDLER(0x08)
IMPLEMENT_DEF_INT_HANDLER(0x09)
IMPLEMENT_DEF_INT_HANDLER(0x0a)
IMPLEMENT_DEF_INT_HANDLER(0x0b)
IMPLEMENT_DEF_INT_HANDLER(0x0c)
IMPLEMENT_DEF_INT_HANDLER(0x0d)
IMPLEMENT_DEF_INT_HANDLER(0x0e)
IMPLEMENT_DEF_INT_HANDLER(0x0f)
IMPLEMENT_DEF_INT_HANDLER(0x10)
IMPLEMENT_DEF_INT_HANDLER(0x11)
IMPLEMENT_DEF_INT_HANDLER(0x12)
IMPLEMENT_DEF_INT_HANDLER(0x13)
IMPLEMENT_DEF_INT_HANDLER(0x14)
IMPLEMENT_DEF_INT_HANDLER(0x15)
IMPLEMENT_DEF_INT_HANDLER(0x16)
IMPLEMENT_DEF_INT_HANDLER(0x17)
IMPLEMENT_DEF_INT_HANDLER(0x18)
IMPLEMENT_DEF_INT_HANDLER(0x19)
IMPLEMENT_DEF_INT_HANDLER(0x1a)
IMPLEMENT_DEF_INT_HANDLER(0x1b)
IMPLEMENT_DEF_INT_HANDLER(0x1c)
IMPLEMENT_DEF_INT_HANDLER(0x1d)
IMPLEMENT_DEF_INT_HANDLER(0x1e)
IMPLEMENT_DEF_INT_HANDLER(0x1f)
IMPLEMENT_DEF_INT_HANDLER(0x20)
IMPLEMENT_DEF_INT_HANDLER(0x21)
IMPLEMENT_DEF_INT_HANDLER(0x22)
IMPLEMENT_DEF_INT_HANDLER(0x23)
IMPLEMENT_DEF_INT_HANDLER(0x24)
IMPLEMENT_DEF_INT_HANDLER(0x25)
IMPLEMENT_DEF_INT_HANDLER(0x26)
IMPLEMENT_DEF_INT_HANDLER(0x27)
IMPLEMENT_DEF_INT_HANDLER(0x28)
IMPLEMENT_DEF_INT_HANDLER(0x29)
IMPLEMENT_DEF_INT_HANDLER(0x2a)
IMPLEMENT_DEF_INT_HANDLER(0x2b)
IMPLEMENT_DEF_INT_HANDLER(0x2c)
IMPLEMENT_DEF_INT_HANDLER(0x2d)
IMPLEMENT_DEF_INT_HANDLER(0x2e)
IMPLEMENT_DEF_INT_HANDLER(0x2f)

#define SET_INT_GATE(x) setIntGate(x, defaultIntHandler##x)
Idt::Idt()
{
	SET_INT_GATE(0x00);
	SET_INT_GATE(0x01);
	SET_INT_GATE(0x02);
	SET_INT_GATE(0x03);
	SET_INT_GATE(0x04);
	SET_INT_GATE(0x05);
	SET_INT_GATE(0x06);
	SET_INT_GATE(0x07);
	SET_INT_GATE(0x08);
	SET_INT_GATE(0x09);
	SET_INT_GATE(0x0a);
	SET_INT_GATE(0x0b);
	SET_INT_GATE(0x0c);
	TRACE_HEX(defaultIntHandler0x0c);
	SET_INT_GATE(0x0d);
	SET_INT_GATE(0x0e);
	SET_INT_GATE(0x0f);
	SET_INT_GATE(0x10);
	SET_INT_GATE(0x11);
	SET_INT_GATE(0x12);
	SET_INT_GATE(0x13);
	SET_INT_GATE(0x14);
	SET_INT_GATE(0x15);
	SET_INT_GATE(0x16);
	SET_INT_GATE(0x17);
	SET_INT_GATE(0x18);
	SET_INT_GATE(0x19);
	SET_INT_GATE(0x1a);
	SET_INT_GATE(0x1b);
	SET_INT_GATE(0x1c);
	SET_INT_GATE(0x1d);
	SET_INT_GATE(0x1e);
	SET_INT_GATE(0x1f);
	SET_INT_GATE(0x20);
	SET_INT_GATE(0x21);
	SET_INT_GATE(0x22);
	SET_INT_GATE(0x23);
	SET_INT_GATE(0x24);
	SET_INT_GATE(0x25);
	SET_INT_GATE(0x26);
	SET_INT_GATE(0x27);
	SET_INT_GATE(0x28);
	SET_INT_GATE(0x29);
	SET_INT_GATE(0x2a);
	SET_INT_GATE(0x2b);
	SET_INT_GATE(0x2c);
	SET_INT_GATE(0x2d);
	SET_INT_GATE(0x2e);
	SET_INT_GATE(0x2f);
}

TSS gDefTss =
{
  .prevTaskLink = 0;
  .reserved1 = 0;
  .esp0 = somewhere appropriate;
  .ss0 = 0x18; // flat mem mode.
  .reserved2 = 0;
  .esp1 = the same as esp0;
  .ss1 = 0x18; // flat mem mode.
  .reserved3 = 0;
  .esp2 = the same as esp0;
  .ss2 = 0x18; // flast mem mode.
  .reserved4 = 0;
  .cr3 = unclear how to set this, need more reading of the spec;
  .eip = 0; // should no need to be precise.
  .eflags = 0; // should no need to be precise.
  .eax = 0;
  .ecx = 0;
  .edx = 0;
  .ebx = 0;
  .esp = 0;
  .ebp = 0;
  .esi = 0;
  .edi = 0;
  .es = 0x10; //flat mem mode.
  .reserved5 = 0;
  .cs = 0x08;
  .reserved6 = 0;
  .ss = 0x18;
  .reserved7 = 0;
  .ds = 0x10;
  .reserved8 = 0;
  .fs = 0x10;
  .reserved9 = 0;
  .gs = 0x10;
  .reserved10 = 0;
  .ldtSelector = let it be zero lenght should be ok;
  .reserved11 = 0;
  .revAndTrapFlag = 0; // Make sure T flag is zero.
  .ioMapBase = figure out.;
};
