#pragma once
#include "PlotDefine.h"

#define MAX_BUTTON	20
class CPlotToolbar
{
public:
	CPlotToolbar(void);
	~CPlotToolbar(void);
private:
	int m_iBtnNum;//
	CRect m_rtCli;//
	CFont *m_pFont;//×ÖÌå
	CWnd* m_pParentWnd;//¸¸´°¿Ú
	PLOT_LINE_TOOLBAR* m_pBtnInfo;
private:
	void RecalcRect(CDC* pDC);
public:
	void CreateToolbar(CRect rect, CWnd* pWnd);
	void CreateButton(UINT ID, LPCTSTR lpstrName);
	void SetFont(CFont* pFont);
public:
	void DrawToolbar(CDC* pDC);
	void SetRect(LPRECT lpRect);
	void CheckClick(CPoint point);
	void SetBtnChecked(int ID, BOOL bCheck);
};
