// DrawSnrWnd.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "DrawSnrWnd.h"


// CDrawSnrWnd

IMPLEMENT_DYNAMIC(CDrawSnrWnd, CWnd)

CDrawSnrWnd::CDrawSnrWnd()
{
	ZeroMemory(&m_listSnr, sizeof(PackageSNR));
}

CDrawSnrWnd::~CDrawSnrWnd()
{
}


BEGIN_MESSAGE_MAP(CDrawSnrWnd, CWnd)
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CDrawSnrWnd message handlers
BOOL CDrawSnrWnd::Create(const RECT &rect, CWnd *pParentWnd, UINT nControlID)
{
	if (GetSafeHwnd())
		return FALSE;
	BOOL bRes = CWnd::Create( NULL, NULL,WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rect, pParentWnd,nControlID );
	return bRes;
}

void CDrawSnrWnd::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CWnd::OnNcPaint() for painting messages
	DrawWindowsRect(this);
}

void CDrawSnrWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	CBCGPMemDC memDC (dc, this);
	CDC* pDC = &memDC.GetDC ();	
	CRect rect; 	
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,clrBkFace);
	DrawAllSnr(pDC, rect.left, rect.Width(), rect.Height(), rect.top);
	ReleaseDC(pDC);
}

void CDrawSnrWnd::Reset(void)
{
	if(IsWindow(m_hWnd))
		Invalidate();
}

void CDrawSnrWnd::Clear(void)
{
	ZeroMemory(&m_listSnr, sizeof(PackageSNR));
	Reset();
}

void CDrawSnrWnd::RefreshView(PackageSNR* data)
{
	memcpy(&m_listSnr, data, sizeof(PackageSNR));
	Reset();
}

void CDrawSnrWnd::DrawAllSnr(CDC* pDC, int l, int w, int h, int top)
{
	CString s;
	int SvId = 0;
	COLORREF rectcolor;
	int hh=h-15,snr=0,y1=0,y2=0,i=0,Nsats=0,ww=0,www=0,x1=0;

	CPen* pOldPen = pDC->SelectObject (&m_GnsspenLine);
	COLORREF clrTextOld = pDC->SetTextColor(clrTextFace );
	CFont* pOldFont=pDC->SelectObject(&m_GnssfontNormal);
	/*pDC->TextOut(l+2, top+1, s, s.GetLength());*/
	pDC->SetTextColor (clrTextOld);
	CRect b(l+1, top+5, l+w-2, top+hh); 
	CBrush pBrush(clrBkFace);//pBrush(RGB(217,233,255));
	CBrush * pOldBrush = pDC->SelectObject( &pBrush );	
	pDC->Rectangle(b);
	pDC->SelectObject( pOldBrush );
	int nOldBkMode=pDC->SetBkMode(TRANSPARENT);
	for (snr=MINSNR+10;snr<MAXSNR;snr+=10)
	{
		y1=top+hh-(snr-MINSNR)*hh/(MAXSNR-MINSNR);
		pDC->MoveTo(l+2,y1);
		pDC->LineTo(l+w-14,y1);
		s.Format("%d",snr);
		DrawText(*pDC,l+w-9,y1,s,clrTextFace,1);
	}
	pDC->SetBkMode( nOldBkMode );
	y1=top+hh;
	Nsats=m_listSnr.num;
	for (i=0;i<Nsats;i++)
	{
		snr = (int)m_listSnr.Snr[i];
		ww=(w-16)/Nsats;
		www=ww-2<12?ww-2:12;
		x1=l+i*(w-16)/Nsats+ww/2;                     
		y2=y1;
		if (snr>0)
			y2-=(snr-MINSNR)*hh/(MAXSNR-MINSNR);
		y2=y2<2?2:(y1<y2?y1:y2);            
		CRect r1(x1,y1,x1+www,y2); 
		if(snr < 20)
			rectcolor=RGB(255,0,0);
		else if(snr > 50)
			rectcolor=RGB(0,255,0);
		else
			rectcolor = RGB((int)((50 - snr) * 8.5), (int)(255 - (50 - snr) * 8.5), 0);//
		CBrush brush(rectcolor);
		CBrush * pOldBrush = ( CBrush* )pDC->SelectObject(&brush);
		pDC->Rectangle(r1);
		SvId = m_listSnr.id[i];
		s.Format("%d", (SvId>40)?SvId-40:SvId);
		DrawText(*pDC,x1+www/2,y1+6,s,clrTextFace,1);
		s.Format("%d",snr);
		DrawText(*pDC,x1+www/2,y2+(y1-y2)/2,s,clrTextFace,1);
		pDC->SelectObject( pOldBrush );
	} 

	pDC->SelectObject (pOldPen);
	pDC->SelectObject(pOldFont);
}

void CDrawSnrWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	Reset();
}
