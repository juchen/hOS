#include "printf-stdarg.h"
#include "putchar.h"
#include "sys_struct.h"
#include "isr.h"
#include "timer8253.h"
#include "x86functions.h"
#include "idlethread.h"
#include "scheduler.h"
#include "genthread.h"
#include "comport.h"
#include "syscall.h"
#include "user_syscall.h"

extern "C" {
void pm_c_entry(void);
}

static inline void init_ISR(Idt &idt)
{
    idt.setTimerISR(timerISR);
    idt.setSysCallISR(syscallISR);
    idt.setToCPU();
}

/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8 and 70, as configured by default */
#define PIC1_COMMAND  0x20
#define PIC1_DATA     0x21
#define PIC2_COMMAND  0xA0
#define PIC2_DATA     0xA1

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

/*
arguments:
	offset1 - vector offset for master PIC
		vectors on the master become offset1..offset1+7
	offset2 - same for slave PIC: offset2..offset2+7
*/
static inline void init_IntCtrlr(void)
{
	unsigned char a1, a2;
	
	a1 = inb(PIC1_DATA);                        // save masks
	a2 = inb(PIC2_DATA);
	
	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	io_wait();
	outb(PIC1_DATA, 0x20 /* offset1 */);                 // define the PIC vectors
	io_wait();
	outb(PIC2_DATA, 0x28 /* offset2 */);
	io_wait();
	outb(PIC1_DATA, 4);                       // continue initialization sequence
	io_wait();
	outb(PIC2_DATA, 2);
	io_wait();
	
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();
	
#warning The mask should be properly configured.
	//outb(PIC1_DATA, a1);   // restore saved masks.
	//outb(PIC2_DATA, a2);
	outb(PIC1_DATA, 0xFE /*a1*/);   // unmask IRQ0 only.
	//outb(PIC1_DATA, 0xFF /*a1*/);   // mask all for debugging.
	outb(PIC2_DATA, 0xFF /*a2*/);
}

char idle_stack[4096];
void idle(void *parm)
{
  TRACE_HEX(parm);
  while(1);
}

class MyThread : public GenThread
{
public:
  MyThread(int id) : _cnt(0), _id(id) {}
  virtual unsigned int threadProc()
  {
    while(true)
    {
      _cnt += 1;
      printf("id = %d, cnt = %d\n", _id, _cnt);
    }
  }
private:
  unsigned int _cnt;
  unsigned int _id;
};

#define SEGS_BASE 0x00000000
void pm_c_entry(void)
{
    ComPort comPort;
    SysCall_setComPort(&comPort); // set this only after syscall isr is installed.

    Screen s;
    s.cls();

    Idt idt;
    Timer8253 timer8253;
    ::init_ISR(idt);
    ::init_IntCtrlr();

    // Before enabling interrupts. TSS has to be setup. 201111271528
    Gdt gdt; // Copy original GDT and give more segment descriptor, TSS, user mode segs, etc.
    gdt.initFromCpu();

    Tss tss; // The single TSS that gives SS:SP for every privellege.
    // We need not to init this TSS cause the task need no initialization.
    // (It is running here)

    unsigned short tssSelector;
    { // This block to make some variable local in local.
        SegDesc tssDesc; // This variable will be released from the stack after leaving this block.
        //TRACE_HEX(sizeof(tss));
        //TRACE_HEX(sizeof(Tss));
        tssDesc.setTssSeg(&tss, sizeof(tss)-1, 0);
        tssSelector = gdt.push(tssDesc);
    }

    unsigned short userCodeSelector;
    {
        SegDesc desc; // The code segment for user mode.
        desc.setCodeSeg(SEGS_BASE, 0x20, 0x03);
        userCodeSelector = gdt.push(desc) | 0x03;
    }

    unsigned short userStackSelector;
    {
        SegDesc desc; // The code segment for user mode.
        desc.setStackSeg(SEGS_BASE, 0x21, 0x03);
        userStackSelector = gdt.push(desc) | 0x03;
    }

    unsigned short sysCallGateSelector;
    {
        CallGateDesc desc; // the call gate descriptor for sys call.
        desc.setCallGate(8 /* FIXME: evil magic number */, SysCall_syscall, 0x03, 1); 
        sysCallGateSelector = gdt.push(*((SegDesc*)&desc)) | 0x03;
        SysCall_u_setCallGateSelector(sysCallGateSelector);
    }


    gdt.setToCpu();

    asm (
            "movw %0, %%bx\n\t"
            "ltrw %%bx\n\t"
            ::"g"(tssSelector):"%bx"
        );

    Scheduler scheduler;
    Scheduler::setScheduler(&scheduler);
    Thread::setScheduler(&scheduler);
    SysCall_u_setScheduler(&scheduler);

    IdleThread idleThread;
    MyThread thread1(1); // create two threads
    MyThread thread2(2);

    TRACE_HEX(&thread1);
    TRACE_HEX(&thread2);

    ContextEsp ctxEsp;
    ContextEbp *ctxEbp; // a dummy one for scheduler to fill in context.


#if 0
    int i = 0;
    while(1)
    {
        TRACE_HEX(i++);
    }
#endif

    asm(
            "mov %%ds, %%ax\n\t"
            "xor $0x03, %%ax\n\t" // make the selector used in usermode has correct RPL.
            "mov %%ax, %%ds\n\t"
            "mov %%ax, %%es\n\t"
            "mov %%ax, %%fs\n\t"
            "mov %%ax, %%gs\n\t"
            "pushl %1\n\t"  // push SS
            "pushl $0\n\t"  // push ESP, going to be set by Scheduler::switchTo().
            "pushl $0x02\n\t" // push EFLAG
            "pushl %2\n\t" // push CS
            "pushl $0\n\t" // push EIP, going to be set by Scheduler::switchTo().
            "pushl $0\n\t" // This position is for ebp right after a function call.
            "mov %%esp, %0\n\t" // get the pointer to ebp context. (In general function, mov %esp, %ebp right on entry)
            :"=g"(ctxEbp)
            :"g"((unsigned int)userStackSelector),
            "g"((unsigned int)userCodeSelector)
       );
    asm( // prepare stack space for function call of 'switchTo'.
            "pushl $0\n\t"
            "pushl $0\n\t"
       );
    Context ctx = { ctxEbp, &ctxEsp };
    scheduler.start(&ctx); // !! Must iret right away to keep stack coherent.
    asm( // clear stack space for function call of 'switchTo'.
            "popl %eax\n\t"
            "popl %eax\n\t"
       );
    asm( // store ss0 and esp0 to TSS.
            "mov %%ss, %0\n\t"
            "mov %%esp, %1\n\t"
            :"=g"(tss.ss0), "=g"(tss.esp0)
       );
    asm(
            "pop %ebp\n\t"
            "iret\n\t" // 'return' to the idle function.
       );
    CHECK_POINT;
    while(1)
    {
        //printf("-> %d \t", i++);
    }
}
