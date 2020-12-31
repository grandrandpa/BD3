#ifndef __PLOT_CONST__
#define __PLOT_CONST__
#pragma once
#include <afxmt.h>
#include <afxtempl.h>
#include <list>
#include <time.h>
#include <map>
#include <vector>
#include <assert.h> 
#include <string>
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
using namespace std;

#define DRAW_MODE_LINE		00		//��ͨģʽ
#define DRAW_MODE_POINTS	01		//����ģʽ

#define	MOUSE_DRAG_MOVE 0
#define	MOUSE_DRAG_ZOOM 1
#define MOUSE_DRAG_BOX_ZOOM 2

#define AXIS_X_HEIGH		60
#define AXIS_Y_WIDTH		120
#define AXIS_LEGEND_WIDTH	120
#define AXIS_TITLE_HEIGH	80

#define TOOLBAR_HEIGH		30
#define BUTTON_WIDTH		50
#define FRAME_WIDTH			2

#define ID_ROOT_CHANNEL_128		(ID_ROOT_CHANNEL_0+128)

#define MAX_SAT	64
typedef struct PLOT_LINE_TOOLBAR 
{
	CString strCaption;	//��ť����
	BOOL	bPressed;	//����
	BOOL	bMouseIn;	//����ڷ�Χ��
	BOOL	bChecked;	//ѡ��״̬
	CRect	rt;			//��ť����RECT
	UINT	ID;
	PLOT_LINE_TOOLBAR()
	{
		ID = 0;
		bPressed = FALSE;
		bMouseIn = FALSE;
		bChecked = FALSE;
		strCaption.Empty();
	}
}PLOT_LINE_TOOLBAR;

typedef struct PLOT_SKY_CHANNEL 
{
	char	nID[MAX_SAT];				//���Ǳ��
	char	Flag[MAX_SAT];				//�����ʶ
	double	dElev[MAX_SAT];				//����
	double	dAzi[MAX_SAT];				//��λ��
	char	nSatNum;					//�������Ǹ���
	DWORD	dwColor;					//ͨ����ɫ
	DWORD	dwType;						//���Ƿ���
	CString	ChName;						//������������GPS, BD2,GLONass...
	BOOL m_bVisible;
	PLOT_SKY_CHANNEL()
	{
		dwType = 0;
		nSatNum = 0;
		ChName.Empty();
		m_bVisible = TRUE;
		dwColor = RGB(0, 255, 0);
	}
	void Clear()
	{
		nSatNum = 0;
	}
	void AddSat(char id, double elv, double azi, int flag)
	{
		nID[nSatNum] = id;
		dAzi[nSatNum] = azi;
		dElev[nSatNum] = elv;
		Flag[nSatNum] = flag;
		nSatNum++;
	}
	void SetChName(LPCTSTR lpstrName)
	{
		ChName.Empty();
		ChName.Format("%s", lpstrName);
	}
	void SetChColor(DWORD	dwColor)
	{
		dwColor = dwColor;
	}
}PLOT_SKY_CHANNEL;

typedef struct PLOT_SNR_CHANNEL 
{
	char	nID[MAX_SAT];		//���Ǳ��
	double	dSNR[MAX_SAT];		//�����
	char	nSatNum;			//�������Ǹ���
	DWORD	dwColor;			//ͨ����ɫ
	CString	ChName;				//������������GPS, BD2,GLONass...
	BOOL m_bVisible;
	PLOT_SNR_CHANNEL()
	{
		nSatNum = 0;
		ChName.Empty();
		m_bVisible = TRUE;
		dwColor = RGB(0, 255, 0);
	}
	void Clear()
	{
		nSatNum = 0;
	}
	void AddSat(char id, double snr)
	{
		nID[nSatNum] = id;
		dSNR[nSatNum] = snr;
		nSatNum++;
	}
	void SetChName(LPCTSTR lpstrName)
	{
		ChName.Empty();
		ChName.Format("%s", lpstrName);
	}
	void SetChColor(DWORD	dwColor)
	{
		dwColor = dwColor;
	}
}PLOT_SNR_CHANNEL;

typedef struct PLOT_LINE_CHANNEL 
{
	//��ǰ���ݵ���
	DWORD m_dwDotsNumCur;
	DWORD m_dwMaxsize; //ѭ�����е����洢�ռ�
	DWORD m_dwFront;//ͷָ�룬�����в��գ�ָ�����ͷԪ��  
	DWORD m_dwRear;//βָ�룬�����в��գ�ָ�����ΪԪ�ص���һ��λ�� 
	//��ŵ��������� x,y
	double *m_pdX;
	double *m_pdY;
	DWORD m_dwPlotType;//��ʽ
	COLORREF m_clrCh;
	COLORREF m_clrDot;
	double m_dMaxY;
	double m_dMinY;
	double m_dMaxX;
	double m_dMinX;
	BOOL m_bVisible;
	CString strChName;
	PLOT_LINE_CHANNEL()
	{
		m_pdX = NULL;
		m_pdY = NULL;
		m_dwRear = 0;
		m_dwFront = 0;
		m_dwMaxsize = 0;
		m_dwDotsNumCur = 0;
		m_clrCh = RGB(0,255,0);
		m_clrDot = RGB(255,0,0);
		m_dMinY = 0.0;
		m_dMaxY = 1.0;
		m_dMaxX = 1.0;
		m_dMinX = 0.0;
		m_bVisible = TRUE;
		strChName.Empty();
	}
	void Clean()
	{
		if (m_pdX)delete[] m_pdX;
		if (m_pdY)delete[] m_pdY;
		m_pdX = NULL;
		m_pdY = NULL;
		m_dwRear = 0;
		m_dwFront = 0;
		m_dwMaxsize = 0;
		strChName.Empty();
	}
	void SetChName(LPCTSTR lpstrName)
	{
		strChName.Empty();
		strChName.Format("%s", lpstrName);
	}
	DWORD GetDotNum()
	{
		return m_dwMaxsize;
	}
	void AddDot(double dx, double dy)
	{
		if (m_dwDotsNumCur == 0)
		{
			m_dMinY = dy;
			m_dMaxY = dy;
			m_dMinX = dx;
			m_dMaxX = dx;
		}
		if ((m_dwRear+1)%m_dwMaxsize == m_dwFront)//����Ϊ�������,�Ƴ����Ƚ�����е�Ԫ��
		{
			m_dwFront = (m_dwFront+1)%m_dwMaxsize;
		}
		m_pdX[m_dwRear] = dx;
		m_pdY[m_dwRear] = dy;
		m_dwRear = (m_dwRear+1)%m_dwMaxsize;
		m_dwDotsNumCur = (m_dwRear - m_dwFront + m_dwMaxsize)%m_dwMaxsize;//�󳤶� 

		if(m_dMinY > dy)m_dMinY = dy;
		if (m_dMaxY < dy)m_dMaxY = dy;

		if (m_dMinX > dx)m_dMinX = dx;
		if (m_dMaxX < dx)m_dMaxX = dx;
	}
	void SetDotsNum(DWORD dwNum)
	{
		Clean();
		m_dwRear = 0;
		m_dwFront = 0;
		m_dwDotsNumCur = 0;
		m_dwMaxsize = dwNum;
		m_pdX = new double[dwNum];
		m_pdY = new double[dwNum];
		memset(m_pdX, 0, sizeof(double)*dwNum);
		memset(m_pdY, 0, sizeof(double)*dwNum);
	}
}PLOT_LINE_CHANNEL;

#endif