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
	void setTssSeg(void *base, unsigned int limit, unsigned int privilege,
      bool buzy = false);
	DWORD getBase()
	{
		return (((DWORD)baseHigh) << 24) + (((DWORD)baseMid) << 16) + ((DWORD)baseLow);
	}
} __attribute__((packed)) __attribute__((aligned(4)));

struct CallGateDesc
{
  WORD offLow; // low 16 bit of offset.
  WORD selector;
  BYTE paramCount; // noly bit 4:0
  BYTE ctl; // 3:0 -- has to be 1100b, 7 - Gate Valid (should be 1), 6:5 - DPL, 4 - should be 0.
  WORD offHi; // hight 16 bit of offset.
  void setCallGate(unsigned short selector, void offset(void *), unsigned int dpl, unsigned int paramCount_);
};

/// Represent GDTR
///
struct GdtReg
{
	WORD dummy; // help to align base to DWORD boundary.
	WORD len;
	DWORD base;
  WORD dummy2;
	void loadFromCpu();
	void storeToCpu();
  WORD getRawLen() { return len; }
  int getByteLen() { return len + 1; }
  int getEntryNum() { return (len + 1) / 8; }
  void setEntryNum(int n) { len = n * 8 - 1; }
  DWORD getBase() { return base; }
  void setBaseAndEntryNumber(SegDesc *b, WORD n /* in entry number */)
  {
    base = (DWORD)b;
    len = n * 8 - 1;
  }
} __attribute__((packed)) __attribute__((aligned(4)));

class Gdt
{
private:
  static const unsigned int MAX_GDT_SIZE = 16;
	SegDesc _gdt[MAX_GDT_SIZE] __attribute__((aligned(8)));
	GdtReg _gdtReg;
	void setEntry(unsigned int index, const SegDesc &segDesc);
	void setEntryNum(unsigned short l);
public:
	//Gdt();
	void initFromCpu();
	void setToCpu();
	void *base();
	int entryNum();
	unsigned short push(const SegDesc &segDesc)
	{
		unsigned short n = entryNum();
    ASSERT(n+1 < MAX_GDT_SIZE);
		setEntry(n, segDesc);
		setEntryNum(n+1);
    return n * 8; // Every selector has it offset from bit 3.
	}
	void remove(unsigned int index)
	{
		ASSERT(false);
	}
	const SegDesc &getEntry(unsigned int index);
} __attribute__((aligned(4)));

struct Tss
{
	WORD prevTaskLink;
	WORD reserved1;
	DWORD esp0;
	WORD ss0;
	WORD reserved2;
	DWORD esp1;
	WORD ss1;
	WORD reserved3;
	DWORD esp2;
	WORD ss2;
	WORD reserved4;
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
	WORD es;
	WORD reserved5;
	WORD cs;
	WORD reserved6;
	WORD ss;
	WORD reserved7;
	WORD ds;
	WORD reserved8;
	WORD fs;
	WORD reserved9;
	WORD gs;
	WORD reserved10;
	WORD ldtSelector;
	WORD reserved11;
	WORD revAndTrapFlag;
	WORD ioMapBase;
} __attribute__((packed)) __attribute__((aligned(8)));

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

#define MAX_INT_NUM 0x40 // HW interrupt map to 0x20~0x2F, SW: 0x30~0x3F
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
  void setSysCallISR(void (*addr)(void))
  {
    setIntGate(0x30, addr);
  }
};
#endif // _SYS_STRUCT_H_
