// PlotSnr.cpp : implementation file
//

#include "stdafx.h"
#include "PlotSnr.h"


// CPlotSnr

IMPLEMENT_DYNAMIC(CPlotSnr, CWnd)

CPlotSnr::CPlotSnr()
{

}

CPlotSnr::~CPlotSnr()
{
}


BEGIN_MESSAGE_MAP(CPlotSnr, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CPlotSnr message handlers
int CPlotSnr::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}

void CPlotSnr::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
}

void CPlotSnr::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}
