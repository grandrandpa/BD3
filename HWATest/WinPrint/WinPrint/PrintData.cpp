#include "StdAfx.h"
#include "PrintData.h"
#include "TransFunc.h"

#define MAXSVNUM     64
#define MAXBAUD     10
#define MAXFREQ     13
#define MAXFREQS     31
#define ELV_LIMIT	5.0
//////////////////////////////////////////////////////////////////////////
CString strFREQ[13] = {"B1I", "B1Q", "B1C", "B1A", "B2a", "B2b", "B2", "B3I", "B3Q", "B3C", "B3A", "B3AE", "Bs" };
CString strMODE[MAXMODE] = {"B1I", "B1Q", "B1C", "B1A", "B2a", "B2b", "B2", "B3I", "B3Q", "B3C", "B3A", "B3AE", "Bs", "B1CB3C", "B1QB3Q", "B1AB3A", "B1AB3AE", "BsB3A", "BsB3AE", "B1CB2a", "B1CB2B3C", "USER" };
//////////////////////////////////////////////////////////////////////////
CString strBDRAN = "   WN    SOW   Num    ID          Range_B1I          Range_B1Q          Range_B1C          Range_B1A          Range_B2a          Range_B2b           Range_B2          Range_B3I          Range_B3Q          Range_B3C          Range_B3A           Range_Bs         Range_B3AE          Range_RDI          Range_RDQ          Phase_B1I          Phase_B1Q          Phase_B1C          Phase_B1A          Phase_B2a          Phase_B2b           Phase_B2          Phase_B3I          Phase_B3Q          Phase_B3C          Phase_B3A           Phase_Bs         Phase_B3AE          Phase_RDI          Phase_RDQ CN0_B1I CN0_B1Q CN0_B1C CN0_B1A CN0_B2a CN0_B2b  CN0_B2 CN0_B3I CN0_B3Q CN0_B3C CN0_B3A  CN0_Bs CN0_B3AE CN0_RDI CN0_RDQ    Dopp_B1I    Dopp_B1Q    Dopp_B1C    Dopp_B1A    Dopp_B2a    Dopp_B2b     Dopp_B2    Dopp_B3I    Dopp_B3Q    Dopp_B3C    Dopp_B3A     Dopp_Bs   Dopp_B3AE    Dopp_RDI    Dopp_RDQ \n";
CString strBDEPH = "   WN     SOW   Sat     IQ      Toe                    e                   M0                   I0                  Cic                  Cis                 IDOT                    w               Omega0                  Cuc                  Cus               DeltaN                RootA             OmegaDOT IODE                  Crc                  Crs IODC                  Toc                   a0                   a1                   a2                 tgd1                 tgd2 SatHel \n";
CString strBSEPH = "   WN     SOW   Sat     IQ               DeltaA                 ADOT               DeltaN            DeltaDotN      Toe                    e                    w                   M0               Omega0             OmegaDOT                   I0                I0DOT IODE                  Cuc                  Cus                  Crc                  Crs                  Cic                  Cis IODC                  Toc                   a0                   a1                   a2                 Tgd1                 Tgd2                 Tgd3 SatHel \n";
CString strBDION = "  WN    SOW   SatID FreqIQ          A1             B               Alpha0               Alpha1               Alpha2               Alpha3                Beta0                Beta1                Beta2                Beta3               Gamma0               Gamma1               Gamma2               Gamma3 \n";
CString strBSION = "  WN    SOW   SatID FreqIQ             Alpha1               Alpha2               Alpha3               Alpha4               Alpha5               Alpha6               Alpha7               Alpha8               Alpha9 \n";
CString strBDALM = "  WN    SatID FreqIQ SatH      RootA        Omega0             e              w             M0        DeltaI      OmegaDOT        Toa          A0               A1 \n";
CString strBSALM = "  WN    SatID FreqIQ SatH      RootA        Omega0             e              w             M0        DeltaI      OmegaDOT        Toa         Af0              Af1 \n";
CString strBDJAL = "   WN	  SEC FreqIQ SatID SatH             SigmaA               Omega0               Alpha0        Toa \n";
CString strBSJAL = "   WN	  SEC FreqIQ SatID SatH             SigmaA               Omega0               Alpha0        Toa \n";
CString strBDCOD = "   WN   SOW  SatID  FREQ  NavSource    CodHex \n";
CString strBDPOS = "   WN    SOW            X            Y            Z              B              L              H      ClockDiff       speedX       speedY       speedZ       HDOP       VDOP       PDOP       TDOP       GDOP        HPL        VPL   HPL_waas   VPL_waas         Herror         Verror       PosError     SatNum  SatCode \n";
CString strBDXPV = "   WN    SOW            X            Y            Z              B              L              H      ClockDiff       speedX       speedY       speedZ       HDOP       VDOP       PDOP       TDOP       GDOP        HPL        VPL   HPL_waas   VPL_waas         Herror         Verror       PosError     SatNum  SatCode \n";


CPrintData::CPrintData(void)
{
	Reset();
	m_nLeap = 0;
	m_nRanTime = 0;
	m_globalWeek = 0;
	m_globalTow = 0;
	m_strPath.Empty();
	m_strSaveData.Empty();
	m_strConfigPath.Empty();
	memset(&m_packRAN, 0, sizeof(m_packRAN));
	memset(&m_cacheRAN, 0, sizeof(m_cacheRAN));
}

CPrintData::~CPrintData(void)
{
}
void CPrintData::Reset()
{
	m_bBDEPHFlag = false;
	m_bBSEPHFlag = false;
	m_bBDIONFlag = false;
	m_bBSIONFlag = false;
	m_bBDALMFlag = false;
	m_bBSALMFlag = false;
	m_bBSJALFlag = false;
	m_bBDRANFlag = false;
	m_nRanTime = 0;
	m_globalWeek = 0;
	m_globalTow = 0;
	m_strPath.Empty();
	m_strSaveData.Empty();
	m_strConfigPath.Empty();
	memset(&m_packRAN, 0, sizeof(m_packRAN));
	memset(&m_cacheRAN, 0, sizeof(m_cacheRAN));
	memset(&m_cacheEPH, 0, sizeof(m_cacheEPH));
	memset(&m_cacheION, 0, sizeof(m_cacheION));
}
void CPrintData::LoadConfig(CString strSaveData, CString strConfigPath)
{
	Reset();
	m_strSaveData = strSaveData;
	m_strConfigPath = strConfigPath;
}
void CPrintData::SaveCODFile(BD2_COD* data)
{
	char buf[MAX_PATH];
	CString strText,strTemp,strName;
	unsigned int i=0,len=0,count=0,branch=0;
	//double curTime = data->week*SECONDS_IN_WEEK + data->tow;
	UTCTime obsTime;
	memset(&obsTime, 0, sizeof(UTCTime));
	m_strPath.Empty();
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "cod", 0, m_strConfigPath);
	branch = BranchToitem(data->branch);
	if(branch == -1)
		return;
	if(!flag || m_strSaveData.IsEmpty())
		return;
	/*if (data->tow%86400 == 0)
	{
	}*/
	obsTime.week = data->week;
	obsTime.tow = data->tow;
	obsTime.leap = m_nLeap;
	BDTime2UTC(&obsTime);
	strName.Format("bd_%s_%04d%02d%02d.cod", strFREQ[branch], obsTime.year, obsTime.month, obsTime.day);
	m_strPath = m_strSaveData + "\\COD\\" + strName;
	len = m_strPath.GetLength();
	if (_access(m_strPath.GetBuffer(len), 0) != 0)
	{
		len = strBDCOD.GetLength();
		RecordFile(strBDCOD.GetBuffer(len), len, m_strPath);
	}
	strText.Format("% 5d% 8.0f% 3d% 8s% 4d  ", data->week, data->tow, data->id, strFREQ[branch],data->prm);
	for (i=0; i<data->len; i++)
	{
		strTemp.Format("%02X", data->CodBuf[i]);
		strText += strTemp;
	}
	strText += "\n";
	len = strText.GetLength();
	if(len > 1024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}
bool CPrintData::CompareEPH(BD2_EPH* eph0, BD2_EPH* eph1)
{
	if (eph0->system == SYSTEM_BD1)
	{
		if(eph0->sqrta != eph1->sqrta)
			return false;
	}
	else
	{
		if(eph0->deltaA != eph1->deltaA || eph0->Adot != eph1->Adot || eph0->Ndot != eph1->Ndot || eph0->tgd3 != eph1->tgd3)
			return false;
	}
	if(eph0->deltaN != eph1->deltaN || eph0->iode != eph1->iode || eph0->toe != eph1->toe || eph0->m0 != eph1->m0 || eph0->e != eph1->e)
		return false;
	if(eph0->w != eph1->w || eph0->omega0 != eph1->omega0 || eph0->i0 != eph1->i0, eph0->omegadot != eph1->omegadot || eph0->idot != eph1->idot)
		return false;
	if(eph0->cis != eph1->cis || eph0->cic != eph1->cic || eph0->crs != eph1->crs || eph0->crc != eph1->crc || eph0->cus != eph1->cus || eph0->cuc != eph1->cuc)
		return false;
	if(eph0->iodc != eph1->iodc || eph0->toc != eph1->toc || eph0->af0 != eph1->af0 || eph0->af1 != eph1->af1 || eph0->af2 != eph1->af2)
		return false;
	if(eph0->tgd1 != eph1->tgd1 || eph0->tgd2 != eph1->tgd2)
		return false;

	return true;
}
bool CPrintData::CompareION(BD2_ION* ion0, BD2_ION* ion1)
{
	if (ion0->system == SYSTEM_BD1)
	{
		if(ion0->A1 != ion1->A1 || ion0->B != ion1->B)
			return false;
		if(ion0->alpha0 != ion1->alpha0 || ion0->alpha1 != ion1->alpha1 || ion0->alpha2 != ion1->alpha2 || ion0->alpha3 != ion1->alpha3)
			return false;
		if(ion0->beta0 != ion1->beta0 || ion0->beta1 != ion1->beta1 || ion0->beta2 != ion1->beta2 || ion0->beta3 != ion1->beta3)
			return false;
		if(ion0->gamma0 != ion1->gamma0 || ion0->gamma1 != ion1->gamma1 || ion0->gamma2 != ion1->gamma2 || ion0->gamma3 != ion1->gamma3)
			return false;
	} 
	else
	{
		if(ion0->af1 != ion1->af1 || ion0->af2 != ion1->af2 || ion0->af3 != ion1->af3 || ion0->af4 != ion1->af4)
			return false;
		if(ion0->af5 != ion1->af5 || ion0->af6 != ion1->af6 || ion0->af7 != ion1->af7 || ion0->af8 != ion1->af8 || ion0->af9 != ion1->af9)
			return false;
	}
	return true;
}
void CPrintData::SaveEPHFile(BD2_EPH* data)
{
	char buf[MAX_PATH];
	unsigned int i=0,len=0,count=0,branch=0;
	CString strText,strTemp,strName;
	UTCTime obsTime;
	memset(&obsTime, 0, sizeof(UTCTime));
	m_strPath.Empty();
	strText.Empty();
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "eph", 0, m_strConfigPath);
	branch = BranchToitem(data->branch);
	if(branch == -1)
		return;
	if(!flag || m_strSaveData.IsEmpty())
		return;
	if(CompareEPH(data, &m_cacheEPH[branch][data->id-1]))//判断星历是否更新
		return;
	memcpy(&m_cacheEPH[branch][data->id-1], data, sizeof(BD2_EPH));
	obsTime.week = data->week;
	obsTime.tow = data->tow;
	obsTime.leap = m_nLeap;
	BDTime2UTC(&obsTime);
	if (data->system == SYSTEM_BD1)
	{
		strName.Format("s%02d_bdeph_%04d%02d%02d.eph", data->id, obsTime.year, obsTime.month, obsTime.day);
		m_strPath = m_strSaveData + "\\EPH\\" + strName;
		len = m_strPath.GetLength();
		if (_access(m_strPath.GetBuffer(len), 0) != 0)
		{
			len = strBDEPH.GetLength();
			RecordFile(strBDEPH.GetBuffer(len), len, m_strPath);
		}
		strTemp.Format("% 5d% 8.0f% 6d% 7s% 9.0f% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e", data->week,data->tow,data->id, strFREQ[branch],data->toe,data->e,data->m0,data->i0,data->cic,data->cis);
		strText += strTemp;
		strTemp.Format("% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e", data->idot,data->w,data->omega0,data->cuc,data->cus,data->deltaN,data->sqrta);
		strText += strTemp;
		strTemp.Format("% 21.12e% 5d% 21.12e% 21.12e% 5d% 21.12e", data->omegadot,data->iode,data->crc,data->crs,data->iodc,data->toc);
		strText += strTemp;
		strTemp.Format("% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e% 7d", data->af0,data->af1,data->af2,data->tgd1,data->tgd2, data->health);
		strText += strTemp;
		strText += "\n";
	}
	else
	{
		strName.Format("s%02d_bseph_%04d%02d%02d.eph", data->id, obsTime.year, obsTime.month, obsTime.day);
		m_strPath = m_strSaveData + "\\EPH\\" + strName;
		len = m_strPath.GetLength();
		if (_access(m_strPath.GetBuffer(len), 0) != 0)
		{
			len = strBSEPH.GetLength();
			RecordFile(strBSEPH.GetBuffer(len), len, m_strPath);
		}
		strTemp.Format("% 5d% 8.0f% 6d% 7s% 21.12e% 21.12e% 21.12e% 21.12e% 9.0f", data->week,data->tow,data->id, strFREQ[branch],data->deltaA,data->Adot,data->deltaN,data->Ndot,data->toe);
		strText += strTemp;
		strTemp.Format("% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e% 5d", data->e,data->w,data->m0,data->omega0,data->omegadot,data->i0,data->idot,data->iode);
		strText += strTemp;
		strTemp.Format("% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e% 5d% 21.12e", data->cuc,data->cus,data->crc,data->crs,data->cic,data->cis,data->iodc,data->toc);
		strText += strTemp;
		strTemp.Format("% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e% 7d", data->af0,data->af1,data->af2,data->tgd1,data->tgd2,data->tgd3, data->health);
		strText += strTemp;
		strText += "\n";
	}
	len = strText.GetLength();
	if (len > 1048)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}
void CPrintData::SaveIONFile(BD2_ION* data)
{
	char buf[MAX_PATH];
	unsigned int i=0,len=0,count=0,branch=0;
	CString strText,strTemp,strName;
	UTCTime obsTime;
	memset(&obsTime, 0, sizeof(UTCTime));
	m_strPath.Empty();
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "ion", 0, m_strConfigPath);
	branch = BranchToitem(data->branch);
	if(branch == -1)
		return;
	if(!flag || m_strSaveData.IsEmpty())
		return;
	if(CompareION(data, &m_cacheION[branch][data->id-1]))//判断星历是否更新
		return;
	memcpy(&m_cacheION[branch][data->id-1], data, sizeof(BD2_ION));
	strText.Empty();
	obsTime.week = data->week;
	obsTime.tow = data->tow;
	obsTime.leap = m_nLeap;
	BDTime2UTC(&obsTime);
	if (data->system == SYSTEM_BD1)
	{
		strName.Format("s%02d_bdion_%04d%02d%02d.ion", data->id, obsTime.year, obsTime.month, obsTime.day);
		m_strPath = m_strSaveData + "\\EPH\\" + strName;
		len = m_strPath.GetLength();
		if (_access(m_strPath.GetBuffer(len), 0) != 0)
		{
			len = strBDION.GetLength();
			RecordFile(strBDION.GetBuffer(len), len, m_strPath);
		}
		strTemp.Format("% 5d% 8.0f% 4d% 7s% 14.6e% 14.6e", data->week,data->tow,data->id,strFREQ[branch],data->A1,data->B);
		strText += strTemp;
		strTemp.Format("% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e", data->alpha0,data->alpha1,data->alpha2,data->alpha3,data->beta0,data->beta1);
		strText += strTemp;
		strTemp.Format("% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e", data->beta2,data->beta3,data->gamma0,data->gamma1,data->gamma2,data->gamma3);
		strText += strTemp;
		strText += "\n";
	}
	else
	{
		strName.Format("s%02d_bsion_%04d%02d%02d.ion", data->id, obsTime.year, obsTime.month, obsTime.day);
		m_strPath = m_strSaveData + "\\EPH\\" + strName;
		len = m_strPath.GetLength();
		if (_access(m_strPath.GetBuffer(len), 0) != 0)
		{
			len = strBSION.GetLength();
			RecordFile(strBSION.GetBuffer(len), len, m_strPath);
		}
		strTemp.Format("% 5d% 8.0f% 4d% 7s", data->week,data->tow,data->id,strFREQ[branch]);
		strText += strTemp;
		strTemp.Format("% 21.12e% 21.12e% 21.12e% 21.12e", data->af1,data->af2,data->af3,data->af4);
		strText += strTemp;
		strTemp.Format("% 21.12e% 21.12e% 21.12e% 21.12e% 21.12e", data->af5,data->af6,data->af7,data->af8,data->af9);
		strText += strTemp;
		strText += "\n";
	}
	len = strText.GetLength();
	if (len > 1024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);

}
void CPrintData::SaveALMFile(BD2_ALM* data)
{
	char buf[MAX_PATH];
	UTCTime obsTime;
	memset(&obsTime, 0, sizeof(UTCTime));
	unsigned int i=0,len=0,count=0,branch=0;
	CString strText,strTemp,strName;
	m_strPath.Empty();
	strText.Empty();
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "cod", 0, m_strConfigPath);
	branch = BranchToitem(data->branch);
	if(branch == -1)
		return;
	if(!flag || m_strSaveData.IsEmpty())
		return;
	if (data->system == SYSTEM_BD1)
	{
		obsTime.week = m_globalWeek;
		obsTime.tow = m_globalTow;
		obsTime.leap = m_nLeap;
		BDTime2UTC(&obsTime);
		strName.Format("s%02d_bdalm_%04d%02d%02d.alm", data->id, obsTime.year, obsTime.month, obsTime.day);
		m_strPath = m_strSaveData + "\\ALM\\" + strName;
		len = m_strPath.GetLength();
		if (_access(m_strPath.GetBuffer(len), 0) != 0)
		{
			len = strBDALM.GetLength();
			RecordFile(strBDALM.GetBuffer(len), len, m_strPath);
		}
		strTemp.Format("% 5d% 8d% 7s% 5d% 11.5f", data->week,data->id,strFREQ[branch],data->health,data->sqrta);
		strText += strTemp;
		strTemp.Format("% 14.6e% 14.6e% 14.6e% 14.6e% 14.6e% 14.6e% 11d% 15.6e% 15.6e\n",data->omega0,data->e,data->w, data->m0,data->sigma,data->omegadot,data->toa,data->af0,data->af1);
		strText += strTemp;
		len = strText.GetLength();
		if (len > 1024)
			return;
		RecordFile(strText.GetBuffer(len), len, m_strPath);
	}
	else
	{
		obsTime.week = m_globalWeek;
		obsTime.tow = m_globalTow;
		obsTime.leap = m_nLeap;
		BDTime2UTC(&obsTime);
		strName.Format("s%02d_bsalm_%04d%02d%02d.alm", data->id, obsTime.year, obsTime.month, obsTime.day);
		m_strPath = m_strSaveData + "\\ALM\\" + strName;
		len = m_strPath.GetLength();
		if (_access(m_strPath.GetBuffer(len), 0) != 0)
		{
			len = strBSALM.GetLength();
			RecordFile(strBSALM.GetBuffer(len), len, m_strPath);
		}
		strTemp.Format("% 5d% 8d% 7s% 5d% 11.5f", data->week,data->id,strFREQ[branch],data->health,data->sqrta);
		strText += strTemp;
		strTemp.Format("% 15.6e% 15.6e% 15.6e% 15.6e% 15.6e% 15.6e% 11d% 15.6e% 15.6e\n",data->omega0,data->e,data->w, data->m0,data->sigma,data->omegadot,data->toa,data->af0,data->af1);
		strText += strTemp;
		len = strText.GetLength();
		if (len > 1024)
			return;
		RecordFile(strText.GetBuffer(len), len, m_strPath);
	}
}
void CPrintData::SaveJALFile(BD2_JAL* data)
{
	char buf[MAX_PATH];
	UTCTime obsTime;
	memset(&obsTime, 0, sizeof(UTCTime));
	unsigned int i=0,len=0,count=0,branch=0;
	CString strText,strTemp,strName;
	m_strPath.Empty();
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "cod", 0, m_strConfigPath);
	branch = BranchToitem(data->branch);
	if(branch == -1)
		return;
	if(!flag || m_strSaveData.IsEmpty())
		return;
	/*if (data->system == SYSTEM_BD1)
	{
		strName.Format("s%02d_bdjal.jal", data->id);
		m_strPath = m_strSaveData + "\\ALM\\" + strName;
		len = m_strPath.GetLength();
		if (_access(m_strPath.GetBuffer(len), 0) != 0)
		{
			len = strBDJAL.GetLength();
			RecordFile(strBDJAL.GetBuffer(len), len, m_strPath);
		}
	}
	else*/
	{
		obsTime.week = m_globalWeek;
		obsTime.tow = m_globalTow;
		obsTime.leap = m_nLeap;
		BDTime2UTC(&obsTime);
		strName.Format("s%02d_bsjal_%04d%02d%02d.jal", data->id, obsTime.year, obsTime.month, obsTime.day);
		m_strPath = m_strSaveData + "\\ALM\\" + strName;
		len = m_strPath.GetLength();
		if (_access(m_strPath.GetBuffer(len), 0) != 0)
		{
			len = strBSJAL.GetLength();
			RecordFile(strBSJAL.GetBuffer(len), len, m_strPath);
		}
		strTemp.Format("% 5d% 8.0f% 7s% 4d% 5.0f% 21.12e% 21.12e% 21.12e% 11d\n", m_globalWeek,m_globalTow,strFREQ[branch], data->id, data->health,data->sigma,data->omega, data->theta, 0);
		strText += strTemp;
		len = strText.GetLength();
		if (len > 1024)
			return;
		RecordFile(strText.GetBuffer(len), len, m_strPath);
	}

}
void CPrintData::SavePOSFile(BD2_POS* data)
{
	char buf[MAX_PATH];
	double x=0,y=0,z=0;
	UTCTime obsTime;
	memset(&obsTime, 0, sizeof(UTCTime));
	unsigned int i=0,len=0,count=0,mode=0;
	CString strText,strTemp,strName;
	m_strPath.Empty();
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "pos", 0, m_strConfigPath);
	mode = ModeToItem(data->mode);
	if(mode > 20 || mode < 0)
		return;
	if(!flag || m_strSaveData.IsEmpty())
		return;
	obsTime.week = data->week;
	obsTime.tow = data->tow;
	obsTime.leap = m_nLeap;
	BDTime2UTC(&obsTime);
	strName.Format("%s_%04d%02d%02d.pos", strMODE[mode], obsTime.year, obsTime.month, obsTime.day);
	m_strPath = m_strSaveData + "\\POS\\" + strName;
	len = m_strPath.GetLength();
	if (_access(m_strPath.GetBuffer(len), 0) != 0)
	{
		len = strBDPOS.GetLength();
		RecordFile(strBDPOS.GetBuffer(len), len, m_strPath);
	}
	Trans_BLH_to_XYZ(data->blh.lat*PI/180.0, data->blh.lon*PI/180.0, data->blh.alt, &x, &y, &z);				//													//
	strTemp.Format("% 5d% 7.0f% 14.4f% 13.4f% 13.4f% 15.8f% 15.8f% 15.3f", data->week,data->tow,x,y,z,data->blh.lat,data->blh.lon,data->blh.alt);
	strText += strTemp;
	strTemp.Format("% 15.3f% 13.3f% 13.3f% 13.3f% 11.3f% 11.3f% 11.3f% 11.3f% 11.3f",data->clock, data->speed.x,data->speed.y,data->speed.z,data->dop.hdop,data->dop.vdop,data->dop.pdop,data->dop.tdop,data->dop.gdop);
	strText += strTemp;
	strTemp.Format("% 11.3f% 11.3f% 11.3f% 11.3f% 15.3f% 16.3f% 16.3f", 0.0,0.0,0.0,0.0,0.0,0.0,0.0);
	strText += strTemp;
	strTemp.Format("% 6d ", data->numuse);
	strText += strTemp;
	for (int i=0; i<data->numuse; i++)
	{
		strTemp.Format("%d,", data->Ids[i]);
		strText += strTemp;
	}
	strText += "\n";
	len = strText.GetLength();
	if(len > 1024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}

void CPrintData::SaveXPVFile(BD2_POS* data)
{
	char buf[MAX_PATH];
	UTCTime obsTime;
	memset(&obsTime, 0, sizeof(UTCTime));
	unsigned int i=0,len=0,count=0,mode=0;
	CString strText,strTemp,strName;
	m_strPath.Empty();
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	int flag = GetPrivateProfileInt("FILE", "xpv", 0, m_strConfigPath);
	mode = ModeToItem(data->mode);
	if(mode == -1)
		return;
	if(!flag || m_strSaveData.IsEmpty())
		return;
	obsTime.week = data->week;
	obsTime.tow = data->tow;
	obsTime.leap = m_nLeap;
	BDTime2UTC(&obsTime);
	strName.Format("%s_%04d%02d%02d.pos", strMODE[mode], obsTime.year, obsTime.month, obsTime.day);
	m_strPath = m_strSaveData + "\\XPV\\" + strName;
	len = m_strPath.GetLength();
	if (_access(m_strPath.GetBuffer(len), 0) != 0)
	{
		len = strBDXPV.GetLength();
		RecordFile(strBDXPV.GetBuffer(len), len, m_strPath);
	}
	Trans_BLH_to_XYZ(data->blh.lat*PI/180.0, data->blh.lon*PI/180.0, data->blh.alt, &data->xyz.x, &data->xyz.y, &data->xyz.z);				//													//
	strTemp.Format("% 5d% 7.0f% 14.4f% 13.4f% 13.4f% 15.8f% 15.8f% 15.3f", data->week,data->tow,data->xyz.x,data->xyz.y,data->xyz.z,data->blh.lat,data->blh.lon,data->blh.alt);
	strText += strTemp;
	strTemp.Format("% 15.3f% 13.3f% 13.3f% 13.3f% 11.3f% 11.3f% 11.3f% 11.3f% 11.3f",data->clock, data->speed.x,data->speed.y,data->speed.z,data->dop.hdop,data->dop.vdop,data->dop.pdop,data->dop.tdop,data->dop.gdop);
	strText += strTemp;
	strTemp.Format("% 11.3f% 11.3f% 11.3f% 11.3f% 15.3f% 16.3f% 16.3f", 0.0,0.0,0.0,0.0,0.0,0.0,0.0);
	strText += strTemp;
	strTemp.Format("% 6d ", data->numuse);
	strText += strTemp;
	for (int i=0; i<data->numuse; i++)
	{
		strTemp.Format("%d,", data->Ids[i]);
		strText += strTemp;
	}
	strText += "\n";
	len = strText.GetLength();
	if(len > 1024)
		return;
	RecordFile(strText.GetBuffer(len), len, m_strPath);
}
void CPrintData::SaveRANFile(BD2_RAN* data)
{
	double nCurTime = 0;
	UTCTime obsTime;
	CString strText,strTemp,strName;
	unsigned int i=0,j=0,len=0,count=0,num=0,branch=0,id=0,item=0;
	m_strPath.Empty();
	memset(&obsTime, 0, sizeof(UTCTime));
	int flag = GetPrivateProfileInt("FILE", "ran", 0, m_strConfigPath);
	branch = BranchToitem(data->branch);
	if(!flag || branch == -1)
		return;

	nCurTime = data->week*SECONDS_IN_WEEK + data->tow;
	if (nCurTime - m_nRanTime > 0  && m_nRanTime != 0)
	{
		num = m_packRAN[0].numuse;
		memset(&m_cacheRAN, 0, sizeof(m_cacheRAN));
		for (i=0; i<MAXFREQ+2; i++)
		{
			count = m_packRAN[i].numuse;
			num = max(num, m_packRAN[i].numuse);
			for (j=0; j<count; j++)
			{
				item = i;
				id = m_packRAN[i].svId[j];
				m_cacheRAN[i].svId[id - 1] = 1;
				m_cacheRAN[i].snr[id - 1] = m_packRAN[i].snr[j];
				memcpy(&m_cacheRAN[i].ran[id - 1], &m_packRAN[i].ran[j], sizeof(BD2_USER_XYZ));
			}
		}
		for (i=0; i<MAXSVNUM; i++)
		{
			if (m_cacheRAN[0].svId[i] || m_cacheRAN[1].svId[i] || m_cacheRAN[2].svId[i] || m_cacheRAN[3].svId[i] ||  
				m_cacheRAN[4].svId[i] || m_cacheRAN[5].svId[i] || m_cacheRAN[6].svId[i] || m_cacheRAN[7].svId[i] || 
				m_cacheRAN[8].svId[i] || m_cacheRAN[9].svId[i] || m_cacheRAN[10].svId[i] || m_cacheRAN[11].svId[i] || 
				m_cacheRAN[0].svId[i] || m_cacheRAN[0].svId[i] || m_cacheRAN[0].svId[i] || m_cacheRAN[0].svId[i] || 
				m_cacheRAN[12].svId[i] || m_cacheRAN[13].svId[i] || m_cacheRAN[14].svId[i] )
			{
				obsTime.week = m_globalWeek;
				obsTime.tow = m_globalTow;
				obsTime.leap = m_nLeap;
				BDTime2UTC(&obsTime);
				strName.Format("s%02d_%04d%02d%02d.ran", i+1, obsTime.year, obsTime.month, obsTime.day);
				m_strPath = m_strSaveData + "\\RAN\\" + strName;
				len = m_strPath.GetLength();
				if (_access(m_strPath.GetBuffer(len), 0) != 0)
				{
					len = strBDRAN.GetLength();
					RecordFile(strBDRAN.GetBuffer(len), len, m_strPath);
				}
				strTemp.Empty();
				strText.Format("% 5d% 7.0f% 6d% 6d% 19.3f% 19.3f% 19.3f% 19.3f% 19.3f% 19.3f% 19.3f", m_globalWeek,m_globalTow,num, i+1,m_cacheRAN[0].ran[i].x,m_cacheRAN[1].ran[i].x,m_cacheRAN[2].ran[i].x,m_cacheRAN[3].ran[i].x,m_cacheRAN[4].ran[i].x,m_cacheRAN[5].ran[i].x,m_cacheRAN[6].ran[i].x);
				strTemp += strText;
				strText.Format("% 19.3f% 19.3f% 19.3f% 19.3f% 19.3f% 19.3f% 19.3f% 19.3f", m_cacheRAN[7].ran[i].x,m_cacheRAN[8].ran[i].x,m_cacheRAN[9].ran[i].x,m_cacheRAN[10].ran[i].x,m_cacheRAN[12].ran[i].x,m_cacheRAN[13].ran[i].x,m_cacheRAN[14].ran[i].x);
				strTemp += strText;
				strText.Format("% 19.3f% 19.3f% 19.3f% 19.3f% 19.3f% 19.3f% 19.3f", m_cacheRAN[0].ran[i].y,m_cacheRAN[1].ran[i].y,m_cacheRAN[2].ran[i].y,m_cacheRAN[3].ran[i].y,m_cacheRAN[4].ran[i].y,m_cacheRAN[5].ran[i].y,m_cacheRAN[6].ran[i].y);
				strTemp += strText;
				strText.Format("% 19.3f% 19.3f% 19.3f% 19.3f% 19.3f% 19.3f% 19.3f% 19.3f", m_cacheRAN[7].ran[i].y,m_cacheRAN[8].ran[i].y,m_cacheRAN[9].ran[i].y,m_cacheRAN[10].ran[i].y,m_cacheRAN[12].ran[i].y,m_cacheRAN[11].ran[i].y,m_cacheRAN[13].ran[i].y,m_cacheRAN[14].ran[i].y);
				strTemp += strText;
				strText.Format("% 8.2f% 8.2f% 8.2f% 8.2f% 8.2f% 8.2f% 8.2f", m_cacheRAN[0].snr[i],m_cacheRAN[1].snr[i],m_cacheRAN[2].snr[i],m_cacheRAN[3].snr[i],m_cacheRAN[4].snr[i],m_cacheRAN[5].snr[i],m_cacheRAN[6].snr[i]);
				strTemp += strText;
				strText.Format("% 8.2f% 8.2f% 8.2f% 8.2f% 8.2f% 9.2f% 8.2f% 8.2f", m_cacheRAN[7].snr[i],m_cacheRAN[8].snr[i],m_cacheRAN[9].snr[i],m_cacheRAN[10].snr[i],m_cacheRAN[12].snr[i],m_cacheRAN[11].snr[i],m_cacheRAN[13].snr[i],m_cacheRAN[14].snr[i]);
				strTemp += strText;
				strText.Format("% 12.3f% 12.3f% 12.3f% 12.3f% 12.3f% 12.3f% 12.3f", m_cacheRAN[0].ran[i].z,m_cacheRAN[1].ran[i].z,m_cacheRAN[2].ran[i].z,m_cacheRAN[3].ran[i].z,m_cacheRAN[4].ran[i].z,m_cacheRAN[5].ran[i].z,m_cacheRAN[6].ran[i].z);
				strTemp += strText;
				strText.Format("% 12.3f% 12.3f% 12.3f% 12.3f% 12.3f% 12.3f% 12.3f% 12.3f", m_cacheRAN[7].ran[i].z,m_cacheRAN[8].ran[i].z,m_cacheRAN[9].ran[i].z,m_cacheRAN[10].ran[i].z,m_cacheRAN[12].ran[i].z,m_cacheRAN[11].ran[i].z,m_cacheRAN[13].ran[i].z,m_cacheRAN[14].ran[i].z);
				strTemp += strText;
				strTemp += "\n";
				len = strTemp.GetLength();
				if (len > 1024)
					continue;
				RecordFile(strTemp.GetBuffer(len), len, m_strPath);
			}
		}
		m_globalWeek = data->week;
		m_globalTow = data->tow;
		m_nRanTime = nCurTime;
		memset(&m_packRAN, 0, sizeof(m_packRAN));
		memset(&m_cacheRAN, 0, sizeof(m_cacheRAN));
	}
	if (!m_bBDRANFlag)
	{
		m_bBDRANFlag = true;
		m_globalWeek = data->week;
		m_globalTow = data->tow;
		m_nRanTime = nCurTime;
	}
	memcpy(&m_packRAN[branch], data, sizeof(BD2_RAN));//缓存数据
}
void CPrintData::SaveGSVFile(BD2_GSV* data)
{
}
void CPrintData::SaveTESTFile(BD2_PAORDER* data)
{
}
void CPrintData::SaveCHDFile(BD2_CHD* data)
{
}

void CPrintData::SaveSTAFile(BD2_STA* data)
{

}
void CPrintData::SaveTIMFile(BD2_TIME* data)
{
	//m_nLeap = data->Leap;
}
void CPrintData::SaveGBSFile(BD2_GBS* data)
{

}
void CPrintData::SaveREFFile(SETREF* data)
{

}
void CPrintData::SaveCOMFile(SETCOM* data)
{

}
void CPrintData::SaveMODFile(SETMOD* data)
{

}
