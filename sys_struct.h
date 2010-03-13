#ifndef _SYS_STRUCT_H_
#define _SYS_STRUCT_H_

#include "debug.h"
#include "types.h"

struct SegDesc
{
	WORD limit;
	WORD baseLow;
	BYTE baseMid;
	BYTE ctlLow;
	BYTE ctlHigh;
	BYTE baseHigh;
	void setBaseLimitDPL(void *base, unsigned int limit, unsigned int privilege);
	void setCodeSeg(void *base, unsigned int limit, unsigned int privilege);
	void setDataSeg(void *base, unsigned int limit, unsigned int privilege);
	void setStackSeg(void *base, unsigned int limit, unsigned int privilege);
	void setTssSeg(void *base, unsigned int limit, unsigned int privilege);
	DWORD getBase()
	{
		return (((DWORD)baseHigh) << 24) + (((DWORD)baseMid) << 16) + ((DWORD)baseLow);
	}
} __attribute__((packed)) __attribute__((aligned(4)));

struct GdtReg
{
	WORD dummy; // help to align base to DWORD boundary.
	WORD len;
	DWORD base;
	void loadFromCpu();
	void storeToCpu();
} __attribute__((packed)) __attribute__((aligned(4)));

const unsigned int MAX_GDT_SIZE = 16;
class Gdt
{
private:
	SegDesc _gdt[MAX_GDT_SIZE] __attribute__((aligned(8)));
	GdtReg _gdtReg;
	void setEntry(unsigned int index, const SegDesc &segDesc);
	void setLen(unsigned short l);
public:
	Gdt();
	void initFromCpu();
	void setToCpu();
	void *base();
	unsigned short len();
	void push(const SegDesc &segDesc)
	{
		unsigned short l = len();
		setEntry(l, segDesc);
		setLen(l+1);
	}
	void remove(unsigned int index)
	{
		ASSERT(false);
	}
	const SegDesc &getEntry(unsigned int index);
} __attribute__((aligned(4)));

struct Tss
{
	WORD reserved1;
	WORD prevTaskLink;
	DWORD esp0;
	WORD reserved2;
	WORD ss0;
	DWORD esp1;
	WORD reserved3;
	WORD ss1;
	DWORD esp2;
	WORD reserved4;
	WORD ss2;
	DWORD cr3;
	DWORD eip;
	DWORD eflags;
	DWORD eax;
	DWORD ecx;
	DWORD edx;
	DWORD ebx;
	DWORD esp;
	DWORD ebp;
	DWORD esi;
	DWORD edi;
	WORD reserved5;
	WORD es;
	WORD reserved6;
	WORD cs;
	WORD reserved7;
	WORD ss;
	WORD reserved8;
	WORD ds;
	WORD reserved9;
	WORD fs;
	WORD reserved10;
	WORD gs;
	WORD reserved11;
	WORD ldtSelector;
	WORD ioMapBase;
	WORD revAndTrapFlag;
};

enum IntGateType
{
	INT_GATE,
	TRAP_GATE,
};

struct IdtDesc
{
	WORD offsetLow;
	WORD selector;
	BYTE ctrl1;
	BYTE ctrl2;
	WORD offsetHigh;
	void set(void (*addr)(void), IntGateType t);
} __attribute__((aligned(4)));

#define MAX_INT_NUM 0x30
class Idt
{
private:
	IdtDesc idt[MAX_INT_NUM] __attribute__((aligned(8)));
	void setIntGate(unsigned int i, void (*addr)(void))
	{
		idt[i].set(addr, INT_GATE);
	}
	void setTrapGate(unsigned int i, void (*addr)(void))
	{
		idt[i].set(addr, TRAP_GATE);
	}
public:	
	Idt();
	void setToCPU();
	void setTimerISR(void (*addr)(void))
	{
		setIntGate(0x20, addr);
	}
};
#endif // _SYS_STRUCT_H_