boot1.o: boot1.c
secboot.o: secboot.c secboot.h types.h
printf-stdarg.o: printf-stdarg.c putchar.h types.h
pm_c_entry.o: pm_c_entry.cpp printf-stdarg.h putchar.h types.h
putchar.o: putchar.cpp putchar.h types.h secboot.h
