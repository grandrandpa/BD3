#pragma once
#include "resource.h"
#include "PlotDefine.h"


// CPlotSnr

class CPlotSnr : public CWnd
{
	DECLARE_DYNAMIC(CPlotSnr)

public:
	CPlotSnr();
	virtual ~CPlotSnr();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


