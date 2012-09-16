#ifndef _ISR_H_
#define _ISR_H_

#ifdef __cplusplus
extern "C" {
#endif
void timerISR(void);
void syscallISR(void);
#ifdef __cplusplus
}
#endif

#endif // _ISR_H_
