#ifndef _SECBOOT_H_
#define _SECBOOT_H_

#include "types.h"

#ifdef _SECBOOT_C_
#define EXTERN
#else
#define EXTERN extern
#endif

#define SEG_DESC_NUM 5
//const DWORD SEG_NULL_SELECTOR = 0;
//const DWORD SEG_CODE_SELECTOR = 8;
//const DWORD SEG_DATA_SELECTOR = 16;
//const DWORD SEG_STACK_SELECTOR = 24;
//const DWORD SEG_VIDEO_SELECTOR = 32;

#define SEG_NULL_SELECTOR  (0)
#define SEG_CODE_SELECTOR  (8)
#define SEG_DATA_SELECTOR  (16)
#define SEG_STACK_SELECTOR (24)
#define SEG_VIDEO_SELECTOR (32)

#undef EXTERN
#endif // _SECBOOT_H_
