// WinListener.h : main header file for the WinListener DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWinListenerApp
// See WinListener.cpp for the implementation of this class
//
#include "HostListener.h"

class HWA_LISTENER_API CWinListenerApp
{
public:
	CWinListenerApp();
	~CWinListenerApp();
private:
	LPVOID m_pListener;
// Overrides
public:
	CHostListener* GetListener();
	LRESULT OnAnswerInfoCOD(WPARAM wParam, LPARAM lParam);//卫星原始导航电文
	LRESULT OnAnswerInfoEPH(WPARAM wParam, LPARAM lParam);//卫星星历信息
	LRESULT OnAnswerInfoION(WPARAM wParam, LPARAM lParam);//卫星电离层参数
	LRESULT OnAnswerInfoALM(WPARAM wParam, LPARAM lParam);//卫星历书信息
	LRESULT OnAnswerInfoJAL(WPARAM wParam, LPARAM lParam);//卫星简约历书信息
	LRESULT OnAnswerInfoCOM(WPARAM wParam, LPARAM lParam);//端口速率信息
	LRESULT OnAnswerInfoMOD(WPARAM wParam, LPARAM lParam);//定位授时模式信息
	LRESULT OnAnswerInfoPOS(WPARAM wParam, LPARAM lParam);//定位、测速结果信息
	LRESULT OnAnswerInfoRAN(WPARAM wParam, LPARAM lParam);//伪距、载波、多普勒信息
	LRESULT OnAnswerInfoREF(WPARAM wParam, LPARAM lParam);//时空参考信息
	LRESULT OnAnswerInfoGSV(WPARAM wParam, LPARAM lParam);//卫星信息
	LRESULT OnAnswerInfoSTA(WPARAM wParam, LPARAM lParam);//终端工作状态信息
	LRESULT OnAnswerInfoTIM(WPARAM wParam, LPARAM lParam);//授时结果信息
	LRESULT OnAnswerInfoXPV(WPARAM wParam, LPARAM lParam);//笛卡尔坐标定位、测速结果信息
	LRESULT OnAnswerInfoSRC(WPARAM wParam, LPARAM lParam);//原始数据
	LRESULT OnAnswerInfoSNR(WPARAM wParam, LPARAM lParam);//原始数据
	LRESULT OnAnswerInfoSKY(WPARAM wParam, LPARAM lParam);//原始数据
	LRESULT OnAnswerInfoGBS(WPARAM wParam, LPARAM lParam);//自主完好性
	LRESULT OnAnswerInfoFrame(WPARAM wParam, LPARAM lParam);//一帧原始数据
	LRESULT OnAnswerInfoPAO(WPARAM wParam, LPARAM lParam);	
	LRESULT OnAnswerInfoCHD(WPARAM wParam, LPARAM lParam);//信道译码信息	
};
