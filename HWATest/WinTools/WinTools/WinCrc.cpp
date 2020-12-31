#include "StdAfx.h"
#include "WinCrc.h"


//校验位计算
//CRC8
u4  CheckCrc(u4 crc, u1* pch, int len)
{
	for (int i = 1; i < len; i++ )
	{
		crc ^= (byte)pch[i];
	}
	return crc;
}
//CRC32
static u4 crc_table[256];
void Init_Crctable()
{
	u4 crc = 0;
	u4 i = 0, j = 0;
	for(i=0; i<256; i++)
	{
		crc = i;
		for(j=0; j<8; j++)
		{
			if(crc & 0x01)
			{
				crc = (crc >> 1)^0xEDB88320;
			}
			else
			{
				crc = (crc >> 1);
			}
		}
		crc_table[i] = crc;
	}
}
u4  CheckCrc32(u4 crc, u1* pch, u4 len)
{
	Init_Crctable();
	for(u4 i=0; i<len; i++)
	{
		crc = crc_table[(crc & 0xFF)^pch[i]] ^ (crc >> 8);
	}
	return crc;
}
//
