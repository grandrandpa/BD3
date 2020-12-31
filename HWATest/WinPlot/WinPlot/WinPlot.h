// WinPlot.h : main header file for the WinPlot DLL
//

#pragma once
#include "PlotLine.h"
#include "PlotSnr.h"
#include "PlotSky.h"

#ifdef HWA_DRAW_EXPORTS
#define HWA_DRAW_API __declspec(dllexport)
#else
#define HWA_DRAW_API __declspec(dllimport)
#endif

// CWinPlotApp
// See WinPlot.cpp for the implementation of this class
//

class HWA_DRAW_API CWinPlotApp// : public CWinApp
{
public:
	CWinPlotApp();
	~CWinPlotApp();

	// Overrides
private:
	LPVOID m_pPlotDev;
/////////////////////////////////////////////////曲线绘制////////////////////////////////////////////////////////////////////////////
public:
	//移动窗口
	void SetWindowPos(int x, int y, int cx, int cy, UINT nFlag);
	//创建绘图区：rt，控件产生区域，pParentWnd，父窗口， //TODO
	//nChannelNum，通道数，最大为25通道, nMaxPlotNum，每通道最大绘图点
	int CreatePlot(const RECT& rt, CWnd* pParentWnd, DWORD dwMode=DRAW_MODE_LINE, int nChannelNum=13, int nMaxPlotNum=2048);
	//设定通道数及绘图点
	void SetChannelNum(int nCh, int nMaxBufLen);
	//设定通道名称//TODO
	int SetChannelName(int iCh, LPCTSTR lpstrName);
	//设定当前绘图模式//TODO
	//模式为MODE_LINE 或者MODE_POINT（点阵）
	void SetPlotMode(DWORD dwMode);	
	//设定通道颜色
	int SetChColor(int iCh, DWORD dwColor);
	//曲线模式时 点增加模式时对通道设定点
	void AddChannelData(int iCh, double dy);
	//星图模式时 点增加模式时对通道设定点
	void AddChannelData(int iCh, double dx, double dy);
	//曲线模式时 为通道设定数据
	int SetChannelDat(int iCh, double *dDat, int iDatCount);
	//星图模式时 为通道设定数据 //TODO
	int SetChannelDat(int iCh, double* dDatX, double* dDatY, int iDatCount);

	//设定Y轴名称 //TODO
	void SetYAxisName(LPCTSTR lpszYAxisName);
	//设定X轴名称 //TODO
	void SetXAxisName(LPCTSTR lpszXAxisName);
	//设定X轴区间，如0~100； //TODO
	void SetXSpan(double iStart, double Span);
	//复位空间变量 //TODO
	void Reset();
	//清屏 //TODO
	void Clear();
	//横向放大
	void ZoomAxisX(double dZoom);
	//纵向放大
	void ZoomAxisY(double dZoom);
	//放大缩小
	void ZoomAxis(double dZoom);
	//自动缩放
	void SetAutoZoomFit(bool bFit);

	//设定显示区域名称[图例名称] //TODO
	void SetTitle(LPCTSTR lpszTitle); //TODO
	//绘制某一通道，注意绘制前后加Lock操作！//todo
	void RenderCh(int iCh ,BOOL bClear = TRUE);	//绘制某一通道
	//设定背景颜色
	void SetBKColor(DWORD dwColor);
	// 设定网格线颜色
	void SetGridLineColor(DWORD dwColor);
	// //设定坐标轴颜色
	void SetAxisColor(DWORD dwColor);
	//字体颜色
	void SetTextColor(DWORD dwColor);

	//设定X轴单位
	void SetUintDotSpanX(LPCTSTR strUint);
	//设定Y轴单位
	void SetUintDotSpanY(LPCTSTR strUint);

	//设定X轴比例//这个比例用于显示坐标使用。例如0~1024表示0~3000MHz,dScale=实际值/点数
	void SetUnitScaleX(double dScale);
	//设定Y轴比例//这个比例用于显示坐标使用。例如0~1024表示0~3000MHz,dScale=实际值/点数
	void SetUnitScaleY(double dScale);

	//设定是否描点
	void SetDrawDot(BOOL bDraw);
	//设定是否显示测量值
	void SetCurSor(BOOL bDraw);
	//设置是否暂停
	void SetVisible(BOOL bPause);
	//是否显示图例
	void SetLegend(BOOL bDraw);
	//XY轴坐标后保留几位小数//-1表示自动无限长度,默认为0
	void SetAxisNumSumAfterDotX(int num=4);
	void SetAxisNumSumAfterDotY(int num=4);
	////////////////////////////////////////////////////////星空图/////////////////////////////////////////////////////////////////////
public:
	//创建绘图区：rt，控件产生区域，pParentWnd，父窗口， //TODO
	//nChNum，通道数，最大为13通道, nSatNum，每通道最大绘图点
	int CreateSKY(const RECT& rt, CWnd* pParentWnd, int nChNum=2, int nSatNum=20);
	////////////////////////////////////////////////////////柱状图/////////////////////////////////////////////////////////////////////
public:
	//创建绘图区：rt，控件产生区域，pParentWnd，父窗口， //TODO
	//nChNum，通道数，最大为13通道, nSatNum，每通道最大绘图点
	int CreateSNR(const RECT& rt, CWnd* pParentWnd, int nChNum=2, int nSatNum=20);
};
