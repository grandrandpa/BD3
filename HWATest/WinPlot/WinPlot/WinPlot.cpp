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

//设定通道数及绘图点
void CWinPlotApp::SetChannelNum(int nCh, int nMaxBufLen)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetChannelNum(nCh, nMaxBufLen);
}
//设定通道名称//TODO
int CWinPlotApp::SetChannelName(int iCh, LPCTSTR lpstrName)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	return m_pPlot->SetChannelName(iCh, lpstrName);
}
//设定当前绘图模式//TODO
//模式为MODE_LINE 或者MODE_POINT（点阵）
void CWinPlotApp::SetPlotMode(DWORD dwMode)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetPlotMode(dwMode);
}
//设定通道颜色
int CWinPlotApp::SetChColor(int iCh, DWORD dwColor)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	return m_pPlot->SetChColor(iCh, dwColor);
}

//曲线模式时 点增加模式时对通道设定点
void CWinPlotApp::AddChannelData(int iCh, double dy)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->AddChannelData(iCh, dy);
}
//点增加模式时对通道设定点
void CWinPlotApp::AddChannelData(int iCh, double dx, double dy)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->AddChannelData(iCh, dx, dy);
}
//曲线模式时 为通道设定数据
int CWinPlotApp::SetChannelDat(int iCh, double *dDat, int iDatCount)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	return m_pPlot->SetChannelDat(iCh, dDat, iDatCount);
}
//星图模式时 为通道设定数据 //TODO
int CWinPlotApp::SetChannelDat(int iCh, double* dDatX, double* dDatY, int iDatCount)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	return m_pPlot->SetChannelDat(iCh, dDatX, dDatY, iDatCount);
}

//设定Y轴名称 //TODO
void CWinPlotApp::SetYAxisName(LPCTSTR lpszYAxisName)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetYAxisName(lpszYAxisName);
}
//设定X轴名称 //TODO
void CWinPlotApp::SetXAxisName(LPCTSTR lpszXAxisName)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetXAxisName(lpszXAxisName);
}
//设定X轴区间，如0~100； //TODO
void CWinPlotApp::SetXSpan(double iStart, double Span)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetXSpan(iStart, Span);
}
//复位空间变量 //TODO
void CWinPlotApp::Reset()
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->Reset();
}
//清屏 //TODO
void CWinPlotApp::Clear()
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->Clear();
}
//横向放大
void CWinPlotApp::ZoomAxisX(double dZoom)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->ZoomAxisX(dZoom);
}
//纵向放大
void CWinPlotApp::ZoomAxisY(double dZoom)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->ZoomAxisY(dZoom);
}
//放大缩小
void CWinPlotApp::ZoomAxis(double dZoom)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->ZoomAxis(dZoom);
}
//自动缩放
void CWinPlotApp::SetAutoZoomFit(bool bFit)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetAutoZoomFit(bFit);
}

//设定显示区域名称[图例名称] //TODO
void CWinPlotApp::SetTitle(LPCTSTR lpszTitle) //TODO
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetTitle(lpszTitle);
}
//绘制某一通道，注意绘制前后加Lock操作！//todo
void CWinPlotApp::RenderCh(int iCh ,BOOL bClear)	//绘制某一通道
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->RenderCh(iCh, bClear);
}
//设定背景颜色
void CWinPlotApp::SetBKColor(DWORD dwColor)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetBKColor(dwColor);
}
// 设定网格线颜色
void CWinPlotApp::SetGridLineColor(DWORD dwColor)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetGridLineColor(dwColor);
}
// //设定坐标轴颜色
void CWinPlotApp::SetAxisColor(DWORD dwColor)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetAxisColor(dwColor);
}
//字体颜色
void CWinPlotApp::SetTextColor(DWORD dwColor)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetTextColor(dwColor);
}

//设定X轴单位
void CWinPlotApp::SetUintDotSpanX(LPCTSTR strUint)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetUintDotSpanX(strUint);
}
//设定Y轴单位
void CWinPlotApp::SetUintDotSpanY(LPCTSTR strUint)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetUintDotSpanY(strUint);
}

//设定X轴比例//这个比例用于显示坐标使用。例如0~1024表示0~3000MHz,dScale=实际值/点数
void CWinPlotApp::SetUnitScaleX(double dScale)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetUnitScaleX(dScale);
}
//设定Y轴比例//这个比例用于显示坐标使用。例如0~1024表示0~3000MHz,dScale=实际值/点数
void CWinPlotApp::SetUnitScaleY(double dScale)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetUnitScaleY(dScale);
}

//设定是否描点
void CWinPlotApp::SetDrawDot(BOOL bDraw)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetDrawDot(bDraw);
}
//设定是否显示测量值
void CWinPlotApp::SetCurSor(BOOL bDraw)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetCurSor(bDraw);
}
//设置是否暂停
void CWinPlotApp::SetVisible(BOOL bPause)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetVisible(bPause);
}
//是否显示图例
void CWinPlotApp::SetLegend(BOOL bDraw)
{
	CPlotLine* m_pPlot = (CPlotLine*)m_pPlotDev;
	m_pPlot->SetLegend(bDraw);
}
//XY轴坐标后保留几位小数//-1表示自动无限长度,默认为0
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
////////////////////////////////////////////////////////星空图/////////////////////////////////////////////////////////////////////
int CWinPlotApp::CreateSKY(const RECT& rt, CWnd* pParentWnd, int nChNum, int nSatNum)
{
	m_pPlotDev = new CPlotSky;
	CPlotSky* m_pPlot = (CPlotSky*)m_pPlotDev;

	return 0;
}


////////////////////////////////////////////////////////柱状图/////////////////////////////////////////////////////////////////////
int CWinPlotApp::CreateSNR(const RECT& rt, CWnd* pParentWnd, int nChNum, int nSatNum)
{
	m_pPlotDev = new CPlotSnr;
	CPlotSnr* m_pPlot = (CPlotSnr*)m_pPlotDev;

	return 0;
}
