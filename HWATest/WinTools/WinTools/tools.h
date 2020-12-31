#pragma once
#include <sstream>
#include <fstream>
#include "datatype.h"

typedef union ConvertData
 {
	 unsigned short	us;
	 unsigned int	uu;
	 unsigned long	ul;
	 short			is;
	 int				ii;
	 long			il;
	 float			ff;
	 double			dd;
	 unsigned char	ch[8];
 }ConvertData;

#define ENDIAN_BIG     FALSE //FALSE-表示小端字节  TRUE-表示大端字节

//数字转换为字符串
HWA_TOOL_API void SetDatau2(u2 data, u1* pch);
HWA_TOOL_API void SetDatau4(u4 data, u1* pch);
HWA_TOOL_API void SetDatau8(u8 data, u1* pch);
HWA_TOOL_API void SetDatai2(i2 data, u1* pch);
HWA_TOOL_API void SetDatai4(i4 data, u1* pch);
HWA_TOOL_API void SetDatai8(i8 data, u1* pch);
HWA_TOOL_API void SetDataf4(f8 data, u1* pch);
HWA_TOOL_API void SetDataf8(f8 data, u1* pch);

//字符串转换为数字
HWA_TOOL_API u2 GetDatau2(u1* pch);
HWA_TOOL_API u4 GetDatau4(u1* pch);
HWA_TOOL_API i2 GetDatai2(u1* pch);
HWA_TOOL_API i4 GetDatai4(u1* pch);
HWA_TOOL_API f4 GetDataf4(u1* pch);
HWA_TOOL_API f8 GetDataf8(u1* pch);
HWA_TOOL_API u8 GetDatau8(u1* pch);
HWA_TOOL_API i8 GetDatai8(u1* pch);

//十六进制转十进制
HWA_TOOL_API u1 GetData_CharToHex(char ch);
HWA_TOOL_API u1 GetData_2CharToHex(char* ch);
HWA_TOOL_API u2 GetData_3CharToHex(char* ch);
HWA_TOOL_API u2 GetData_4CharToHex(char* ch);
HWA_TOOL_API u4 GetData_5CharToHex(char* ch);
HWA_TOOL_API u4 GetData_6CharToHex(char* ch);
HWA_TOOL_API u4 GetData_7CharToHex(char* ch);
HWA_TOOL_API u4 GetData_8CharToHex(char* ch);
//在字符串中查找字符
HWA_TOOL_API u4 Pack_FindCharsPos(u1* pbuff, u1* pch);
HWA_TOOL_API u4 Pack_SplitChars(char* input, int len, u1* output);

//文件记录
HWA_TOOL_API void dumpfile(char* buf, int len, char* filename);
HWA_TOOL_API void dumpfile(double data, char* filename);
HWA_TOOL_API void RecordFile(char* buf, int len, CString strFileName);
HWA_TOOL_API void RecordFile(char* buf, int len, CString strFileName, int protocol);