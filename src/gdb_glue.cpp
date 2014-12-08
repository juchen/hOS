#include "comport.h"
#include "sys_struct.h"
#include "gdb_glue.h"

#define EXTERN extern "C"
EXTERN void putDebugChar(int c);	/* write a single character      */
EXTERN int getDebugChar();	/* read and return a single char */
EXTERN void exceptionHandler(int, void*);	/* assign an exception handler   */

static ComPort *port;
static Idt     *idt;

void GdbGlue_setDebugComPort(ComPort *p)
{
    port = p;
}

void GdbGlue_setIdt(Idt *_idt)
{
    idt = _idt;
}

void putDebugChar(int c)
{
    port->transChar((char)c);
}

int getDebugChar()
{
    return (int)port->recvChar();
}

void exceptionHandler(int n, void *addr)
{
    idt->setGdbExceptionGate(n, (void (*)())addr);
}

void testDebugPort()
{
    while(1) {
        int c = getDebugChar();
        putDebugChar(c);
        putDebugChar(c);
        putDebugChar(c);
    }
}
