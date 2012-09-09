/* Copyright 2009, Hsuan-Ju Chen */

#ifndef _PUTCHAR_H_
#define _PUTCHAR_H_

#include "types.h"

#ifdef _PUTCHAR_CPP_
#define EXTERN
#else
#define EXTERN extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

int putchar(int c);
int puts(const char* str);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
class Screen
{
private:
	BYTE *curPos;
	const unsigned int width;
	const unsigned int height;
	BYTE _attr;
public:
	Screen();
	void setAttr(BYTE attr);
	void putchar(int c);
	void cls();
};
#endif // __cplusplus

#undef EXTERN
#endif //_PUTCHAR_H_
