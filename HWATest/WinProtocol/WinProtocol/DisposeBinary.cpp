#include "StdAfx.h"
#include "DisposeBinary.h"
//////////////////////////////////////////////////////////////////////////
///备注：当卫星号大于40，则减去40。
//////////////////////////////////////////////////////////////////////////
const DisposeFrame FrameBIN[] =
{
	{"$GNREF,", OUT_GNREF, NULL},
	{"$GNMOD,", OUT_GNMOD, NULL},
	{"$GNCOM,", OUT_GNCOM, NULL},
	{"$BDRAN,", OUT_BDRAN, NULL},
	{"$BDEPH,", OUT_BDEPH, NULL},
	{"$BSEPH,", OUT_BSEPH, NULL},
	{"$BDALM,", OUT_BDALM, NULL},
	{"$BSALM,", OUT_BSALM, NULL},
	{"$BDJAL,", OUT_BDJAL, NULL},
	{"$BSJAL,", OUT_BSJAL, NULL},
	{"$BDION,", OUT_BDION, NULL},
	{"$BSION,", OUT_BSION, NULL},
	{"$GNCOD,", OUT_GNCOD, NULL},
	{"$GNPOS,", OUT_GNPOS, NULL},
	{"$GNXPV,", OUT_GNXPV, NULL},
	{"$GNTIM,", OUT_GNTIM, NULL},
	{"$GNSTA,", OUT_GNSTA, NULL},
	{"$BDGSV,", OUT_BDGSV, NULL},
	{"$BDGBS,", OUT_GNGBS, NULL},
	{"$BDSIM,", OUT_BDSIM, NULL},
	{"$BDVER,", OUT_BDVER, NULL},
	{"$STMOD,", SET_MOD, NULL},
	{"$STLOG,", SET_LOG, NULL},
	{"$STSTA,", SET_STA, NULL},
	{"$BDCHD,", OUT_BDCHD, NULL},//add by cy 20180715
	{"$BDPAO,", OUT_BDPAO, NULL}
	
};
const u1 m_nframeNum = sizeof(FrameBIN)/sizeof(DisposeFrame);

CDisposeBinary::CDisposeBinary(void)
{
	Reset();
}

CDisposeBinary::~CDisposeBinary(void)
{
	Reset();
}

int CDisposeBinary::FindHead(u1* buf, int len)
{
	unsigned short data = 0;
	for (int i = 0; i < m_nframeNum; i++)
	{
		data = (buf[5] << 8) + buf[4];
		if (FrameBIN[i].nFrame == data)
		{
			return data;
		}
	}
	return -1;
}
void CDisposeBinary::DisposeData(char* buf, int len)
{
	u1 ch = 0;
	u4 crc = 0;
	//BD2_SRC* data = new BD2_SRC;
	//data->length = len;
	//memcpy(data->Buffer, buf, len);
	//m_Listener.OnAnswerInfoFrame((WPARAM)data, 0);//先将原始数据上发，在解析
	for (int i = 0; i < len; i++)
	{
		ch = buf[i];
		switch(m_CmdState)
		{
		case RECV_CMD_START:
			if(m_chLen == 0)
			{
				if(ch == 0xAA)
				{
					m_chBuffer[m_chLen++] = ch;
				}
			}
			else if(m_chLen == 1)
			{
				if(ch == 0x44)
				{
					m_chBuffer[m_chLen++] = ch;
				}
				else if(ch == 0xAA)
				{
					m_chLen = 0;
					m_chBuffer[m_chLen++] = ch;
				}
				else
				{
					Reset();
				}
			}
			else
			{
				m_chBuffer[m_chLen++] = ch;
				if (m_chLen > 10)
				{
					m_nFrame = FindHead((u1*)m_chBuffer, m_chLen);
					if (m_nFrame != -1)
					{
						m_CmdState = RECV_CMD_DATA;
					}
					else
					{
						Reset();
					}
				}
			}
			break;
		case RECV_CMD_DATA:
			m_chBuffer[m_chLen++] = ch;
			if(m_chBuffer[m_chLen - 4] == 0x55 && m_chBuffer[m_chLen - 3] == 0x66 && m_chBuffer[m_chLen - 2] == char(0x77) && m_chBuffer[m_chLen - 1] == char(0x88))
			{
				crc = CheckCrc32(INIT_CRC, (u1*)m_chBuffer, m_chLen-8);
				if(crc == GetDatau4((u1*)m_chBuffer+(m_chLen - 8)))
				{
					DisposeIndex(m_nFrame);
					Reset();
				}
			}
			if (m_chLen > BUFF_LEN)
			{
				Reset();
			}
			break;
		default:
			break;
		}
	}
}
void CDisposeBinary::DisposeIndex(int index)
{
	switch (index)
	{
	case OUT_GNREF:
		DisposeGNREF((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_GNMOD:
		DisposeGNMOD((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_GNCOM:
		DisposeGNCOM((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_BDRAN:
		DisposeGNRAN((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_BDEPH:
		DisposeBDEPH((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_BSEPH:
		DisposeBSEPH((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_BDALM:
		DisposeBDALM((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_BSALM:
		DisposeBSALM((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_BDJAL:
		break;
	case OUT_BSJAL:
		DisposeBSJAL((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_BDION:
		DisposeBDION((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_BSION:
		DisposeBSION((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_GNCOD:
		DisposeGNCOD((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_GNPOS:
		DisposeGNPOS((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_GNXPV:
		DisposeGNXPV((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_GNTIM:
		DisposeGNTIM((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_GNSTA:
		DisposeGNSTA((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_BDGSV:
		DisposeGNGSV((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_GNGBS:
		DisposeGNGBS((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_BDSIM:
		DisposeBDSIM((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_BDVER:
		DisposeBDVER((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_BDCHD:
		DisposeBDCHD((u1*)m_chBuffer, m_chLen);
		break;
	case OUT_BDPAO:
		DisposeBDPAO((u1*)m_chBuffer, m_chLen);
		break;


#ifdef _HWA_TEST
	case SET_MOD:
		DisposeSETMOD((u1*)m_chBuffer, m_chLen);
		break;
	case SET_LOG:
		DisposeSETLOG((u1*)m_chBuffer, m_chLen);
		break;
	case SET_STA:
		DisposeSETSTA((u1*)m_chBuffer, m_chLen);
		break;
#endif
	default:
		break;
	}
	BD2_SRC data;
	data.type = index;
	data.length = m_chLen;
	memcpy(data.Buffer, m_chBuffer, m_chLen);
	m_Listener.OnAnswerInfoSRC((WPARAM)&data, index);
}
/******************************参数设置*****************************************************/
int CDisposeBinary::PacketBD2POSData(char* pBuff, const BD2_POS& data)
{
	int i=0;
	u4 crc=0, len=0;
	u1 chBuff[512];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = (0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(OUT_GNPOS, (u1*)chBuff+len);
	len += 2;
	SetDatau2(data.week, chBuff+len);
	len += 2;
	SetDatau4(int(data.tow*10), chBuff+len);
	len += 4;
	chBuff[len] = data.mode;
	len += 1;
	chBuff[len] = data.num;
	len += 1;
	chBuff[len] = data.numuse;
	len += 1;
	SetDataf8(data.blh.lat, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.blh.lon, chBuff+len);
	len += 8;
	SetDataf8(data.blh.alt, chBuff+len);
	len += 8;
	SetDataf8(data.speed.x, chBuff+len);
	len += 8;
	SetDataf8(data.speed.y, chBuff+len);
	len += 8;
	SetDataf8(data.clock, chBuff+len);
	len += 8;
	SetDataf8(data.dop.hdop, chBuff+len);
	len += 8;
	SetDataf8(data.dop.vdop, chBuff+len);
	len += 8;
	SetDataf8(data.dop.pdop, chBuff+len);
	len += 8;
	SetDataf8(data.dop.tdop, chBuff+len);
	len += 8;
	SetDataf8(data.dop.gdop, chBuff+len);
	len += 8;
	for(i=0; i<data.numuse; i++)
	{
		chBuff[len+i] = data.Ids[i];
	}
	len += data.numuse;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = (0x88);
	len += 1;
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketTIMData(char* pBuff, const SETTIM& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_TIM, (u1*)chBuff+len);
	len += 2;
	SetDataf8(data.delay, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.zeroVal, (u1*)(chBuff+len));
	len += 8;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketTMDData(char* pBuff, const SETTMD& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_TMD, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.mode;
	len += 1;
	if(data.mode == 0)
	{
		chBuff[len] = data.svId;
		len += 1;
		chBuff[len] = data.branch;
		len += 1;
	}
	else
	{
		chBuff[len] = data.flag;
		len += 1;
		chBuff[len] = 0;
		len += 1;
	}
	SetDataf8(data.lat, (u1*)(chBuff+len));
	len += 8;
	SetDataf8(data.lon, (u1*)(chBuff+len));
	len += 8;
	SetDataf8(data.alt, (u1*)(chBuff+len));
	len += 8;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;

	memcpy(pBuff, chBuff, len);
	return len;
}
int CDisposeBinary::PacketCHAData(char* pBuff, const SETCHA& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_CHA, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.id;
	len += 1;
	chBuff[len] = data.branch;
	len += 1;
	chBuff[len] = data.pilot;
	len += 1;
	SetDatau2(data.chId, (u1*)(chBuff+len));
	len += 2;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketCOMData(char* pBuff, const SETCOM& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_COM, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.com;
	len += 1;
	chBuff[len] = data.baud;
	len += 1;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketMODData(char* pBuff, const SETMOD& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_MOD, (u1*)chBuff+len);
	len += 2;
	SetDatau2(data.BD2Pos, (u1*)chBuff+len);
	len += 2;
	SetDatau2(data.BD1Pos, (u1*)(chBuff+len));
	len += 2;
	chBuff[len] = 0;
	len += 1;
	chBuff[len] = 0;
	len += 1;
	SetDatau2(0, (u1*)(chBuff+len));
	len += 2;
	SetDatau2(data.BD2Time, (u1*)(chBuff+len));
	len += 2;
	SetDatau2(data.BD1Time, (u1*)(chBuff+len));
	len += 2;
	chBuff[len] = 0;
	len += 1;
	chBuff[len] = 0;
	len += 1;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;
	memcpy(pBuff, chBuff, len);

	return len;
}


int CDisposeBinary::PacketWORKMODData(char* pBuff, const WORKMOD& data)//工作模式
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_WORK, (u1*)chBuff+len);
	len += 2;
	//
	chBuff[len] = data.mode;
	len += 1;
	chBuff[len] = data.svstart;
	len += 1;
	chBuff[len] = data.svend;
	len += 1;
	//
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;
	memcpy(pBuff, chBuff, len);

	return len;
}

int CDisposeBinary::PacketISTData(char* pBuff, const SETIST& data)//入站信号发射
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_IST, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.fp;
	len += 1;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;
	memcpy(pBuff, chBuff, len);

	return len;
}


int CDisposeBinary::PacketLOGData(char* pBuff, const SETLOG& data)
{
	u4 crc = 0;
	int len=0, type=0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));

	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_LOG, (u1*)chBuff+len);
	len += 2;
	if(data.freq != -3)
		type = data.type;

	chBuff[len] = data.port;
	len += 1;
	SetDatau2(type, (u1*)(chBuff+len));
	len += 2;
	SetDatau2(data.freq, (u1*)(chBuff+len));
	len += 2;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketPOSData(char* pBuff, const SETPOS& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_POS, (u1*)chBuff+len);
	len += 2;
	SetDataf8(data.xyz.x, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.xyz.y, (u1*)(chBuff+len));
	len += 8;
	SetDataf8(data.xyz.z, (u1*)(chBuff+len));
	len += 8;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketWIDData(char* pBuff, const SETWID& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_WID, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.id;
	len += 1;
	chBuff[len] = data.branch;
	len += 1;
	chBuff[len] = data.width;
	len += 1;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketBDIData(char* pBuff, const SETREF& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[200];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_BDI, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.timeSys;
	len += 1;
	chBuff[len] = data.timeFmt;
	len += 1;
	chBuff[len] = data.posSys;
	len += 1;
	chBuff[len] = data.posFmt;
	len += 1;
	SetDataf8(data.ellipse.a, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.f, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.w, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.gm, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.dx, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.dy, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.dz, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.alpha, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.beta, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.gamma, (u1*)chBuff+len);
	len += 8;
	chBuff[len] = data.com.com;
	len += 1;
	chBuff[len] = data.com.baud;
	len += 1;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketREFData(char* pBuff, const SETREF& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[200];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_REF, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.timeSys;
	len += 1;
	chBuff[len] = data.timeFmt;
	len += 1;
	chBuff[len] = data.posSys;
	len += 1;
	chBuff[len] = data.posFmt;
	len += 1;
	SetDataf8(data.ellipse.a, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.f, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.w, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.gm, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.dx, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.dy, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.dz, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.alpha, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.beta, (u1*)chBuff+len);
	len += 8;
	SetDataf8(data.ellipse.gamma, (u1*)chBuff+len);
	len += 8;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketMUTData(char* pBuff, const SETMUT& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_MUT, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.branch;
	len += 1;
	chBuff[len] = data.mutiPath;
	len += 1;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;

	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketEACData(char* pBuff, const SETEAC& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_EAC, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.id;
	len += 1;
	chBuff[len] = data.pilotId;
	len += 1;
	chBuff[len] = data.pilotBranch;
	len += 1;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;

	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketBGTData(char* pBuff, const SETBGT& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_BGT, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.id;
	len += 1;
	SetDatau2(data.wn, (u1*)(chBuff+len));
	len += 2;
	SetDatau4(data.t0, (u1*)(chBuff+len));
	len += 4;
	SetDataf8(data.a0, (u1*)(chBuff+len));
	len += 8;
	SetDataf8(data.a1, (u1*)(chBuff+len));
	len += 8;
	SetDataf8(data.a2, (u1*)(chBuff+len));
	len += 8;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;

	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketTTFData(char* pBuff, const SETTTF& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_TTF, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.mod;
	len += 1;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;

	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketSTAData(char* pBuff, const SETSTA& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_STA, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.mod;
	len += 1;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;

	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketSTSData(char* pBuff, const SETSTS& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_STS, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.b1;
	len += 1;
	chBuff[len] = data.b2;
	len += 1;
	chBuff[len] = data.b3;
	len += 1;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;

	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketEVAData(char* pBuff, const SETEVA& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_EVA, (u1*)chBuff+len);
	len += 2;
	SetDatau2(data.elv, (u1*)chBuff+len);
	len += 2;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;

	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketACQData(char* pBuff, const SETACQ& data)//捕获模式
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_ACQ, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.branch;
	len += 1;
	chBuff[len] = data.mode;
	len += 1;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;

	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketTRKData(char* pBuff, const SETTRK& data)//跟踪模式
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_TRK, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.branch;
	len += 1;
	chBuff[len] = data.mode;
	len += 1;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;

	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketIONData(char* pBuff, const SETION& data)
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));

	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_ION, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.ionFlag;
	len += 1;
	chBuff[len] = data.troFlag;
	len += 1;
	chBuff[len] = data.altFlag;
	len += 1;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;

	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketPILOTData(char* pBuff, const SETPILOT& data)//数据导频
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(data.ID, (u1*)chBuff+len);
	len += 2;
	chBuff[len] = data.branch;
	len += 1;
	chBuff[len] = data.mode;
	len += 1;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;

	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBinary::PacketACKData(char* pBuff, const SETACK& data)//查询模式
{
	u4 crc = 0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	chBuff[0] = char(0xAA);
	chBuff[1] = 0x44;
	chBuff[2] = 0x12;
	chBuff[3] = 0x34;
	len += 4;
	SetDatau2(SET_ACK, (u1*)chBuff+len);
	len += 2;
	SetDatau2(data.ID, (u1*)chBuff+len);
	len += 2;
	crc = CheckCrc32(crc, (u1*)chBuff, len);
	SetDatau4(crc, (u1*)chBuff+len);
	len += 4;
	chBuff[len] = 0x55;
	len += 1;
	chBuff[len] = 0x66;
	len += 1;
	chBuff[len] = 0x77;
	len += 1;
	chBuff[len] = char(0x88);
	len += 1;

	memcpy(pBuff, chBuff, len);

	return len;
}


int CDisposeBinary::PacketEPQData(char* pBuff, const SETEPQ& data)
{
    return 0;
}

/****************************数据解析************************************************************/
//////////////////////////////////////////////////////////////////////////
void CDisposeBinary::DisposeGNREF(u1* buf, int len)
{
	int branch = 0, chLen=6;
	SETREF result;
	result.timeSys = buf[chLen];
	chLen += 1;
	result.timeFmt = buf[chLen];
	chLen += 1;
	result.posSys = buf[chLen];
	chLen += 1;
	result.posFmt = buf[chLen];
	chLen += 1;
	result.ellipse.a = GetDataf8(buf+chLen);
	chLen += 8;
	result.ellipse.f = GetDataf8(buf+chLen);
	chLen += 8;
	result.ellipse.w = GetDataf8(buf+chLen);
	chLen += 8;
	result.ellipse.gm = GetDataf8(buf+chLen);
	chLen += 8;
	result.ellipse.dx = GetDataf8(buf+chLen);
	chLen += 8;
	result.ellipse.dy = GetDataf8(buf+chLen);
	chLen += 8;
	result.ellipse.dz = GetDataf8(buf+chLen);
	chLen += 8;
	result.ellipse.alpha = GetDataf8(buf+chLen);
	chLen += 8;
	result.ellipse.beta = GetDataf8(buf+chLen);
	chLen += 8;
	result.ellipse.gamma = GetDataf8(buf+chLen);

	m_Listener.OnAnswerInfoREF((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeGNMOD(u1* buf, int len)
{
	SETMOD result;
	int branch = 0, chLen = 6;
	result.BD2Pos = GetDatau2(buf+chLen);
	chLen += 2;
	result.BD1Pos = GetDatau2(buf+chLen);
	chLen += 2;
	chLen += 4;
	result.BD2Time = GetDatau2(buf+chLen);
	chLen += 2;
	result.BD1Time = GetDatau2(buf+chLen);

	m_Listener.OnAnswerInfoMOD((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeGNCOM(u1* buf, int len)
{
	SETCOM result;
	int branch = 0, chLen = 6;
	result.com = buf[chLen];
	chLen += 1;
	result.baud = buf[chLen];

	m_Listener.OnAnswerInfoCOM((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeGNRAN(u1* buf, int len)//20180715 待分析 对应不上
{
	int id=0;
	double snr=0;
	BD2_GSV packSnr;
	BD2_RAN result;
	int freq = 0, mode = 0, branch = 0, chLen=6;
	ZeroMemory(&result, sizeof(BD2_RAN));
	ZeroMemory(&packSnr, sizeof(BD2_GSV));

	result.week = GetDatau2(buf+chLen);
	chLen += 2;
	result.tow = GetDatau4(buf+chLen)/10.0;
	chLen += 4;
	result.numuse = GetDatau2(buf+chLen);
	chLen += 2;
	branch = buf[chLen];
	result.branch = branch;
	chLen += 1;
//#ifdef _PROTOCOL_SATID
//	if (branch != 1 && branch != 2 && branch != 21 && branch != 22)
//		mode = 1;
//#endif
	for (int i = 0; i < result.numuse; i++)
	{
		id = buf[chLen];
		chLen += 1;
		result.ran[i].x = GetDataf8(buf+chLen);
		chLen += 8;
		result.ran[i].y = GetDataf8(buf+chLen);
		chLen += 8;
		result.ran[i].z = GetDataf4(buf+chLen);
		chLen += 4;

		result.daltapseudos[i] = GetDataf8(buf+chLen);
		chLen += 8;
		result.deltacarriers[i] = GetDataf8(buf+chLen);
		chLen += 8;


		snr = GetDataf4(buf+chLen);
		chLen += 4;
		result.status1[i] = GetDatau4(buf+chLen);
		chLen += 4;
		result.status2[i] = GetDatau4(buf+chLen);
		chLen += 4;
#ifdef _PROTOCOL_SATID
		id = (id > 60)?(id-SATID_BASE):id;
#endif
		result.svId[i] = id;
		result.snr[i] = snr;

		packSnr.id[i] = id;
		packSnr.snr[i] = snr;
	}
	result.flag = true;
	packSnr.week = result.week;
	packSnr.tow = result.tow;
	packSnr.num = result.numuse;
	m_Listener.OnAnswerInfoSNR((WPARAM)(&packSnr), result.branch);
	m_Listener.OnAnswerInfoRAN((WPARAM)(&result), result.branch);
}
void CDisposeBinary::DisposeGNPOS(u1* buf, int len)
{
	int branch=0,chLen=6,id=0;
	BD2_POS result;
	result.week = GetDatau2(buf+chLen);
	chLen += 2;
	result.tow = GetDatau4(buf+chLen)/10.0;
	chLen += 4;
	result.mode = buf[chLen];
	chLen += 1;
	result.num = buf[chLen];
	chLen += 1;
	result.numuse = buf[chLen];
	chLen += 1;
	result.blh.lat = GetDataf8(buf+chLen);
	chLen += 8;
	result.blh.lon = GetDataf8(buf+chLen);
	chLen += 8;
	result.blh.alt = GetDataf8(buf+chLen);
	chLen += 8;
	result.speed.x = GetDataf8(buf+chLen);
	chLen += 8;
	result.speed.y = GetDataf8(buf+chLen);
	chLen += 8;
	result.clock = GetDataf8(buf+chLen);
	chLen += 8;
	result.dop.hdop = GetDataf8(buf+chLen);
	chLen += 8;
	result.dop.vdop = GetDataf8(buf+chLen);
	chLen += 8;
	result.dop.pdop = GetDataf8(buf+chLen);
	chLen += 8;
	result.dop.tdop = GetDataf8(buf+chLen);
	chLen += 8;
	result.dop.gdop = GetDataf8(buf+chLen);
	chLen += 8;
	for (int i=0; i<result.numuse; i++)
	{
		id = buf[chLen+i];
		result.Ids[i] = id;
		m_packGSV.idErr[id - 1] = 1;
	}

	m_Listener.OnAnswerInfoPOS((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeGNXPV(u1* buf, int len)
{
	unsigned char id=0;
	int branch=0,chLen=6,index=0;
	BD2_POS result;
	result.week = GetDatau2(buf+chLen);
	chLen += 2;
	result.tow = GetDatau4(buf+chLen)/10.0;
	chLen += 4;
	result.mode = buf[chLen];
	chLen += 1;
	result.num = buf[chLen];
	chLen += 1;
	result.numuse = buf[chLen];
	chLen += 1;
	result.blh.lat = GetDataf8(buf+chLen);
	chLen += 8;
	result.blh.lon = GetDataf8(buf+chLen);
	chLen += 8;
	result.blh.alt = GetDataf8(buf+chLen);
	chLen += 8;
	result.speed.x = GetDataf8(buf+chLen);
	chLen += 8;
	result.speed.y = GetDataf8(buf+chLen);
	chLen += 8;
	result.speed.z = GetDataf8(buf+chLen);
	chLen += 8;
	result.clock = GetDataf8(buf+chLen);
	chLen += 8;
	result.dop.hdop = GetDataf8(buf+chLen);
	chLen += 8;
	result.dop.vdop = GetDataf8(buf+chLen);
	chLen += 8;
	result.dop.pdop = GetDataf8(buf+chLen);
	chLen += 8;
	result.dop.tdop = GetDataf8(buf+chLen);
	chLen += 8;
	result.dop.gdop = GetDataf8(buf+chLen);
	chLen += 8;
	for (int i=0; i<result.numuse; i++)
	{
		id = buf[chLen+i];
		result.Ids[i] = id;
		m_packGSV.idErr[id - 1] = 1;
	}

	m_Listener.OnAnswerInfoXPV((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeGNTIM(u1* buf, int len)
{
	BD2_TIME result;
	int i=0,branch=0, chLen=6,id=0;
	result.week = GetDatau2(buf+chLen);
	chLen += 2;
	result.tow = GetDatau4(buf+chLen)/10.0;
	chLen += 4;
	result.posMod = buf[chLen];
	chLen += 1;
	result.timMod = buf[chLen];
	chLen += 1;
	result.num = buf[chLen];
	chLen += 1;
	result.year = GetDatau2(buf+chLen);
	chLen += 2;
	result.month = GetDatau2(buf+chLen);
	chLen += 2;
	result.day = GetDatau2(buf+chLen);
	chLen += 2;
	result.hour = GetDatau2(buf+chLen);
	chLen += 2;
	result.minute = GetDatau2(buf+chLen);
	chLen += 2;
	result.second = GetDatau2(buf+chLen);
	chLen += 2;
	result.Leap = buf[chLen];
	chLen += 1;
	result.clkErr = GetDataf8(buf+chLen);
	chLen += 8;
	result.flag = true;
	for (i=0; i<result.num; i++)
	{
		result.svId[i] = buf[chLen];
		chLen += 1;
	}

	m_Listener.OnAnswerInfoTIM((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeGNSTA(u1* buf, int len)
{
	int branch = 0, chLen=6;
	BD2_STA result;
	result.week = GetDatau2(buf+chLen);
	chLen += 2;
	result.tow = GetDatau4(buf+chLen)/10.0;
	chLen += 4;
	result.number  = buf[chLen];
	chLen += 1;
	result.cpu  = buf[chLen];
	chLen += 1;
	result.soft  = buf[chLen];
	chLen += 1;
	result.clock  = buf[chLen];
	chLen += 1;
	result.pps  = buf[chLen];
	result.flag = true;

	m_Listener.OnAnswerInfoSTA((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeGNGSV(u1* buf, int len)
{
	int line = 0, num = 0;
	int id = 0, branch = 0, chLen = 6;
	double elv = 0, azi = 0, snr = 0;

	m_nlines = GetDatau2(buf+chLen);
	chLen += 2;
	line = buf[chLen];
	chLen += 1;
	m_packGSV.num = GetDatau2(buf+chLen);
	chLen += 2;
	num = (m_packGSV.num%4 == 0)?4:(m_packGSV.num%4);
	if (m_nlines > line+1)
	{
		for (int i=0; i<4; i++)
		{
			id = buf[chLen];
			chLen += 1;
			elv = GetDataf4(buf+chLen);
			chLen += 4;
			azi = GetDataf4(buf+chLen);
			chLen += 4;
			snr = GetDataf4(buf+chLen);
			chLen += 4;
			m_packGSV.id[line*4+i] = id;
			m_packGSV.elv[line*4+i] = elv;
			m_packGSV.azi[line*4+i] = azi;
			m_packGSV.snr[line*4+i] = snr;
		}
	}
	else if(m_nlines == line+1)
	{
		for (int j=0; j<num; j++)
		{
			id = buf[chLen];
			chLen += 1;
			elv = GetDataf4(buf+chLen);
			chLen += 4;
			azi = GetDataf4(buf+chLen);
			chLen += 4;
			snr = GetDataf4(buf+chLen);
			chLen += 4;
			m_packGSV.id[line*4+j] = id;
			m_packGSV.elv[line*4+j] = elv;
			m_packGSV.azi[line*4+j] = azi;
			m_packGSV.snr[line*4+j] = snr;
		}
		m_Listener.OnAnswerInfoGSV((WPARAM)(&m_packGSV), branch);
		ZeroMemory(&m_packGSV, sizeof(m_packGSV));
	}
}
void CDisposeBinary::DisposeGNGBS(u1* buf, int len)
{
	int chLen = 6, id=0;
	BD2_GBS result;
	result.week = GetDatau2(buf+chLen);
	chLen += 2;
	result.tow = GetDatau4(buf+chLen)/10.0;
	chLen += 4;
	result.latErr = GetDataf8(buf+chLen);
	chLen += 8;
	result.lonErr = GetDataf8(buf+chLen);
	chLen += 8;
	result.altErr = GetDataf8(buf+chLen);
	chLen += 8; 
	result.idErr = buf[chLen];
	chLen += 1;
	result.checkErr = GetDataf8(buf+chLen);
	chLen += 8;
	result.evaluateErr = GetDataf8(buf+chLen);
	chLen += 8;
	result.offset = GetDataf8(buf+chLen);

	m_Listener.OnAnswerInfoGBS((WPARAM)(&result), result.idErr);
}


void CDisposeBinary::DisposeBDCHD(u1* buf, int len)
{
	int chLen = 6, branch = 0;
	BD2_CHD result;
	result.week = GetDatau2(buf+chLen);
	chLen += 2;
	result.tow = GetDatau4(buf+chLen);
	chLen += 4;
	result.branch = buf[chLen];
	chLen += 1;
	result.svID = buf[chLen];
	chLen += 1; 
	result.NavType = buf[chLen];
	chLen += 1;
	result.SubfameIdorMessType = buf[chLen];
	chLen += 1;
	result.Decodeinfo = buf[chLen];


	m_Listener.OnAnswerInfoCHD((WPARAM)(&result), branch);
}

void CDisposeBinary::DisposeBDPAO(u1* buf, int len)
{
	int chLen = 6, branch = 0;
	BD2_PAORDER result;
	result.sv =buf[chLen];
	chLen += 1;
	result.branch = buf[chLen];
	chLen += 1;
	result.pageid = buf[chLen];
	chLen += 1;
	result.almid = buf[chLen];
	chLen += 1;
	result.briefalmid = GetDatau4(buf+chLen);

	m_Listener.OnAnswerInfoPAO((WPARAM)(&result), branch);
}




//一期
void CDisposeBinary::DisposeBDEPH(u1* buf, int len)
{
	int branch = 0, chLen=6, id=0;
	BD2_EPH result;
	result.week = GetDatau2(buf+chLen);
	chLen += 2;
	result.tow = GetDatau4(buf+chLen)/10.0;
	chLen += 4;
	result.id = buf[chLen];
	chLen += 1;
	result.branch = buf[chLen];
	chLen += 1;
	result.iode = GetDatau2(buf+chLen);
	chLen += 2;
	result.toe = GetDataf8(buf+chLen);
	chLen += 8;
	result.e = GetDataf8(buf+chLen);
	chLen += 8;
	result.m0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.i0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.cic = GetDataf8(buf+chLen);
	chLen += 8;
	result.cis = GetDataf8(buf+chLen);
	chLen += 8;
	result.idot = GetDataf8(buf+chLen);
	chLen += 8;
	result.w = GetDataf8(buf+chLen);
	chLen += 8;
	result.omega0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.cuc = GetDataf8(buf+chLen);
	chLen += 8;
	result.cus = GetDataf8(buf+chLen);
	chLen += 8;
	result.deltaN = GetDataf8(buf+chLen);
	chLen += 8;
	result.sqrta = GetDataf8(buf+chLen);
	chLen += 8;
	result.omegadot = GetDataf8(buf+chLen);
	chLen += 8;
	result.crc = GetDataf8(buf+chLen);
	chLen += 8;
	result.crs = GetDataf8(buf+chLen);
	chLen += 8;
	result.iodc = GetDatau2(buf+chLen);
	chLen += 2;
	result.toc = GetDataf8(buf+chLen);
	chLen += 8;
	result.af0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af1 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af2 = GetDataf8(buf+chLen);
	chLen += 8;
	result.tgd1 = GetDataf8(buf+chLen);
	chLen += 8;
	result.tgd2 = GetDataf8(buf+chLen);
	result.flag = true;
	result.system = SYSTEM_BD1;

	m_Listener.OnAnswerInfoEPH((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeBDALM(u1* buf, int len)
{
	int branch = 0, chLen=6, id=0;
	BD2_ALM result;
	result.id = buf[chLen];
	chLen += 1;
	result.branch = buf[chLen];
	chLen += 1;
	result.week = GetDatau2(buf+chLen);
	chLen += 2;
	result.health = GetDatau2(buf+chLen);
	chLen += 2;
	result.toa = GetDatau2(buf+chLen);
	chLen += 2;
	result.sqrta = GetDataf8(buf+chLen);
	chLen += 8;
	result.e = GetDataf8(buf+chLen);
	chLen += 8;
	result.w = GetDataf8(buf+chLen);
	chLen += 8;
	result.m0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.omega0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.omegadot = GetDataf8(buf+chLen);
	chLen += 8;
	result.sigma = GetDataf8(buf+chLen);
	chLen += 8;
	result.af0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af1 = GetDataf8(buf+chLen);
	result.flag = true;
	result.system = SYSTEM_BD1;

	m_Listener.OnAnswerInfoALM((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeBDJAL(u1* buf, int len)
{
	int branch = 0, chLen=6, id=0;
	BD2_JAL result;
	result.id = buf[chLen];
	chLen += 1;
	result.branch = buf[chLen];
	chLen += 1;
	result.sigma = GetDatau4(buf+chLen);
	chLen += 4;
	result.omega = GetDataf8(buf+chLen);
	chLen += 8;
	result.theta = GetDataf8(buf+chLen);
	chLen += 8;
	result.health = GetDatau2(buf+chLen);
	result.flag = true;
	result.system = SYSTEM_BD1;

	m_Listener.OnAnswerInfoJAL((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeBDION(u1* buf, int len)
{
	int branch = 0, chLen=6, id=0;
	BD2_ION result;
	result.week = GetDatau2(buf+chLen);
	chLen += 2;
	result.tow = GetDatau4(buf+chLen)/10.0;
	chLen += 4;
	result.id = buf[chLen];
	chLen += 1;
	result.branch = buf[chLen];
	chLen += 1;
	result.A1 = GetDataf8(buf+chLen);
	chLen += 8;
	result.B = GetDataf8(buf+chLen);
	chLen += 8;
	result.alpha0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.alpha1 = GetDataf8(buf+chLen);
	chLen += 8;
	result.alpha2 = GetDataf8(buf+chLen);
	chLen += 8;
	result.alpha3 = GetDataf8(buf+chLen);
	chLen += 8;
	result.beta0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.beta1 = GetDataf8(buf+chLen);
	chLen += 8;
	result.beta2 = GetDataf8(buf+chLen);
	chLen += 8;
	result.beta3 = GetDataf8(buf+chLen);
	chLen += 8;
	result.gamma0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.gamma1 = GetDataf8(buf+chLen);
	chLen += 8;
	result.gamma2 = GetDataf8(buf+chLen);
	chLen += 8;
	result.gamma3 = GetDataf8(buf+chLen);
	result.flag = true;
	result.system = SYSTEM_BD1;

	m_Listener.OnAnswerInfoION((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeGNCOD(u1* buf, int len)
{
	int branch = 0, chLen=6, id=0, mode=0;
	BD2_COD result;
	result.id = buf[chLen];
	chLen += 1;
	result.branch = buf[chLen];
	chLen += 1;
	result.prm = buf[chLen];
	chLen += 1;
	result.len = len - 17;
	memcpy(result.CodBuf, buf+chLen, result.len);

	m_Listener.OnAnswerInfoCOD((WPARAM)(&result), branch);
}
//二期
void CDisposeBinary::DisposeBSEPH(u1* buf, int len)
{
	int branch = 0, chLen=6;
	BD2_EPH result;
	result.week = GetDatau2(buf+chLen);
	chLen += 2;
	result.tow = GetDatau4(buf+chLen)/10.0;
	chLen += 4;
	result.id = buf[chLen];
	chLen += 1;
	result.branch = buf[chLen];
	chLen += 1;
	result.iode = GetDatau2(buf+chLen);
	chLen += 2;
	result.toe = GetDataf8(buf+chLen);
	chLen += 8;
	result.deltaA = GetDataf8(buf+chLen);
	chLen += 8;
	result.Adot = GetDataf8(buf+chLen);
	chLen += 8;
	result.deltaN = GetDataf8(buf+chLen);
	chLen += 8;
	result.Ndot = GetDataf8(buf+chLen);
	chLen += 8;
	result.m0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.e = GetDataf8(buf+chLen);
	chLen += 8;
	result.w = GetDataf8(buf+chLen);
	chLen += 8;
	result.omega0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.i0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.omegadot = GetDataf8(buf+chLen);
	chLen += 8;
	result.idot = GetDataf8(buf+chLen);
	chLen += 8;
	result.cis = GetDataf8(buf+chLen);
	chLen += 8;
	result.cic = GetDataf8(buf+chLen);
	chLen += 8;
	result.crs = GetDataf8(buf+chLen);
	chLen += 8;
	result.crc = GetDataf8(buf+chLen);
	chLen += 8;
	result.cus = GetDataf8(buf+chLen);
	chLen += 8;
	result.cuc = GetDataf8(buf+chLen);
	chLen += 8;
	result.iodc = GetDatau2(buf+chLen);
	chLen += 2;
	result.toc = GetDataf8(buf+chLen);
	chLen += 8;
	result.af0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af1 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af2 = GetDataf8(buf+chLen);
	chLen += 8;
	result.tgd1 = GetDataf8(buf+chLen);
	chLen += 8;
	result.tgd2 = GetDataf8(buf+chLen);
	chLen += 8;
	result.tgd3 = GetDataf8(buf+chLen);
	result.flag = true;
	result.system = SYSTEM_BD2;

	m_Listener.OnAnswerInfoEPH((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeBSALM(u1* buf, int len)
{
	int branch = 0, chLen=6, id=0;
	BD2_ALM result;
	result.id = buf[chLen];
	chLen += 1;
	result.branch = buf[chLen];
	chLen += 1;
	result.week = GetDatau2(buf+chLen);
	chLen += 2;
	result.health = GetDatau2(buf+chLen);
	chLen += 2;
	result.toa = GetDatau2(buf+chLen);
	chLen += 2;
	result.e = GetDataf8(buf+chLen);
	chLen += 8;
	result.sigma = GetDataf8(buf+chLen);
	chLen += 8;
	result.sqrta = GetDataf8(buf+chLen);
	chLen += 8;
	result.omega0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.omegadot = GetDataf8(buf+chLen);
	chLen += 8;
	result.w = GetDataf8(buf+chLen);
	chLen += 8;
	result.m0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af0 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af1 = GetDataf8(buf+chLen);
	result.flag = true;
	result.system = SYSTEM_BD2;

	m_Listener.OnAnswerInfoALM((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeBSJAL(u1* buf, int len)
{
	int branch = 0, chLen=6, id=0;
	BD2_JAL result;
	result.id = buf[chLen];
	chLen += 1;
	result.branch = buf[chLen];
	chLen += 1;
	result.sigma = GetDatau4(buf+chLen);
	chLen += 4;
	result.omega = GetDataf8(buf+chLen);
	chLen += 8;
	result.theta = GetDataf8(buf+chLen);
	chLen += 8;
	result.health = GetDatau2(buf+chLen);
	chLen += 2;
	result.flag = true;
	result.system = SYSTEM_BD2;

	m_Listener.OnAnswerInfoJAL((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeBSION(u1* buf, int len)
{
	int branch = 0, chLen=6, id=0;
	BD2_ION result;
	result.week = GetDatau2(buf+chLen);
	chLen += 2;
	result.tow = GetDatau4(buf+chLen)/10.0;
	chLen += 4;
	result.id = buf[chLen];
	chLen += 1;
	result.branch = buf[chLen];
	chLen += 1;
	result.af1 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af2 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af3 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af4 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af5 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af6 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af7 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af8 = GetDataf8(buf+chLen);
	chLen += 8;
	result.af9 = GetDataf8(buf+chLen);
	result.flag = true;
	result.system = SYSTEM_BD2;

	m_Listener.OnAnswerInfoION((WPARAM)(&result), branch);
}
//////////////////////////////对接测试平台////////////////////////////////////////////
void CDisposeBinary::DisposeSETMOD(u1* buf, int len)
{
	SETMOD result;
	int branch = 0, chLen = 6;
	result.BD2Pos = GetDatau2(buf+chLen);
	chLen += 2;
	result.BD1Pos = GetDatau2(buf+chLen);
	chLen += 2;
	chLen += 4;
	result.BD2Time = GetDatau2(buf+chLen);
	chLen += 2;
	result.BD1Time = GetDatau2(buf+chLen);

	m_Listener.OnEmulatorSetupMOD((WPARAM)(&result), branch);
}
void CDisposeBinary::DisposeSETLOG(u1* buf, int len)
{
	SETLOG result;
	int branch = 0, chLen = 6;
	result.port = buf[chLen];
	chLen += 1;
	result.type = GetDatau2(buf+chLen);
	chLen += 2;
	result.freq = GetDatau2(buf+chLen);

	m_Listener.OnEmulatorSetupLOG((WPARAM)(&result), branch);
}

void CDisposeBinary::DisposeSETSTA(u1* buf, int len)
{
	SETSTA result;
	int branch = 0, chLen = 6;
	result.mod = buf[chLen];

	m_Listener.OnEmulatorSetupSTA((WPARAM)(&result), branch);
}

void CDisposeBinary::DisposeBDSIM(u1* buf, int len)
{
	BD2_SIM sim;
	int branch = 0, chLen = 6;
	memset(&sim, 0, sizeof(BD2_SIM));
	sim.branch = buf[chLen];
	chLen += 1;
	sim.prmFlag = buf[chLen];
	chLen += 1;
	sim.prmWeek0 = GetDatau2(buf+chLen);
	chLen += 2;
	sim.prmWeek1 = GetDatau2(buf+chLen);
	chLen += 2;
	sim.mpdFlag = buf[chLen];
	chLen += 1;
	sim.mpdWeek0 = GetDatau2(buf+chLen);
	chLen += 2;
	sim.mpdWeek1 = GetDatau2(buf+chLen);
	chLen += 2;

	m_Listener.OnAnswerInfoSIM((WPARAM)(&sim), branch);
}
void CDisposeBinary::DisposeBDVER(u1* buf, int len)
{
	BD2_VER data;
	int branch = 0, chLen = 6;
	memset(&data, 0, sizeof(BD2_VER));
	data.type = buf[chLen];
	chLen += 1;
	data.dsp.ver[0] = buf[chLen];
	chLen += 1;
	data.dsp.ver[1] = buf[chLen];
	chLen += 1;
	data.dsp.ver[2] = buf[chLen];
	chLen += 1;
	data.dsp.ver[3] = buf[chLen];
	chLen += 1;
	data.dsp.year = GetDatau2(buf+chLen);
	chLen += 2;
	data.dsp.month = buf[chLen];
	chLen += 1;
	data.dsp.day = buf[chLen];
	chLen += 1;
	data.dsp.hour = buf[chLen];
	chLen += 1;
	data.dsp.minute = buf[chLen];
	chLen += 1;
	data.dsp.second = buf[chLen];
	chLen += 1;
	data.fpga.ver[0] = buf[chLen];
	chLen += 1;
	data.fpga.ver[1] = buf[chLen];
	chLen += 1;
	data.fpga.ver[2] = buf[chLen];
	chLen += 1;
	data.fpga.ver[3] = buf[chLen];
	chLen += 1;
	data.fpga.year = GetDatau2(buf+chLen);
	chLen += 2;
	data.fpga.month = buf[chLen];
	chLen += 1;
	data.fpga.day = buf[chLen];
	chLen += 1;
	data.fpga.hour = buf[chLen];
	chLen += 1;
	data.fpga.minute = buf[chLen];
	chLen += 1;
	data.fpga.second = buf[chLen];
	chLen += 1;

	m_Listener.OnAnswerInfoVER((WPARAM)(&data), branch);
}