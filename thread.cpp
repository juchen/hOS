#define _THREAD_CPP_
#include "thread.h"
#include "debug.h"

unsigned int threadEntry(Thread *thread)
{
  thread->threadProc();
}

Thread::Thread(BYTE *stack, unsigned int stackByteCnt)
  : _next(0),
    _stack(stack),
    _stackByteCnt(stackByteCnt & (~0x03))
{
  // init stack to take input parameters to stack entry function.
  // The parameter points to 'this' object of Thread class.
  // Entry function will in turn call the virtual function of threadProc of this object.
  DWORD *pos = reinterpret_cast<DWORD *>(_stack + _stackByteCnt);
  *(--pos) = reinterpret_cast<DWORD>(this);
  *(--pos) = 0;

  // Init context. So that context switch can go smoothly.
  // The SS:SP must be correct.
  _ctxEbp._esp = (DWORD)pos;
  _ctxEbp._eip = (DWORD)(Thread::invokeThread);
}

// This function is going to be run under user mode.
void Thread::invokeThread(Thread *This)
{
  int ret = This->threadProc();
  printf("Thread 0x%x returned with value %d\n", ret);
  while(1)
  {
    // TODO: call some system call to remove this thread out of the scheduler.
  }
}

void Thread::loadContext(Context *ctx)
{
  ctx->_contextEbp->_eip = _ctxEbp._eip;
  ctx->_contextEbp->_esp = _ctxEbp._esp;
  ctx->_contextEbp->_ebp = _ctxEbp._ebp;

  *(ctx->_contextEsp) = _ctxEsp;
}

