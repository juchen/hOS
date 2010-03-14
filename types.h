#ifndef _TYPES_H_
#define _TYPES_H_

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned long long QWORD;

#define HIBYTE(x) ((BYTE)(((WORD)(x)) >> 8))
#define LOBYTE(x) (BYTE)(((WORD)(x)) & 0xFF)
#endif //_TYPES_H_
