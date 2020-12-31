// WinPrint.h : main header file for the WinPrint DLL
//

#pragma once
#include "PrintFile.h"
#include "PrintData.h"

// CWinPrintApp
// See WinPrint.cpp for the implementation of this class
//
#ifdef HWA_PRINT_EXPORTS
#define HWA_PRINT_API __declspec(dllexport)
#else
#define HWA_PRINT_API __declspec(dllimport)
#endif


class HWA_PRINT_API CWinPrintApp : public CBasicListener
{
public:
	CWinPrintApp();
	~CWinPrintApp();
	// Overrides
private:
	bool m_bSave;
	CString strProjPath;
	CPrintFile m_wndPrint;
	CPrintData m_printData;
	int			m_globalWeek;
	double		m_globalTow;
public:
	void Start();
	void LoadConfig(CString strDatabase, CString strConfigPath);
	void Stop();
private:
	virtual LRESULT OnAnswerInfoCOD(WPARAM wParam, LPARAM lParam);//卫星原始导航电文
	virtual LRESULT OnAnswerInfoEPH(WPARAM wParam, LPARAM lParam);//卫星星历信息
	virtual LRESULT OnAnswerInfoION(WPARAM wParam, LPARAM lParam);//卫星电离层参数
	virtual LRESULT OnAnswerInfoALM(WPARAM wParam, LPARAM lParam);//卫星历书信息
	virtual LRESULT OnAnswerInfoJAL(WPARAM wParam, LPARAM lParam);//卫星简约历书信息
	virtual LRESULT OnAnswerInfoCOM(WPARAM wParam, LPARAM lParam);//端口速率信息
	virtual LRESULT OnAnswerInfoMOD(WPARAM wParam, LPARAM lParam);//定位授时模式信息
	virtual LRESULT OnAnswerInfoPOS(WPARAM wParam, LPARAM lParam);//定位、测速结果信息
	virtual LRESULT OnAnswerInfoRAN(WPARAM wParam, LPARAM lParam);//伪距、载波、多普勒信息
	virtual LRESULT OnAnswerInfoREF(WPARAM wParam, LPARAM lParam);//时空参考信息
	virtual LRESULT OnAnswerInfoGSV(WPARAM wParam, LPARAM lParam);//卫星信息
	virtual LRESULT OnAnswerInfoSTA(WPARAM wParam, LPARAM lParam);//终端工作状态信息
	virtual LRESULT OnAnswerInfoTIM(WPARAM wParam, LPARAM lParam);//授时结果信息
	virtual LRESULT OnAnswerInfoXPV(WPARAM wParam, LPARAM lParam);//笛卡尔坐标定位、测速结果信息
	virtual LRESULT OnAnswerInfoGBS(WPARAM wParam, LPARAM lParam);//自主完好性
	virtual LRESULT OnAnswerInfoPAO(WPARAM wParam, LPARAM lParam);	
	virtual LRESULT OnAnswerInfoCHD(WPARAM wParam, LPARAM lParam);		//信道译码信息

    virtual LRESULT OnUpdataInfoAllGSV(WPARAM wParam, LPARAM lParam);//卫星信息
};
