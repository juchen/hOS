boot1.o: boot1.c
secboot.o: secboot.c secboot.h types.h
printf-stdarg.o: printf-stdarg.c putchar.h types.h
debug.o: debug.cpp debug.h printf-stdarg.h
pm_c_entry.o: pm_c_entry.cpp printf-stdarg.h putchar.h types.h \
 sys_struct.h debug.h isr.h timer8253.h x86functions.h idlethread.h \
 thread.h scheduler.h genthread.h comport.h syscall.h user_syscall.h
putchar.o: putchar.cpp putchar.h types.h secboot.h comport.h debug.h \
 printf-stdarg.h user_syscall.h
sys_struct.o: sys_struct.cpp sys_struct.h debug.h printf-stdarg.h types.h
timer8253.o: timer8253.cpp timer8253.h x86functions.h types.h debug.h \
 printf-stdarg.h
x86functions.o: x86functions.cpp x86functions.h types.h
scheduler.o: scheduler.cpp scheduler.h thread.h types.h debug.h \
 printf-stdarg.h
thread.o: thread.cpp thread.h types.h debug.h printf-stdarg.h scheduler.h
idlethread.o: idlethread.cpp idlethread.h thread.h types.h debug.h \
 printf-stdarg.h
comport.o: comport.cpp comport.h types.h x86functions.h
isr.o: isr.cpp isr.h thread.h types.h scheduler.h x86functions.h \
 syscall.h
syscall.o: syscall.cpp syscall.h comport.h types.h scheduler.h
user_syscall.o: user_syscall.cpp user_syscall.h syscall.h scheduler.h
