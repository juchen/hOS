#ifndef _GDB_GLUE_H_
#define _GDB_GLUE_H_

#ifdef __cplusplus
extern "C" {
#endif
void GdbGlue_setDebugComPort(ComPort *p);
void GdbGlue_setIdt(Idt *_idt);

void set_debug_traps (void);
void breakpoint (void);

void testDebugPort(void);

#ifdef __cplusplus
}
#endif
#endif // _GDB_GLUE_H_

