CC=gcc
CPP=g++
AS=gcc -c
LD=gcc

CFLAG = -m32 -fno-stack-protector -nostdlib -g
ASFLAG = -m32
#-ffreestanding
CPPFLAG = $(CFLAG) -fno-rtti -fno-exceptions 
#LDFLAG = -m32 -Wl,-e main -Wl,-N -Wl,--oformat binary -Wl,-Ttext 0x0
LDFLAG = -Wl,-N -Wl,-emain -Wl,-Ttext=0x0
ENTRY_OBJ = boot3.o
OBJS = boot1.o

SEC_ENTRY_OBJ = secbootinit.o pm_entry.o 
SEC_OBJS = secboot.o printf-stdarg.o 
SEC_CPP_OBJS = debug.o\
							 pm_c_entry.o\
							 putchar.o\
							 sys_struct.o\
							 timer8253.o\
							 x86functions.o\
							 scheduler.o\
							 thread.o\
							 idlethread.o\
							 comport.o\
							 isr.o\
							 syscall.o\
							 user_syscall.o\

TOTAL_OBJS = $(OBJS) $(SEC_OBJS)
TOTAL_CPP_OBJS = $(SEC_CPP_OBJS)
C_FILES = $(addsuffix .c, $(basename $(TOTAL_OBJS)))
CPP_FILES = $(addsuffix .cpp, $(basename $(TOTAL_CPP_OBJS)))

.phony:clean all

all:boot.bin secboot.bin

clean:
	rm -rf $(ENTRY_OBJ) $(OBJS) $(SEC_ENTRY_OBJ) $(SEC_OBJS) $(SEC_CPP_OBJS)
	rm -rf boot.bin secboot.bin secboot.elf boot.elf

boot.bin:boot.elf
	objcopy -R .note.gnu.build-id -R .eh_frame -O binary boot.elf boot.bin

boot.elf:$(ENTRY_OBJ) $(OBJS)
	$(LD) $(CFLAG) $(LDFLAG) -o boot.elf $(ENTRY_OBJ) $(OBJS) 

secboot.bin:secboot.elf
	objcopy -O binary secboot.elf secboot.bin

secboot.elf:$(SEC_ENTRY_OBJ) $(SEC_OBJS) $(SEC_CPP_OBJS)
	$(LD) $(CFLAG) -o secboot.elf $(SEC_ENTRY_OBJ) $(SEC_OBJS) $(SEC_CPP_OBJS) -Wl,-Tlink.ld 

boot1.o:boot1.c
	$(CC) -c -Os $(CFLAG) $<

%.o:%.c
	$(CC) -c $(CFLAG) $<

%.s:%.c
	$(CC) -S $(CFLAG) $<

%.o:%.cpp
	$(CPP) -c $(CPPFLAG) $<

%.s:%.cpp
	$(CPP) -S $(CPPFLAG) $<

%.o:%.C
	$(CPP) -c $(CPPFLAG) $<

%.o:%.s
	$(AS) $(ASFLAG) -o $@ $< 

dependency:
	$(CC) -MM $(C_FILES) $(CPP_FILES) > dependency.mak

include dependency.mak


