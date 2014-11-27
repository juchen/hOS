#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#ifdef __cplusplus
class ComPort;
class Scheduler;
#else
typedef struct ComPort ComPort;
typedef struct _tag_Scheduler Scheduler;
#endif

typedef struct SysCall_PutCharParam SysCall_PutCharParam;
struct SysCall_PutCharParam
{
  unsigned int _c; // The char to be put.
};

enum SysCallNumber
{
  SYS_CALL_PUT_CHAR,
  SYS_CALL_LOCK_SCHEDULER,
  SYS_CALL_UNLOCK_SCHEDULER,
};

void SysCall_setComPort(ComPort *);

void SysCall_putChar(SysCall_PutCharParam *);
void SysCall_lockScheduler(Scheduler *param);
void SysCall_unlockScheduler(Scheduler *param);

void SysCall_syscall(void *param);

#endif /* _SYSCALL_H_ */

