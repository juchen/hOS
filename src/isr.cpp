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

