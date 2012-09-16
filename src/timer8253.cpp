#define _TIMER8253_CPP_
#include "timer8253.h"
#include "x86functions.h"
#include "debug.h"

#define CH0_DATA 0x40
#define CH1_DATA 0x41
#define CH2_DATA 0x42
#define MODE_CMD 0x43
#define PERIOD 20 // ms
#define DIVISOR ((WORD)((1193.180)*PERIOD/2))

Timer8253::Timer8253()
{
	outb(MODE_CMD, 0x36); // channel 0, rw LSB/MSB, mode3 (square wave), Binary.
	io_wait();
	outb(CH0_DATA, LOBYTE(DIVISOR));
	io_wait();
	outb(CH0_DATA, HIBYTE(DIVISOR));
}
