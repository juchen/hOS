#include "isr.h"
#include "thread.h"
#include "scheduler.h"
#include "x86functions.h"

void timerISR(void)
{
  ContextEsp ctxEsp;
  ContextEbp *ctxEbp;
  Context ctx;
  asm(
      "mov %%eax, %0\n\t"
      "mov %%ebx, %1\n\t"
      "mov %%ecx, %2\n\t"
      "mov %%edx, %3\n\t"
      "mov %%edi, %4\n\t"
      "mov %%esi, %5\n\t"
      ::"g"(ctxEsp._eax),
      "g"(ctxEsp._ebx),
      "g"(ctxEsp._ecx),
      "g"(ctxEsp._edx),
      "g"(ctxEsp._edi),
      "g"(ctxEsp._esi)
     );
  asm(
      "mov %%ebp, %0\n\t"
      :"=g"(ctxEbp)
     );
  ctx._contextEbp = ctxEbp;
  Scheduler *sch = Scheduler::instance();
  sch->contextSwitch(&ctx);
  //outb(0x20, 0x20);
  asm(
      "mov %0, %%eax\n\t"
      "mov %1, %%ebx\n\t"
      "mov %2, %%ecx\n\t"
      "mov %3, %%edx\n\t"
      "mov %4, %%edi\n\t"
      "mov %5, %%esi\n\t"
      "mov $0x20, %%al\n\t"
      "out %%al, $0x20\n\t"
      "leave\n\t"
      "iret\n\t"
      :"=g"(ctxEsp._eax),
      "=g"(ctxEsp._ebx),
      "=g"(ctxEsp._ecx),
      "=g"(ctxEsp._edx),
      "=g"(ctxEsp._edi),
      "=g"(ctxEsp._esi)
     );
}
