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
	//�趨ͨ������//TODO
	void SetChName(int iCh, CString strName);
	//�趨ͨ��������ͼ��
	void SetChNum(int nCh, int nMaxLen);
	//�趨Y������ //TODO
	void SetYAxisName(LPCTSTR lpszYAxisName);
	//�趨X������ //TODO
	void SetXAxisName(LPCTSTR lpszXAxisName);
	//����Ŵ�
	void ZoomAxisX(double dZoom);
	//����Ŵ�
	void ZoomAxisY(double dZoom);
	//�Ŵ���С
	void ZoomAxis(double dZoom);
	//�Զ�����
	void SetAutoZoomFit(bool bFit);
	//�趨X�ᵥλ
	void SetUintDotSpanX(LPCTSTR strUint);
	//�趨Y�ᵥλ
	void SetUintDotSpanY(LPCTSTR strUint);
	//�趨�Ƿ����
	void SetDrawDot(BOOL bDraw);
	//�趨�Ƿ���ʾ����ֵ
	void SetCurSor(BOOL bDraw);
	//�����Ƿ���ͣ
	void SetVisible(BOOL bPause);
	//�Ƿ���ʾͼ��
	void SetLegend(BOOL bDraw);
	//XY�����������λС��//-1��ʾ�Զ����޳���,Ĭ��Ϊ0
	void SetAxisNumSumAfterDotX(int num=4);
	void SetAxisNumSumAfterDotY(int num=4);
	void InsertData(int iCh, double dy);
	void InsertData(int iCh, double dx, double dy);
	void Clean();
private:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


