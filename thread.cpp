#define _THREAD_CPP_
#include "thread.h"

unsigned int threadEntry(Thread *thread)
{
  thread->threadProc();
}

Thread::Thread(BYTE *stack, unsigned int stackByteCnt)
  : _stack(stack),
    _next(0),
    _stackByteCnt(stackByteCnt & (~0x03))
{
  // init stack to take input parameters to stack entry function.
  // The parameter points to 'this' object of Thread class.
  // Entry function will in turn call the virtual function of threadProc of this object.
  DWORD *pos = static_cast<DWORD *>(_stack + _stackByteCnt);
  *(--pos) = reinterpret_cast<DWORD>(this);
  *(--pos) = 0;

  // Init context. So that context switch can go smoothly.
  // The SS:SP must be correct.
}
