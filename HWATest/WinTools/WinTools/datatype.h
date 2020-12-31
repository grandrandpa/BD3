#pragma once

#ifdef HWA_TOOL_EXPORTS
#define HWA_TOOL_API __declspec(dllexport)
#else
#define HWA_TOOL_API __declspec(dllimport)
#endif

typedef char       i1;
typedef short      i2;
typedef int        i4;
typedef long       i8;

typedef unsigned char      u1;
typedef unsigned short     u2;
typedef unsigned int       u4;
typedef unsigned long      u8;

typedef float     f4;
typedef double    f8;
