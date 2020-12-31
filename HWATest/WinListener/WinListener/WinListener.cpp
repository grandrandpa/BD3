// WinListener.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "WinListener.h"

// CWinListenerApp construction
CWinListenerApp::CWinListenerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_pListener = new CHostListener;
}
CWinListenerApp::~CWinListenerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	if(m_pListener)
		delete m_pListener;
	m_pListener = NULL;
}


// The one and only CWinListenerApp object
CHostListener* CWinListenerApp::GetListener()
{
	//m_pListener = new CHostListener;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot;
}
LRESULT CWinListenerApp::OnAnswerInfoCOD(WPARAM wParam, LPARAM lParam)//卫星原始导航电文
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoCOD(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoEPH(WPARAM wParam, LPARAM lParam)//卫星星历信息
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoEPH(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoION(WPARAM wParam, LPARAM lParam)//卫星电离层参数
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoION(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoALM(WPARAM wParam, LPARAM lParam)//卫星历书信息
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoALM(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoJAL(WPARAM wParam, LPARAM lParam)//卫星简约历书信息
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoJAL(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoCOM(WPARAM wParam, LPARAM lParam)//端口速率信息
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoCOM(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoMOD(WPARAM wParam, LPARAM lParam)//定位授时模式信息
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoMOD(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoPOS(WPARAM wParam, LPARAM lParam)//定位、测速结果信息
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoPOS(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoRAN(WPARAM wParam, LPARAM lParam)//伪距、载波、多普勒信息
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoRAN(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoREF(WPARAM wParam, LPARAM lParam)//时空参考信息
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoREF(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoGSV(WPARAM wParam, LPARAM lParam)//卫星信息
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoGSV(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoPAO(WPARAM wParam, LPARAM lParam)//电文页面播发顺序和历书播发顺序
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoPAO(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoCHD(WPARAM wParam, LPARAM lParam)//信道译码信息
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoCHD(wParam, lParam); 
}



LRESULT CWinListenerApp::OnAnswerInfoSTA(WPARAM wParam, LPARAM lParam)//终端工作状态信息
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoSTA(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoTIM(WPARAM wParam, LPARAM lParam)//授时结果信息
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoTIM(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoXPV(WPARAM wParam, LPARAM lParam)//笛卡尔坐标定位、测速结果信息
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoXPV(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoSRC(WPARAM wParam, LPARAM lParam)//原始数据
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoSRC(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoSNR(WPARAM wParam, LPARAM lParam)//原始数据
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoSNR(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoSKY(WPARAM wParam, LPARAM lParam)//原始数据
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoSKY(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoGBS(WPARAM wParam, LPARAM lParam)//自主完好性
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoGBS(wParam, lParam); 
}
LRESULT CWinListenerApp::OnAnswerInfoFrame(WPARAM wParam, LPARAM lParam)//自主完好性
{
	if(m_pListener == NULL)
		return -1;
	CHostListener* m_pPlot = (CHostListener*)m_pListener;
	return m_pPlot->OnAnswerInfoFrame(wParam, lParam); 
}
