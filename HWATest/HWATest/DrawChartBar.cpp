// DrawChartBar.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "DrawChartBar.h"


// CDrawChartBar

IMPLEMENT_DYNAMIC(CDrawChartBar, CWnd)

CDrawChartBar::CDrawChartBar()
{
	m_strChartTitle[0] = "B1I 信号强度";
	m_strChartTitle[1] = "B1Q 信号强度";
	m_strChartTitle[2] = "B1C 信号强度";
	m_strChartTitle[3] = "B1A 信号强度";
	ZeroMemory(&m_arPackSNR, sizeof(BD2_GSV)*4);
}

CDrawChartBar::~CDrawChartBar()
{
}


BEGIN_MESSAGE_MAP(CDrawChartBar, CWnd)
//	ON_WM_CREATE()
//	ON_WM_SIZE()
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_COMMAND(ID_USER_CLEAR, &CDrawChartBar::OnUserClear)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CDrawChartBar message handlers
BOOL CDrawChartBar::Create(const RECT &rect, CWnd *pParentWnd, UINT nControlID, int nType)
{
	m_nVisibleWindowType = nType;
	if (GetSafeHwnd())
		return FALSE;
	BOOL bRes = CWnd::Create( NULL, NULL,WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rect, pParentWnd,nControlID );
	return bRes;
}

void CDrawChartBar::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CWnd::OnNcPaint() for painting messages
	DrawWindowsRect(this);
}

void CDrawChartBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	CBCGPMemDC memDC (dc, this);
	CDC* pDC = &memDC.GetDC ();	
	CRect rect; 	
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,clrBkFace);
	ReDrawAll(pDC, rect);

	ReleaseDC(pDC);
}
void CDrawChartBar::ReDrawAll(CDC* pDC, CRect rect)
{
	if (m_nVisibleWindowType == 1)
	{
		DrawChart(pDC, 0, rect.left, rect.Width(), rect.Height(), rect.top);	
	} 
	else if(m_nVisibleWindowType == 2)
	{
		DrawChart(pDC, 0, rect.left, rect.Width(), rect.Height()/2, rect.top);
		DrawChart(pDC, 1, rect.left, rect.Width(), rect.Height()/2, rect.top+rect.Height()/2);
	}
	else if (m_nVisibleWindowType == 3)
	{
		DrawChart(pDC, 0, rect.left, rect.Width()/2, rect.Height()/2, rect.top);
		DrawChart(pDC, 1, rect.left+ rect.Width()/2, rect.Width()/2, rect.Height()/2,rect.top);
		DrawChart(pDC, 2, rect.left, rect.Width(), rect.Height()/2, rect.top+rect.Height()/2);
	}
	else if (m_nVisibleWindowType == 4)
	{
		DrawChart(pDC, 0, rect.left, rect.Width()/2, rect.Height()/2, rect.top);
		DrawChart(pDC, 1, rect.left+ rect.Width()/2, rect.Width()/2, rect.Height()/2, rect.top);
		DrawChart(pDC, 2, rect.left, rect.Width()/2, rect.Height()/2, rect.top+rect.Height()/2);
		DrawChart(pDC, 3, rect.left+ rect.Width()/2, rect.Width()/2, rect.Height()/2, rect.top+rect.Height()/2);
	}
}
//void CDrawChartBar::OnSize(UINT nType, int cx, int cy)
//{
//	CWnd::OnSize(nType, cx, cy);
//
//	// TODO: Add your message handler code here
//	//Reset();
//}

void CDrawChartBar::Reset(void)
{
	if(IsWindow(m_hWnd))
		Invalidate();
}
void CDrawChartBar::Clean()
{
	ZeroMemory(&m_arPackSNR, sizeof(BD2_GSV)*4);
}
void CDrawChartBar::Clear(void)
{
	ZeroMemory(&m_arPackSNR, sizeof(BD2_GSV)*4);
	Reset();
}
void CDrawChartBar::ClearChartData(int index)
{
	if(index < 0)
		return;
	int id = index%4;//取余(范围0~3)
	ZeroMemory(&m_arPackSNR[id], sizeof(BD2_GSV));
}
void CDrawChartBar::SetChartData(int index, BD2_GSV* data)
{
	if(index < 0)
		return;
	int id = index%4;//取余(范围0~3)
	memcpy(&m_arPackSNR[id], data, sizeof(BD2_GSV));
}
void CDrawChartBar::SetChartTitle(int index, CString strTitle)
{
	int id = index%4;//取余(范围0~3)
	m_strChartTitle[id] = strTitle;
}

void CDrawChartBar::DrawChart(CDC* pDC, int chartType, int l, int w, int h, int top)
{
	int SvId=0, index=0;
	CString strText;
	COLORREF rectcolor;
	int hh=h-15,snr=0,y1=0,y2=0,i=0,Nsats=0,ww=0,www=0,x1=0;

	index = chartType%4;
	CPen* pOldPen = pDC->SelectObject (&m_GnsspenLine);
	COLORREF clrTextOld = pDC->SetTextColor(clrTextFace );
	CFont* pOldFont=pDC->SelectObject(&m_GnssfontNormal);
	strText = m_strChartTitle[index]+"(单位：dBHz)";
	pDC->TextOut(l+2, top, strText, strText.GetLength());
	pDC->SetTextColor (clrTextOld);
	CRect b(l+1, top+15, l+w-2, top+hh); 
	CBrush pBrush(clrBkFace);//pBrush(RGB(217,233,255));//
	CBrush * pOldBrush = pDC->SelectObject( &pBrush );	
	pDC->Rectangle(b);
	pDC->SelectObject (&m_GnssDotpenLine);
	pDC->SelectObject( pOldBrush );
	int nOldBkMode=pDC->SetBkMode(TRANSPARENT);
	for (snr=MINSNR+10;snr<MAXSNR;snr+=10)
	{
		y1=top+hh-(snr-MINSNR)*hh/(MAXSNR-MINSNR);
		pDC->MoveTo(l+2,y1);
		pDC->LineTo(l+w-14,y1);
		strText.Format("%d",snr);
		DrawText(*pDC,l+w-10,y1,strText, clrTextFace,1);
	}
	pDC->SelectObject( pOldPen );
	pDC->SetBkMode( nOldBkMode );
	y1=top+hh;
	Nsats=m_arPackSNR[index].num;
	for (i=0;i<Nsats;i++)
	{
		snr = (int)(m_arPackSNR[index].snr[i]+0.5);
		ww=(w-16)/Nsats;
		www=ww-2<8?ww-2:12;
		x1=l+i*(w-16)/Nsats+ww/2;                     
		y2=y1;
		if (snr>MINSNR)
			y2-=(snr-MINSNR)*hh/(MAXSNR-MINSNR);
		y2=y2<2?2:(y1<y2?y1:y2);            
		CRect r1(x1,y1,x1+www,y2); 
		if(snr < 25)
			rectcolor=RGB(255,0,0);
		else if(snr > 50)
			rectcolor=RGB(0,255,0);
		else
			rectcolor = RGB((int)((50 - snr) * 10.2), (int)(255 - (50 - snr) * 10.2), 0);//
		CBrush brush(rectcolor);
		CBrush * pOldBrush = ( CBrush* )pDC->SelectObject(&brush);
		pDC->Rectangle(r1);
		SvId = m_arPackSNR[index].id[i];
		strText.Format("%d", SvId);
		DrawText(*pDC,x1+www/2,y1+8,strText,clrTextFace,1);
		strText.Format("%d",snr);
		DrawText(*pDC,x1+www/2, y2,strText,clrTextFace,1);
		pDC->SelectObject( pOldBrush );
	} 

	pDC->SelectObject (pOldPen);
	pDC->SelectObject(pOldFont);
}

void CDrawChartBar::OnUserClear()
{
	// TODO: Add your command handler code here
	Clear();
}

void CDrawChartBar::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//CPoint pt;
	//CMenu menu;
	//GetCursorPos(&pt);
	//menu.CreatePopupMenu();
	//menu.AppendMenu(MF_STRING, ID_USER_CLEAR, "清除");
	////UpdateRClickMenuState(&menuPlot);
	//menu.TrackPopupMenu(TPM_LEFTALIGN,pt.x, pt.y, this);
	//menu.DestroyMenu();

	CWnd::OnRButtonDown(nFlags, point);
}
