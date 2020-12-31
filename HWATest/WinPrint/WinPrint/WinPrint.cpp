// WinPrint.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "WinPrint.h"
#include "nmea.h"

// CWinPrintApp construction
CWinPrintApp::CWinPrintApp()
{
	// TODO: add construction code here,
	m_globalWeek = 0;
	m_globalTow = 0;
	m_bSave = false;
	strProjPath.Empty();
}
CWinPrintApp::~CWinPrintApp()
{
	// TODO: add construction code here,
	m_bSave = false;
}
void CWinPrintApp::LoadConfig(CString strDatabase, CString strConfigPath)
{
	char buf[MAX_PATH];
	m_globalWeek = 0;
	m_globalTow = 0;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	if(strDatabase.IsEmpty() || strConfigPath.IsEmpty())
		return;
	GetPrivateProfileString("Product", "SaveData", "", buf, MAX_PATH, strConfigPath);
	strProjPath = CString(buf);
	strProjPath.ReleaseBuffer();

	m_wndPrint.LoadConfig(strDatabase, strConfigPath);
	m_printData.LoadConfig(strProjPath, strConfigPath);
}
void CWinPrintApp::Start()
{
	m_bSave = true;
}
void CWinPrintApp::Stop()
{
	m_bSave = false;
}
// The one and only CWinPrintApp object
LRESULT CWinPrintApp::OnAnswerInfoCOD(WPARAM wParam, LPARAM lParam)//卫星原始导航电文
{
	if(!m_bSave)
		return false;
	BD2_COD* data = (BD2_COD*)wParam;
	data->week = m_globalWeek;
	data->tow = m_globalTow;
	m_wndPrint.SaveCODFile(data);
	m_printData.SaveCODFile(data);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoEPH(WPARAM wParam, LPARAM lParam)//卫星星历信息
{
	if(!m_bSave)
		return false;
	BD2_EPH* data = (BD2_EPH*)wParam;
	m_globalWeek = data->week;
	m_globalTow = data->tow;
	m_wndPrint.SaveEPHFile(data);
	m_printData.SaveEPHFile(data);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoION(WPARAM wParam, LPARAM lParam)//卫星电离层参数
{
	if(!m_bSave)
		return false;
	BD2_ION* data = (BD2_ION*)wParam;
	m_globalWeek = data->week;
	m_globalTow = data->tow;
	m_wndPrint.SaveIONFile(data);
	m_printData.SaveIONFile(data);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoALM(WPARAM wParam, LPARAM lParam)//卫星历书信息
{
	if(!m_bSave)
		return false;
	BD2_ALM* data = (BD2_ALM*)wParam;
	m_wndPrint.SaveALMFile(data);
	m_printData.SaveALMFile(data);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoJAL(WPARAM wParam, LPARAM lParam)//卫星简约历书信息
{
	if(!m_bSave)
		return false;
	BD2_JAL* data = (BD2_JAL*)wParam;
	m_wndPrint.SaveJALFile(data);
	m_printData.SaveJALFile(data);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoCOM(WPARAM wParam, LPARAM lParam)//端口速率信息
{
	if(!m_bSave)
		return false;
	SETCOM* data = (SETCOM*)wParam;
	m_wndPrint.SaveCOMFile(data);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoMOD(WPARAM wParam, LPARAM lParam)//定位授时模式信息
{
	if(!m_bSave)
		return false;
	SETMOD* data = (SETMOD*)wParam;
	m_wndPrint.SaveMODFile(data);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoPOS(WPARAM wParam, LPARAM lParam)//定位、测速结果信息
{
	if(!m_bSave)
		return false;
	BD2_POS* data = (BD2_POS*)wParam;
	m_globalWeek = data->week;
	m_globalTow = data->tow;
	m_wndPrint.SavePOSFile(data);
	m_printData.SavePOSFile(data);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoRAN(WPARAM wParam, LPARAM lParam)//伪距、载波、多普勒信息
{
	if(!m_bSave)
		return false;
	BD2_RAN* data = (BD2_RAN*)wParam;
	m_globalWeek = data->week;
	m_globalTow = data->tow;
	m_wndPrint.SaveRANFile(data);
	m_printData.SaveRANFile(data);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoREF(WPARAM wParam, LPARAM lParam)//时空参考信息
{
	if(!m_bSave)
		return false;
	SETREF* data = (SETREF*)wParam;
	m_wndPrint.SaveREFFile(data);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoGSV(WPARAM wParam, LPARAM lParam)//卫星信息
{
	if(!m_bSave)
		return false;
	NmeaAllData* data = (NmeaAllData*)wParam;

 //   BD2_GSV packGSV;
 //   int id=0;
 //   double elv=0,azi=0;

 //   switch(data->sys)
 //   {
 //   case GP:
 //       packGSV.num = data->GP_view_C;
 //       break;

 //   case BD:
 //       packGSV.num = data->BD_view_C;
 //       break;

 //   case GL:
 //       packGSV.num = data->GL_view_C;
 //       break;

 //   case GA:
 //       packGSV.num = data->GA_view_C;
 //       break;

 //   default:
 //       packGSV.num = data->BD_view_C;
 //       break;
 //   
 //   }

 //   for (int i=0; i<packGSV.num; i++)
	//{
 //       id = atoi(data->BD_view[i].PRN);
 //       elv = strtod(data->BD_view[i].yang_cour, NULL);
 //       azi = strtod(data->BD_view[i].fangwei_cour, NULL);


	//	packGSV.id[i] = id;
	//	packGSV.elv[i] = elv;
	//	packGSV.azi[i] = azi;
 //       packGSV.snr[i] = strtod(data->BD_view[i].CN0, NULL);
	//}

 //   packGSV.system_type = data->sys;

	m_wndPrint.SaveAllGSVFile(data);//SaveGSVFile(&packGSV);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoPAO(WPARAM wParam, LPARAM lParam)//电文页面播发顺序和历书播发顺序
{
	if(!m_bSave)
		return false;
	BD2_PAORDER* data = (BD2_PAORDER*)wParam;
	m_wndPrint.SaveTESTFile(data);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoCHD(WPARAM wParam, LPARAM lParam)//信道译码信息
{
	if(!m_bSave)
		return false;
	BD2_CHD* data = (BD2_CHD*)wParam;
	m_wndPrint.SaveCHDFile(data);
	return true; 
}



LRESULT CWinPrintApp::OnAnswerInfoSTA(WPARAM wParam, LPARAM lParam)//终端工作状态信息
{
	if(!m_bSave)
		return false;
	BD2_STA* data = (BD2_STA*)wParam;
	m_wndPrint.SaveSTAFile(data);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoTIM(WPARAM wParam, LPARAM lParam)//授时结果信息
{
	if(!m_bSave)
		return false;
	BD2_TIME* data = (BD2_TIME*)wParam;
	m_globalWeek = data->week;
	m_globalTow = data->tow;
	m_wndPrint.SaveTIMFile(data);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoXPV(WPARAM wParam, LPARAM lParam)//笛卡尔坐标定位、测速结果信息
{
	if(!m_bSave)
		return false;
	BD2_POS* data = (BD2_POS*)wParam;
	m_globalWeek = data->week;
	m_globalTow = data->tow;
	m_wndPrint.SaveXPVFile(data);
	m_printData.SaveXPVFile(data);
	return true; 
}
LRESULT CWinPrintApp::OnAnswerInfoGBS(WPARAM wParam, LPARAM lParam)//自主完好性
{
	if(!m_bSave)
		return false;
	BD2_GBS* data = (BD2_GBS*)wParam;
	m_wndPrint.SaveGBSFile(data);
	return true;
}


LRESULT CWinPrintApp::OnUpdataInfoAllGSV(WPARAM wParam, LPARAM lParam)
{
	if(!m_bSave)
		return false;
	NmeaAllData* data = (NmeaAllData*)wParam;

	m_wndPrint.SaveAllGSVFile(data);
	return true; 
}