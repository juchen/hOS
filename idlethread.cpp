#include "idlethread.h"
#include "debug.h"

IdleThread::IdleThread()
  : Thread(_stack, sizeof(_stack))
{
}

unsigned int IdleThread::threadProc()
{
  CHECK_POINT;
  while(1) {}
  return 0;
}
