#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

class Thread;
struct Context;

class Scheduler
{
public:
  //Scheduler(Thread *idle);
  Scheduler();
  //void switchTo(Context *ctx);
  void addThread(Thread *thr);
  void start(Context *ctx);
  void contextSwitch(Context *ctx);
  static Scheduler *instance();
  static void setScheduler(Scheduler *sch);

private:
  Thread *mCurrent;
  Thread *mReadyHead;
  Thread *mReadyTail;
  void addThreadToTail(Thread *thr);
  Thread *getThreadFromHead();
  static Scheduler *_sch;
};

#endif // _SCHEDULER_H_
