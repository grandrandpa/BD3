// BaseView.cpp : implementation file
//

#include "stdafx.h"
#include "BaseView.h"


/////////////////////////////////////////////////////////////////////////////
// CResizeGroupBox

CResizeGroupBox::CResizeGroupBox()
{
}

CResizeGroupBox::~CResizeGroupBox()
{
}

IMPLEMENT_DYNAMIC(CResizeGroupBox, CXTPButton)

BEGIN_MESSAGE_MAP(CResizeGroupBox, CXTPButton)
//{{AFX_MSG_MAP(CResizeGroupBox)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizeGroupBox message handlers

void CResizeGroupBox::Exclude(CDC* pDC, CRect& rcClient)
{
	// get a pointer to the parent.
	CWnd* pWndParent = GetParent();
	if (!pWndParent)
		return;
	
	// get a pointer to the parents first child.
	CWnd* pWnd = pWndParent->GetWindow(GW_CHILD);
	if (pWnd == NULL)
		return;
	
	// iterate thru all children and exclude those children that
	// are located inside the group box.
	CWnd* pChildWnd = pWnd->GetWindow(GW_HWNDFIRST);
	while (pChildWnd != NULL)
	{
		// make sure we do not exclude ourself
		if (pChildWnd != this && pChildWnd->IsWindowVisible())
		{
			CRect rc;
			pChildWnd->GetWindowRect(&rc);
			ScreenToClient(&rc);
			
			// if the parent's child is located in our group box, exclude
			// it from painting.
			if (rcClient.PtInRect(rc.TopLeft()) ||
				rcClient.PtInRect(rc.BottomRight()))
			{
				pDC->ExcludeClipRect(&rc);
			}
		}
		
		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
	}
}

BOOL CResizeGroupBox::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void CResizeGroupBox::OnPaint()
{
	CPaintDC dc(this);
	
	// get the client area size.
	CRect rcClient;
	GetClientRect(&rcClient);
	
	// exclude controls that we "group"
	Exclude(&dc, rcClient);
	
	// Paint to a memory device context to help
	// eliminate screen flicker.
	CXTPBufferDC memDC(dc);
	
	HBRUSH hBrush = (HBRUSH)GetParent()->SendMessage(WM_CTLCOLORBTN, (WPARAM)memDC.GetSafeHdc(), (LRESULT)m_hWnd);
	if (hBrush)
	{
		::FillRect(memDC, rcClient, hBrush);
	}
	else
	{
		memDC.FillSolidRect(rcClient, GetSysColor(COLOR_3DFACE));
	}
	
#ifdef _XTP_INCLUDE_TOOLKIT
	OnDraw(&memDC);
#else
	// Let the window do its default painting...
	CButton::DefWindowProc(WM_PAINT, (WPARAM)memDC.m_hDC, 0);
#endif
}