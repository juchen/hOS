CC=gcc
CPP=g++
AS=as
LD=ld

CFLAG = -fno-stack-protector -nostdlib -g
#-ffreestanding
CPPFLAG = $(CFLAG) -fno-rtti -fno-exceptions 
LDFLAG = -e main -N --oformat binary -Ttext 0x0
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

TOTAL_OBJS = $(OBJS) $(SEC_OBJS)
TOTAL_CPP_OBJS = $(SEC_CPP_OBJS)
C_FILES = $(addsuffix .c, $(basename $(TOTAL_OBJS)))
CPP_FILES = $(addsuffix .cpp, $(basename $(TOTAL_CPP_OBJS)))

.phony:clean all

all:boot.bin secboot.bin

clean:
	rm -rf $(ENTRY_OBJ) $(OBJS) $(SEC_ENTRY_OBJ) $(SEC_OBJS) $(SEC_CPP_OBJS)
	rm -rf boot.bin secboot.bin

boot.bin:$(ENTRY_OBJ) $(OBJS)
	$(LD) -o boot.bin $(ENTRY_OBJ) $(OBJS) $(LDFLAG)

secboot.bin:secboot.elf
	objcopy -O binary secboot.elf secboot.bin

secboot.elf:$(SEC_ENTRY_OBJ) $(SEC_OBJS) $(SEC_CPP_OBJS)
	$(LD) -o secboot.elf $(SEC_ENTRY_OBJ) $(SEC_OBJS) $(SEC_CPP_OBJS) -Tlink.ld -g

boot1.o:boot1.c
	$(CC) -c $< $(CFLAG) 

%.o:%.c
	$(CC) -c $< $(CFLAG)

%.s:%.c
	$(CC) -S $< $(CFLAG) 

%.o:%.cpp
	$(CPP) -c $< $(CPPFLAG)

%.s:%.cpp
	$(CPP) -S $< $(CPPFLAG)

%.o:%.C
	$(CPP) -c $< $(CPPFLAG)

%.o:%.s
	$(AS) -o $@ $< $(ASFLAG)

dependency:
	$(CC) -MM $(C_FILES) $(CPP_FILES) > dependency.mak

include dependency.mak

