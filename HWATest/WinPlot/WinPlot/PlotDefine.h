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

#define DRAW_MODE_LINE		00		//普通模式
#define DRAW_MODE_POINTS	01		//点阵模式

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
	CString strCaption;	//按钮名称
	BOOL	bPressed;	//按下
	BOOL	bMouseIn;	//鼠标在范围内
	BOOL	bChecked;	//选中状态
	CRect	rt;			//按钮所在RECT
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
	char	nID[MAX_SAT];				//卫星编号
	char	Flag[MAX_SAT];				//错误标识
	double	dElev[MAX_SAT];				//仰角
	double	dAzi[MAX_SAT];				//方位角
	char	nSatNum;					//导航卫星个数
	DWORD	dwColor;					//通道颜色
	DWORD	dwType;						//卫星分组
	CString	ChName;						//卫星组名，如GPS, BD2,GLONass...
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
	char	nID[MAX_SAT];		//卫星编号
	double	dSNR[MAX_SAT];		//载噪比
	char	nSatNum;			//导航卫星个数
	DWORD	dwColor;			//通道颜色
	CString	ChName;				//卫星组名，如GPS, BD2,GLONass...
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
	//当前数据点数
	DWORD m_dwDotsNumCur;
	DWORD m_dwMaxsize; //循环队列的最大存储空间
	DWORD m_dwFront;//头指针，若队列不空，指向队列头元素  
	DWORD m_dwRear;//尾指针，若队列不空，指向队列为元素的下一个位置 
	//存放点数据数据 x,y
	double *m_pdX;
	double *m_pdY;
	DWORD m_dwPlotType;//方式
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
		if ((m_dwRear+1)%m_dwMaxsize == m_dwFront)//队列为满的情况,移除最先进入队列的元素
		{
			m_dwFront = (m_dwFront+1)%m_dwMaxsize;
		}
		m_pdX[m_dwRear] = dx;
		m_pdY[m_dwRear] = dy;
		m_dwRear = (m_dwRear+1)%m_dwMaxsize;
		m_dwDotsNumCur = (m_dwRear - m_dwFront + m_dwMaxsize)%m_dwMaxsize;//求长度 

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