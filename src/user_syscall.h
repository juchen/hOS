#ifndef _USER_SYSCALL_H_
#define _USER_SYSCALL_H_

#ifdef __cplusplus
class Scheduler;
#else
typedef struct _tag_Scheduler Scheduler;
#endif

#ifdef __cplusplus
extern "C" {
#endif

void SysCall_u_putChar(char c); // for user mode.
void SysCall_u_lockScheduler();
void SysCall_u_unlockScheduler();
void SysCall_u_setScheduler(Scheduler *s);
void SysCall_u_setCallGateSelector(short s);

#ifdef __cplusplus
};
#endif

#endif /* _USER_SYSCALL_H_ */

