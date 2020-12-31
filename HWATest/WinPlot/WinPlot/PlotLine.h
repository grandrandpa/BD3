#pragma once
#include "resource.h"
#include "PlotDefine.h"
#include "PlotToolbar.h"

// CPlotLine

class CPlotLine : public CWnd
{
	DECLARE_DYNAMIC(CPlotLine)

public:
	CPlotLine();
	virtual ~CPlotLine();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//////////////////////////////////////////////////////////////////////////
public://右键菜单
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRootAxismove();
	afx_msg void OnRootAxiszoom();
	afx_msg void OnRootChannelAll();
	afx_msg void OnRootChannelSingle();
	afx_msg void OnRootCurvalue();
	afx_msg void OnRootMarkPoints();
	afx_msg void OnRootPause();
	afx_msg void OnRootZoomfit();
	afx_msg void OnRootZoomin();
	afx_msg void OnRootZoomout();
	afx_msg void OnRootShowCh(UINT uiCH);
	afx_msg void OnRootClean();

	void CheckMouseHitLegend(CPoint point);
private:
	void UpdateRClickMenuState(CMenu* pMenu);
	bool Create(const RECT &rect, DWORD dwStyle, CWnd *pParentWnd, UINT nControlID=65535);
private:
	CPlotToolbar*	  m_pToolbar;
	CFont *m_pToolbarFont;//字体
	PLOT_LINE_CHANNEL *m_pChDat;
	CCriticalSection *m_pcsSetDat;
private:
	//绘制模式
	DWORD m_dwDrawMode;
	//参考颜色//从iplot中获取
	DWORD m_dwColorRef[255];
	//主要背景颜色,各个模块"使用这个颜色清屏"
	COLORREF m_clrMainBGColor;
	COLORREF m_dwGridLineColor;//格网颜色
	COLORREF m_dwAxisColor;//坐标轴颜色
	COLORREF m_dwTextColor;//字体颜色
private:
	DWORD m_dwChNum;   //通道数
	DWORD m_dwChDatNum;//通道数据个数
	//是否通道单选模式
	BOOL m_bSingleChSel;
	//是否自动缩放
	BOOL m_bAutoZoomFit;
	//是否轴移动
	BOOL m_bAxisMove;
	//工具栏按钮
	BOOL m_bToolBarShow;
	BOOL m_bMouseInToolBarHotSpot;

	//是否绘制坐标轴的起始和终止值
	BOOL m_bDrawAxisValue;

	//X轴坐标后保留几位小数//-1表示自动无限长度,默认为0
	int m_iNumSumAfterDot;
	//这个比例用于显示坐标使用。例如0~1024表示0~3000MHz,dScale=实际值/点数
	double m_dUnitScaleX;
	//这个比例用于显示坐标使用。例如0~1024表示0~3000MHz,dScale=实际值/点数
	double m_dUnitScaleY;

	//X轴坐标后保留几位小数//-1表示自动无限长度,默认为0
	int m_iNumSumAfterDotX;
	int m_iNumSumAfterDotY;

	//鼠标按下时在plot区域的坐标
	double m_dMouseDownOnPlotX;
	double m_dMouseDownOnPlotY;
protected:
	//绘制X轴区域
	CRect m_rtAxisX;
	//绘制Y轴区域
	CRect m_rtAxisY;
	//绘制 图形 区域
	CRect m_rtPlot;
	//绘制 通道颜色示例区域
	CRect m_rtLegend;
	//绘制工具栏区域
	CRect m_rtToolBar;
	//绘制标题栏区域
	CRect m_rtTitle;
	//绘制信息区域0
	CRect m_rtInfo0;
	//图形标题
	CString m_strTitle;

	//X轴单位参数
	double m_dDotSpanX;
	CString m_strXUnit;
	//Y轴单位参数
	double m_dDotSpanY;
	CString m_strYUnit;
	//x轴名称
	CString m_strAxisXName;
	//y轴名称
	CString m_strAxisYName;
	//Y轴刻度文字字体
	CFont* m_pFontAxisY;
	//Legeng参数
	int m_iChLabelHei;
	bool m_bshowlegend;

	//显示的坐标轴范围
	double m_dAxisXMin;
	double m_dAxisXMax;
	double m_dAxisYMin;
	double m_dAxisYMax;

	double m_dXMul;
	double m_dYMul;

	//处理鼠标消息
	BOOL m_bLBtnDown;
	CPoint m_ptMouseLast;
	CPoint m_ptLMouseDown;
	double m_dMulXMouseDown;
	double m_dMulYMouseDown;
	//鼠标模式
	DWORD m_dwMouseDragMode;
	//绘制plot属性
	//是否绘制描点
	BOOL m_bDrawDot;
	//是否绘制网格线
	BOOL m_bDrawGridLineMain;
	//暂停绘图
	BOOL m_bPausePlot;
	//字体
	CFont* m_pMainFont;

	//数值测量功能的使用
	BOOL m_bShowCursor;
	CPoint m_poCursor;
	//显示鼠标附近点使用
	CPoint m_poMouseCursorCur;

	//区域缩放时的相关变量
	CPoint m_ptBoxZoomBegin;
	CPoint m_ptBoxZoomEnd;
	BOOL m_bBoxZoomDrawRect;
	CRect m_rtBoxZoom;
	double m_dBoxXMin,m_dBoxXMax,m_dBoxYMin, m_dBoxYMax;
public:
	void ReDrawAll(CDC* pDc, CRect rect);
	void DrawLines(CDC* pDc);//曲线图
	void DrawPoints(CDC* pDc);//点阵图
private:
	void DrawAxisX(CDC* pDc);//绘制X轴
	void DrawAxisY(CDC* pDc);//绘制Y轴
	void DrawPlotGrid(CDC* pDc);//绘制网格
	void DrawLegend(CDC* pDc);//
	void DrawTitle(CDC* pDc);//标题
	void ClearRect(CDC* pDc, LPRECT rt, COLORREF clr = RGB(0,0,0));//
	void DrawDot(CDC *pDc, double x, double y,  int iDotSize, COLORREF clr);//描点
private:
	void InitPara();
	void RecalcRect(CRect rect);
	void RecalcAxisRange(BOOL bRefMul=1);
	void RecalcAutoZoomFit();
	//菜单功能
	//处理鼠标拖动操作
	void MouseDragMove(CPoint point);//
	void MouseDragZoom(CPoint point);//
public:
public:
	//创建绘图区：rt，控件产生区域，pParentWnd，父窗口，dwMode, 设定当前绘图模式
	//nChannelNum，通道数，最大为8通道, nMaxPlotNum，每通道最大绘图点
	int CreatePlot(const RECT& rt, CWnd* pParentWnd, DWORD dwMode=DRAW_MODE_LINE, int nChannelNum=8, int nMaxPlotNum=2048);
	//设定通道数及绘图点
	void SetChannelNum(int nCh, int nMaxBufLen);
	//设定通道名称//TODO
	int SetChannelName(int iCh, LPCTSTR lpstrName);
	//获取当前绘图模式//TODO
	DWORD GetPlotMode();
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
	//设定Y轴区间，如0~100； //TODO
	void SetYSpan(double iStart, double Span);
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
	void SetAxisNumSumAfterDotX(int num=0);
	void SetAxisNumSumAfterDotY(int num=0);
};


