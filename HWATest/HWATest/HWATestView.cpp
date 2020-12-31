// HWATestView.cpp : implementation of the CHWATestView class
//

#include "stdafx.h"
#include "HWATest.h"

#include "HWATestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////±³¾°É«ºÍ×ÖÌå///////////////////////
COLORREF	clrBkFace;
COLORREF	clrBarFace;
COLORREF	clrTextFace;
CPen		m_GnsspenLine;
CPen		m_GnssDotpenLine;
CFont		m_GnssfontBold;
CFont		m_GnssfontNormal;
CFont		m_GnssfontNormal25;
//////////////////////////////////////////////////////////////////////////
int bauds[MAXBAUD] = {1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400, 460800};
CString strFREQS[MAXFREQS] = {"B1I", "B1Q", "B1C", "B1A", "B1C_data", "B1C_pilot", "B1A_data", "B1A_pilot", "B2I", "B2Q", "B2a", "B2b", "B2", "B2a_data", "B2a_pilot", "B2b_data", "B2b_pilot", "B3I", "B3Q", "B3C", "B3A" , "B3AE", "B3C_data", "B3C_pilot", "B3A_data", "B3A_pilot", "Bs", "Bs_data", "Bs_pilot", "B3AE_data", "B3AE_pilot"};
//CString strFREQ[MAXFREQ] = {"B1I", "B1Q", "B1C", "B1A", "B2a", "B2b", "B2", "B3I", "B3Q", "B3C", "B3A", "B3AE", "Bs" };
//CString strMODE[MAXMODE] = {"B1I", "B1Q", "B1C", "B1A", "B2a", "B2b", "B2", "B3I", "B3Q", "B3C", "B3A", "B3AE", "Bs", "B1CB3C", "B1QB3Q", "B1AB3A", "B1AB3AE", "BsB3A", "BsB3AE", "B1CB2a", "B1CB2B3C", "USER" };
CString strFrameID[16] = {"GNREF", "GNMOD", "GNCOM", "GNRAN", "BDEPH", "BSEPH", "BSALM","BSJAL", "BDION", "BSION", "BDCOD", "BSCOD", "GNPOS", "GNXPV","GNTIM", "GNSTA"};


CString strFREQ[MAXFREQ] = {"B1I", "B1Q", "B1C", "B1A", "B2a", "B2b_I", "B2b_Q", "B3I", "B3Q", "B3C", "B3A", "B3AE", "Bs" };
CString strMODE[MAXMODE] = {"B1I", "B1Q", "B1C", "B1A", "B2a", "B2b_I", "B2b_Q", "B3I", "B3Q", "B3C", "B3A", "B3AE", "Bs", "B1CB3C", "B1QB3Q", "B1AB3A", "B1AB3AE", "BsB3A", "BsB3AE", "B1CB2a", "B1CB2B3C", "USER" };

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CToolbarLabel, CBCGPToolbarButton, 1)
CToolbarLabel::CToolbarLabel (UINT nID, LPCTSTR lpszText)
{
	if (lpszText != NULL)	
	{		
		m_strText = lpszText;
	}	

	m_bText = TRUE;
	m_nID = nID;
	m_iImage = -1;
}

void CToolbarLabel::OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* pImages, 
							BOOL bHorz, BOOL /*bCustomizeMode*/, BOOL /*bHighlight*/,	
							BOOL /*bDrawBorder*/,	BOOL /*bGrayDisabledButtons*/)
{
	UINT nStyle = m_nStyle;	
	m_nStyle &= ~TBBS_DISABLED;

	CBCGPToolbarButton::OnDraw (pDC, rect, pImages, bHorz, FALSE,
		FALSE, FALSE, FALSE);

	m_nStyle = nStyle;
}
//////////////////////////////////////////////////////////////////////////
// CHWATestView

IMPLEMENT_DYNCREATE(CHWATestView, CView)

BEGIN_MESSAGE_MAP(CHWATestView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHWATestView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CHWATestView::OnFilePrint)
	ON_MESSAGE(WM_PRINTCLIENT, OnPrintClient)
END_MESSAGE_MAP()

// CHWATestView construction/destruction

CHWATestView::CHWATestView()
{
	// TODO: add construction code here

}

CHWATestView::~CHWATestView()
{
}

BOOL CHWATestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CHWATestView drawing

void CHWATestView::OnDraw(CDC* /*pDC*/)
{
	CHWATestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CHWATestView printing

void CHWATestView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL CHWATestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHWATestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHWATestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CHWATestView diagnostics

#ifdef _DEBUG
void CHWATestView::AssertValid() const
{
	CView::AssertValid();
}

void CHWATestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHWATestDoc* CHWATestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHWATestDoc)));
	return (CHWATestDoc*)m_pDocument;
}
#endif //_DEBUG


// CHWATestView message handlers

LRESULT CHWATestView::OnPrintClient(WPARAM wp, LPARAM lp)
{
	if ((lp & PRF_CLIENT) == PRF_CLIENT)
	{
		CDC* pDC = CDC::FromHandle((HDC) wp);
		ASSERT_VALID(pDC);
		
		OnDraw(pDC);
	}
	
	return 0;
}

void CHWATestView::OnUpdateAllViews(CGlobalVariant* data, int type)
{

}
void CHWATestView::Clear()
{

}
//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////
void DrawWindowsRect(CWnd *pwnd)
{
	CWindowDC dc1 (pwnd);
	CRect rect2;
	::GetWindowRect(pwnd->m_hWnd,&rect2);	 
	rect2.bottom -= rect2.top;
	rect2.right -= rect2.left;
	rect2.left = rect2.top = 0;
	dc1.Draw3dRect (&rect2, clrBarFace, clrBarFace);
	rect2.DeflateRect (2, 2);
	dc1.Draw3dRect (rect2, RGB(231,241,254), RGB(231,241,254));	
}
void DrawText(CDC& dc, int x, int y, CString s,COLORREF color, int align)
{
	CSize off=dc.GetTextExtent(s);
	COLORREF clrTextOld = dc.SetTextColor(color ); //HXZ(RGB(35,121,121) 
	if (align==1) 
	{
		x-=off.cx/2;
		y-=off.cy/2;
	}
	else if (align==2)
		x-=off.cx;
	dc.TextOut(x,y,s);
	dc.SetTextColor (clrTextOld);
}

void DrawFontText(CDC* pDC, int x, int y,CFont *oldFont, CString s,COLORREF color, int align)
{
	CSize off=pDC->GetTextExtent(s);
	CFont* pOldFont = pDC->SelectObject (oldFont);
	if (align==1)
	{
		x-=off.cx/2;
		y-=off.cy/2;
	}
	else if (align==2)
		x-=off.cx;
	COLORREF clrTextOld = pDC->SetTextColor (color);	
	pDC->ExtTextOut (x,y,NULL, NULL, s, NULL);
	pDC->SelectObject (pOldFont);
	pDC->SetTextColor (clrTextOld);
}
