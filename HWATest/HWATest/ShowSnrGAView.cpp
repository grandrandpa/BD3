// ShowSnrGAView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowSnrGAView.h"
#include "BarView.h"

// CShowSnrGAView

IMPLEMENT_DYNAMIC(CShowSnrGAView, CBCGPDockingControlBar)

CShowSnrGAView::CShowSnrGAView()
: m_nCurrentTime(0)
{
	//Clear();
	m_dwRecvFlag = 0;

    m_pContext = NULL;
    CRuntimeClass* pFactory = RUNTIME_CLASS(CBarView);
    m_pFormView = (CBarView *)(pFactory->CreateObject());
}

CShowSnrGAView::~CShowSnrGAView()
{
	Clear();
}


BEGIN_MESSAGE_MAP(CShowSnrGAView, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CShowSnrGAView message handlers

void CShowSnrGAView::OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL /*bDisableIfNoHndler*/)
{
}


int CShowSnrGAView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
    if (m_pFormView != NULL)
	{
		m_pFormView->CreateView(this, m_pContext);
	}

    m_pFormView->CreateChartGA();
    RecalcLayout();

	return 0;
}

void CShowSnrGAView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	//m_wndTabs.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	//Reset();

    if (m_pFormView->GetSafeHwnd ())
	{
		m_pFormView->SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}

void CShowSnrGAView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CBCGPDockingControlBar::OnPaint() for painting messages
	//CBCGPMemDC memDC (dc, this);
	////memDC.IsMemDC();
	//CDC* pDC = &memDC.GetDC();	
	//CRect rectClient; 	
	//GetClientRect(&rectClient);	
	//pDC->FillSolidRect(&rectClient,RGB(231,241,254));

    CRect rect;
	GetClientRect (rect);

	dc.FillSolidRect (rect, ::GetSysColor (COLOR_3DFACE));
}

void CShowSnrGAView::RefreshView(NmeaAllData* data, int branch)
{
    try{
        m_pFormView->DealData(data);
    } 
    catch(...)
    {
    }
}

void CShowSnrGAView::Reset(void)
{
	//m_wndSnrB1.Reset();
	//m_wndSnrB2.Reset();
	//m_wndSnrB3.Reset();
	//m_wndSnrBs.Reset();
}
void CShowSnrGAView::Clear()
{
	//m_wndSnrB1.Clear();
	//m_wndSnrB2.Clear();
	//m_wndSnrB3.Clear();
	//m_wndSnrBs.Clear();
}
void CShowSnrGAView::Clean()
{
	//m_wndSnrB1.Clean();
	//m_wndSnrB2.Clean();
	//m_wndSnrB3.Clean();
	//m_wndSnrBs.Clean();
}

