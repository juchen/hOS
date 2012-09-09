#define _DEBUG_CPP_
#include "debug.h"
#include "printf-stdarg.h"

void onAssert(const char *filename, unsigned int linenum, bool condition)
{
	if(!condition)
	{
		printf("%s:%d: Assertion Failed!\n", filename, linenum);
		while(1);
	}
}
