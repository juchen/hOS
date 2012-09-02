#ifndef _IDLETHREAD_H_
#define _IDLETHREAD_H_

#include "thread.h"

class IdleThread : public Thread
{
public:
  IdleThread();
  virtual unsigned int threadProc();
private:
  BYTE _stack[4096];
};
#endif // _IDLETHREAD_H_

