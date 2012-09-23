#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "printf-stdarg.h"

#define ASSERT(x) onAssert(__FILE__, __LINE__, (x))

void onAssert(const char *filename, unsigned int linenum, bool condition);

#define TRACE_HEX(x) printf(__FILE__ ":%d:" #x " = 0x%08x\n", __LINE__, (unsigned int)(x))
#define CHECK_POINT printf(__FILE__ ":%d: check point\n", __LINE__)

#endif // _DEBUG_H_
