#include "user_syscall.h"
#include "syscall.h"
#include "scheduler.h"

static Scheduler *scheduler;
short callGateSelector;
static void *syscall(int no, void *param)
{
  void *ret;
  //unsigned int s = (((unsigned int)callGateSelector) << 16);
  unsigned int s = callGateSelector;
  asm(
      "mov %1, %%eax\n\t"
      "mov %2, %%edx\n\t"
      "pushf\n\t"
      //"mov %0, %%eax\n\t"
      //"ljump $8, $0\n\t"
      //"lcall *%0\n\t"
      "lcall $0x43, $0\n\t"
      ::"g"(s), "g"(no), "g"(param)
     );
  /*
  asm(
      "mov %1, %%eax\n\t"
      "mov %2, %%ebx\n\t"
      "int $0x30\n\t"
      "mov %%eax, %0\n\t"
      :"=g"(ret):"g"(no),"g"(param):"eax","ebx"
     );
     */
  return ret;
}

void SysCall_u_putChar(char c)
{
  SysCall_PutCharParam param;
  param._c = c;
  syscall(SYS_CALL_PUT_CHAR, &param);
}

void SysCall_u_lockScheduler()
{
  if(0 != scheduler)
  {
    syscall(SYS_CALL_LOCK_SCHEDULER, scheduler);
  }
}

void SysCall_u_unlockScheduler()
{
  if(0 != scheduler)
  {
    syscall(SYS_CALL_UNLOCK_SCHEDULER, scheduler);
  }
}

void SysCall_u_setScheduler(Scheduler *s)
{
  scheduler = s;
}

void SysCall_u_setCallGateSelector(short s)
{
  callGateSelector = s;
  /*
  asm(
      "ljmp $0x8, $0x00888888\n\t"
     );
     */
  /*
  asm(
      "pushf\n\t"
      "mov %0, %%eax\n\t"
      //"ljump $8, $0\n\t"
      //"lcall $8, $0\n\t"
      ::"g"(s)
     );
     */
}

