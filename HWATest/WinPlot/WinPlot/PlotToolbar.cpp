#include "StdAfx.h"
#include "PlotToolbar.h"

CPlotToolbar::CPlotToolbar(void)
{
	m_iBtnNum = 0;
	m_pFont = NULL;
	m_pParentWnd = NULL;
	m_pBtnInfo = NULL;
	m_pFont = NULL;
	m_pBtnInfo = new PLOT_LINE_TOOLBAR[MAX_BUTTON];
}

CPlotToolbar::~CPlotToolbar(void)
{
	delete[] m_pBtnInfo;
	m_pBtnInfo = NULL;
	if(m_pFont !=NULL)
	{
		m_pFont->DeleteObject();
		delete m_pFont;
		m_pFont = NULL;
	}
}
void CPlotToolbar::CreateToolbar(CRect rect, CWnd* pWnd)
{
	m_iBtnNum = 0;
	m_rtCli = rect;
	m_pParentWnd = pWnd;
}
void CPlotToolbar::CreateButton(UINT ID, LPCTSTR lpstrName)
{
	m_pBtnInfo[m_iBtnNum].ID = ID;
	m_pBtnInfo[m_iBtnNum].strCaption.Format("%s", lpstrName);
	m_iBtnNum++;
}
void CPlotToolbar::SetFont(CFont* pFont)
{
	m_pFont = pFont;
}
void CPlotToolbar::CheckClick(CPoint point)
{
	int i;
	for (i=0;i<m_iBtnNum;i++)
	{
		if (m_pBtnInfo[i].rt.PtInRect(point))
		{
			if (m_pParentWnd)
				m_pParentWnd->PostMessage(WM_COMMAND, m_pBtnInfo[i].ID, 0);
			break;
		}
	}
}
void CPlotToolbar::SetBtnChecked(int ID, BOOL bCheck)
{
	int i=0;
	for (i=0; i<m_iBtnNum; i++)
	{
		if(m_pBtnInfo[i].ID == ID)
			m_pBtnInfo[i].bChecked = bCheck;
	}
}
void CPlotToolbar::SetRect(LPRECT lpRect)
{
	//int i = 0,width=20;
	m_rtCli = lpRect;
	/*for (i=0;i<m_iBtnNum;i++)
	{
		m_pBtnInfo[i].rt.left = width;
		m_pBtnInfo[i].rt.right = width + m_pBtnInfo[i].strCaption.GetLength()*12+5;
		m_pBtnInfo[i].rt.top = m_rtCli.top+FRAME_WIDTH;
		m_pBtnInfo[i].rt.bottom = m_rtCli.bottom-FRAME_WIDTH;
		width = m_pBtnInfo[i].rt.right + 5;
	}*/
}
void CPlotToolbar::RecalcRect(CDC* pDC)
{
	CSize csSZ;
	int i = 0,width=20;

	for (i=0;i<m_iBtnNum;i++)
	{
		csSZ = pDC->GetTextExtent(m_pBtnInfo[i].strCaption);
		m_pBtnInfo[i].rt.left = width;
		m_pBtnInfo[i].rt.right = width + csSZ.cx + 10;
		m_pBtnInfo[i].rt.top = m_rtCli.top+FRAME_WIDTH;
		m_pBtnInfo[i].rt.bottom = m_rtCli.bottom-FRAME_WIDTH;
		width = m_pBtnInfo[i].rt.right + 5;
	}
}
void CPlotToolbar::DrawToolbar(CDC* pDC)
{
	CSize sz;
	int i=0,sx=0,sy=0;
	CString strText;
	CBrush br(RGB(128,128,128));
	pDC->FillRect(m_rtCli, &br);
	pDC->SetBkMode(TRANSPARENT);
	CBrush brFrame(RGB(255,255,255));
	CBrush brBtnChecked(RGB(255,255,0));
	CFont *pOldFont ;
	pOldFont = pDC->SelectObject(m_pFont);

	strText.Empty();
	RecalcRect(pDC);
	for (i=0;i<m_iBtnNum;i++)
	{
		if (m_pBtnInfo[i].bChecked)
		{
			pDC->FillRect(m_pBtnInfo[i].rt, &brBtnChecked);
		}
		pDC->FrameRect(m_pBtnInfo[i].rt, &brFrame);
		if (m_pBtnInfo[i].strCaption.IsEmpty())
			strText.Format("B%02d", i);
		else
			strText.Format("%s", m_pBtnInfo[i].strCaption);

		sz = pDC->GetTextExtent(strText);
		sx = (m_pBtnInfo[i].rt.Width() - sz.cx)/2;
		sy = (m_pBtnInfo[i].rt.Height() - sz.cy)/2;
		pDC->TextOut(m_pBtnInfo[i].rt.left + sx, m_pBtnInfo[i].rt.top +sy, strText, strText.GetLength());
	}
	pDC->SelectObject(pOldFont);
}
