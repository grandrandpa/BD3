// WinPlot.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "WinPlot.h"

// CWinPlotApp construction
CWinPlotApp::CWinPlotApp()
{
	// TODO: add construction code here,
	m_pPlotDev = NULL;
}
CWinPlotApp::~CWinPlotApp()
{
	// TODO: add construction code here,
	if(m_pPlotDev != NULL)
	{
		delete m_pPlotDev;
		m_pPlotDev = NULL;
	}
}
// The one and only CWinPlotApp object
int CWinPlotApp::CreatePlot(const RECT& rt, CWnd* pParentWnd, DWORD dwMode, int nChannelNum, int nMaxPlotNum)
{
	m_pPlotDev = new CPlotLine;
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;

	return m_pPlot->CreatePlot(rt, pParentWnd, dwMode, nChannelNum, nMaxPlotNum);
}
void CWinPlotApp::SetWindowPos(int x, int y, int cx, int cy, UINT nFlag)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetWindowPos(NULL, x, y, cx, cy, nFlag);
}

//�趨ͨ��������ͼ��
void CWinPlotApp::SetChannelNum(int nCh, int nMaxBufLen)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetChannelNum(nCh, nMaxBufLen);
}
//�趨ͨ������//TODO
int CWinPlotApp::SetChannelName(int iCh, LPCTSTR lpstrName)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	return m_pPlot->SetChannelName(iCh, lpstrName);
}
//�趨��ǰ��ͼģʽ//TODO
//ģʽΪMODE_LINE ����MODE_POINT������
void CWinPlotApp::SetPlotMode(DWORD dwMode)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetPlotMode(dwMode);
}
//�趨ͨ����ɫ
int CWinPlotApp::SetChColor(int iCh, DWORD dwColor)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	return m_pPlot->SetChColor(iCh, dwColor);
}

//����ģʽʱ ������ģʽʱ��ͨ���趨��
void CWinPlotApp::AddChannelData(int iCh, double dy)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->AddChannelData(iCh, dy);
}
//������ģʽʱ��ͨ���趨��
void CWinPlotApp::AddChannelData(int iCh, double dx, double dy)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->AddChannelData(iCh, dx, dy);
}
//����ģʽʱ Ϊͨ���趨����
int CWinPlotApp::SetChannelDat(int iCh, double *dDat, int iDatCount)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	return m_pPlot->SetChannelDat(iCh, dDat, iDatCount);
}
//��ͼģʽʱ Ϊͨ���趨���� //TODO
int CWinPlotApp::SetChannelDat(int iCh, double* dDatX, double* dDatY, int iDatCount)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	return m_pPlot->SetChannelDat(iCh, dDatX, dDatY, iDatCount);
}

//�趨Y������ //TODO
void CWinPlotApp::SetYAxisName(LPCTSTR lpszYAxisName)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetYAxisName(lpszYAxisName);
}
//�趨X������ //TODO
void CWinPlotApp::SetXAxisName(LPCTSTR lpszXAxisName)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetXAxisName(lpszXAxisName);
}
//�趨X�����䣬��0~100�� //TODO
void CWinPlotApp::SetXSpan(double iStart, double Span)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetXSpan(iStart, Span);
}
//��λ�ռ���� //TODO
void CWinPlotApp::Reset()
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->Reset();
}
//���� //TODO
void CWinPlotApp::Clear()
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->Clear();
}
//����Ŵ�
void CWinPlotApp::ZoomAxisX(double dZoom)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->ZoomAxisX(dZoom);
}
//����Ŵ�
void CWinPlotApp::ZoomAxisY(double dZoom)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->ZoomAxisY(dZoom);
}
//�Ŵ���С
void CWinPlotApp::ZoomAxis(double dZoom)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->ZoomAxis(dZoom);
}
//�Զ�����
void CWinPlotApp::SetAutoZoomFit(bool bFit)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetAutoZoomFit(bFit);
}

//�趨��ʾ��������[ͼ������] //TODO
void CWinPlotApp::SetTitle(LPCTSTR lpszTitle) //TODO
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetTitle(lpszTitle);
}
//����ĳһͨ����ע�����ǰ���Lock������//todo
void CWinPlotApp::RenderCh(int iCh ,BOOL bClear)	//����ĳһͨ��
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->RenderCh(iCh, bClear);
}
//�趨������ɫ
void CWinPlotApp::SetBKColor(DWORD dwColor)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetBKColor(dwColor);
}
// �趨��������ɫ
void CWinPlotApp::SetGridLineColor(DWORD dwColor)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetGridLineColor(dwColor);
}
// //�趨��������ɫ
void CWinPlotApp::SetAxisColor(DWORD dwColor)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetAxisColor(dwColor);
}
//������ɫ
void CWinPlotApp::SetTextColor(DWORD dwColor)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetTextColor(dwColor);
}

//�趨X�ᵥλ
void CWinPlotApp::SetUintDotSpanX(LPCTSTR strUint)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetUintDotSpanX(strUint);
}
//�趨Y�ᵥλ
void CWinPlotApp::SetUintDotSpanY(LPCTSTR strUint)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetUintDotSpanY(strUint);
}

//�趨X�����//�������������ʾ����ʹ�á�����0~1024��ʾ0~3000MHz,dScale=ʵ��ֵ/����
void CWinPlotApp::SetUnitScaleX(double dScale)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetUnitScaleX(dScale);
}
//�趨Y�����//�������������ʾ����ʹ�á�����0~1024��ʾ0~3000MHz,dScale=ʵ��ֵ/����
void CWinPlotApp::SetUnitScaleY(double dScale)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetUnitScaleY(dScale);
}

//�趨�Ƿ����
void CWinPlotApp::SetDrawDot(BOOL bDraw)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetDrawDot(bDraw);
}
//�趨�Ƿ���ʾ����ֵ
void CWinPlotApp::SetCurSor(BOOL bDraw)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetCurSor(bDraw);
}
//�����Ƿ���ͣ
void CWinPlotApp::SetVisible(BOOL bPause)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetVisible(bPause);
}
//�Ƿ���ʾͼ��
void CWinPlotApp::SetLegend(BOOL bDraw)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetLegend(bDraw);
}
//XY�����������λС��//-1��ʾ�Զ����޳���,Ĭ��Ϊ0
void CWinPlotApp::SetAxisNumSumAfterDotX(int num)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetAxisNumSumAfterDotX(num);
}
void CWinPlotApp::SetAxisNumSumAfterDotY(int num)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetAxisNumSumAfterDotY(num);
}
////////////////////////////////////////////////////////�ǿ�ͼ/////////////////////////////////////////////////////////////////////
int CWinPlotApp::CreateSKY(const RECT& rt, CWnd* pParentWnd, int nChNum, int nSatNum)
{
	m_pPlotDev = new CPlotSky;
	CPlotSky* m_pPlot = (CPlotSky*)m_pPlotDev;

	return 0;
}


////////////////////////////////////////////////////////��״ͼ/////////////////////////////////////////////////////////////////////
int CWinPlotApp::CreateSNR(const RECT& rt, CWnd* pParentWnd, int nChNum, int nSatNum)
{
	m_pPlotDev = new CPlotSnr;
	CPlotSnr* m_pPlot = (CPlotSnr*)m_pPlotDev;

	return 0;
}
