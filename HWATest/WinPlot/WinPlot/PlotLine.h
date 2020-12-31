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
public://�Ҽ��˵�
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
	CFont *m_pToolbarFont;//����
	PLOT_LINE_CHANNEL *m_pChDat;
	CCriticalSection *m_pcsSetDat;
private:
	//����ģʽ
	DWORD m_dwDrawMode;
	//�ο���ɫ//��iplot�л�ȡ
	DWORD m_dwColorRef[255];
	//��Ҫ������ɫ,����ģ��"ʹ�������ɫ����"
	COLORREF m_clrMainBGColor;
	COLORREF m_dwGridLineColor;//������ɫ
	COLORREF m_dwAxisColor;//��������ɫ
	COLORREF m_dwTextColor;//������ɫ
private:
	DWORD m_dwChNum;   //ͨ����
	DWORD m_dwChDatNum;//ͨ�����ݸ���
	//�Ƿ�ͨ����ѡģʽ
	BOOL m_bSingleChSel;
	//�Ƿ��Զ�����
	BOOL m_bAutoZoomFit;
	//�Ƿ����ƶ�
	BOOL m_bAxisMove;
	//��������ť
	BOOL m_bToolBarShow;
	BOOL m_bMouseInToolBarHotSpot;

	//�Ƿ�������������ʼ����ֵֹ
	BOOL m_bDrawAxisValue;

	//X�����������λС��//-1��ʾ�Զ����޳���,Ĭ��Ϊ0
	int m_iNumSumAfterDot;
	//�������������ʾ����ʹ�á�����0~1024��ʾ0~3000MHz,dScale=ʵ��ֵ/����
	double m_dUnitScaleX;
	//�������������ʾ����ʹ�á�����0~1024��ʾ0~3000MHz,dScale=ʵ��ֵ/����
	double m_dUnitScaleY;

	//X�����������λС��//-1��ʾ�Զ����޳���,Ĭ��Ϊ0
	int m_iNumSumAfterDotX;
	int m_iNumSumAfterDotY;

	//��갴��ʱ��plot���������
	double m_dMouseDownOnPlotX;
	double m_dMouseDownOnPlotY;
protected:
	//����X������
	CRect m_rtAxisX;
	//����Y������
	CRect m_rtAxisY;
	//���� ͼ�� ����
	CRect m_rtPlot;
	//���� ͨ����ɫʾ������
	CRect m_rtLegend;
	//���ƹ���������
	CRect m_rtToolBar;
	//���Ʊ���������
	CRect m_rtTitle;
	//������Ϣ����0
	CRect m_rtInfo0;
	//ͼ�α���
	CString m_strTitle;

	//X�ᵥλ����
	double m_dDotSpanX;
	CString m_strXUnit;
	//Y�ᵥλ����
	double m_dDotSpanY;
	CString m_strYUnit;
	//x������
	CString m_strAxisXName;
	//y������
	CString m_strAxisYName;
	//Y��̶���������
	CFont* m_pFontAxisY;
	//Legeng����
	int m_iChLabelHei;
	bool m_bshowlegend;

	//��ʾ�������᷶Χ
	double m_dAxisXMin;
	double m_dAxisXMax;
	double m_dAxisYMin;
	double m_dAxisYMax;

	double m_dXMul;
	double m_dYMul;

	//���������Ϣ
	BOOL m_bLBtnDown;
	CPoint m_ptMouseLast;
	CPoint m_ptLMouseDown;
	double m_dMulXMouseDown;
	double m_dMulYMouseDown;
	//���ģʽ
	DWORD m_dwMouseDragMode;
	//����plot����
	//�Ƿ�������
	BOOL m_bDrawDot;
	//�Ƿ����������
	BOOL m_bDrawGridLineMain;
	//��ͣ��ͼ
	BOOL m_bPausePlot;
	//����
	CFont* m_pMainFont;

	//��ֵ�������ܵ�ʹ��
	BOOL m_bShowCursor;
	CPoint m_poCursor;
	//��ʾ��긽����ʹ��
	CPoint m_poMouseCursorCur;

	//��������ʱ����ر���
	CPoint m_ptBoxZoomBegin;
	CPoint m_ptBoxZoomEnd;
	BOOL m_bBoxZoomDrawRect;
	CRect m_rtBoxZoom;
	double m_dBoxXMin,m_dBoxXMax,m_dBoxYMin, m_dBoxYMax;
public:
	void ReDrawAll(CDC* pDc, CRect rect);
	void DrawLines(CDC* pDc);//����ͼ
	void DrawPoints(CDC* pDc);//����ͼ
private:
	void DrawAxisX(CDC* pDc);//����X��
	void DrawAxisY(CDC* pDc);//����Y��
	void DrawPlotGrid(CDC* pDc);//��������
	void DrawLegend(CDC* pDc);//
	void DrawTitle(CDC* pDc);//����
	void ClearRect(CDC* pDc, LPRECT rt, COLORREF clr = RGB(0,0,0));//
	void DrawDot(CDC *pDc, double x, double y,  int iDotSize, COLORREF clr);//���
private:
	void InitPara();
	void RecalcRect(CRect rect);
	void RecalcAxisRange(BOOL bRefMul=1);
	void RecalcAutoZoomFit();
	//�˵�����
	//��������϶�����
	void MouseDragMove(CPoint point);//
	void MouseDragZoom(CPoint point);//
public:
public:
	//������ͼ����rt���ؼ���������pParentWnd�������ڣ�dwMode, �趨��ǰ��ͼģʽ
	//nChannelNum��ͨ���������Ϊ8ͨ��, nMaxPlotNum��ÿͨ������ͼ��
	int CreatePlot(const RECT& rt, CWnd* pParentWnd, DWORD dwMode=DRAW_MODE_LINE, int nChannelNum=8, int nMaxPlotNum=2048);
	//�趨ͨ��������ͼ��
	void SetChannelNum(int nCh, int nMaxBufLen);
	//�趨ͨ������//TODO
	int SetChannelName(int iCh, LPCTSTR lpstrName);
	//��ȡ��ǰ��ͼģʽ//TODO
	DWORD GetPlotMode();
	//�趨��ǰ��ͼģʽ//TODO
	//ģʽΪMODE_LINE ����MODE_POINT������
	void SetPlotMode(DWORD dwMode);	
	//�趨ͨ����ɫ
	int SetChColor(int iCh, DWORD dwColor);
	//����ģʽʱ ������ģʽʱ��ͨ���趨��
	void AddChannelData(int iCh, double dy);
	//��ͼģʽʱ ������ģʽʱ��ͨ���趨��
	void AddChannelData(int iCh, double dx, double dy);
	//����ģʽʱ Ϊͨ���趨����
	int SetChannelDat(int iCh, double *dDat, int iDatCount);
	//��ͼģʽʱ Ϊͨ���趨���� //TODO
	int SetChannelDat(int iCh, double* dDatX, double* dDatY, int iDatCount);

	//�趨Y������ //TODO
	void SetYAxisName(LPCTSTR lpszYAxisName);
	//�趨X������ //TODO
	void SetXAxisName(LPCTSTR lpszXAxisName);
	//�趨X�����䣬��0~100�� //TODO
	void SetXSpan(double iStart, double Span);
	//�趨Y�����䣬��0~100�� //TODO
	void SetYSpan(double iStart, double Span);
	//��λ�ռ���� //TODO
	void Reset();
	//���� //TODO
	void Clear();
	//����Ŵ�
	void ZoomAxisX(double dZoom);
	//����Ŵ�
	void ZoomAxisY(double dZoom);
	//�Ŵ���С
	void ZoomAxis(double dZoom);
	//�Զ�����
	void SetAutoZoomFit(bool bFit);

	//�趨��ʾ��������[ͼ������] //TODO
	void SetTitle(LPCTSTR lpszTitle); //TODO
	//����ĳһͨ����ע�����ǰ���Lock������//todo
	void RenderCh(int iCh ,BOOL bClear = TRUE);	//����ĳһͨ��
	//�趨������ɫ
	void SetBKColor(DWORD dwColor);
	// �趨��������ɫ
	void SetGridLineColor(DWORD dwColor);
	// //�趨��������ɫ
	void SetAxisColor(DWORD dwColor);
	//������ɫ
	void SetTextColor(DWORD dwColor);

	//�趨X�ᵥλ
	void SetUintDotSpanX(LPCTSTR strUint);
	//�趨Y�ᵥλ
	void SetUintDotSpanY(LPCTSTR strUint);

	//�趨X�����//�������������ʾ����ʹ�á�����0~1024��ʾ0~3000MHz,dScale=ʵ��ֵ/����
	void SetUnitScaleX(double dScale);
	//�趨Y�����//�������������ʾ����ʹ�á�����0~1024��ʾ0~3000MHz,dScale=ʵ��ֵ/����
	void SetUnitScaleY(double dScale);

	//�趨�Ƿ����
	void SetDrawDot(BOOL bDraw);
	//�趨�Ƿ���ʾ����ֵ
	void SetCurSor(BOOL bDraw);
	//�����Ƿ���ͣ
	void SetVisible(BOOL bPause);
	//�Ƿ���ʾͼ��
	void SetLegend(BOOL bDraw);

	//XY�����������λС��//-1��ʾ�Զ����޳���,Ĭ��Ϊ0
	void SetAxisNumSumAfterDotX(int num=0);
	void SetAxisNumSumAfterDotY(int num=0);
};


