#include "StdAfx.h"
#include "PrintFile.h"
#include "PrintData.h"
#include "TransFunc.h"
#include "EphFunc.h"

CPrintFile::CPrintFile(void)
{
	m_nStart = 0;
	m_strPath.Empty();
	m_strDatabase.Empty();
	m_strConfigPath.Empty();
}

CPrintFile::~CPrintFile(void)
{
}
void CPrintFile::LoadConfig(CString strDatabase, CString strConfigPath)
{
	m_strDatabase = strDatabase;
	m_strConfigPath = strConfigPath;
}

void CPrintFile::SaveCODFile(BD2_COD* data)
{
	char buf[MAX_PATH];
	unsigned int i=0,len=0;
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "cod", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "codFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;

	strText.Format("%02d	%02d	%02d	", data->id, data->branch,data->prm);
	for (i=0; i<data->len; i++)
	{
		strTemp.Format("%02X", data->CodBuf[i]);
		strText += strTemp;
	}
	strText += "\r\n";
	len = strText.GetLength();
	if(len > 1024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}
void CPrintFile::SaveEPHFile(BD2_EPH* data)
{
	int len=0,length=0,branch=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "eph", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "ephFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;

	if (data->system == SYSTEM_BD1)
	{
		strText.Format("BD1:%d	%.1f	%02d	%02d	%d	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%d	%f	%f	%f	%f	%f	%f\n", 
			data->week,data->tow,data->id, data->branch,data->iode,data->toe,data->sqrta,data->deltaN,data->m0,data->e,data->w,data->omega0,data->i0,data->omegadot,data->idot,data->cis,data->cic,data->crs,data->crc,
			data->cus,data->cuc,data->iodc,data->toc,data->af0,data->af1,data->af2,data->tgd1,data->tgd2);
	} 
	else
	{
		strText.Format("BD2:%d	%.1f	%02d	%02d	%d	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%d	%f	%f	%f	%f	%f	%f	%f\n", 
			data->week,data->tow,data->id, data->branch,data->iode,data->toe,data->deltaA,data->Adot,data->deltaN,data->Ndot,data->m0,data->e,data->w,data->omega0,data->i0,data->omegadot,data->idot,data->cis,data->cic,data->crs,data->crc,
			data->cus,data->cuc,data->iodc,data->toc,data->af0,data->af1,data->af2,data->tgd1,data->tgd2,data->tgd3);
	}
	len = strText.GetLength();
	if (len > 2048)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);

	
#ifdef __SAVE_SAT_POS_
	CString strName, strPath;
	BD2_EPH TempEPH;
	BD2_OBSTIME obsTime;
	BD2_SAT_POS satpos;
	branch = BranchToitem(data->branch);
	if(branch == -1)
		return;
	memcpy(&TempEPH, data, sizeof(BD2_EPH));
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	GetPrivateProfileString("Product", "ProjSat", "", buf, MAX_PATH, m_strConfigPath);
	strPath = CString(buf);
	strPath.ReleaseBuffer();
	if (!strPath.IsEmpty())
	{
		obsTime.Weeks = data->week;
		obsTime.Tow = data->tow;
		strName.Format("s%02d_%s_satpos.dat", data->id, strFREQ[branch]);
		if (data->flag)
		{
			if (CalculateSatPos(TempEPH, obsTime, &satpos, 0))
			{
				strText.Format("% 6.1f% 5d% 5d% 21.6f% 21.6f% 21.6f\n", data->tow, data->id, data->branch, satpos.x, satpos.y, satpos.z);
				length = strText.GetLength();
				RecordFile(strText.GetBuffer(length), length, strPath + strName);//
			}
		}
	}
#endif
}
void CPrintFile::SaveIONFile(BD2_ION* data)
{
	int len=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "ion", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "ionFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;

	if (data->system == SYSTEM_BD1)
	{
		strText.Format("BD1:%d	%.1f	%02d	%02d	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f\n",
			data->week,data->tow,data->id,data->branch,data->A1,data->B,data->alpha0,data->alpha1,data->alpha2,data->alpha3,data->beta0,data->beta1,data->beta2,data->beta3,data->gamma0,data->gamma1,data->gamma2,data->gamma3);
	} 
	else
	{
		strText.Format("BD2:%d	%.1f	%02d	%02d	%f	%f	%f	%f	%f	%f	%f	%f	%f\n",
			data->week,data->tow,data->id,data->branch,data->af1,data->af2,data->af3,data->af4,data->af5,data->af6,data->af7,data->af8,data->af9);
	}
	len = strText.GetLength();
	if (len > 2024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}
void CPrintFile::SaveALMFile(BD2_ALM* data)
{
	int len=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "alm", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "almFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;

	/*if (data->type == 1)
	{*/
	strText.Format("%02d	%02d	%d	%d	%d	%f	%f	%f	%f	%f	%f	%f	%f	%f\n",data->id,data->branch,data->week,data->health,data->toa,
		data->sqrta,data->e,data->w,data->m0,data->omega0,data->omegadot,data->sigma,data->af0,data->af1);
	/*} 
	else
	{
	}*/
	len = strText.GetLength();
	if (len > 1024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}
void CPrintFile::SaveJALFile(BD2_JAL* data)
{
	int len=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "jal", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "jalFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;

	strText.Format("%02d	%02d	%d	%f	%f	%d\n",data->id,data->branch,data->sigma,data->omega,data->theta,data->health);
	len = strText.GetLength();
	if (len > 1024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}
void CPrintFile::SaveCOMFile(SETCOM* data)
{
	int len=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "com", 0, m_strConfigPath);
	if(!flag)
		return;
}
void CPrintFile::SaveMODFile(SETMOD* data)
{
	int len=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "mod", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "modFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;

	strText.Format("%02d	%02d	%02d	%02d	%02d	%02d	%02d	%02d	%02d\n",
		data->BD2Pos,data->BD1Pos,data->GPSPos,data->GaliPos,data->ComPos,data->BD2Time,data->BD1Time,data->GPSTime,data->GaliTime);
	len = strText.GetLength();
	if (len > 1024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}
void CPrintFile::SavePOSFile(BD2_POS* data)
{
	int len=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "pos", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "posFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;

	strText.Format("%d	%.1f	%02d	%02d	%02d	%.8f	%.8f	%.3f	%.3f	%.3f	%.1f	%.1f	%.1f	%.1f	%.1f	%.1f	",
		data->week,data->tow,data->mode,data->num,data->numuse,data->blh.lat,data->blh.lon,data->blh.alt,data->speed.x,data->speed.y,data->clock,data->dop.hdop,data->dop.vdop,data->dop.pdop,data->dop.tdop,data->dop.gdop);
	for (int i=0; i<data->numuse; i++)
	{
		strTemp.Format("%02d,", data->Ids[i]);
		strText += strTemp;
	}
	strText += "\n";
	len = strText.GetLength();
	if(len > 2024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}
void CPrintFile::SaveRANFile(BD2_RAN* data)
{
	int len=0,branch=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "ran", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "ranFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	branch = BranchToitem(data->branch);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;
	for (int i=0; i<data->numuse; i++)
	{
		strTemp.Format("s%02d_ran.table", data->svId[i], strFREQ[branch]);
		strText.Empty();
		strText.Format("% 5d% 8.1f% 4d% 4d% 4d% 20.3f% 20.6f %15.3f	% 8.2f/% 8.2f  %08X  %08X\n",
			data->week,data->tow,data->numuse,data->branch,data->svId[i],data->ran[i].x,data->ran[i].y,data->ran[i].z,data->snr[i],data->snr[i]-173.0,data->status1[i],data->status2[i]);
		len = strText.GetLength();
		if (len > 1024)
			continue;
		RecordFile(strText.GetBuffer(len), len, m_strDatabase + strTemp);
		//RecordFile(strText.GetBuffer(len), len, m_strPath);
	}
}
void CPrintFile::SaveREFFile(SETREF* data)
{
	int len=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "ref", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "refFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;

	strText.Format("%02d	%02d	%02d	%02d	%f	%f	%f	%f	%f	%f	%f	%f	%f	%f\n",
		data->timeSys,data->timeFmt,data->posSys,data->posFmt,data->ellipse.a,data->ellipse.f,data->ellipse.w,data->ellipse.gm,data->ellipse.dx,data->ellipse.dy,data->ellipse.dz,data->ellipse.alpha,data->ellipse.beta,data->ellipse.gamma);
	
	len = strText.GetLength();
	if (len > 1024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}
void CPrintFile::SaveGSVFile(BD2_GSV* data)
{
	int len=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "gsv", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "gsvFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;
	for (int i=0; i<data->num; i++)
	{
		strText.Empty();
		strText.Format("%02d	%02d	%.1f	%.1f	%.1f/%.1f\n", data->num, data->id[i],data->elv[i],data->azi[i],data->snr[i],data->snr[i]-173);
		len = strText.GetLength();
		if (len > 1024)
			continue;
		RecordFile(strText.GetBuffer(len), len, m_strPath);
	}
}

void CPrintFile::SaveAllGSVFile(NmeaAllData* data)
{
	int len=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "gsv", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "gsvFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;

    int num = 0;
    switch(data->sys)
    {
    case GP:
        num = data->GP_view_C;
        break;

    case BD:
        num = data->BD_view_C;
        break;

    case GL:
        num = data->GL_view_C;
        break;

    case GA:
        num = data->GA_view_C;
        break;

    default:
        num = data->BD_view_C;
        break;    
    }


	for (int i=0; i<num; i++)
	{
		strText.Empty();

        switch(data->sys)
        {
        case GP:
            strText.Format("%02d	%02d	%.1f	%.1f	%.1f/%.1f\n", num, atoi(data->GP_view[i].PRN),
                strtod(data->GP_view[i].yang_cour, NULL),strtod(data->GP_view[i].fangwei_cour, NULL),
                strtod(data->GP_view[i].CN0, NULL),strtod(data->GP_view[i].CN0, NULL)-173);
            break;

        case BD:
            strText.Format("%02d	%02d	%.1f	%.1f	%.1f/%.1f\n", num, atoi(data->BD_view[i].PRN),
                strtod(data->BD_view[i].yang_cour, NULL),strtod(data->BD_view[i].fangwei_cour, NULL),
                strtod(data->BD_view[i].CN0, NULL),strtod(data->BD_view[i].CN0, NULL)-173);        
            break;

        case GL:
            strText.Format("%02d	%02d	%.1f	%.1f	%.1f/%.1f\n", num, atoi(data->GL_view[i].PRN),
                strtod(data->GL_view[i].yang_cour, NULL),strtod(data->GL_view[i].fangwei_cour, NULL),
                strtod(data->GL_view[i].CN0, NULL),strtod(data->GL_view[i].CN0, NULL)-173);        
            break;

        case GA:
            strText.Format("%02d	%02d	%.1f	%.1f	%.1f/%.1f\n", num, atoi(data->GA_view[i].PRN),
                strtod(data->GA_view[i].yang_cour, NULL),strtod(data->GA_view[i].fangwei_cour, NULL),
                strtod(data->GA_view[i].CN0, NULL),strtod(data->GA_view[i].CN0, NULL)-173);        
            break;

        default:
            strText.Format("%02d	%02d	%.1f	%.1f	%.1f/%.1f\n", num, atoi(data->BD_view[i].PRN),
                strtod(data->BD_view[i].yang_cour, NULL),strtod(data->BD_view[i].fangwei_cour, NULL),
                strtod(data->BD_view[i].CN0, NULL),strtod(data->BD_view[i].CN0, NULL)-173);        
            break;    
        }
		
		len = strText.GetLength();
		if (len > 1024)
			continue;
		RecordFile(strText.GetBuffer(len), len, m_strPath);
	}
}

void CPrintFile::SaveTESTFile(BD2_PAORDER* data)
{
	
}
void CPrintFile::SaveCHDFile(BD2_CHD* data)
{
	
}
void CPrintFile::SaveSTAFile(BD2_STA* data)
{
	int len=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "sta", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "staFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;

	strText.Format("%d	%.1f	%d	%d	%d	%d	%d\n",data->week,data->tow,data->number,data->cpu,data->soft,data->clock,data->pps);
	len = strText.GetLength();
	if (len > 1024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}
void CPrintFile::SaveTIMFile(BD2_TIME* data)
{
	int len=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "tim", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "timFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;

	strText.Format("%d	%.1f	%d	%d	%04d/%02d/%02d-%02d:%02d:%02d-%02d	%.4f	", 
		data->week,data->tow,data->posMod,data->timMod,data->year,data->month,data->day,data->hour,data->minute,data->second,data->clkErr);
	for (int i=0; i<data->num; i++)
	{
		strTemp.Format("%02d", data->svId[i]);
		strText += strTemp;
	}
	strText += "\n";
	len = strText.GetLength();
	if (len > 1024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}
void CPrintFile::SaveGBSFile(BD2_GBS* data)
{
	int len=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "gbs", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "gbsFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;

	strText.Format("%d	%.1f	%.3f	%.3f	%.3f	%d	%.3f	%.3f	%.3f\n",data->week,data->tow,data->latErr,data->lonErr,data->altErr,data->idErr,data->checkErr,data->evaluateErr,data->offset);
	len = strText.GetLength();
	if (len > 1024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}
void CPrintFile::SaveXPVFile(BD2_POS* data)
{
	int len=0;
	char buf[MAX_PATH];
	CString strText,strTemp;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "xpv", 0, m_strConfigPath);
	GetPrivateProfileString("FILE", "xpvFile", "", buf, MAX_PATH, m_strConfigPath);
	m_strPath = CString(buf);
	if(!flag || m_strPath.IsEmpty())
		return;
	m_strPath = m_strDatabase + m_strPath;

	strText.Format("%d	%.1f	%02d	%02d	%02d	%.8f	%.8f	%.3f	%.3f	%.3f	%.1f	%.1f	%.1f	%.1f	%.1f	%.1f	",
		data->week,data->tow,data->mode,data->num,data->numuse,data->blh.lat,data->blh.lon,data->blh.alt,data->speed.x,data->speed.y,data->clock,data->dop.hdop,data->dop.vdop,data->dop.pdop,data->dop.tdop,data->dop.gdop);
	for (int i=0; i<data->numuse; i++)
	{
		strTemp.Format("%02d,", data->Ids[i]);
		strText += strTemp;
	}
	strText += "\n";
	len = strText.GetLength();
	if(len > 2024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}