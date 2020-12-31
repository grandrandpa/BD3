// WinCalPos.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "WinCalPos.h"
																																													//0.2344418048875855  B3C_BPSK
double Lambda[13]={0.19203948631,0.19203948631,0.19029367279836488,0.19029367279836488,0.25482804879085384,0.2483493695843067,0.25154700095234499,0.2363324646044209,0.2363324646044209,0.2363324646044209,0.2363324646044209,0.12030059774609274,0.2363324646044209};
					//	B1I			B1Q				B1C						B1A				   B2a				  B2b				B2					B3I					B3Q					B3CBoc				B3A						Bs				B3AE
int CalBranchToitem(int branch)
{
	int ch = 0;
	switch (branch)
	{
	case CH_B1I:
		ch = 0;
		break;
	case CH_B1Q:
		ch = 1;
		break;
	case CH_B1C:
	case CH_B1C_data:
	case CH_B1C_pilot:
		ch = 2;
		break;
	case CH_B1A:
	case CH_B1A_data:
	case CH_B1A_pilot:
		ch = 3;
		break;
	case CH_B2a:
	case CH_B2a_data:
	case CH_B2a_pilot:
		ch = 4;
		break;
	case CH_B2b:
	case CH_B2b_data:
	case CH_B2b_pilot:
		ch = 5;
		break;
	case CH_B2:
		ch = 6;
		break;
	case CH_B3I:
		ch = 7;
		break;
	case CH_B3Q:
		ch = 8;
		break;
	case CH_B3C:
	case CH_B3C_data:
	case CH_B3C_pilot:
		ch = 9;
		break;
	case CH_B3A:
	case CH_B3A_data:
	case CH_B3A_pilot:
		ch = 10;
		break;
	case CH_Bs:
	case  CH_Bs_data:
	case  CH_Bs_pilot:
		ch = 11;
		break;
	case CH_B3AE:
	case CH_B3AE_data:
	case CH_B3AE_pilot:
		ch = 12;
		break;
	default:
		ch = -1;
		break;
	}
	return ch;
}
int CWinCalPosApp::GetConfig(CString strFile, BD2_NORMAL_POS_MODE* norMOD)
{
	CString strText="";
	char buf[MAX_PATH], output[MAX_PATH];
	UINT8 i=0,j=0,id=0,type=0,data=0,len=0,count=0;

	m_bHgtEnable = GetPrivateProfileInt("POSMOD", "ALTError", 0, strFile);
	m_bIonEnable = GetPrivateProfileInt("POSMOD", "IONCheck", 0, strFile);
	m_bTroEnable = GetPrivateProfileInt("POSMOD", "TROCheck", 0, strFile);
	m_nTestFlag = GetPrivateProfileInt("POSMOD", "Tester", 0, "config.ini");
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	ZeroMemory(&m_selSat, sizeof(m_selSat));
	GetPrivateProfileString("POSMOD", "SatSel", "", buf, MAX_PATH, strFile);
	len = strlen(buf);
	count = Pack_SplitChars(buf, len, (u1*)output);
	for (i=0; i<count; i++)
	{
		id = output[i];
		m_selSat.selSat[id-1] = 1;
	}
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB1I", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 1;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB1Q", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 2;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB1C", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 3;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB1A", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 4;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB2a", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 5;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB2b", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 6;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB2", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 7;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB3I", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 8;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB3Q", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 9;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB3C", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 10;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB3A", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 11;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB3AE", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 13;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalBs", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 12;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB1CB3C", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 21;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB1QB3Q", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 22;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB1AB3A", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 23;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB1AB3AE", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 27;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalBsB3A", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 24;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalBsB3AE", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 28;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB1CB2a", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 26;
	////////////////////////////////////////////////////////////////
	data = GetPrivateProfileInt("POSMOD", "NormalB1CB2B3C", 0, strFile);
	if(data == 1)
		norMOD->posMod[norMOD->number++] = 25;
	////////////////////////////////////////////////////////////////

	return norMOD->number;
}
void CWinCalPosApp::LoadConfig(CString strFile)
{
	char buf[MAX_PATH];
	double lat=0,lon=0,alt=0,x=0,y=0,z=0;
	m_strProjFile = strFile;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	GetPrivateProfileString("Local", "lat", "", buf, MAX_PATH, strFile);
	lat = strtod(buf, NULL);
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	GetPrivateProfileString("Local", "lon", "", buf, MAX_PATH, strFile);
	lon = strtod(buf, NULL);
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	GetPrivateProfileString("Local", "alt", "", buf, MAX_PATH, strFile);
	alt = strtod(buf, NULL);
/*
	Trans_BLH_to_XYZ(lat, lon, alt, &x, &y, &z);//坐标转换
	//初始化用户接收机坐标
	m_epochData.initPVT.blh.lat = lat;
	m_epochData.initPVT.blh.lon = lon;
	m_epochData.initPVT.blh.alt = alt;
	m_epochData.initPVT.xyz.x = x;
	m_epochData.initPVT.xyz.y = y;
	m_epochData.initPVT.xyz.z = z;
	*/
}
CWinCalPosApp::CWinCalPosApp()
{
	// TODO: add construction code here,
	Reset();
	Clear();
}

CWinCalPosApp::~CWinCalPosApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	Reset();
	Clear();
}
void CWinCalPosApp::Clear()
{
	m_bHgtEnable = 0;
	m_bIonEnable = 0;
	m_bTroEnable = 0;
	m_bUpdateData = 0;
	m_dTotalSeconds = 0;
	//m_nTestPosMod = 0;
	m_nTestFlag = 0;
	ZeroMemory(&m_calEPH, sizeof(m_calEPH));
	ZeroMemory(&m_calION, sizeof(m_calION));
	ZeroMemory(&m_selSat, sizeof(m_selSat));
	ZeroMemory(&m_normalPOS, sizeof(m_normalPOS));
	ZeroMemory(&m_epochData, sizeof(BD2_EPOCH));
	ZeroMemory(&m_epochLeast, sizeof(BD2_LS_EPOCH));
}
void CWinCalPosApp::Reset()
{
	ZeroMemory(&m_calRAN, sizeof(m_calRAN));
}
// The one and only CWinCalPosApp object
LRESULT CWinCalPosApp::OnAnswerCalPositionMOD(WPARAM wParam, LPARAM lParam)
{
	UINT8 i=0, mode=0;
	SETMOD* output = (SETMOD*)wParam;
	for (i=0; i<14; i++)
	{
		if (((output->BD2Pos >> i) & 0x01) || ((output->BD1Pos >> i) & 0x01))
		{
			if (i<7)
			{
				mode = i+1;
			}
			else
			{
				mode = i;
			}
		}
	}
	if (((output->BD2Pos >> 2) & 0x01) && ((output->BD2Pos >> 10) & 0x01))//B1CB3C
	{
		mode = 21;
	}
	else if (((output->BD1Pos >> 1) & 0x01) && ((output->BD1Pos >> 9) & 0x01))//B1QB3Q
	{
		mode = 22;
	}
	else if (((output->BD2Pos >> 3) & 0x01) && ((output->BD2Pos >> 11) & 0x01))//B1AB3A
	{
		mode = 23;
	}
	else if (((output->BD2Pos >> 3) & 0x01) && ((output->BD2Pos >> 13) & 0x01))//B1AB3AE
	{
		mode = 27;
	}
	else if (((output->BD2Pos >> 12) & 0x01) && ((output->BD2Pos >> 11) & 0x01))//BsB3A
	{
		mode = 24;
	}
	else if (((output->BD2Pos >> 12) & 0x01) && ((output->BD2Pos >> 13) & 0x01))//BsB3AE
	{
		mode = 28;
	}
	else if (((output->BD2Pos >> 2) & 0x01) && ((output->BD2Pos >> 4) & 0x01))//B1CB2a
	{
		mode = 26;
	}
	else if (((output->BD2Pos >> 2) & 0x01) && ((output->BD2Pos >> 6) & 0x01) && ((output->BD2Pos >> 10) & 0x01))//B1CB2B3C
	{
		mode = 25;
	}
	m_nTestPosMod = mode;
	
	return 0;
}
//数据存放顺序：B1I/B1Q/B1C/B1A/B2a/B2b/B2/B3I/B3Q/B3C/B3A/Bs/B3AE
LRESULT CWinCalPosApp::OnAnswerCalPositionEPH(WPARAM wParam, LPARAM lParam)//卫星星历信息
{
	int Freq=0,id = 0;
	BD2_EPH* data = (BD2_EPH*)wParam;
	id = data->id;
	Freq = CalBranchToitem(data->branch);
	if(Freq == -1)
		return 0;
	memcpy(&m_calEPH[Freq][id-1], data, sizeof(BD2_EPH));

	return 0;
}
LRESULT CWinCalPosApp::OnAnswerCalPositionION(WPARAM wParam, LPARAM lParam)//卫星电离层参数
{
	int Freq=0,id = 0;
	BD2_ION* data = (BD2_ION*)wParam;
	id = data->id;
	Freq = CalBranchToitem(data->branch);
	if(Freq == -1)
		return 0;
	memcpy(&m_calION[Freq][id-1], data, sizeof(BD2_ION));

	return 0;
}
LRESULT CWinCalPosApp::OnAnswerCalPositionALM(WPARAM wParam, LPARAM lParam)//卫星历书信息
{
	return 0;
}
LRESULT CWinCalPosApp::OnAnswerCalPositionJAL(WPARAM wParam, LPARAM lParam)//卫星简约历书信息
{
	return 0;
}
LRESULT CWinCalPosApp::OnAnswerCalPositionRAN(WPARAM wParam, LPARAM lParam)//伪距、载波、多普勒信息
{
	int Freq=0,Run=0;
	double totalSec=0;
	BD2_RAN* data = (BD2_RAN*)wParam;
	Freq = CalBranchToitem(data->branch);
	if(Freq == -1)
		return 0;

    m_nPosType=0;
#ifdef _CALPOS_DEBUG

	//判断是否对接测试平台
	m_nTestFlag = GetPrivateProfileInt("POSMOD", "Tester", 0, "config.ini");
	if (m_nTestFlag)
	{
		m_normalPOS.number = 1;
		m_normalPOS.posMod[0] = m_nTestPosMod;
	}
#endif
	//当时刻发生变化时，开始计算上一秒用户接收机的位置信息
	totalSec = data->week*SECONDS_IN_WEEK + data->tow;
	if(fabs(totalSec-m_dTotalSeconds)>2)
	{
		memset(&m_epochData.Count,0,sizeof(m_epochData.Count));
		memset(&m_epochData.LockCn,0,sizeof(m_epochData.LockCn));
	}
	if(fabs(totalSec-m_dTotalSeconds)> 0)//&& m_dTotalSeconds > SECONDS_IN_WEEK
	{
		m_dTotalSeconds = totalSec;
#ifndef _CALPOS_DEBUG
		memset(&m_normalPOS, 0, sizeof(BD2_NORMAL_POS_MODE));
		m_nPosType = GetConfig(m_strProjFile, &m_normalPOS);//获取参数配置信息
		if (m_nTestFlag)
		{
			m_normalPOS.number = 1;
			m_normalPOS.posMod[0] = m_nTestPosMod;
		}
#endif
		if (fabs(totalSec-m_dTotalSeconds)> 10)//观测量时间间隔过大则清零
			Clear();
		else
			Run = CalReceiverNormalPos(&m_epochData);
	}
	//当前时间
	//memset(&m_calRAN[Freq],0,sizeof(BD2_RAN));
	m_epochData.utcTime.week = data->week;
	m_epochData.utcTime.tow = data->tow;
	m_epochData.utcTime.leap = (int)lParam;
	m_epochData.obsTime.Weeks = data->week;
	m_epochData.obsTime.Tow = data->tow;
	m_epochData.obsTime.Leap = (int)lParam;
	memcpy(&m_calRAN[Freq], data, sizeof(BD2_RAN));

	return Run;
}
//开始计算用户接收机位置
int CWinCalPosApp::CalReceiverNormalPos(BD2_EPOCH* epoch)
{
	CString strText;
	BD2_RAN ImportData[MAX_FREQ];
	static BD2_EPH ImportEPH[MAXCHANNELS];
	BD2_ION ImportION[MAXCHANNELS];
	UINT8 i=0,j=0,k=0,h=0,SatID=0,Branch=0;
	UINT8 posmod=0,SatNum=0,style=0;
	double dIono=0,dTro=0,SNR=0;
	double Them=1500,delta=5.0,temp0=0.0,temp1=0.0;
	BD2_LS_EPOCH epochLeast;
	char SInd[MAX_FREQ][MAXCHANNELS];
	static double Diff13C=0,Diff13A=0,Diff13Q=0,Diffs3A=0,Diff32C=0,Diff31C=0,DiffCA=0,Diff13AE=0,Diffs3E=0;
	static bool F13C=1,F13A=1,F13Q=1,Fs3A=1,F123C=1,FCA=1,F13AE=1,Fs3E=1;
	unsigned  short Mode[21]={1,2,3,4,5,6,7,8,9,10,11,12,13,21,22,23,24,25,26,27,28};
	static double SaveTime=0;

	epoch->PosMode.cPosMode=-1;
	memset(&SInd,-1,sizeof(char)*MAX_FREQ*MAXCHANNELS);
	memset(&m_calPOS, 0, sizeof(BD2_POS));
	memcpy(&ImportData, &m_calRAN, sizeof(BD2_RAN)*MAX_FREQ);
	Reset();
	for (j=0; j<21; j++)
	{
		memset(&epochLeast,0,sizeof(BD2_LS_EPOCH));
		memset(&epoch->SatInfo,0,sizeof(BD2_SAT_INFO)*MAX_SatNum);
		
		if(epoch->calcPVT.valid==0)
		{
			epoch->initPVT.blh.lat = 40.111;
			epoch->initPVT.blh.lon = 116.111;
			epoch->initPVT.blh.alt = 50.0;
			epoch->initPVT.xyz.x = -2144821.666;
			epoch->initPVT.xyz.y = 4397536.666;
			epoch->initPVT.xyz.z = 4077985.666;
			epoch->initPVT.valid=0;
			memset(&epoch->calcPVT,0,sizeof(BD2_PVT));
			memset(&epoch->LockCn[j],0,sizeof(epoch->LockCn[j]));
		}
		else
		{
			if((m_epochData.obsTime.Tow-SaveTime>20)||(m_epochData.obsTime.Tow<SaveTime))
			{
				epoch->initPVT.blh.lat = 40.111;
				epoch->initPVT.blh.lon = 116.111;
				epoch->initPVT.blh.alt = 50.0;
				epoch->initPVT.xyz.x = -2144821.666;
				epoch->initPVT.xyz.y = 4397536.666;
				epoch->initPVT.xyz.z = 4077985.666;
				epoch->Count[j]=0;
				memset(&epoch->calcPVT,0,sizeof(BD2_PVT));
				memset(&epoch->LockCn[j],0,sizeof(epoch->LockCn[j]));
				epoch->initPVT.valid=0;
			}
			else
				memcpy(&epoch->initPVT,&epoch->calcPVT,sizeof(BD2_PVT));
		}
		
		posmod = Mode[j];
		for(h=0;h<m_normalPOS.number;h++)
		{
			if(posmod== m_normalPOS.posMod[h])
			{
				epoch->PosMode.cPosMode=m_normalPOS.posMod[h];
				break;
			}
		}
		
		if(posmod <1)
			continue;
		if(posmod < 21)
			style = posmod - 1;
		else if(posmod<22)//MOD_B1CB3C
			style = 9;
		else if(posmod<23)//MOD_B1QB3Q
			style = 8;
		else if(posmod<25)//MOD_B1AB3A
			style = 10;
		else if(posmod<26)//MOD_B1CB2B3C
			style = 9;
		else if(posmod<27)//MOD_B1CB2a
			style = 2;
		else if(posmod<29)//MOD_BsB3AE
			style = 12;
		else if(posmod<28)//MOD_B1AB3AE
			style = 12;
		else
			continue;
		TransYMDHMS(&epoch->obsTime,false);
		SatNum=0;
		k=0;
		if(style>12)
			continue;
		if(posmod==10)
			SatNum=0;
		Branch = ImportData[style].branch;
		
		for (i=0; i<ImportData[style].numuse; i++)
		{
			if(ImportData[style].flag != true)
				continue;
			SatID = ImportData[style].svId[i];
			SNR = ImportData[style].snr[i];
			if((SatID<1)||(SatID>64))
				continue;
			if(SNR < SNRLIMIT)
				continue;
			if(!ObsCheck(ImportData[style].ran[i].x))
				continue;

			epoch->LockCn[j][SatID-1]++;
			if(epoch->LockCn[j][SatID-1]>2000)
				epoch->LockCn[j][SatID-1]=2000;

			//if(m_nPosType)
			{
				if(!m_selSat.selSat[SatID - 1])
					continue;
			}
			
			if(epoch->Count[j]>1000)
			{
				if(epoch->LockCn[j][SatID-1]<800)
					continue;
			}
			if(posmod < 20)
			{
				SInd[style][SatID-1]=i;
			}
			if(m_normalPOS.number>0)
			{
				if(epoch->PosMode.cPosMode!=posmod)
					continue;
			}
			else
				continue;

			if(m_calEPH[style][SatID-1].flag)
			{
				memcpy(&ImportEPH[SatID-1], &m_calEPH[style][SatID-1], sizeof(BD2_EPH));
				if(m_calION[style][SatID-1].flag)
					memcpy(&ImportION[SatID-1], &m_calION[style][SatID-1], sizeof(BD2_ION));
			}
			else
			{
				if(style<4)
				{
					if(m_calEPH[0][SatID-1].flag)
					{
						memcpy(&ImportEPH[SatID-1], &m_calEPH[0][SatID-1], sizeof(BD2_EPH));
						if(m_calION[0][SatID-1].flag)
							memcpy(&ImportION[SatID-1], &m_calION[0][SatID-1], sizeof(BD2_ION));
					}
					else if(m_calEPH[1][SatID-1].flag)
					{
						memcpy(&ImportEPH[SatID-1], &m_calEPH[1][SatID-1], sizeof(BD2_EPH));
						if(m_calION[1][SatID-1].flag)
							memcpy(&ImportION[SatID-1], &m_calION[1][SatID-1], sizeof(BD2_ION));
					}
					else if(m_calEPH[2][SatID-1].flag)
					{
						memcpy(&ImportEPH[SatID-1], &m_calEPH[2][SatID-1], sizeof(BD2_EPH));
						if(m_calION[2][SatID-1].flag)
							memcpy(&ImportION[SatID-1], &m_calION[2][SatID-1], sizeof(BD2_ION));
					}
					else if(m_calEPH[3][SatID-1].flag)
					{
						memcpy(&ImportEPH[SatID-1], &m_calEPH[3][SatID-1], sizeof(BD2_EPH));
						if(m_calION[3][SatID-1].flag)
							memcpy(&ImportION[SatID-1], &m_calION[3][SatID-1], sizeof(BD2_ION));
					}
				}
				else if(style<7)
				{
					if(m_calEPH[4][SatID-1].flag)
					{
						memcpy(&ImportEPH[SatID-1], &m_calEPH[4][SatID-1], sizeof(BD2_EPH));
						if(m_calION[4][SatID-1].flag)
							memcpy(&ImportION[SatID-1], &m_calION[4][SatID-1], sizeof(BD2_ION));
					}
					else if(m_calEPH[5][SatID-1].flag)
					{
						memcpy(&ImportEPH[SatID-1], &m_calEPH[5][SatID-1], sizeof(BD2_EPH));
						if(m_calION[5][SatID-1].flag)
							memcpy(&ImportION[SatID-1], &m_calION[5][SatID-1], sizeof(BD2_ION));
					}
					else if(m_calEPH[6][SatID-1].flag)
					{
						memcpy(&ImportEPH[SatID-1], &m_calEPH[6][SatID-1], sizeof(BD2_EPH));
						if(m_calION[6][SatID-1].flag)
							memcpy(&ImportION[SatID-1], &m_calION[6][SatID-1], sizeof(BD2_ION));
					}
				}
				else if(style<11)
				{
					if(m_calEPH[7][SatID-1].flag)
					{
						memcpy(&ImportEPH[SatID-1], &m_calEPH[7][SatID-1], sizeof(BD2_EPH));
						if(m_calION[7][SatID-1].flag)
							memcpy(&ImportION[SatID-1], &m_calION[7][SatID-1], sizeof(BD2_ION));
					}
					else if(m_calEPH[8][SatID-1].flag)
					{
						memcpy(&ImportEPH[SatID-1], &m_calEPH[8][SatID-1], sizeof(BD2_EPH));
						if(m_calION[8][SatID-1].flag)
							memcpy(&ImportION[SatID-1], &m_calION[8][SatID-1], sizeof(BD2_ION));
					}
					else if(m_calEPH[9][SatID-1].flag)
					{
						memcpy(&ImportEPH[SatID-1], &m_calEPH[9][SatID-1], sizeof(BD2_EPH));
						if(m_calION[9][SatID-1].flag)
							memcpy(&ImportION[SatID-1], &m_calION[9][SatID-1], sizeof(BD2_ION));
					}
					else if(m_calEPH[10][SatID-1].flag)
					{
						memcpy(&ImportEPH[SatID-1], &m_calEPH[10][SatID-1], sizeof(BD2_EPH));
						if(m_calION[10][SatID-1].flag)
							memcpy(&ImportION[SatID-1], &m_calION[10][SatID-1], sizeof(BD2_ION));
					}
				}
				else if(style<13)//MOD_BsB3AE
				{
					if(m_calEPH[11][SatID-1].flag)
					{
						memcpy(&ImportEPH[SatID-1], &m_calEPH[11][SatID-1], sizeof(BD2_EPH));
						if(m_calION[11][SatID-1].flag)
							memcpy(&ImportION[SatID-1], &m_calION[11][SatID-1], sizeof(BD2_ION));
					}
					else if(m_calEPH[12][SatID-1].flag)
					{
						memcpy(&ImportEPH[SatID-1], &m_calEPH[12][SatID-1], sizeof(BD2_EPH));
						if(m_calION[12][SatID-1].flag)
							memcpy(&ImportION[SatID-1], &m_calION[12][SatID-1], sizeof(BD2_ION));
					}
				}
				else
				{
					if(m_calEPH[style][SatID-1].flag)
						memcpy(&ImportEPH[SatID-1], &m_calEPH[style][SatID-1], sizeof(BD2_EPH));
					if(m_calION[style][SatID-1].flag)
						memcpy(&ImportION[SatID-1], &m_calION[style][SatID-1], sizeof(BD2_ION));
				}
			}

			if(posmod<21)
			{
				epoch->SatInfo[SatNum].Pseudorang = ImportData[style].ran[i].x;
				if(!ObsCheck(epoch->SatInfo[SatNum].Pseudorang))
					continue;
			}
			else if (posmod<22)//B1CB3C 
			{
				if(SInd[2][SatID-1]==-1)
					continue;
				if(!ObsCheck(ImportData[2].ran[SInd[2][SatID-1]].x))
					continue;
				temp0= ImportData[style].ran[i].x-ImportEPH[SatID-1].tgd1*299792458;
				if((F13C)&&(fabs( temp0-ImportData[2].ran[SInd[2][SatID-1]].x)<Them))
				{
					k++;
					if(i==ImportData[style].numuse)
						F13C=0;
					Diff13C=Diff13C*(k-1)+(temp0-ImportData[2].ran[SInd[2][SatID-1]].x-delta);
					Diff13C/=k;
					
				}
				epoch->SatInfo[SatNum].Pseudorang = -temp0*1.843645083933 +(ImportData[2].ran[SInd[2][SatID-1]].x+Diff13C)*2.843645083933;
				if(!ObsCheck(epoch->SatInfo[SatNum].Pseudorang))
					continue;
			}
			else if (posmod<23)//B1QB3Q
			{
				if(SInd[1][SatID-1]==-1)
					continue;
				if(!ObsCheck(ImportData[1].ran[SInd[1][SatID-1]].x))
					continue;
				temp0=ImportData[style].ran[i].x-ImportEPH[SatID-1].tgd1*299792458;
				if((F13Q)&&(fabs( temp0-ImportData[1].ran[SInd[1][SatID-1]].x)<Them))
				{
					k++;
					if(i==ImportData[style].numuse)
						F13Q=0;
					Diff13Q= Diff13Q*(k-1)+(temp0-ImportData[1].ran[SInd[1][SatID-1]].x-delta);
					Diff13Q /=k;
				}
				epoch->SatInfo[SatNum].Pseudorang = - temp0*1.943681770146 + (ImportData[1].ran[SInd[1][SatID-1]].x+Diff13Q)*2.943681770146;
				if(!ObsCheck(epoch->SatInfo[SatNum].Pseudorang))
					continue;
			}
			else if (posmod<24)//B1AB3A
			{
				if(SInd[3][SatID-1]==-1)
					continue;
				if(!ObsCheck(ImportData[3].ran[SInd[3][SatID-1]].x))
					continue;
				temp0=ImportData[style].ran[i].x-ImportEPH[SatID-1].tgd1*299792458;
				if((F13A)&&(fabs( temp0-ImportData[3].ran[SInd[3][SatID-1]].x)<Them))
				{
					k++;
					if(i==ImportData[style].numuse)
						F13A=0;
					Diff13A= Diff13A*(k-1)+(temp0-ImportData[3].ran[SInd[3][SatID-1]].x-delta);
					Diff13A/=k ;
				}
				epoch->SatInfo[SatNum].Pseudorang = - temp0*1.843645083933 + (ImportData[3].ran[SInd[3][SatID-1]].x+Diff13A)*2.843645083933;
				if(!ObsCheck(epoch->SatInfo[SatNum].Pseudorang))
					continue;
			}
			else if (posmod<25)//BsB3A
			{
				if(SInd[11][SatID-1]==-1)
					continue;
				if(!ObsCheck(ImportData[11].ran[SInd[11][SatID-1]].x))
					continue;
				temp0=ImportData[style].ran[i].x-ImportEPH[SatID-1].tgd1*299792458;
				if((Fs3A)&&(fabs( temp0-ImportData[11].ran[SInd[11][SatID-1]].x)<Them))
				{
					k++;
					if(i==ImportData[style].numuse)
						Fs3A=0;
					Diffs3A= Diffs3A*(k-1)+(temp0-ImportData[11].ran[SInd[11][SatID-1]].x-delta);
					Diffs3A/=k;
				}
				epoch->SatInfo[SatNum].Pseudorang = - temp0*0.349733060146 + (ImportData[11].ran[SInd[11][SatID-1]].x+Diffs3A)*1.349733060146;
				if(!ObsCheck(epoch->SatInfo[SatNum].Pseudorang))
					continue;
			}
			else if (posmod<26)//B1CB2B3C
			{
				if((SInd[2][SatID-1]==-1)||(SInd[6][SatID-1]==-1))
					continue;
				if((!ObsCheck(ImportData[2].ran[SInd[2][SatID-1]].x))||(!ObsCheck(ImportData[6].ran[SInd[6][SatID-1]].x)))
					continue;
				temp0=ImportData[style].ran[i].x-ImportEPH[SatID-1].tgd1*299792458;
				temp1=ImportData[style].ran[i].x-ImportEPH[SatID-1].tgd2*299792458;
				if((F123C)&&(fabs( temp0-ImportData[2].ran[SInd[2][SatID-1]].x)<Them)&&(fabs( temp1-ImportData[6].ran[SInd[6][SatID-1]].x)<Them))
				{
					k++;
					if(i==ImportData[style].numuse)
						F123C=0;
					Diff31C= Diff31C*(k-1)+(temp0-ImportData[2].ran[SInd[2][SatID-1]].x-delta);
					Diff32C= Diff32C*(k-1)+(temp1-ImportData[6].ran[SInd[6][SatID-1]].x-delta);
					Diff31C/=k;
					Diff32C/=k;
				}
				epoch->SatInfo[SatNum].Pseudorang = - temp0*1.843645083933 + (ImportData[2].ran[SInd[2][SatID-1]].x+Diff31C)*2.843645083933;//B1CB3C
				epoch->SatInfo[SatNum].Pseudorang += (-(Diff32C+ImportData[6].ran[SInd[6][SatID-1]].x)*7.524462924463+ temp1*8.524462924463);//B2B3C
				epoch->SatInfo[SatNum].Pseudorang /= 2;
				if(!ObsCheck(epoch->SatInfo[SatNum].Pseudorang))
					continue;
			}
			else if (posmod <27)//B1CB2a  
			{
				if(SInd[4][SatID-1]==-1)
					continue;
				if(!ObsCheck(ImportData[4].ran[SInd[4][SatID-1]].x))
					continue;
				temp1=ImportData[4].ran[SInd[4][SatID-1]].x-ImportEPH[SatID-1].tgd2*299792458;//f1*f1/(f1*f1-f2*f2)
				if((FCA)&&(fabs( ImportData[style].ran[i].x-temp1)<Them))
				{
					k++;
					if(i==ImportData[style].numuse)
						FCA=0;
					DiffCA= DiffCA*(k-1)+(ImportData[style].ran[i].x-temp1-delta);
					DiffCA/=k;
				}
				epoch->SatInfo[SatNum].Pseudorang = -(DiffCA+temp1)*1.26060432752 +  ImportData[style].ran[i].x*2.26060432752;
				if(!ObsCheck(epoch->SatInfo[SatNum].Pseudorang))
					continue;
			}
			else if (posmod<28)//B1AB3AE
			{
				if(SInd[3][SatID-1]==-1)
					continue;
				if(!ObsCheck(ImportData[3].ran[SInd[3][SatID-1]].x))
					continue;
				temp0=ImportData[style].ran[i].x-ImportEPH[SatID-1].tgd1*299792458;
				if((F13AE)&&(fabs( temp0-ImportData[3].ran[SInd[3][SatID-1]].x)<Them))
				{
					k++;
					if(i==ImportData[style].numuse)
						F13AE=0;
					Diff13AE= Diff13AE*(k-1)+(temp0-ImportData[3].ran[SInd[3][SatID-1]].x-delta);
					Diff13AE/=k ;
				}
				epoch->SatInfo[SatNum].Pseudorang = - temp0*1.843645083933 + (ImportData[3].ran[SInd[3][SatID-1]].x+Diff13AE)*2.843645083933;
				if(!ObsCheck(epoch->SatInfo[SatNum].Pseudorang))
					continue;
			}
			else if (posmod<29)//BsB3AE
			{
				if(SInd[11][SatID-1]==-1)
					continue;
				if(!ObsCheck(ImportData[11].ran[SInd[11][SatID-1]].x))
					continue;
				temp0=ImportData[style].ran[i].x-ImportEPH[SatID-1].tgd1*299792458;
				if((Fs3E)&&(fabs( temp0-ImportData[11].ran[SInd[11][SatID-1]].x)<Them))
				{
					k++;
					if(i==ImportData[style].numuse)
						Fs3E=0;
					Diffs3E= Diffs3E*(k-1)+(temp0-ImportData[11].ran[SInd[11][SatID-1]].x-delta);
					Diffs3E/=k;
				}
				epoch->SatInfo[SatNum].Pseudorang = - temp0*0.349733060146 + (ImportData[11].ran[SInd[11][SatID-1]].x+Diffs3A)*1.349733060146;
				if(!ObsCheck(epoch->SatInfo[SatNum].Pseudorang))
					continue;
			}
			else
				continue;
			if(CalculateSatPos(ImportEPH[SatID-1], epoch->obsTime, &epoch->SatInfo[SatNum].SatPos,epoch->SatInfo[SatNum].Pseudorang))//计算卫星位置和速度
			{
				if(epoch->Count[j]>=1)
				{
					CalculateSatAZEL(&epoch->SatInfo[SatNum].SatPos, epoch->calcPVT, &epoch->SatInfo[SatNum].SatAzel);
					if(epoch->SatInfo[SatNum].SatAzel.elv < ELVLIMIT)
						continue;
				}
			}
			else
				continue;
			
			epoch->SatInfo[SatNum].SatID = SatID;
			epoch->SatInfo[SatNum].SNR = SNR;
			epoch->SatInfo[SatNum].CarrierPhase = ImportData[style].ran[i].y;
			/*if((ImportData[style].status[i]>>6)&0x01)
			{
				if(style==4)
					epoch->SatInfo[SatNum].Doppler = ImportData[style].ran[i].z*0.25482804879085384;
				if(style==9)
					epoch->SatInfo[SatNum].Doppler = ImportData[style].ran[i].z*0.23633246460442;
			}
			else*/
				epoch->SatInfo[SatNum].Doppler = ImportData[style].ran[i].z*Lambda[style];

			if(epoch->Count[j]>=1)
			{
				if(m_bIonEnable)
				{
					dIono=0;
					if(epoch->initPVT.xyz.x!=0)
						dIono = CalculateIono(epoch->obsTime, &epoch->calcPVT, &epoch->SatInfo[SatNum], &ImportION[SatID-1],posmod);
					epoch->SatInfo[SatNum].Pseudorang -= dIono;
				}
				if(m_bTroEnable)
				{
					dTro = 0;
					dTro = CalculateTrop(epoch->SatInfo[SatNum].SatAzel.elv, epoch->calcPVT.blh.alt);
					epoch->SatInfo[SatNum].Pseudorang -= dTro;
				}
			}
			SatNum++;
		}
		
		epoch->SatNum = SatNum;
		if(SatNum < 4)
			continue;

		if(RaimLeastSquare(epoch, &epochLeast)!=1)
			continue;
		epoch->Count[j]++;
		if(epoch->Count[j]>2000)
			epoch->Count[j]=2000;

		if (epoch->initPVT.valid)
		{
			SaveTime = epoch->obsTime.Tow;
			m_calPOS.week = epoch->obsTime.Weeks;
			m_calPOS.tow = epoch->obsTime.Tow;
			m_calPOS.mode = posmod;
			m_calPOS.num = epoch->SatNum;
			m_calPOS.numuse = epoch->NumUse;
			m_calPOS.clock = epoch->bias*1.0e9/299792458;
			m_calPOS.blh.lat = epoch->calcPVT.blh.lat;
			m_calPOS.blh.lon = epoch->calcPVT.blh.lon;
			m_calPOS.blh.alt = epoch->calcPVT.blh.alt;
			m_calPOS.speed.x = epoch->calcPVT.ENUV.x;
			m_calPOS.speed.y = epoch->calcPVT.ENUV.y;
			memcpy(&m_calPOS.dop, &epoch->calcPVT.Dop, sizeof(BD2_DOP));
			memcpy(&m_calPOS.Ids, &epoch->calcPVT.UseSat, sizeof(UINT8)*epoch->NumUse);
			
			if (m_normalPOS.number>0)
			{
				if(epoch->PosMode.cPosMode==posmod)
					m_Listener.OnAnswerCalPositionPOS(WPARAM(&m_calPOS), posmod);//将计算后的结果返回
			}
			else 
			{
				m_Listener.OnAnswerCalPositionPOS(WPARAM(&m_calPOS), posmod);//将计算后的结果返回
			}

		}
		
	}
    
	return ERROR_POS_SUCCESS;
}
/*
int CWinCalPosApp::CalReceiverPosition(BD2_EPOCH* epoch)
{
	int Run = 0;
	BD2_RAN ImportData[MAX_FREQ];
	BD2_EPH ImportEPH[MAXCHANNELS];
	BD2_ION ImportION[MAXCHANNELS];
	UINT8 i=0,j=0,SatID=0,Branch=0;
	UINT8 posmod=0,SatNum=0,style=0;
	double SNR=0,rate=0,PR0=0,PR1=0;
	double dIono=0,dTro=0,dHgt=0;

	SatNum = 0;
	for (i=0; i<MAXCHANNELS; i++)
	{
		style = ModeToItem(MOD_B1I);
		if (ImportData[0].flag && m_normalPOS.posMod[style])//B1I
		{
		}
		style = ModeToItem(MOD_B1Q);
		if (ImportData[1].flag && m_normalPOS.posMod[style])//B1Q
		{
		}
		style = ModeToItem(MOD_B1C);
		if (ImportData[2].flag && m_normalPOS.posMod[style])//B1C
		{
		}
		style = ModeToItem(MOD_B1A);
		if (ImportData[3].flag && m_normalPOS.posMod[style])//B1A
		{
		}
		style = ModeToItem(MOD_B2a);
		if (ImportData[4].flag && m_normalPOS.posMod[style])//B2a
		{
		}
		style = ModeToItem(MOD_B2b);
		if (ImportData[5].flag && m_normalPOS.posMod[style])///B2b
		{
		}
		style = ModeToItem(MOD_B2);
		if (ImportData[6].flag && m_normalPOS.posMod[style])///B2
		{
		}
		style = ModeToItem(MOD_B3I);
		if (ImportData[7].flag && m_normalPOS.posMod[style])//B3I
		{
		}
		style = ModeToItem(MOD_B3Q);
		if (ImportData[8].flag && m_normalPOS.posMod[style])//B3Q
		{
		}
		style = ModeToItem(MOD_B3C);
		if (ImportData[9].flag && m_normalPOS.posMod[style])//B3C
		{
		}
		style = ModeToItem(MOD_B3A);
		if (ImportData[10].flag && m_normalPOS.posMod[style])//B3A
		{
		}
		style = ModeToItem(MOD_Bs);
		if (ImportData[11].flag && m_normalPOS.posMod[style])//Bs
		{
		}
		style = ModeToItem(MOD_B3AE);
		if (ImportData[12].flag && m_normalPOS.posMod[style])//B3AE
		{
		}
		style = ModeToItem(MOD_B1CB3C);
		if (ImportData[2].flag && ImportData[9].flag && m_normalPOS.posMod[style])//B1CB3C
		{
		}
		style = ModeToItem(MOD_B1QB3Q);
		if (ImportData[1].flag && ImportData[8].flag && m_normalPOS.posMod[style])//B1QB3Q
		{
		}
		style = ModeToItem(MOD_B1AB3A);
		if (ImportData[3].flag && ImportData[10].flag && m_normalPOS.posMod[style])//B1AB3A
		{
		}
		style = ModeToItem(MOD_B1AB3AE);
		if (ImportData[3].flag && ImportData[12].flag && m_normalPOS.posMod[style])//B1AB3AE
		{
		}
		style = ModeToItem(MOD_BsB3A);
		if (ImportData[11].flag && ImportData[10].flag && m_normalPOS.posMod[style])//BsB3A
		{
		}
		style = ModeToItem(MOD_BsB3AE);
		if (ImportData[11].flag && ImportData[12].flag && m_normalPOS.posMod[style])//BsB3AE
		{
		}
		style = ModeToItem(MOD_B1CB2a);
		if (ImportData[2].flag && ImportData[4].flag && m_normalPOS.posMod[style])//B1CB2a
		{
		}
		style = ModeToItem(MOD_B1CB2B3C);
		if (ImportData[2].flag && ImportData[6].flag && ImportData[9].flag && m_normalPOS.posMod[style])//B1CB3C
		{
		}
	}

	return Run;
}
*/