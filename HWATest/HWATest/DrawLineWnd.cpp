// DrawChartWnd.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "DrawLineWnd.h"


// CDrawLineWnd

IMPLEMENT_DYNAMIC(CDrawLineWnd, CWnd)

CDrawLineWnd::CDrawLineWnd()
{
	m_nDrawNum = 100;
	m_dwDrawMode = DRAW_MODE_LINE;
}

CDrawLineWnd::~CDrawLineWnd()
{
}

BEGIN_MESSAGE_MAP(CDrawLineWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CDrawLineWnd message handlers
BOOL CDrawLineWnd::Create(const RECT& rect, CWnd* pParentWnd, DWORD dwMode, int chNum, int DatNum)
{
	m_nDrawNum = chNum;
	m_dwDrawMode = dwMode;
	m_nDataNum = DatNum;
	if (GetSafeHwnd())
		return FALSE;
	BOOL bRes = CWnd::Create( NULL, NULL,WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rect, pParentWnd, 65535);
	return bRes;
}
int CDrawLineWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);
	// TODO:  Add your specialized creation code here
	m_wndChart.CreatePlot(rect, this, m_dwDrawMode, m_nDrawNum, m_nDataNum);

	return 0;
}

void CDrawLineWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndChart.SetWindowPos(0, 0, cx, cy, nType);
}
void CDrawLineWnd::InsertData(int iCh, double dy)
{
	m_wndChart.AddChannelData( iCh, dy);
}
void CDrawLineWnd::InsertData(int iCh, double dx, double dy)
{
	m_wndChart.AddChannelData( iCh, dx, dy);
}
void CDrawLineWnd::Clean()
{
	m_wndChart.Clear();
}
void CDrawLineWnd::SetTitle(CString strTitle)
{
	m_wndChart.SetTitle(strTitle);
}
void CDrawLineWnd::SetChName(int iCh, CString strName)
{
	m_wndChart.SetChannelName(iCh, strName);
}
void CDrawLineWnd::SetChNum(int nCh, int nMaxLen)
{
	m_wndChart.SetChannelNum(nCh, nMaxLen);
}
//�趨Y������ //TODO
void CDrawLineWnd::SetYAxisName(LPCTSTR lpszYAxisName)
{
	m_wndChart.SetYAxisName(lpszYAxisName);
}
//�趨X������ //TODO
void CDrawLineWnd::SetXAxisName(LPCTSTR lpszXAxisName)
{
	m_wndChart.SetXAxisName(lpszXAxisName);
}
//����Ŵ�
void CDrawLineWnd::ZoomAxisX(double dZoom)
{
	m_wndChart.ZoomAxisX(dZoom);
}
//����Ŵ�
void CDrawLineWnd::ZoomAxisY(double dZoom)
{
	m_wndChart.ZoomAxisY(dZoom);
}
//�Ŵ���С
void CDrawLineWnd::ZoomAxis(double dZoom)
{
	m_wndChart.ZoomAxis(dZoom);
}
//�Զ�����
void CDrawLineWnd::SetAutoZoomFit(bool bFit)
{
	m_wndChart.SetAutoZoomFit(bFit);
}
//�趨X�ᵥλ
void CDrawLineWnd::SetUintDotSpanX(LPCTSTR strUint)
{
	m_wndChart.SetUintDotSpanX(strUint);
}
//�趨Y�ᵥλ
void CDrawLineWnd::SetUintDotSpanY(LPCTSTR strUint)
{
	m_wndChart.SetUintDotSpanY(strUint);
}
//�趨�Ƿ����
void CDrawLineWnd::SetDrawDot(BOOL bDraw)
{
	m_wndChart.SetDrawDot(bDraw);
}
//�趨�Ƿ���ʾ����ֵ
void CDrawLineWnd::SetCurSor(BOOL bDraw)
{
	m_wndChart.SetCurSor(bDraw);
}
//�����Ƿ���ͣ
void CDrawLineWnd::SetVisible(BOOL bPause)
{
	m_wndChart.SetVisible(bPause);
}
//�Ƿ���ʾͼ��
void CDrawLineWnd::SetLegend(BOOL bDraw)
{
	m_wndChart.SetLegend(bDraw);
}
//XY�����������λС��//-1��ʾ�Զ����޳���,Ĭ��Ϊ0
void CDrawLineWnd::SetAxisNumSumAfterDotX(int num)
{
	m_wndChart.SetAxisNumSumAfterDotX(num);
}
void CDrawLineWnd::SetAxisNumSumAfterDotY(int num)
{
	m_wndChart.SetAxisNumSumAfterDotY(num);
}

