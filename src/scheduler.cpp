#include "scheduler.h"
#include "thread.h"
#include "debug.h"

/*
Scheduler::Scheduler(Thread *idle)
  : mCurrent(idle),
  mReadyHead(0),
  mReadyTail(0)
{
}
*/

Scheduler::Scheduler()
  : mCurrent(0),
  mReadyHead(0),
  mReadyTail(0),
  mLockCount(0)
{
}

/*
void Scheduler::switchTo(Context *ctx)
{
  mCurrent->loadContext(ctx);
}
*/

void Scheduler::addThreadToTail(Thread *thr)
{
  thr->setNext(0);
  if(0 == mReadyTail)
  {
    ASSERT(0 == mReadyHead);
    mReadyHead = thr;
  }
  else
  {
    mReadyTail->setNext(thr);
  }
  mReadyTail = thr;
}

void Scheduler::addThread(Thread *thr)
{
  addThreadToTail(thr);
}

Scheduler *Scheduler::_sch = 0;

void Scheduler::setScheduler(Scheduler *sch)
{
  _sch = sch;
}

Scheduler *Scheduler::instance()
{
  ASSERT(0 != _sch);
  return _sch;
}

Thread *Scheduler::getThreadFromHead()
{
  Thread *ret = 0;
  if(0 == mReadyHead)
  {
  }
  else
  {
    ret = mReadyHead;
    mReadyHead = mReadyHead->next();
    ret->setNext(0);
    if(0 == mReadyHead) // list become empty.
    {
      mReadyTail = 0;
    }
  }
  return ret;
}

void Scheduler::contextSwitch(Context *ctx)
{
  if(mLockCount > 0 && ctx->isToSwitch() && 0 != mReadyHead)
  {
    mCurrent->storeContext(ctx);
    addThreadToTail(mCurrent);
    mCurrent = getThreadFromHead();
    mCurrent->loadContext(ctx);
  }
}

void Scheduler::start(Context *ctx)
{
  ASSERT(0 == mCurrent);
  ASSERT(0 != mReadyHead);
  mCurrent = getThreadFromHead();
  ASSERT(0 != mCurrent);
  mCurrent->loadContext(ctx);
}

/*
void contextSwitch(Context *ctx)
{
  if(ctx->isToSwitch())
  {
    mCurrent->
  }
}
*/

void Scheduler::lock()
{
  mLockCount++;
}

void Scheduler::unlock()
{
  ASSERT(mLockCount > 0);
  mLockCount--;
}

