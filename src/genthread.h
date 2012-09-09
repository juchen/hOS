#ifndef _GENTHREAD_H_
#define _GENTHREAD_H_
#include "thread.h"
#include "types.h"

class GenThread : public Thread
{
public:
  GenThread() : Thread(_stack, sizeof(_stack)) {}
  //GenThread(void (*fun)())
private:
  BYTE _stack[4096];
};
#endif // _GENTHREAD_H_
