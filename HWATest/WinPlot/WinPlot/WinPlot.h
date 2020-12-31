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
/////////////////////////////////////////////////���߻���////////////////////////////////////////////////////////////////////////////
public:
	//�ƶ�����
	void SetWindowPos(int x, int y, int cx, int cy, UINT nFlag);
	//������ͼ����rt���ؼ���������pParentWnd�������ڣ� //TODO
	//nChannelNum��ͨ���������Ϊ25ͨ��, nMaxPlotNum��ÿͨ������ͼ��
	int CreatePlot(const RECT& rt, CWnd* pParentWnd, DWORD dwMode=DRAW_MODE_LINE, int nChannelNum=13, int nMaxPlotNum=2048);
	//�趨ͨ��������ͼ��
	void SetChannelNum(int nCh, int nMaxBufLen);
	//�趨ͨ������//TODO
	int SetChannelName(int iCh, LPCTSTR lpstrName);
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
	void SetAxisNumSumAfterDotX(int num=4);
	void SetAxisNumSumAfterDotY(int num=4);
	////////////////////////////////////////////////////////�ǿ�ͼ/////////////////////////////////////////////////////////////////////
public:
	//������ͼ����rt���ؼ���������pParentWnd�������ڣ� //TODO
	//nChNum��ͨ���������Ϊ13ͨ��, nSatNum��ÿͨ������ͼ��
	int CreateSKY(const RECT& rt, CWnd* pParentWnd, int nChNum=2, int nSatNum=20);
	////////////////////////////////////////////////////////��״ͼ/////////////////////////////////////////////////////////////////////
public:
	//������ͼ����rt���ؼ���������pParentWnd�������ڣ� //TODO
	//nChNum��ͨ���������Ϊ13ͨ��, nSatNum��ÿͨ������ͼ��
	int CreateSNR(const RECT& rt, CWnd* pParentWnd, int nChNum=2, int nSatNum=20);
};
