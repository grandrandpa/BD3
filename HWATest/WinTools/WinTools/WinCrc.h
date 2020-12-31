#pragma once
#include "datatype.h"

#define INIT_CRC	0x00
//CRC8
HWA_TOOL_API u4  CheckCrc(u4 crc, u1* pch, int len);

//CRC32
HWA_TOOL_API void Init_Crctable();
HWA_TOOL_API u4  CheckCrc32(u4 crc, u1* pch, u4 len);

