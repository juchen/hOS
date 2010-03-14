boot1.o: boot1.c
secboot.o: secboot.c secboot.h types.h
printf-stdarg.o: printf-stdarg.c putchar.h types.h
debug.o: debug.cpp debug.h printf-stdarg.h
pm_c_entry.o: pm_c_entry.cpp printf-stdarg.h putchar.h types.h \
  sys_struct.h debug.h isr.h
putchar.o: putchar.cpp putchar.h types.h secboot.h
sys_struct.o: sys_struct.cpp sys_struct.h debug.h printf-stdarg.h types.h
