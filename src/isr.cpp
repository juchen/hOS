#include "isr.h"
#include "thread.h"
#include "scheduler.h"
#include "x86functions.h"
#include "syscall.h"

extern "C" {
  void c_timerISR(Context *ctx);
  void c_syscallISR(Context *ctx);
}

void c_timerISR(Context *ctx)
{
  Scheduler *sch = Scheduler::instance();
  sch->contextSwitch(ctx);
  outb(0x20, 0x20); // clear PIC
}

void c_syscallISR(Context *ctx)
{
  int callNo = ctx->_contextEsp->_eax;
  void *callParam = (void*)ctx->_contextEsp->_ebx;
  if(SYS_CALL_PUT_CHAR == callNo) // not to do context switch.
  {
    SysCall_PutCharParam *param = (SysCall_PutCharParam *)callParam;
    SysCall_putChar(param);
    ctx->_contextEsp->_eax = 0; // eax is used to carry return value
  }
  else if(SYS_CALL_LOCK_SCHEDULER == callNo)
  {
    SysCall_lockScheduler((Scheduler*)callParam);
  }
  else if(SYS_CALL_UNLOCK_SCHEDULER == callNo)
  {
    SysCall_unlockScheduler((Scheduler*)callParam);
  }
  else
  {
    switch(callNo)
    {
      default:
        // Invalid system call. Do nothing.
        break;
    }
    Scheduler *sch = Scheduler::instance();
    sch->contextSwitch(ctx);
  }
  //outb(0x20, 0x20);
}

void timerISR(void)
{
  asm(
      "push %esi\n\t"
      "push %edi\n\t"
      "push %edx\n\t"
      "push %ecx\n\t"
      "push %ebx\n\t"
      "push %eax\n\t"
      "mov %esp, %eax\n\t"
      "push %eax\n\t"
      "push %ebp\n\t"
      "mov %esp, %eax\n\t"
      "push %eax\n\t"
      "call c_timerISR\n\t"
      "pop %ebx\n\t"
      "pop %ebx\n\t"
      "pop %ebx\n\t" // 3 dummy pop to recover stack pointer after function call.
      "pop %eax\n\t"
      "pop %ebx\n\t"
      "pop %ecx\n\t"
      "pop %edx\n\t"
      "pop %edi\n\t"
      "pop %esi\n\t"
      "leave\n\t"
      "iret\n\t"
     );
}

void syscallISR(void)
{
  asm(
      "push %esi\n\t"
      "push %edi\n\t"
      "push %edx\n\t"
      "push %ecx\n\t"
      "push %ebx\n\t"
      "push %eax\n\t"
      "mov %esp, %eax\n\t"
      "push %eax\n\t"
      "push %ebp\n\t"
      "mov %esp, %eax\n\t"
      "push %eax\n\t"
      "call c_syscallISR\n\t"
      "pop %ebx\n\t"
      "pop %ebx\n\t"
      "pop %ebx\n\t" // 3 dummy pop to recover stack pointer after function call.
      "pop %eax\n\t"
      "pop %ebx\n\t"
      "pop %ecx\n\t"
      "pop %edx\n\t"
      "pop %edi\n\t"
      "pop %esi\n\t"
      "leave\n\t"
      "iret\n\t"
     );
}

