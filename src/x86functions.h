#ifndef _X86FUNCTIONS_H_
#define _X86FUNCTIONS_H_
#include "types.h"

BYTE inb(unsigned int port);
void outb(unsigned int port, BYTE value);
void io_wait(void);


#endif // _X86FUNCTIONS_H_
