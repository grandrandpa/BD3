#include "StdAfx.h"
#include "DisposeBD3.h"
#include <string>
#include <iostream>

const DisposeFrame FrameTXT[] =
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
	{"$BDCHD,", OUT_BDCHD, NULL},//add by cy 20180715
	{"$BDPAO,", OUT_BDPAO, NULL},

    //GPS
    {"$GPGSA,", OUT_GPGSA, NULL},
    {"$GPGGA,", OUT_GPGGA, NULL},
    {"$GPGSV,", OUT_GPGSV, NULL},
    {"$GPGLL,", OUT_GPGLL, NULL},
    {"$GPRMC,", OUT_GPRMC, NULL},
    //BD3
    {"$BDGSA,", OUT_BDGSA, NULL},
    {"$BDGGA,", OUT_BDGGA, NULL},
    {"$BDGSV,", OUT_BDGSV, NULL},
    {"$BDGLL,", OUT_BDGLL, NULL},
    {"$BDRMC,", OUT_BDRMC, NULL},

    //GL
    {"$GLGSA,", OUT_GLGSA, NULL},
    {"$GLGGA,", OUT_GLGGA, NULL},
    {"$GLGSV,", OUT_GLGSV, NULL},
    {"$GLGLL,", OUT_GLGLL, NULL},
    {"$GLRMC,", OUT_GLRMC, NULL},

    //GA
    {"$GAGSA,", OUT_GAGSA, NULL},
    {"$GAGGA,", OUT_GAGGA, NULL},
    {"$GAGSV,", OUT_GAGSV, NULL},
    {"$GAGLL,", OUT_GAGLL, NULL},
    {"$GARMC,", OUT_GARMC, NULL},

    {"$BDEPI,", RES_BDEPI, NULL},
    {"$BDTCI,", RES_BDTCI, NULL},
    {"$BDQRI,", RES_BDQRI, NULL},
};
const int m_nframeSize = sizeof(FrameTXT)/sizeof(DisposeFrame);

CDisposeBD3::CDisposeBD3(void)
{
	Reset();
    memset(&m_packGSV, 0, sizeof(m_packGSV));

    memset(&save_GSA, 0, sizeof(save_GSA));
    memset(&save_GGA, 0, sizeof(save_GGA));
    memset(&save_GSV, 0, sizeof(save_GSV));
    memset(&save_GLL, 0, sizeof(save_GLL));
    memset(&save_RMC, 0, sizeof(save_RMC));

    memset(&nmea_char_save, 0, sizeof(nmea_char_save));
}

CDisposeBD3::~CDisposeBD3(void)
{
	Reset();
}

int CDisposeBD3::FindHead(char* buf, int len)
{
	for (int i = 0; i < m_nframeSize; i++)
	{
		if(strstr(buf, FrameTXT[i].cFrame))
		{
			return FrameTXT[i].nFrame;
		}
	}
	return -1;
}
void CDisposeBD3::DisposeData(char* buf, int len)
{
	char ch = 0;
	u4 crc = 0;
	/*BD2_SRC* data = new BD2_SRC;
	data->length = len;
	memcpy(data->Buffer, buf, m_chLen);
	m_Listener.OnAnswerInfoFrame((WPARAM)data, 0);*///先将原始数据上发，在解析
	for (int i = 0; i < len; i++)
	{
		ch = buf[i];
		switch(m_CmdState)
		{
		case RECV_CMD_START:
			if(m_chLen == 0)
			{
				if(ch == '$')
				{
					m_chBuffer[m_chLen++] = ch;
				}
			}
			else if(m_chLen == 1)
			{
				if(ch == 'B' || ch == 'G')
				{
					m_chBuffer[m_chLen++] = ch;
				}
				else if(ch == '$')
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
				if (m_chLen > 15)
				{
					m_nFrame = FindHead(m_chBuffer, m_chLen);
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
			if(/*m_chBuffer[m_chLen - 5] == '*' &&*/ m_chBuffer[m_chLen - 2] == 0x0D && m_chBuffer[m_chLen - 1] == 0x0A)
			{
                if( CheckData(m_chBuffer) == 0)
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
void CDisposeBD3::DisposeIndex(int index)
{
	switch (index)
	{
	case OUT_GNREF:
		DisposeGNREF(m_chBuffer, m_chLen);
		break;
	case OUT_GNMOD:
		DisposeGNMOD(m_chBuffer, m_chLen);
		break;
	case OUT_GNCOM:
		DisposeGNCOM(m_chBuffer, m_chLen);
		break;
	case OUT_GNRAN:
		DisposeGNRAN(m_chBuffer, m_chLen);
		break;
	case OUT_BDEPH:
		DisposeBDEPH(m_chBuffer, m_chLen);
		break;
	case OUT_BSEPH:
		DisposeBSEPH(m_chBuffer, m_chLen);
		break;
	case OUT_BDALM:
		break;
	case OUT_BSALM:
		DisposeBSALM(m_chBuffer, m_chLen);
		break;
	case OUT_BDJAL:
		break;
	case OUT_BSJAL:
		DisposeBSJAL(m_chBuffer, m_chLen);
		break;
	case OUT_BDION:
		DisposeBDION(m_chBuffer, m_chLen);
		break;
	case OUT_BSION:
		DisposeBSION(m_chBuffer, m_chLen);
		break;
	case OUT_GNCOD:
		DisposeGNCOD(m_chBuffer, m_chLen);
		break;
		break;
	case OUT_GNPOS:
		DisposeGNPOS(m_chBuffer, m_chLen);
		break;
	case OUT_GNXPV:
		DisposeGNXPV(m_chBuffer, m_chLen);
		break;
	case OUT_GNTIM:
		DisposeGNTIM(m_chBuffer, m_chLen);
		break;
	case OUT_GNSTA:
		DisposeGNSTA(m_chBuffer, m_chLen);
		break;
	//case OUT_BDGSV:
		//DisposeGNGSV(m_chBuffer, m_chLen);
		//break;
	case OUT_GNGBS:
		DisposeGNGBS(m_chBuffer, m_chLen);
		break;
	case OUT_BDCHD:
		DisposeBDCHD(m_chBuffer, m_chLen);
		break;
	case OUT_BDPAO:
		DisposeBDPAO(m_chBuffer, m_chLen);
		break;

    case OUT_BDGSA:
    case OUT_BDGGA:
    case OUT_BDGSV:
    case OUT_BDGLL:
    case OUT_BDRMC:

    case OUT_GPGSA:
    case OUT_GPGGA:
    case OUT_GPGSV:
    case OUT_GPGLL:
    case OUT_GPRMC:

    case OUT_GLGSA:
    case OUT_GLGGA:
    case OUT_GLGSV:
    case OUT_GLGLL:
    case OUT_GLRMC:

    case OUT_GAGSA:
    case OUT_GAGGA:
    case OUT_GAGSV:
    case OUT_GAGLL:
    case OUT_GARMC:
        AnalyzeNmeaData(m_chBuffer, m_chLen);
        break;

    case RES_BDEPI:
        break;

    case RES_BDTCI:
        {
        //char test[] = "D5E2CAC7D2BBB8F6B2E2CAD4B1A8CEC4";
        //CString str = HexToString(test, strlen(test));
        }
        break;

    case RES_BDQRI:
        break;

	default:
		break;
	}

    //if (index == -1)
    //{
    //    index = 999;
    //}

	BD2_SRC data;
	data.type = index;
	data.length = m_chLen;
	memcpy(data.Buffer, m_chBuffer, m_chLen);
	m_Listener.OnAnswerInfoSRC((WPARAM)&data, index);
}
/****************************************************************************************/
void CDisposeBD3::DisposeSETMOD(u1* buf, int len)
{

}
void CDisposeBD3::DisposeGNREF(char* buf, int len)
{
	int branch = 0;
	SETREF result;
	char chTemp[20][30];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 30 || line >= 20)
			return;
	}
	result.timeSys = atoi(chTemp[1]);
	result.timeFmt = atoi(chTemp[2]);
	result.posSys = atoi(chTemp[3]);
	result.posFmt = atoi(chTemp[4]);
	result.ellipse.a = atoi(chTemp[5]);
	result.ellipse.f = atoi(chTemp[6]);
	result.ellipse.w = atoi(chTemp[7]);
	result.ellipse.gm = atoi(chTemp[8]);
	result.ellipse.dx = atoi(chTemp[9]);
	result.ellipse.dy = atoi(chTemp[10]);
	result.ellipse.dz = atoi(chTemp[11]);
	result.ellipse.alpha = atoi(chTemp[12]);
	result.ellipse.beta = atoi(chTemp[13]);
	result.ellipse.gamma = atoi(chTemp[14]);

	m_Listener.OnAnswerInfoREF((WPARAM)(&result), branch);
}
void CDisposeBD3::DisposeGNMOD(char* buf, int len)
{
	int branch = 0;
	SETMOD result;
	char chTemp[10][20];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 20 || line >= 10)
			return;
	}
	result.BD2Pos = atoi(chTemp[1]);
	result.BD1Pos = atoi(chTemp[2]);
	result.BD2Time = atoi(chTemp[6]);
	result.BD1Time = atoi(chTemp[7]);

	m_Listener.OnAnswerInfoMOD((WPARAM)(&result), branch);
}
void CDisposeBD3::DisposeGNCOM(char* buf, int len)
{
	int branch = 0;
	SETCOM result;
	char chTemp[20][20];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 20 || line >= 20)
			return;
	}
	result.com = atoi(chTemp[1]);
	result.baud = atoi(chTemp[2]);

	m_Listener.OnAnswerInfoCOM((WPARAM)(&result), branch);
}
void CDisposeBD3::DisposeGNRAN(char* buf, int len)
{
	BD2_RAN result;
	char chTemp[200][30];
	char buffer[30];
	double snr = 0;
	BD2_GSV packSnr;
	int i=0, id=0, line = 0, row = 0;
	ZeroMemory(&result, sizeof(BD2_RAN));
	ZeroMemory(&buffer, sizeof(char)*30);
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 30 || line >= 200)
			return;
	}
	result.flag = 1;
	result.week = atoi(chTemp[1]);
	result.tow = atoi(chTemp[2]) / 10.0;
	result.numuse = atoi(chTemp[3]); //卫星数
	result.branch = atoi(chTemp[4]);//每一包数据频点相同
	for (int j=0; j<result.numuse; j++)
	{
		id = atoi(chTemp[5+6*j]);
		result.ran[j].x = strtod(chTemp[6+6*j], NULL);
		result.ran[j].y = strtod(chTemp[7+6*j], NULL);
		result.ran[j].z = (f4)strtod(chTemp[8+6*j], NULL);
		snr = (f4)strtod(chTemp[9+6*j], NULL);
		memcpy(buffer, chTemp[10+6*j], sizeof(char)*30);
	//	result.status[j] = strtoul(buffer, NULL, 10);
		//result.status0[j] = GetData_8CharToHex(buffer);
		//result.status1[j] = GetData_8CharToHex(buffer+8);


		result.svId[j] = id;
		result.snr[j] = snr;

		packSnr.id[j] = id;
		packSnr.snr[j] = snr;
	}
	packSnr.num = result.numuse;
	m_Listener.OnAnswerInfoSNR((WPARAM)(&packSnr), result.branch);
	m_Listener.OnAnswerInfoRAN((WPARAM)(&result), result.branch);
}
void CDisposeBD3::DisposeGNPOS(char* buf, int len)
{
	int branch = 0;
	unsigned short id=0,index=0;
	BD2_POS result;
	char chTemp[20][40];
	int i=0, j=0, line=0, row=0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 40 || line >= 20)
			return;
	}
	result.week = atoi(chTemp[1]);
	result.tow = atoi(chTemp[2]) / 10.0;
	result.mode = atoi(chTemp[3]);
	result.num = atoi(chTemp[4]);
	result.numuse = atoi(chTemp[5]);
	result.blh.lat = strtod(chTemp[6], NULL);
	result.blh.lon = strtod(chTemp[7], NULL);
	result.blh.alt = strtod(chTemp[8], NULL);
	result.speed.x = strtod(chTemp[9], NULL);
	result.speed.y = strtod(chTemp[10], NULL);
	result.clock = strtod(chTemp[11], NULL);
	result.dop.hdop = strtod(chTemp[12], NULL);
	result.dop.vdop = strtod(chTemp[13], NULL);
	result.dop.pdop = strtod(chTemp[14], NULL);
	result.dop.tdop = strtod(chTemp[15], NULL);
	result.dop.gdop = strtod(chTemp[16], NULL);
	//memcpy(result.Ids, chTemp[17], sizeof(char)*2*result.numuse);
	for (i=0,j=0; i<result.numuse; i++,j+=2)
	{
		id = ((GetData_CharToHex(chTemp[17][j]) << 4)&0xF0) | (GetData_CharToHex(chTemp[17][j+1])&0x0F);
		//index = (id>40)?id-40:id;
		result.Ids[i] = id;
		m_SvIdErr[id-1]=1;
	}
#ifdef __LOGFILE__
	dumpfile("Recv:POS\r\n", 10, "RecvFrmCom.dat");
#endif
	m_Listener.OnAnswerInfoPOS((WPARAM)(&result), branch);
}
void CDisposeBD3::DisposeGNXPV(char* buf, int len)
{
	int branch = 0;
	unsigned short id=0,index=0;
	BD2_POS result;
	char chTemp[20][40];
	int i=0,j=0, line=0, row=0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 40 || line >= 20)
			return;
	}
	result.week = atoi(chTemp[1]);
	result.tow = atoi(chTemp[2]) / 10.0;
	result.mode = atoi(chTemp[3]);
	result.num = atoi(chTemp[4]);
	result.numuse = atoi(chTemp[5]);
	result.blh.lat = strtod(chTemp[6], NULL);
	result.blh.lon = strtod(chTemp[7], NULL);
	result.blh.alt = strtod(chTemp[8], NULL);
	result.speed.x = strtod(chTemp[9], NULL);
	result.speed.y = strtod(chTemp[10], NULL);
	result.speed.z = strtod(chTemp[11], NULL);
	result.clock = strtod(chTemp[12], NULL);
	result.dop.hdop = strtod(chTemp[13], NULL);
	result.dop.vdop = strtod(chTemp[14], NULL);
	result.dop.pdop = strtod(chTemp[15], NULL);
	result.dop.tdop = strtod(chTemp[16], NULL);
	result.dop.gdop = strtod(chTemp[17], NULL);
	//memcpy(result.Ids, chTemp[18], sizeof(char)*2*result.numuse);
	for (i=0,j=0; i<result.numuse; i++,j+=2)
	{
		id = ((GetData_CharToHex(chTemp[18][j]) << 4)&0xF0) | (GetData_CharToHex(chTemp[18][j+1])&0x0F);
		//index = (id>40)?id-40:id;
		result.Ids[i] = id;
		m_SvIdErr[id-1]=1;
	}

	m_Listener.OnAnswerInfoXPV((WPARAM)(&result), branch);
}
void CDisposeBD3::DisposeGNTIM(char* buf, int len)
{
	int branch = 0;
	BD2_TIME result;
	char chTemp[15][30];
	int i=0, k=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 30 || line >= 15)
			return;
	}
	result.flag = false;
	result.week = atoi(chTemp[1]);
	result.tow = atoi(chTemp[2]) / 10.0;
	result.posMod = atoi(chTemp[3]);
	result.timMod = atoi(chTemp[4]);
	result.num = atoi(chTemp[5]);
	result.year = atoi(chTemp[6]);
	result.month = atoi(chTemp[7]);
	result.day = atoi(chTemp[8]);
	result.hour = atoi(chTemp[9]);
	result.minute = atoi(chTemp[10]);
	result.second = atoi(chTemp[11]);
	result.Leap = atoi(chTemp[12]);
	result.clkErr = strtod(chTemp[13], NULL);
	k = 0;
	for (i=0; i<result.num; i++)
	{
		result.svId[i] = ((GetData_CharToHex(chTemp[14][k]) << 4)&0xF0) | (GetData_CharToHex(chTemp[14][k+1])&0x0F);
		k += 2;
	}
	result.flag = true;

	m_Listener.OnAnswerInfoTIM((WPARAM)(&result), branch);
}
void CDisposeBD3::DisposeGNSTA(char* buf, int len)
{
	int branch = 0;
	BD2_STA result;
	char chTemp[10][20];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 20 || line >= 10)
			return;
	}
	result.week = atoi(chTemp[1]);
	result.tow = atoi(chTemp[2]) / 10.0;
	result.number  = atoi(chTemp[3]);
	result.cpu  = atoi(chTemp[4]);
	result.soft  = atoi(chTemp[5]);
	result.clock  = atoi(chTemp[6]);
	result.pps = atoi(chTemp[7]);
	result.flag = true;

	m_Listener.OnAnswerInfoSTA((WPARAM)(&result), branch);
}
void CDisposeBD3::DisposeGNGSV(char* buf, int len)
{

#if 0
	char chTemp[200][20];
	int id=0, line=0, row=0;
	double elv=0,azi=0;
	int count = 0, m_nlines=0;
	for (int i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 20 || line >= 200)
			return;
	}
	m_nlines = atoi(chTemp[1]);
	line = atoi(chTemp[2]);
	m_packGSV.num = atoi(chTemp[3]);
	count = (m_packGSV.num%4 == 0)?4:(m_packGSV.num%4);
	if (m_nlines > line+1)
	{
		for (int i=0; i<4; i++)
		{
			id = atoi(chTemp[4+i*4]);
			elv = strtod(chTemp[5+i*4], NULL);
			azi = strtod(chTemp[6+i*4], NULL);
			m_packGSV.snr[line*4+i] = strtod(chTemp[7+i*4], NULL);

			m_packGSV.id[line*4+i] = id;
			m_packGSV.elv[line*4+i] = elv;
			m_packGSV.azi[line*4+i] = azi;
		}
	}
	else if (m_nlines == line+1)
	{
		for (int i=0; i<count; i++)
		{
			id = atoi(chTemp[4+i*4]);
			elv = strtod(chTemp[5+i*4], NULL);
			azi = strtod(chTemp[6+i*4], NULL);
			m_packGSV.snr[line*4+i] = strtod(chTemp[7+i*4], NULL);

			m_packGSV.id[line*4+i] = id;
			m_packGSV.elv[line*4+i] = elv;
			m_packGSV.azi[line*4+i] = azi;
		}
		memcpy(m_packGSV.idErr, m_SvIdErr, sizeof(int)*MAXCHANNELS);
		m_Listener.OnAnswerInfoGSV((WPARAM)(&m_packGSV), 0);
		memset(&m_SvIdErr, 0, sizeof(int)*MAXCHANNELS);
	}
#endif

    int id=0;
	double elv=0,azi=0;

    int sum = save_GSV.GSV_count - '0';
    int index = save_GSV.GSV_numb - '0';
    int count = strtod(save_GSV.satellite_view, NULL);
    if (sum == index)
    {
        for (int i=0; i<sum; i++)
		{
            nmea_char_save.GP_view[i].PRN;
            id = atoi(nmea_char_save.GP_view[i].PRN);
            elv = strtod(nmea_char_save.GP_view[i].yang_cour, NULL);
            azi = strtod(nmea_char_save.GP_view[i].fangwei_cour, NULL);

			m_packGSV.id[i] = id;
			m_packGSV.elv[i] = elv;
			m_packGSV.azi[i] = azi;
            m_packGSV.snr[i] = strtod(nmea_char_save.GP_view[i].CN0, NULL);
		}

        m_Listener.OnAnswerInfoGSV((WPARAM)(&m_packGSV), 0);
    }


#ifdef __LOGFILE__
	dumpfile(buf, len, "RecvFrmCom.dat");
#endif
}
void CDisposeBD3::DisposeGNGBS(char* buf, int len)
{
	int branch = 0;
	BD2_GBS result;
	char chTemp[20][20];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 20 || line >= 20)
			return;
	}
	result.week = atoi(chTemp[1]);
	result.tow = atoi(chTemp[2]) / 10.0;
	result.latErr = strtod(chTemp[3], NULL);
	result.lonErr = strtod(chTemp[4], NULL);
	result.altErr = strtod(chTemp[5], NULL);
	result.idErr = atoi(chTemp[6]);
	result.checkErr = strtod(chTemp[7], NULL);
	result.evaluateErr = strtod(chTemp[8], NULL);
	result.offset = strtod(chTemp[9], NULL);

	m_Listener.OnAnswerInfoGBS((WPARAM)(&result), branch);
}

void CDisposeBD3::DisposeBDCHD(char* buf, int len)
{
	int branch = 0;
	BD2_GBS result;
	char chTemp[20][20];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 20 || line >= 20)
			return;
	}
	result.week = atoi(chTemp[1]);
	result.tow = atoi(chTemp[2]) / 10.0;
	result.latErr = strtod(chTemp[3], NULL);
	result.lonErr = strtod(chTemp[4], NULL);
	result.altErr = strtod(chTemp[5], NULL);
	result.idErr = atoi(chTemp[6]);
	result.checkErr = strtod(chTemp[7], NULL);
	result.evaluateErr = strtod(chTemp[8], NULL);
	result.offset = strtod(chTemp[9], NULL);

	m_Listener.OnAnswerInfoCHD((WPARAM)(&result), branch);
}

void CDisposeBD3::DisposeBDPAO(char* buf, int len)
{
	int branch = 0;
	BD2_STA result;
	char chTemp[10][20];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 20 || line >= 10)
			return;
	}
	result.week = atoi(chTemp[1]);
	result.tow = atoi(chTemp[2]) / 10.0;
	result.number  = atoi(chTemp[3]);
	result.cpu  = atoi(chTemp[4]);
	result.soft  = atoi(chTemp[5]);
	result.clock  = atoi(chTemp[6]);
	result.pps = atoi(chTemp[7]);
	result.flag = true;

	m_Listener.OnAnswerInfoPAO((WPARAM)(&result), branch);
}


//一期
void CDisposeBD3::DisposeBDEPH(char* buf, int len)
{
	int branch = 0;
	BD2_EPH result;
	char chTemp[30][30];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 30 || line >= 30)
			return;
	}
	result.week = atoi(chTemp[1]);
	result.tow = atoi(chTemp[2]) / 10.0;
	result.id = atoi(chTemp[3]);
	result.branch = atoi(chTemp[4]);
	result.iode = atoi(chTemp[5]);
	result.toe = strtod(chTemp[6], NULL);
	result.e = strtod(chTemp[7], NULL)* 1.16415321826935e-10;
	result.m0 = strtod(chTemp[8], NULL) * PI * 4.65661287307739e-10;
	result.i0 = strtod(chTemp[9], NULL) * PI * 4.65661287307739e-10;
	result.cic = strtod(chTemp[10], NULL) * 4.65661287307739e-10;
	result.cis = strtod(chTemp[11], NULL) * 4.65661287307739e-10;
	result.idot = strtod(chTemp[12], NULL) * PI * 1.13686837721616e-13;
	result.w = strtod(chTemp[13], NULL) * PI * 4.65661287307739e-10;
	result.omega0 = strtod(chTemp[14], NULL) * PI * 4.65661287307739e-10;
	result.cuc = strtod(chTemp[15], NULL) * 4.65661287307739e-10;
	result.cus = strtod(chTemp[16], NULL) * 4.65661287307739e-10;
	result.deltaN = strtod(chTemp[17], NULL) * PI * 1.13686837721616e-13;
	result.sqrta = strtod(chTemp[18], NULL) * EPH_SQRT_A;
	result.omegadot = strtod(chTemp[19], NULL) * PI * 1.13686837721616e-13;
	result.crc = strtod(chTemp[20], NULL)*0.015625;
	result.crs = strtod(chTemp[21], NULL)*0.015625;
	result.iodc = atoi(chTemp[22]);//
	result.toc = strtod(chTemp[23], NULL);//
	result.af0 = strtod(chTemp[24], NULL)*EPH_AF00;
	result.af1 = strtod(chTemp[25], NULL)*EPH_AF1;
	result.af2 = strtod(chTemp[26], NULL)*EPH_AF2;
	result.tgd1 = strtod(chTemp[27], NULL) * 1.0e-10;
	result.tgd2 = strtod(chTemp[28], NULL) * 1.0e-10;
	result.system = SYSTEM_BD1;
	result.flag = true;

	m_Listener.OnAnswerInfoEPH((WPARAM)(&result), result.branch);
}
void CDisposeBD3::DisposeBDALM(char* buf, int len)
{
	int branch = 0;
	BD2_ALM result;
	char chTemp[20][30];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 30 || line >= 20)
			return;
	}
	result.id = atoi(chTemp[1]);
	result.branch = atoi(chTemp[2]);
	result.week = atoi(chTemp[3]);
	result.health = atoi(chTemp[4]);
	result.toa = atoi(chTemp[5])*ALM_TOA;
	result.sqrta = strtod(chTemp[8], NULL)*ALM_SQRT_A;
	result.e = strtod(chTemp[6], NULL)*4.76837158203125e-7;
	result.w = strtod(chTemp[11], NULL)*PI * 1.19209289550781e-7;
	result.m0 = strtod(chTemp[12], NULL)*PI * 1.19209289550781e-7;
	result.omega0 = strtod(chTemp[9], NULL)*PI * 1.19209289550781e-7;
	result.omegadot = strtod(chTemp[10], NULL) * PI * 3.63797880709171e-12;
	result.sigma = strtod(chTemp[7], NULL)*ALM_SIGMA;
	result.af0 = strtod(chTemp[13], NULL)*ALM_AF0;
	result.af1 = strtod(chTemp[14], NULL)*3.63797880709171e-12;
	result.system = SYSTEM_BD1;
	result.flag = true;

	m_Listener.OnAnswerInfoALM((WPARAM)(&result), result.branch);
}
void CDisposeBD3::DisposeBDJAL(char* buf, int len)
{
	int branch = 0;
	BD2_JAL result;
	char chTemp[10][20];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 20 || line >= 10)
			return;
	}
	result.id = atoi(chTemp[1]);
	result.branch = atoi(chTemp[2]);
	result.sigma = atoi(chTemp[3])*JAL_SIGMA;
	result.omega = strtod(chTemp[4], NULL)*JAL_OMEGA;
	result.theta = strtod(chTemp[5], NULL)*JAL_PHI;
	result.health = atoi(chTemp[6]);
	result.system = SYSTEM_BD1;
	result.flag = true;

	m_Listener.OnAnswerInfoJAL((WPARAM)(&result), result.branch);
}
void CDisposeBD3::DisposeBDION(char* buf, int len)
{
	int branch = 0;
	BD2_ION result;
	char chTemp[20][20];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 20 || line >= 20)
			return;
	}
	result.week = atoi(chTemp[1]);
	result.tow = atoi(chTemp[2]) / 10.0;
	result.id = atoi(chTemp[3]);
	result.branch = atoi(chTemp[4]);
	result.A1 = strtod(chTemp[5], NULL)*ION_A;
	result.B = strtod(chTemp[6], NULL)*ION_B;
	result.alpha0 = strtod(chTemp[7], NULL)*ION_Alpha0;
	result.alpha1 = strtod(chTemp[8], NULL)*ION_Alpha1;
	result.alpha2 = strtod(chTemp[9], NULL)*ION_Alpha2;
	result.alpha3 = strtod(chTemp[10], NULL)*ION_Alpha3;
	result.beta0 = strtod(chTemp[11], NULL)*ION_Beta0;
	result.beta1 = strtod(chTemp[12], NULL)*ION_Beta1;
	result.beta2 = strtod(chTemp[13], NULL)*ION_Beta2;
	result.beta3 = strtod(chTemp[14], NULL)*ION_Beta3;
	result.gamma0 = strtod(chTemp[15], NULL)*ION_Gamma0;
	result.gamma1 = strtod(chTemp[16], NULL)*ION_Gamma1;
	result.gamma2 = strtod(chTemp[17], NULL)*ION_Gamma2;
	result.gamma3 = strtod(chTemp[18], NULL)*ION_Gamma3;
	result.system = SYSTEM_BD1;
	result.flag = true;

	m_Listener.OnAnswerInfoION((WPARAM)(&result), result.branch);
}
void CDisposeBD3::DisposeGNCOD(char* buf, int len)
{
	int branch = 0;
	BD2_COD result;
	char chTemp[10][250];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 250 || line >= 10)
			return;
	}
	result.id = atoi(chTemp[1]);
	result.branch = atoi(chTemp[2]);
	result.prm = atoi(chTemp[3]);
	result.len = strlen(chTemp[4]);
	memcpy(result.CodBuf, chTemp[4], result.len);
	result.system = SYSTEM_BD1;
	result.flag = true;

	m_Listener.OnAnswerInfoCOD((WPARAM)(&result), branch);
}
//二期
void CDisposeBD3::DisposeBSEPH(char* buf, int len)
{
	int branch = 0;
	BD2_EPH result;
	char chTemp[35][20];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 20 || line >= 35)
			return;
	}
	result.week = atoi(chTemp[1]);
	result.tow = atoi(chTemp[2]) / 10.0;
	result.id = atoi(chTemp[3]);
	result.branch = atoi(chTemp[4]);
	result.iode = atoi(chTemp[5]);
	result.toe = strtod(chTemp[6], NULL)*EPH_TOE;
	result.deltaA = strtod(chTemp[7], NULL)*EPH_DELTA_A;
	result.Adot = strtod(chTemp[8], NULL)*EPH_A_DOT;
	result.deltaN = strtod(chTemp[9], NULL)*EPH_DELTA_N;
	result.Ndot = strtod(chTemp[10], NULL)*EPH_N_DOT;
	result.m0 = strtod(chTemp[11], NULL)*EPH_M0;
	result.e = strtod(chTemp[12], NULL)*EPH_E;
	result.w = strtod(chTemp[13], NULL)*EPH_W;
	result.omega0 = strtod(chTemp[14], NULL)*EPH_OMEGA0;
	result.i0 = strtod(chTemp[15], NULL)*EPH_I0;
	result.omegadot = strtod(chTemp[16], NULL)*EPH_OMEGA_DOT;
	result.idot = strtod(chTemp[17], NULL)*EPH_IDOT;
	result.cis = strtod(chTemp[18], NULL)*EPH_CIS;
	result.cic = strtod(chTemp[19], NULL)*EPH_CIC;
	result.crs = strtod(chTemp[20], NULL)*EPH_CRS;
	result.crc = strtod(chTemp[21], NULL)*EPH_CRC;
	result.cus = strtod(chTemp[22], NULL)*EPH_CUS;
	result.cuc = strtod(chTemp[23], NULL)*EPH_CUC;
	result.iodc = atoi(chTemp[24]);
	result.toc = strtod(chTemp[25], NULL)*EPH_TOC;
	result.af0 = strtod(chTemp[26], NULL)*EPH_AF0;
	result.af1 = strtod(chTemp[27], NULL)*EPH_AF1;
	result.af2 = strtod(chTemp[28], NULL)*EPH_AF2;
	result.tgd1 = strtod(chTemp[29], NULL)*EPH_TGD1;
	result.tgd2 = strtod(chTemp[30], NULL)*EPH_TGD2;
	result.tgd3 = strtod(chTemp[31], NULL)*EPH_TGD3;
	result.system = SYSTEM_BD2;
	result.flag = true;

	m_Listener.OnAnswerInfoEPH((WPARAM)(&result), result.branch);
}
void CDisposeBD3::DisposeBSALM(char* buf, int len)
{
	int branch = 0;
	BD2_ALM result;
	char chTemp[20][20];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 20 || line >= 20)
			return;
	}
	result.id = atoi(chTemp[1]);
	result.branch = atoi(chTemp[2]);
	result.week = atoi(chTemp[3]);
	result.health = atoi(chTemp[4]);
	result.toa = atoi(chTemp[5])*ALM_TOA;
	result.e = strtod(chTemp[6], NULL)*ALM_E;
	result.sigma = strtod(chTemp[7], NULL)*ALM_SIGMA;
	result.sqrta = strtod(chTemp[8], NULL)*ALM_SQRT_A;
	result.omega0 = strtod(chTemp[9], NULL)*ALM_OMEGA0;
	result.omegadot = strtod(chTemp[10], NULL)*ALM_OMEGA_DOT;
	result.w = strtod(chTemp[11], NULL)*ALM_W;
	result.m0 = strtod(chTemp[12], NULL)*ALM_M0;
	result.af0 = strtod(chTemp[13], NULL)*ALM_AF0;
	result.af1 = strtod(chTemp[14], NULL)*ALM_AF1;
	result.system = SYSTEM_BD2;
	result.flag = true;

	m_Listener.OnAnswerInfoALM((WPARAM)(&result), result.branch);
}
void CDisposeBD3::DisposeBSJAL(char* buf, int len)
{
	int branch = 0;
	BD2_JAL result;
	char chTemp[10][20];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 20 || line >= 10)
			return;
	}
	result.id = atoi(chTemp[1]);
	result.branch = atoi(chTemp[2]);
	result.sigma = atoi(chTemp[3])*JAL_SIGMA;
	result.omega = strtod(chTemp[4], NULL)*JAL_OMEGA;
	result.theta = strtod(chTemp[5], NULL)*JAL_PHI;
	result.health = atoi(chTemp[6]);
	result.system = SYSTEM_BD2;
	result.flag = true;

	m_Listener.OnAnswerInfoJAL((WPARAM)(&result), result.branch);
}
void CDisposeBD3::DisposeBSION(char* buf, int len)
{
	int branch = 0;
	BD2_ION result;
	char chTemp[20][20];
	int i=0, line = 0, row = 0;
	for (i=0; i<len; i++)
	{
		chTemp[line][row] = buf[i];
		row++;
		if (buf[i] == ',')
		{
			chTemp[line][row-1] = '\0';
			line++;
			row = 0;
		}
		if (buf[i] == '*')
		{
			chTemp[line][row-1] = '\0';
			break;
		}
		if(row >= 20 || line >= 20)
			return;
	}
	result.week = atoi(chTemp[1]);
	result.tow = atoi(chTemp[2]) / 10.0;
	result.id = atoi(chTemp[3]);
	result.branch = atoi(chTemp[4]);
	result.af1 = strtod(chTemp[5], NULL)*ION_ALPHA;
	result.af2 = strtod(chTemp[6], NULL)*ION_ALPHA;
	result.af3 = strtod(chTemp[7], NULL)*ION_ALPHA;
	result.af4 = strtod(chTemp[8], NULL)*ION_ALPHA;
	result.af5 = strtod(chTemp[9], NULL)*ION_ALPHA;
	result.af6 = strtod(chTemp[10], NULL)*ION_ALPHA;
	result.af7 = strtod(chTemp[11], NULL)*ION_ALPHA;
	result.af8 = strtod(chTemp[12], NULL)*ION_ALPHA;
	result.af9 = strtod(chTemp[13], NULL)*ION_ALPHA;
	result.system = SYSTEM_BD2;
	result.flag = true;

	m_Listener.OnAnswerInfoION((WPARAM)(&result), result.branch);
}

/***********************************************************************************/
int CDisposeBD3::PacketACKData(char* pBuff, const SETACK& data)//查询模式
{
	return 0;
}
int CDisposeBD3::PacketPILOTData(char* pBuff, const SETPILOT& data)//数据导频
{
	return 0;
}
int CDisposeBD3::PacketIONData(char* pBuff, const SETION& data)
{
	return 0;
}
int CDisposeBD3::PacketBD2POSData(char* pBuff, const BD2_POS& data)
{
	return 0;
}
int CDisposeBD3::PacketTIMData(char* pBuff, const SETTIM& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%0.2f,%0.2f", "$SETTIM", data.delay, data.zeroVal);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketTMDData(char* pBuff, const SETTMD& data)
{
	u4 crc=0,branch=0;
	int len = 0, type=0;
	char chBuff[100];
	type = (data.mode == 0)?data.svId:data.flag;
	branch = (data.mode == 0)?data.branch:0;
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%d,%d,%d,%.6f,%.6f,%.6f", "$SETTMD", data.mode, type, branch, data.lat, data.lon, data.alt);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);
	return len;
}
int CDisposeBD3::PacketCHAData(char* pBuff, const SETCHA& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%02d,%02d,%02d,%02d", "$SETCHA", data.id, data.branch, data.pilot, data.chId);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketCOMData(char* pBuff, const SETCOM& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%02d,%02d", "$SETCOM", data.com, data.baud);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketMODData(char* pBuff, const SETMOD& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[100];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%02d,%02d,0,0,0,%02d,%02d,0,0", "$SETMOD", data.BD2Pos, data.BD1Pos, data.BD2Time, data.BD1Time);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketWORKMODData(char* pBuff, const WORKMOD& data)//add by cy 20180714
{
	u4 crc=0;
	int len = 0;
	char chBuff[100];
	ZeroMemory(chBuff, sizeof(chBuff));
	
	sprintf(chBuff, "%s,%d,%02d,%02d", "$SETWORKMODMOD", data.mode, data.svstart, data.svend);
	
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketISTData(char* pBuff, const SETIST& data)//add by cy 20180714
{
	u4 crc=0;
	int len = 0;
	char chBuff[100];
	ZeroMemory(chBuff, sizeof(chBuff));
	
	sprintf(chBuff, "%s,%d", "$SETIST", data.fp);
	
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}


int CDisposeBD3::PacketLOGData(char* pBuff, const SETLOG& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	if (data.freq == -3)
	{
		sprintf(chBuff, "%s,%02d,0,%02d", "$SETLOG", data.port, data.freq);
	}
	else
	{
		sprintf(chBuff, "%s,%02d,%c%c%c%c%c,%02d", "$SETLOG", data.port, data.frame[0], data.frame[1], data.frame[2], data.frame[3], data.frame[4], data.freq);
	}
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketPOSData(char* pBuff, const SETPOS& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[100];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%.6f,%.6f,%.6f", "$SETPOS", data.xyz.x, data.xyz.y, data.xyz.z);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketWIDData(char* pBuff, const SETWID& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%02d,%02d,%02d", "$SETWID", data.id, data.branch, data.width);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketBDIData(char* pBuff, const SETREF& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[500];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%02d,%02d,%02d,%02d,", "$SETBDI", data.timeSys, data.timeFmt, data.posSys, data.posFmt);
	len = strlen(chBuff);
	sprintf(chBuff+len, "%.6f,%.12f,%.12f,%.6f,", data.ellipse.a, data.ellipse.f, data.ellipse.w, data.ellipse.gm);
	len = strlen(chBuff);
	sprintf(chBuff+len, "%.6f,%.6f,%.6f,", data.ellipse.dx, data.ellipse.dy, data.ellipse.dz);
	len = strlen(chBuff);
	sprintf(chBuff+len, "%.6f,%.6f,%.6f,%02d,%02d", data.ellipse.alpha, data.ellipse.beta, data.ellipse.gamma, data.com.com, data.com.baud);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketREFData(char* pBuff, const SETREF& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[500];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%02d,%02d,%02d,%02d,", "$SETREF", data.timeSys, data.timeFmt, data.posSys, data.posFmt);
	len = strlen(chBuff);
	sprintf(chBuff+len, "%.6f,%.12f,%.12f,%.6f,", data.ellipse.a, data.ellipse.f, data.ellipse.w, data.ellipse.gm);
	len = strlen(chBuff);
	sprintf(chBuff+len, "%.6f,%.6f,%.6f,%.6f,%.6f,%.6f", data.ellipse.dx, data.ellipse.dy, data.ellipse.dz, data.ellipse.alpha, data.ellipse.beta, data.ellipse.gamma);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}

int CDisposeBD3::PacketMUTData(char* pBuff, const SETMUT& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%02d,%02d", "$SETMUT", data.branch, data.mutiPath);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketEACData(char* pBuff, const SETEAC& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%02d,%02d,%02d", "$SETEAC", data.id, data.pilotId, data.pilotBranch);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketBGTData(char* pBuff, const SETBGT& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[200];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%d,%d,%d,%0.6f,%0.6f,%0.6f", "$SETBGT", data.id, data.wn, data.t0, data.a0, data.a1, data.a2);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketTTFData(char* pBuff, const SETTTF& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%02d", "$SETTTF", data.mod);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketSTAData(char* pBuff, const SETSTA& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%02d", "$SETSTA", data.mod);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketSTSData(char* pBuff, const SETSTS& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%d,%d,%d", "$SETSTS", data.b1, data.b2, data.b3);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}
int CDisposeBD3::PacketEVAData(char* pBuff, const SETEVA& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[50];
	ZeroMemory(chBuff, sizeof(chBuff));
	sprintf(chBuff, "%s,%d", "$SETEVA", data.elv);
	len = strlen(chBuff);
	crc = CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%08X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

	return len;
}

int CDisposeBD3::PacketACQData(char* pBuff, const SETACQ& data)//捕获模式
{
	u4 crc = 0;
	int len = 0;

	return len;
}
int CDisposeBD3::PacketTRKData(char* pBuff, const SETTRK& data)//跟踪模式
{
	u4 crc = 0;
	int len = 0;
	return len;
}

int CDisposeBD3::PacketEPQData(char* pBuff, const SETEPQ& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[80];
	ZeroMemory(chBuff, sizeof(chBuff));
    sprintf(chBuff, "%s,%d,%d,%d,%d,%d,%0.8f,%d,%d", "$CCEPQ",
        data.CardId, data.Model, data.Freq, data.Speed, data.UrgFlag,data.ElevValue, data.SOSType, data.Times);
    //sprintf(chBuff, "%s","$GPGSV,2,1,08,05,66,005,47,02,55,065,47,13,45,153,47,29,40,317,46");
	len = strlen(chBuff);
	crc = CalCheckVal(chBuff, len);//CheckCrc32(crc, (u1*)chBuff+1, len-1);
	sprintf(chBuff+len, "*%02X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

    m_Listener.OnShowCmdView((WPARAM)(pBuff), 0);

	return len;
}

int CDisposeBD3::PacketTCQData(char* pBuff, const SETTCQ& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[2048];
	ZeroMemory(chBuff, sizeof(chBuff));
    sprintf(chBuff, "%s,%d,%d,%d,%d,%s,%d", "$CCTCQ",
        data.CardId, data.Freq, data.Confirm,data.CodeType, data.Data, data.Times);

	len = strlen(chBuff);
	crc = CalCheckVal(chBuff, len);
	sprintf(chBuff+len, "*%02X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

    m_Listener.OnShowCmdView((WPARAM)(pBuff), 0);

	return len;
}

int CDisposeBD3::PacketQRQData(char* pBuff, const SETQRQ& data)
{
	u4 crc=0;
	int len = 0;
	char chBuff[128];
	ZeroMemory(chBuff, sizeof(chBuff));
    sprintf(chBuff, "%s,%d,%d", "$CCQRQ", data.CardId, data.Type);

	len = strlen(chBuff);
	crc = CalCheckVal(chBuff, len);
	sprintf(chBuff+len, "*%02X\r\n", crc);
	len = strlen(chBuff);
	memcpy(pBuff, chBuff, len);

    m_Listener.OnShowCmdView((WPARAM)(pBuff), 0);

	return len;
}

int CDisposeBD3::SendCMDEvent(char* pBuff, int len)
{
    m_Listener.OnShowCmdView((WPARAM)(pBuff), 0);
    return 0;
}


//private//
void CDisposeBD3::AnalyzeNmeaData(char *start_buffer, int length)
{
	int i,j,k, t=0;
	int GSV_num=0;
	char bb[30][15];
    memset(bb, 0, sizeof(bb));

	k=0;
	j=0;
	//for(i=0; (start_buffer+i) <= end;i++)
	for(i=0; i <= length; i++)
	{
		//*(str+i) = *(start_buffer+i+1);
		if(*(start_buffer+i) == ',')
		{
			bb[k][j]=0;
			k++;
			j=0;
		}
		else
		{
			bb[k][j]=*(start_buffer+i);
			j++;
		}
	}
	bb[k][j]=0;
	i=k;
		
	if(*(start_buffer+1) == 'G' && *(start_buffer+2) == 'P')
	{
		nmea_char_save.sys = GP;
	}
	else if(*(start_buffer+1) == 'B' && *(start_buffer+2) == 'D')
	{
		nmea_char_save.sys = BD;
	}
	else if(*(start_buffer+1) == 'G' && *(start_buffer+2) == 'L')
	{
		nmea_char_save.sys = GL;
	}
    else if(*(start_buffer+1) == 'G' && *(start_buffer+2) == 'A')
	{
		nmea_char_save.sys = GA;
	}
	else if(*(start_buffer+1) == 'G' && *(start_buffer+2) == 'N')
	{
		nmea_char_save.sys = GN;
	}

	if(*(start_buffer+3) == 'G' && *(start_buffer+4) == 'S' && *(start_buffer+5) == 'A')
	{
		nmea_char_save.cmd = GSA;
		
		save_GSA.mode = bb[1][0];
		save_GSA.location_tpye = bb[2][0];

		j=3;
		for(; j<(i-3); j++)
		{
			save_GSA.PRN[j-3][0] = bb[j][0];
			save_GSA.PRN[j-3][1] = bb[j][1];
		}
		save_GSA.PRN_count = j-3;
		strcpy(save_GSA.PDOP,bb[i-2]);
		strcpy(save_GSA.HDOP,bb[i-1]);
		memset((void *)save_GSA.VDOP, 0, 4);
		t=0;
		while(bb[i][t] != '*')
		{
			save_GSA.VDOP[t]=bb[i][t];
			t++;
		}
		t--;
	}
	else if(*(start_buffer+3) == 'G' && *(start_buffer+4) == 'G' && *(start_buffer+5) == 'A')
	{
		nmea_char_save.cmd = GGA;
		
		memset((void *)&save_GGA, 0x0, sizeof(save_GGA));
		strcpy(save_GGA.UTC,bb[1]);
		strcpy(save_GGA.Latitude,bb[2]);
		save_GGA.N_S = bb[3][0];
		strcpy(save_GGA.Lontitude,bb[4]);
		save_GGA.E_W = bb[5][0];
		save_GGA.state = bb[6][0];
		strcpy(save_GGA.satellite_use,bb[7]);
		strcpy(save_GGA.HDOP,bb[8]);
		strcpy(save_GGA.Altitude,bb[9]);
        save_GGA.AntennaHeightUnit = bb[10][0];

        strcpy(save_GGA.AltitudeAbnormal, bb[11]);
        save_GGA.AltitudeAbnormalUnit = bb[12][0];

        strcpy(save_GGA.del_fentime,bb[13]);
        strcpy(save_GGA.del_ID, bb[14]);

        if(i==15)
		{
			//memset(save_GGA.VDOP, 0, 4);
			t=0;
			while(bb[i][t] != '*')
			{
				save_GGA.VDOP[t]=bb[i][t];
				t++;
			}
		}
		
	}
	else if(*(start_buffer+3) == 'G' && *(start_buffer+4) == 'S' && *(start_buffer+5) == 'V')
	{
		printf("++++GSV+++\n");
		nmea_char_save.cmd = GSV;
		
		save_GSV.GSV_count = bb[1][0];
		save_GSV.GSV_numb = bb[2][0];
		strcpy(save_GSV.satellite_view,bb[3]);

		//int GSV_num=0;
		if(i==19)
			GSV_num = 4;
		else if(i==11)
			GSV_num = 2;
		else if(i==15)
			GSV_num = 3;
		else
			GSV_num = 1;
		
		j=0;
		int count = save_GSV.GSV_numb - '0';
		for(; j<GSV_num; j++)
		{
			strcpy(save_GSV.satellite_info[count-1][j].PRN,bb[j*4+4]);
			if (3 == strlen(bb[j*4+5]) || '-' == bb[j*4+5][0])
			{
				strcpy(save_GSV.satellite_info[count-1][j].yang_cour,"00");
			} 
			else
			{
				strcpy(save_GSV.satellite_info[count-1][j].yang_cour,bb[j*4+5]);
			}
			strcpy(save_GSV.satellite_info[count-1][j].fangwei_cour,bb[j*4+6]);
			if((j*4+7) != i)
				strcpy(save_GSV.satellite_info[count-1][j].CN0,bb[j*4+7]);
			else
			{
				t=0;
				while(bb[j*4+7][t] != '*')
				{
					save_GSV.satellite_info[count-1][j].CN0[t]=bb[j*4+7][t];
					t++;
				}
			}
		}
		
	}
	else if(*(start_buffer+3) == 'G' && *(start_buffer+4) == 'L' && *(start_buffer+5) == 'L')
	{
		printf("++++GLL+++\n");
		nmea_char_save.cmd = GLL;
		
		strcpy(save_GLL.Latitude,bb[1]);
		save_GLL.N_S = bb[2][0];
		strcpy(save_GLL.Lontitude,bb[3]);
		save_GLL.E_W = bb[4][0];
		strcpy(save_GLL.UTC,bb[5]);
		save_GLL.locat_state = bb[6][0];
		save_GLL.mode_state=bb[7][0];

	}
	else if(*(start_buffer+3) == 'R' && *(start_buffer+4) == 'M' && *(start_buffer+5) == 'C')
	{
		printf("++++RMC+++\n");
		nmea_char_save.cmd = RMC;
	
		strcpy(save_RMC.UTC,bb[1]);
		save_RMC.locat_state = bb[2][0];
		strcpy(save_RMC.Latitude,bb[3]);
		save_RMC.N_S = bb[4][0];
		strcpy(save_RMC.Lontitude,bb[5]);
		save_RMC.E_W = bb[6][0];
		strcpy(save_RMC.speed,bb[7]);
		strcpy(save_RMC.direction,bb[8]);
		strcpy(save_RMC.UTC_date,bb[9]);
		strcpy(save_RMC.mag_cour,bb[10]);
		save_RMC.mag_direct = bb[11][0];
		save_RMC.mode_state=bb[12][0];

	}	

//save to nmea struct
	if(nmea_char_save.cmd == GSA)
	{
		char gsa_num[25] = {0};

		strcpy(nmea_char_save.PDOP, save_GSA.PDOP);	
		strcpy(nmea_char_save.HDOP, save_GSA.HDOP);
		strcpy(nmea_char_save.VDOP, save_GSA.VDOP);

		if(nmea_char_save.sys == GP)
		{
			for (int i=0; i<12; i++)
			{
				strcpy(nmea_char_save.GP_PRN[i], save_GSA.PRN[i]);
				strcat(gsa_num, save_GSA.PRN[i]);
			}
			nmea_char_save.gp_n = strlen(gsa_num)/2;
		}
		else if(nmea_char_save.sys == BD)
		{
			for (int i=0; i<12; i++)
			{
				strcpy(nmea_char_save.BD_PRN[i], save_GSA.PRN[i]);
				strcat(gsa_num, save_GSA.PRN[i]);
			}
			nmea_char_save.bd_n = strlen(gsa_num)/2;
		}
		else if(nmea_char_save.sys == GL)
		{
			for (int i=0; i<12; i++)
			{
				strcpy(nmea_char_save.GL_PRN[i], save_GSA.PRN[i]);
				strcat(gsa_num, save_GSA.PRN[i]);
			}
			nmea_char_save.gl_n = strlen(gsa_num)/2;
		}
        else if(nmea_char_save.sys == GA)
        {
			for (int i=0; i<12; i++)
			{
				strcpy(nmea_char_save.GA_PRN[i], save_GSA.PRN[i]);
				strcat(gsa_num, save_GSA.PRN[i]);
			}
			nmea_char_save.ga_n = strlen(gsa_num)/2;        
        }
        else if(nmea_char_save.sys == GN)
        {
        
        }

        //TODO
        //send event to updating UI
	}
	else if(nmea_char_save.cmd == GGA)	//use
	{
        //转换成正常的经纬度值
        double lat = atof(save_GGA.Latitude)/100.0;
        double lon = atof(save_GGA.Lontitude)/100.0;
        sprintf(nmea_char_save.Latitude, "%f", lat);
        sprintf(nmea_char_save.Longitude, "%f", lon);

		//strcpy(nmea_char_save.Latitude, save_GGA.Latitude);
		//strcpy(nmea_char_save.Longitude, save_GGA.Lontitude);
		strcpy(nmea_char_save.Altitude, save_GGA.Altitude);
		strcpy(nmea_char_save.sat_num, save_GGA.satellite_use);

        strcpy(nmea_char_save.HDOP, save_GGA.HDOP);
		strcpy(nmea_char_save.VDOP, save_GGA.VDOP);

		if(nmea_char_save.sys == GP)
		{
			nmea_char_save.gp_gga = TRUE;
			nmea_char_save.gp_gga1 = TRUE;

			strcpy(nmea_char_save.GP_in_use, save_GGA.satellite_use);
			nmea_char_save.GP_use = atoi(save_GGA.satellite_use);
		}
		else if(nmea_char_save.sys == BD)
		{
			nmea_char_save.bd_gga = TRUE;

			strcpy(nmea_char_save.BD_in_use,save_GGA.satellite_use);
			nmea_char_save.BD_use = atoi(save_GGA.satellite_use);
		}
		else if(nmea_char_save.sys == GL)
		{
			nmea_char_save.gl_gga = TRUE;
			strcpy(nmea_char_save.GL_in_use, save_GGA.satellite_use);
			nmea_char_save.GL_use = atoi(save_GGA.satellite_use);
		}
        else if(nmea_char_save.sys == GA)
		{
			nmea_char_save.ga_gga = TRUE;
			strcpy(nmea_char_save.GA_in_use, save_GGA.satellite_use);
			nmea_char_save.GA_use = atoi(save_GGA.satellite_use);
		}
		else if(nmea_char_save.sys == GN)
		{
			nmea_char_save.gn_gga = TRUE;

			strcpy(nmea_char_save.GN_in_use, save_GGA.satellite_use);
			nmea_char_save.GN_use = atoi(save_GGA.satellite_use);
			//nmea_save.BD_in_use = atoi(save_GGA.satellite_use);
		}

        //TODO BD3_GGA_POS
        //BD3_GGA_POS result;

        nmea_char_save.N_S = save_GGA.N_S;
        nmea_char_save.E_W = save_GGA.E_W;

        //strncpy(nmea_char_save.utc_date,save_GGA.UTC,7);
		strncpy(nmea_char_save.utc_clk,save_GGA.UTC,9);

		//strToTime(atoi(nmea_char_save.utc_date));
        std::string utc(nmea_char_save.utc_clk);
		strToTime1(utc);

        m_Listener.OnUpdateGGAPOSView((WPARAM)(&nmea_char_save), 0);
	}
	else if(nmea_char_save.cmd == GSV)	//ID\CN0\view
	{
		int m;//可视卫星数

		strcpy(nmea_char_save.GSV_in_use, save_GSV.satellite_view);
		m = atoi(nmea_char_save.GSV_in_use);

		if(nmea_char_save.sys == GP)
		{
			nmea_char_save.GP_view_C = atoi(save_GSV.satellite_view);
			strcpy(nmea_char_save.GP_view_count, save_GSV.satellite_view);

			/*int ll_len=0;
			switch((save_GSV.GSV_numb - '0'))
			{
			case 1:
				if(nmea_char_save.GP_view_C==1)
					ll_len = nmea_char_save.GP_view_C - '0';
				else
					ll_len = 4;
				break;
			case 2:
				if(nmea_char_save.GP_view_C==2)
					ll_len = nmea_char_save.GP_view_C - '0';
				else
					ll_len = 4;
				break;
			case 3:
				if(nmea_char_save.GP_view_C==3)
					ll_len = nmea_char_save.GP_view_C - '0';
				else
					ll_len = 4;
				break;
			default:
				break;
			}*/
			int mm=(save_GSV.GSV_numb-'1')*4;
			for(int i=0; i<GSV_num; i++, mm++)
			{
				//sprintf(nmea_char_save.GP_view[mm].PRN, "%s-GPS", save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].PRN);
				strcpy(nmea_char_save.GP_view[mm].PRN, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].PRN);
				strcpy(nmea_char_save.GP_view[mm].CN0, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].CN0);

				strcpy(nmea_char_save.GP_view[mm].yang_cour, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].yang_cour);
				strcpy(nmea_char_save.GP_view[mm].fangwei_cour, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].fangwei_cour);
			}

			int kh=0, kn=0;
			if (save_GSV.GSV_numb == save_GSV.GSV_count)
			{
				int n = nmea_char_save.gp_n;//使用卫星数, 根据GSA来确定
				memset(nmea_char_save.GP_have, 0, SATALLITE_NUM);
				memset(nmea_char_save.GP_no, 0, SATALLITE_NUM);
				for (int i=0; i<m; i++)
				{
					int j=0;
					for (; j<n; j++)
					{
						if (atoi(nmea_char_save.GP_view[i].PRN)-atoi(nmea_char_save.GP_PRN[j]) == 0)//参与定位的卫星
						{
							nmea_char_save.GP_have[kh++] = i;
							nmea_char_save.GP_SEQ[i] = TRUE;
							break;
						}
					}
					if (j == n)//不参与定位的卫星
					{
						nmea_char_save.GP_no[kn++] = i;
						nmea_char_save.GP_SEQ[i] = FALSE;
					}
				}
			}
		}
		else if(nmea_char_save.sys == BD)
		{
			nmea_char_save.BD_view_C = atoi(save_GSV.satellite_view);
			strcpy(nmea_char_save.BD_view_count, save_GSV.satellite_view);

			/*int ll_len=0;
			switch(save_GSV.GSV_numb)
			{
			case 1:
				if(nmea_char_save.BD_view_C==1)
					ll_len = nmea_char_save.BD_view_C;
				else
					ll_len = 4;
				break;
			case 2:
				if(nmea_char_save.BD_view_C==2)
					ll_len = nmea_char_save.BD_view_C - 4;
				else
					ll_len = 4;
				break;
			case 3:
				if(nmea_char_save.BD_view_C==3)
					ll_len = nmea_char_save.BD_view_C - 4*2;
				else
					ll_len = 4;
				break;
			default:
				break;
			}*/
			int mm=(save_GSV.GSV_numb-'1')*4;
			for(int i=0; i<GSV_num; i++, mm++)
			{
				//sprintf(nmea_char_save.BD_view[mm].PRN, "%s-BD", save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].PRN);
				strcpy(nmea_char_save.BD_view[mm].PRN, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].PRN);
				strcpy(nmea_char_save.BD_view[mm].CN0, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].CN0);

				strcpy(nmea_char_save.BD_view[mm].yang_cour, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].yang_cour);
				strcpy(nmea_char_save.BD_view[mm].fangwei_cour, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].fangwei_cour);
			}	
			
			int kh=0, kn=0;
			if (save_GSV.GSV_numb == save_GSV.GSV_count)
			{
				nmea_char_save.gn_gsv = TRUE;
				nmea_char_save.gn_gsv1 = TRUE;

				int n = nmea_char_save.bd_n;
				memset(nmea_char_save.BD_have, 0, SATALLITE_NUM);
				memset(nmea_char_save.BD_no, 0, SATALLITE_NUM);
				for (int i=0; i<m; i++)
				{
					int j=0;
					for (; j<n; j++)
					{
						if (atoi(nmea_char_save.BD_view[i].PRN)-atoi(nmea_char_save.BD_PRN[j]) == 0)//参与定位的卫星
						{
							nmea_char_save.BD_have[kh++] = i;
							nmea_char_save.BD_SEQ[i] = TRUE;
							break;
						}
					}
					if (j == n)//不参与定位的卫星
					{
						nmea_char_save.BD_no[kn++] = i;
						nmea_char_save.BD_SEQ[i] = FALSE;
					}
				}
			}
		}
		else if(nmea_char_save.sys == GL)
		{
			nmea_char_save.GL_view_C = atoi(save_GSV.satellite_view);
			strcpy(nmea_char_save.GL_view_count, save_GSV.satellite_view);

			/*int ll_len=0;
			switch(save_GSV.GSV_numb)
			{
			case 1:
				if(nmea_char_save.BD_view_C==1)
					ll_len = nmea_char_save.BD_view_C;
				else
					ll_len = 4;
				break;
			case 2:
				if(nmea_char_save.BD_view_C==2)
					ll_len = nmea_char_save.BD_view_C - 4;
				else
					ll_len = 4;
				break;
			case 3:
				if(nmea_char_save.BD_view_C==3)
					ll_len = nmea_char_save.BD_view_C - 4*2;
				else
					ll_len = 4;
				break;
			default:
				break;
			}*/
			int mm=(save_GSV.GSV_numb-'1')*4;
			for(int i=0; i<GSV_num; i++, mm++)
			{
				//sprintf(nmea_char_save.BD_view[mm].PRN, "%s-BD", save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].PRN);
				strcpy(nmea_char_save.GL_view[mm].PRN, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].PRN);
				strcpy(nmea_char_save.GL_view[mm].CN0, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].CN0);

				strcpy(nmea_char_save.GL_view[mm].yang_cour, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].yang_cour);
				strcpy(nmea_char_save.GL_view[mm].fangwei_cour, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].fangwei_cour);
			}	
			
			int kh=0, kn=0;
			if (save_GSV.GSV_numb == save_GSV.GSV_count)
			{
				nmea_char_save.gn_gsv = TRUE;
				nmea_char_save.gn_gsv1 = TRUE;

				int n = nmea_char_save.bd_n;
				memset(nmea_char_save.GL_have, 0, SATALLITE_NUM);
				memset(nmea_char_save.GL_no, 0, SATALLITE_NUM);
				for (int i=0; i<m; i++)
				{
					int j=0;
					for (; j<n; j++)
					{
						if (atoi(nmea_char_save.GL_view[i].PRN)-atoi(nmea_char_save.GL_PRN[j]) == 0)//参与定位的卫星
						{
							nmea_char_save.GL_have[kh++] = i;
							nmea_char_save.GL_SEQ[i] = TRUE;
							break;
						}
					}
					if (j == n)//不参与定位的卫星
					{
						nmea_char_save.GL_no[kn++] = i;
						nmea_char_save.GL_SEQ[i] = FALSE;
					}
				}
			}
		}
        else if(nmea_char_save.sys == GA)
		{
			nmea_char_save.GA_view_C = atoi(save_GSV.satellite_view);
			strcpy(nmea_char_save.GA_view_count, save_GSV.satellite_view);

			int mm=(save_GSV.GSV_numb-'1')*4;
			for(int i=0; i<GSV_num; i++, mm++)
			{
				//sprintf(nmea_char_save.BD_view[mm].PRN, "%s-BD", save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].PRN);
				strcpy(nmea_char_save.GA_view[mm].PRN, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].PRN);
				strcpy(nmea_char_save.GA_view[mm].CN0, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].CN0);

				strcpy(nmea_char_save.GA_view[mm].yang_cour, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].yang_cour);
				strcpy(nmea_char_save.GA_view[mm].fangwei_cour, save_GSV.satellite_info[save_GSV.GSV_numb-'1'][i].fangwei_cour);
			}	
			
			int kh=0, kn=0;
			if (save_GSV.GSV_numb == save_GSV.GSV_count)
			{
				nmea_char_save.gn_gsv = TRUE;
				nmea_char_save.gn_gsv1 = TRUE;

				int n = nmea_char_save.bd_n;
				memset(nmea_char_save.GA_have, 0, SATALLITE_NUM);
				memset(nmea_char_save.GA_no, 0, SATALLITE_NUM);
				for (int i=0; i<m; i++)
				{
					int j=0;
					for (; j<n; j++)
					{
						if (atoi(nmea_char_save.GA_view[i].PRN)-atoi(nmea_char_save.GA_PRN[j]) == 0)//参与定位的卫星
						{
							nmea_char_save.GA_have[kh++] = i;
							nmea_char_save.GA_SEQ[i] = TRUE;
							break;
						}
					}
					if (j == n)//不参与定位的卫星
					{
						nmea_char_save.GA_no[kn++] = i;
						nmea_char_save.GA_SEQ[i] = FALSE;
					}
				}
			}
		}
		else if(nmea_char_save.sys == GN)
		{
			;
		}

        //send event to updating UI
        //m_Listener.OnAnswerInfoSKY((WPARAM)(&nmea_char_save), 0);

        int id=0;
	    double elv=0,azi=0;

        int sum = save_GSV.GSV_count - '0';
        int index = save_GSV.GSV_numb - '0';
        int count = strtod(save_GSV.satellite_view, NULL);

        m_packGSV.num = count;
        if (sum == index)
        {
      //      for (int i=0; i<count; i++)
		    //{
      //          id = atoi(nmea_char_save.BD_view[i].PRN);
      //          elv = strtod(nmea_char_save.BD_view[i].yang_cour, NULL);
      //          azi = strtod(nmea_char_save.BD_view[i].fangwei_cour, NULL);


			   // m_packGSV.id[i] = id;
			   // m_packGSV.elv[i] = elv;
			   // m_packGSV.azi[i] = azi;
      //          m_packGSV.snr[i] = strtod(nmea_char_save.BD_view[i].CN0, NULL);

		    //}

      //      m_packGSV.system_type = nmea_char_save.sys;

            //m_Listener.OnAnswerInfoGSV((WPARAM)(&m_packGSV), 0);
            //m_Listener.OnAnswerInfoSNR((WPARAM)(&m_packGSV), 1);

            m_Listener.OnAnswerInfoGSV((WPARAM)(&nmea_char_save), 0);
            m_Listener.OnAnswerInfoSNR((WPARAM)(&nmea_char_save), 1);
        }
	}
	else if(nmea_char_save.cmd == GLL)
	{
		;
	}
	else if(nmea_char_save.cmd == RMC)
	{
		nmea_char_save.fix_mode = save_RMC.locat_state;
		strcpy(nmea_char_save.speed, save_RMC.speed);
		nmea_char_save.direction = atof(save_RMC.direction);

		strncpy(nmea_char_save.utc_date,save_RMC.UTC_date,7);
		strncpy(nmea_char_save.utc_clk,save_RMC.UTC,7);

		strToTime(atoi(nmea_char_save.utc_date));
		//strToTime1(atoi(nmea_char_save.utc_clk));
        std::string utc(nmea_char_save.utc_clk);
		strToTime1(utc);
	}
}

int CDisposeBD3::CalCheckVal(char *pData, int len)
{
    int check_result = *(pData+1);
    pData += 2;
    while (len>1)
    {
        check_result ^=  *pData;
        pData++;
        --len;
    }

    return check_result;
}

int CDisposeBD3::CheckData(char *start)
{
    int nmea_cr = 0;
    int t = 0;
    int check_result = *(start+1);
	start += 2;
	while(*start != '*')
	{
		check_result ^= *start;
		start++;
	}
	start++;	//'*'之后

	//for(; start <= end; start++)
	for(int i=0; i < 2; i++,start++)
	{	
		if(*start >= '0' && *start <= '9')
			t = *start - 48;
		else if(*start <= 'f' && *start >='a')
			t = *start - 87;
		else if(*start >= 'A' && *start <= 'F')
			t = *start - 55;

		nmea_cr <<= 4;
		nmea_cr |= t;
	}

    if(check_result == nmea_cr)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

void CDisposeBD3::strToTime(int time_clk)
{
	//日月年
	nmea_char_save.UTC.year = time_clk%100+2000;
	nmea_char_save.UTC.month = time_clk/100%100;
	nmea_char_save.UTC.day = time_clk/10000;
}

void CDisposeBD3::strToTime1(std::string time_date)
{
	//时分秒.毫秒
	//nmea_char_save.UTC.hour = (int)time_date/10000;
	//nmea_char_save.UTC.minute = ((int)time_date)/100%100;
	//nmea_char_save.UTC.second = int (time_date)%100;

    nmea_char_save.UTC.hour = atoi(time_date.substr(0,2).c_str());
    nmea_char_save.UTC.minute = atoi(time_date.substr(2,2).c_str());
    nmea_char_save.UTC.second = atof(time_date.substr(4,5).c_str());
}

int char2num(char ch) /*将字符转成数字*/
{
    if (ch >= 'a')
        return ch - 'a' + 10;
    else if (ch >= 'A')
        return ch - 'A' + 10;
    else
        return ch - '0';
}

CString CDisposeBD3::HexToString(char *hex, int len)
{
    int n = 0;
    int j = 0;
    char st2[1024];
    memset(st2, 0, 1024);
    for (int i=0; i<len; i+=2)
    {
        n=char2num(hex[i])*16+char2num(hex[i+1]);
        st2[j++]=n;
    }

    TRACE("hex string :%s\n", st2);
    CString str;
    str.Format("%s", st2);
    return str;
}