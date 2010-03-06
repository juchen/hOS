#include "printf-stdarg.h"
#include "putchar.h"

extern "C" {
void pm_c_entry(void);
}

void pm_c_entry(void)
{
	Screen s;
	s.cls();
	//puts("Hello! World!\n");
	//printf("Give me %d\n", 5);
	//puts("Hello! World!\n");
	printf("Booting hOS...\n");
	/*
	putchar('H');
	putchar('e');
	putchar('l');
	putchar('l');
	putchar('o');
	putchar(' ');
	putchar('W');
	putchar('o');
	putchar('r');
	putchar('l');
	putchar('d');
	putchar('!');
	putchar('\n');
	putchar('y');
	*/
	asm(
			"mov $0xA0000001, %edx\n\t"
	   );
	while(1);
}
