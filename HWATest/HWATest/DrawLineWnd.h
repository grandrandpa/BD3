#pragma once
#include "WinPlot.h"


// CDrawLineWnd

class CDrawLineWnd : public CWnd
{
	DECLARE_DYNAMIC(CDrawLineWnd)

public:
	CDrawLineWnd();
	virtual ~CDrawLineWnd();

protected:
	DECLARE_MESSAGE_MAP()
private:
	CWinPlotApp m_wndChart;
	DWORD	m_dwDrawMode;
	int     m_nDrawNum;
	int     m_nDataNum;
public:
	void SetTitle(CString strTitle);
	BOOL Create(const RECT& rect, CWnd* pParentWnd, DWORD dwMode, int chNum, int DatNum);
	//设定通道名称//TODO
	void SetChName(int iCh, CString strName);
	//设定通道数及绘图点
	void SetChNum(int nCh, int nMaxLen);
	//设定Y轴名称 //TODO
	void SetYAxisName(LPCTSTR lpszYAxisName);
	//设定X轴名称 //TODO
	void SetXAxisName(LPCTSTR lpszXAxisName);
	//横向放大
	void ZoomAxisX(double dZoom);
	//纵向放大
	void ZoomAxisY(double dZoom);
	//放大缩小
	void ZoomAxis(double dZoom);
	//自动缩放
	void SetAutoZoomFit(bool bFit);
	//设定X轴单位
	void SetUintDotSpanX(LPCTSTR strUint);
	//设定Y轴单位
	void SetUintDotSpanY(LPCTSTR strUint);
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
	void InsertData(int iCh, double dy);
	void InsertData(int iCh, double dx, double dy);
	void Clean();
private:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


