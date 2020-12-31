#include "stdafx.h"
#include "tools.h"

static ConvertData   packset;
const int doy[13] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
const int Leapdoy[13] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };

//数字转换为字符串
void SetDatau2(u2 data, u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	packset.us = data;
	if(!ENDIAN_BIG)
	{
		pch[0] = packset.ch[0];
		pch[1] = packset.ch[1];
	}
	else
	{
		pch[0] = packset.ch[1];
		pch[1] = packset.ch[0];
	}
}
void SetDatau4(u4 data, u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	packset.uu = data;
	if(!ENDIAN_BIG)
	{
		pch[0] = packset.ch[0];
		pch[1] = packset.ch[1];
		pch[2] = packset.ch[2];
		pch[3] = packset.ch[3];
	}
	else
	{
		pch[0] = packset.ch[3];
		pch[1] = packset.ch[2];
		pch[2] = packset.ch[1];
		pch[3] = packset.ch[0];
	}
}
void SetDatau8(u8 data, u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	packset.ul = data;
	if(!ENDIAN_BIG)
	{
		pch[0] = packset.ch[0];
		pch[1] = packset.ch[1];
		pch[2] = packset.ch[2];
		pch[3] = packset.ch[3];
		pch[4] = packset.ch[4];
		pch[5] = packset.ch[5];
		pch[6] = packset.ch[6];
		pch[7] = packset.ch[7];
	}
	else
	{
		pch[0] = packset.ch[7];
		pch[1] = packset.ch[6];
		pch[2] = packset.ch[5];
		pch[3] = packset.ch[4];
		pch[4] = packset.ch[3];
		pch[5] = packset.ch[2];
		pch[6] = packset.ch[1];
		pch[7] = packset.ch[0];
	}
}
void SetDatai2(i2 data, u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	packset.is = data;
	if(!ENDIAN_BIG)
	{
		pch[0] = packset.ch[0];
		pch[1] = packset.ch[1];
	}
	else
	{
		pch[0] = packset.ch[1];
		pch[1] = packset.ch[0];
	}
}
void SetDatai4(i4 data, u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	packset.ii = data;
	if(!ENDIAN_BIG)
	{
		pch[0] = packset.ch[0];
		pch[1] = packset.ch[1];
		pch[2] = packset.ch[2];
		pch[3] = packset.ch[3];
	}
	else
	{
		pch[0] = packset.ch[3];
		pch[1] = packset.ch[2];
		pch[2] = packset.ch[1];
		pch[3] = packset.ch[0];
	}
}
void SetDatai8(i8 data, u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	packset.il = data;
	if(!ENDIAN_BIG)
	{
		pch[0] = packset.ch[0];
		pch[1] = packset.ch[1];
		pch[2] = packset.ch[2];
		pch[3] = packset.ch[3];
		pch[4] = packset.ch[4];
		pch[5] = packset.ch[5];
		pch[6] = packset.ch[6];
		pch[7] = packset.ch[7];
	}
	else
	{
		pch[0] = packset.ch[7];
		pch[1] = packset.ch[6];
		pch[2] = packset.ch[5];
		pch[3] = packset.ch[4];
		pch[4] = packset.ch[3];
		pch[5] = packset.ch[2];
		pch[6] = packset.ch[1];
		pch[7] = packset.ch[0];
	}
}
void SetDataf4(f8 data, u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	packset.ff = data;
	if(!ENDIAN_BIG)
	{
		pch[0] = packset.ch[0];
		pch[1] = packset.ch[1];
		pch[2] = packset.ch[2];
		pch[3] = packset.ch[3];
	}
	else
	{
		pch[0] = packset.ch[3];
		pch[1] = packset.ch[2];
		pch[2] = packset.ch[1];
		pch[3] = packset.ch[0];
	}
}
void SetDataf8(f8 data, u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	packset.dd = data;
	if(!ENDIAN_BIG)
	{
		pch[0] = packset.ch[0];
		pch[1] = packset.ch[1];
		pch[2] = packset.ch[2];
		pch[3] = packset.ch[3];
		pch[4] = packset.ch[4];
		pch[5] = packset.ch[5];
		pch[6] = packset.ch[6];
		pch[7] = packset.ch[7];
	}
	else
	{
		pch[0] = packset.ch[7];
		pch[1] = packset.ch[6];
		pch[2] = packset.ch[5];
		pch[3] = packset.ch[4];
		pch[4] = packset.ch[3];
		pch[5] = packset.ch[2];
		pch[6] = packset.ch[1];
		pch[7] = packset.ch[0];
	}
}

//字符串转换为数字
u2 GetDatau2(u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	if(!ENDIAN_BIG)
	{
		packset.ch[0] = pch[0];
		packset.ch[1] = pch[1];
	}
	else
	{
		packset.ch[1] = pch[0];
		packset.ch[0] = pch[1];
	}
	return packset.us;
}
u4 GetDatau4(u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	if(!ENDIAN_BIG)
	{
		packset.ch[0] = pch[0];
		packset.ch[1] = pch[1];
		packset.ch[2] = pch[2];
		packset.ch[3] = pch[3];
	}
	else
	{
		packset.ch[3] = pch[0];
		packset.ch[2] = pch[1];
		packset.ch[1] = pch[2];
		packset.ch[0] = pch[3];
	}
	return packset.uu;
}
u8 GetDatau8(u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	if(!ENDIAN_BIG)
	{
		packset.ch[0] = pch[0];
		packset.ch[1] = pch[1];
		packset.ch[2] = pch[2];
		packset.ch[3] = pch[3];
		packset.ch[4] = pch[4];
		packset.ch[5] = pch[5];
		packset.ch[6] = pch[6];
		packset.ch[7] = pch[7];
	}
	else
	{
		packset.ch[7] = pch[0];
		packset.ch[6] = pch[1];
		packset.ch[5] = pch[2];
		packset.ch[4] = pch[3] ;
		packset.ch[3] = pch[4];
		packset.ch[2] = pch[5];
		packset.ch[1] = pch[6];
		packset.ch[0] = pch[7];
	}
	return packset.ul;
}
i8 GetDatai8(u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	if(!ENDIAN_BIG)
	{
		packset.ch[0] = pch[0];
		packset.ch[1] = pch[1];
		packset.ch[2] = pch[2];
		packset.ch[3] = pch[3];
		packset.ch[4] = pch[4];
		packset.ch[5] = pch[5];
		packset.ch[6] = pch[6];
		packset.ch[7] = pch[7];
	}
	else
	{
		packset.ch[7] = pch[0];
		packset.ch[6] = pch[1];
		packset.ch[5] = pch[2];
		packset.ch[4] = pch[3] ;
		packset.ch[3] = pch[4];
		packset.ch[2] = pch[5];
		packset.ch[1] = pch[6];
		packset.ch[0] = pch[7];
	}
	return packset.il;
}
i2 GetDatai2(u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	if(!ENDIAN_BIG)
	{
		packset.ch[0] = pch[0];
		packset.ch[1] = pch[1];
	}
	else
	{
		packset.ch[1] = pch[0];
		packset.ch[0] = pch[1];
	}
	return packset.is;
}
i4 GetDatai4(u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	if(!ENDIAN_BIG)
	{
		packset.ch[0] = pch[0];
		packset.ch[1] = pch[1];
		packset.ch[2] = pch[2];
		packset.ch[3] = pch[3];
	}
	else
	{
		packset.ch[3] = pch[0];
		packset.ch[2] = pch[1];
		packset.ch[1] = pch[2];
		packset.ch[0] = pch[3];
	}
	return packset.ii;
}
f4 GetDataf4(u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	if(!ENDIAN_BIG)
	{
		packset.ch[0] = pch[0];
		packset.ch[1] = pch[1];
		packset.ch[2] = pch[2];
		packset.ch[3] = pch[3];
	}
	else
	{
		packset.ch[3] = pch[0];
		packset.ch[2] = pch[1];
		packset.ch[1] = pch[2];
		packset.ch[0] = pch[3];
	}
	return packset.ff;
}
f8 GetDataf8(u1* pch)
{
	memset(&packset, 0, sizeof(ConvertData));
	if(!ENDIAN_BIG)
	{
		packset.ch[0] = pch[0];
		packset.ch[1] = pch[1];
		packset.ch[2] = pch[2];
		packset.ch[3] = pch[3];
		packset.ch[4] = pch[4];
		packset.ch[5] = pch[5];
		packset.ch[6] = pch[6];
		packset.ch[7] = pch[7];
	}
	else
	{
		packset.ch[7] = pch[0];
		packset.ch[6] = pch[1];
		packset.ch[5] = pch[2];
		packset.ch[4] = pch[3] ;
		packset.ch[3] = pch[4];
		packset.ch[2] = pch[5];
		packset.ch[1] = pch[6];
		packset.ch[0] = pch[7];
	}
	return packset.dd;
}
u1 GetData_CharToHex(char ch)
{
	u1 result = 0;

	if(ch >= '0' && ch <= '9')
	{
		result = ch - '0';
	}
	else if(ch >= 'a' && ch <= 'f')
	{
		result = (ch - 'a') + 10;
	}
	else if(ch >= 'A' && ch <= 'F')
	{
		result = (ch - 'A') + 10;
	}
	return result;
}
u1 GetData_2CharToHex(char* ch)
{
	u1 data = (GetData_CharToHex(ch[0]) << 4) + GetData_CharToHex(ch[1]);
	return data;
}
u2 GetData_3CharToHex(char* ch)
{
	u2 data = (GetData_2CharToHex(ch) << 4) + GetData_CharToHex(ch[2]);
	return data;
}
u2 GetData_4CharToHex(char* ch)
{
	u2 data = (GetData_3CharToHex(ch) << 4) + GetData_CharToHex(ch[3]);
	return data;
}
u4 GetData_5CharToHex(char* ch)
{
	u4 data = (GetData_4CharToHex(ch) << 4) + GetData_CharToHex(ch[4]);
	return data;
}
u4 GetData_6CharToHex(char* ch)
{
	u4 data = (GetData_5CharToHex(ch) << 4) + GetData_CharToHex(ch[5]);
	return data;
}
u4 GetData_7CharToHex(char* ch)
{
	u4 data = (GetData_6CharToHex(ch) << 4) + GetData_CharToHex(ch[6]);
	return data;
}
u4 GetData_8CharToHex(char* ch)
{
	u4 data = (GetData_7CharToHex(ch) << 4) + GetData_CharToHex(ch[7]);
	return data;
}
//在字符串中查找字符
u4 Pack_FindCharsPos(u1* pbuff, u1* pch)
{
	u1* pTemp;
	u4   length = 0;
	u4   count = 0;
	pTemp = pbuff;

	while((*pTemp != *pch) && ( *pch != 0))
	{
		pTemp++;
		count++;
		if(count >= 100)//限制了pbuff的长度为100个字节，可以更改
		{
			return 0;
		}
	}

	if(*pTemp == 0)
	{
		length = 0;
	}
	else
	{
		length = (u4)(pTemp - pbuff) + 1;
	}

	return length;
}
u4 Pack_SplitChars(char* input, int len, u1* output)
{
	int length = 0;
	char chTemp[1000][30];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = input[i];
		row++;
		if (input[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (input[i] == '\0')
		{
			break;
		}
		if(row >= 30 || line >= 1000)
			break;
	}
	for (i=0; i<line; i++)
	{
		output[i] = atoi(chTemp[i]);
	}
	return line;
}

void dumpfile(char* buf, int len, char* filename)
{
	ofstream logfile;
	logfile.open(filename, ios::app);
	logfile.write(buf, len);
	logfile.close();
}

void dumpfile(double data, char* filename)
{
	int len=0;
	char buf[MAX_PATH];
	ofstream logfile;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	logfile.open(filename, ios::app);
	sprintf(buf, "%f\r\n", data);
	len = strlen(buf);
	logfile.write(buf, len);
	logfile.close();
}

void RecordFile(char* buf, int len, CString strFileName)
{
	ofstream logfile;
	logfile.open(strFileName, ios::app);
	logfile.write(buf, len);
	logfile.close();
}
void RecordFile(char* buf, int len, CString strFileName, int protocol)
{
	ofstream logfile;
	if (protocol == PROTOCOL_BINARY)
	{
		logfile.open(strFileName, ios::app | ios::binary);
	} 
	else
	{
		logfile.open(strFileName, ios::app);
	}
	logfile.write(buf, len);
	logfile.close();
}