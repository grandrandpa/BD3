#pragma once
#include "resource.h"
#include "PlotDefine.h"


// CPlotSky

class CPlotSky : public CWnd
{
	DECLARE_DYNAMIC(CPlotSky)

public:
	CPlotSky();
	virtual ~CPlotSky();

protected:
	DECLARE_MESSAGE_MAP()
public:
	bool Create(const RECT &rect, DWORD dwStyle, CWnd *pParentWnd, UINT nControlID=65535);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	//通道数
	DWORD m_dwChNum;   
	//是否通道单选模式
	BOOL m_bSingleChSel;
	//半径
	int		m_nRadiu;
	//中心点
	CPoint m_ptCenterPoint;
	PLOT_SKY_CHANNEL*	m_pCharData;
	CCriticalSection*	m_pcsSetDat;
private:
	CPen	m_GnsspenLine;
	CPen	m_GnssDotpenLine;
	//字体
	CFont* m_pMainFont;
	//字体颜色
	COLORREF m_dwTextColor;
	//参考颜色//从iplot中获取
	DWORD m_dwColorRef[255];
	//主要背景颜色,各个模块"使用这个颜色清屏"
	COLORREF m_clrMainBGColor;
	//格网颜色
	COLORREF m_dwGridLineColor;
private:
	void ReDrawAll(CDC* pDc, CRect rect);
	void DrawPlot(CDC* pDc, CRect rect);
	void DrawPlotGrid(CDC* pDc, CRect rect);
	void DrawLegend(CDC* pDc, CRect rect);//
	void DrawSatellite(CDC* pDC, int x, int y, int SvNo, int SVType, int iFlag);
public:
	//创建绘图区：rt，控件产生区域，pParentWnd，父窗口
	//nChannelNum，通道数，最大为3通道, nMaxPlotNum，每通道最大绘图点20
	int CreatePlot(const RECT& rt, CWnd* pParentWnd, int nChannelNum=3, int nMaxPlotNum=20);
};


