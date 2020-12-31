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
	//ͨ����
	DWORD m_dwChNum;   
	//�Ƿ�ͨ����ѡģʽ
	BOOL m_bSingleChSel;
	//�뾶
	int		m_nRadiu;
	//���ĵ�
	CPoint m_ptCenterPoint;
	PLOT_SKY_CHANNEL*	m_pCharData;
	CCriticalSection*	m_pcsSetDat;
private:
	CPen	m_GnsspenLine;
	CPen	m_GnssDotpenLine;
	//����
	CFont* m_pMainFont;
	//������ɫ
	COLORREF m_dwTextColor;
	//�ο���ɫ//��iplot�л�ȡ
	DWORD m_dwColorRef[255];
	//��Ҫ������ɫ,����ģ��"ʹ�������ɫ����"
	COLORREF m_clrMainBGColor;
	//������ɫ
	COLORREF m_dwGridLineColor;
private:
	void ReDrawAll(CDC* pDc, CRect rect);
	void DrawPlot(CDC* pDc, CRect rect);
	void DrawPlotGrid(CDC* pDc, CRect rect);
	void DrawLegend(CDC* pDc, CRect rect);//
	void DrawSatellite(CDC* pDC, int x, int y, int SvNo, int SVType, int iFlag);
public:
	//������ͼ����rt���ؼ���������pParentWnd��������
	//nChannelNum��ͨ���������Ϊ3ͨ��, nMaxPlotNum��ÿͨ������ͼ��20
	int CreatePlot(const RECT& rt, CWnd* pParentWnd, int nChannelNum=3, int nMaxPlotNum=20);
};


