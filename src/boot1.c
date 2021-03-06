asm(".code16gcc");
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned long long QWORD;

typedef enum
{
	DevIndx_FD0 = 0x00,
	DevIndx_HD0 = 0x80,
} DeviceIndex;

typedef struct DiskAddrPack DiskAddrPack;

struct DiskAddrPack
{
	BYTE sizeOfPack;
	BYTE reserved;
	WORD numOfBlocks;
	WORD addr;
	WORD seg;
	QWORD lba;
} __attribute__((packed));

void __readSectors(unsigned short seg, unsigned short addr, 
		DeviceIndex di, unsigned int lba, unsigned int secnum)
{
  volatile DiskAddrPack theDap;
	volatile DiskAddrPack *dap = &theDap;
	dap->sizeOfPack = sizeof(DiskAddrPack);
	dap->reserved = 0;
	dap->numOfBlocks = secnum;
	dap->seg = seg;
	dap->addr = addr;
	dap->lba = lba;
    (void)theDap;
	asm(
			"mov %1, %%si\n\t"
			"movb $0x42, %%ah\n\t"
			"movb %0, %%dl\n\t"
			"int $0x13\n\t"
			::"g"((char)di),"g"((unsigned short)dap):"ah","dl","si"
	   );
}

/*
static inline void printChar(char a)
{
	asm(
		"movw $0x0007, %%bx\n\t"
		"movb $9, %%ah\n\t"
		"movb %0, %%al\n\t"
		"movw $1, %%cx\n\t"
		"int $0x10"
		::"g"(a):"ax", "bx", "cx"
	   );

}
*/

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

void c_entry(void)
{
	//printChar('1');
	volatile DWORD *b;
	DWORD i;

	for(b = (DWORD *)(0x8000); b < (DWORD *)(0x8000 + 512 * 62 / 4); b++)
	{ // zero memory for bss section of the code being loaded.
		*b = 0;
	}

	for(i = 1; i < 127; i++)
	{
        unsigned int addr = 0x18000 + (512 * (i - 1));
        unsigned short seg = (addr / 0x10000) * 0x1000;
        unsigned short off = (addr % 0x10000);
		__readSectors(seg, off, DevIndx_HD0, i, 1);
	}
	//printString("Start 3oading", 13, 22); 
	asm(
		"ljmpl $0x1800, $0\n\t"
	   );
}

