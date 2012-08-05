#define _PUTCHAR_CPP_
#include "putchar.h"
#include "secboot.h"

static Screen *screen;

Screen::Screen():curPos(0), width(80), height(25), _attr(0x07)
{
	screen = this;
	/*
	if(screen == 0)
	{
		screen = this;
	}
	else
	{ // If more then one Screen is to be constructed
		asm( // give an error code in edx
				"mov $0xE0000001, %edx\n\t"
		   );
		while(1); // halt
	}
	*/
}

void Screen::setAttr(BYTE attr)
{
	_attr = attr;
}

void Screen::putchar(int c)
{
	if(((char)c) == '\n')
	{
		curPos = (BYTE*)(((((DWORD)curPos) / (width * 2)) + 1) * (width * 2));
	}
	else if(((char)c) == '\t')
	{
		curPos = (BYTE*)((((DWORD)curPos)/8 + 1) * 8);
	}
	else
	{
	curPos = (BYTE *)(((DWORD)curPos) % (width * height * 2));
  char attr = _attr;
	asm(
			"push %%ds\n\t"
			"mov %0, %%ax\n\t"
			"mov %%ax, %%ds\n\t"
			"mov %1, %%ebx\n\t"
			"movb %2, %%al\n\t"
			"movb %%al, (%%ebx)\n\t"
			"movb %3, %%al\n\t"
			"movb %%al, 1(%%ebx)\n\t"
			"pop %%ds\n\t"::"g"(SEG_VIDEO_SELECTOR),
				"g"((DWORD)curPos),
			       	"g"(char(c)),
			       	"g"(char(attr)):"ax","ebx"
	   );
	curPos += 2;
	}
}

void Screen::cls()
{
	curPos = 0;
	while(((DWORD)curPos)<(width*height*2))
	{
		asm(
				"push %%ds\n\t"
				"mov %0, %%ax\n\t"
				"mov %%ax, %%ds\n\t"
				"mov %1, %%ebx\n\t"
				//"mov $0xC0000001, %%edx\n\t"
				//"there:\n\t"
				//"jmp there\n\t"
				"movw $0x0720, (%%ebx)\n\t"
				"pop %%ds\n\t"::"g"(SEG_VIDEO_SELECTOR),"g"((DWORD)curPos):"ax","ebx"
		   );
		curPos+=2;
	}
	curPos = 0;
}

int putchar(int c)
{
	screen->putchar(c);
	return 0;
}

int puts(const char* str)
{
	int pc = 0;
	for(;(*str) != '\0'; str++)
	{
		putchar(*str);
		pc++;
	}
	return pc;
}
