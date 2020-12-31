// ShowSkyView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowSkyView.h"
#include "RadarPointView.h"

// CShowSkyView

IMPLEMENT_DYNAMIC(CShowSkyView, CBCGPDockingControlBar)

CShowSkyView::CShowSkyView()
{
	//m_pDawSky=NULL;	

    m_pContext = NULL;

    CRuntimeClass* pFactory = RUNTIME_CLASS(RadarPointView);
    m_pFormView = (RadarPointView *)(pFactory->CreateObject());
}

CShowSkyView::~CShowSkyView()
{
	Clear();
}


BEGIN_MESSAGE_MAP(CShowSkyView, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CShowSkyView message handlers

void CShowSkyView::OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL /*bDisableIfNoHndler*/)
{
}

int CShowSkyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	//m_pDawSky=new CDrawSkyWnd;
	//if (m_pDawSky == NULL)
	//	return 0;
	//CRect rectClient;
	//GetClientRect (rectClient);	
	//CRect chartRect(rectClient.left,rectClient.top,rectClient.Width()-50,rectClient.Height());
	//if (!m_pDawSky->Create(chartRect, this, 1))
	//{
	//	if (!m_pDawSky->GetSafeHwnd())
	//	{
	//		AfxMessageBox("´´½¨ÐÇ¿ÕÍ¼Ê§°Ü");
	//		return 0;
	//	}		
	//}
	//m_pDawSky->Clear();

	if (m_pFormView != NULL)
	{
		m_pFormView->CreateView(this, m_pContext);
	}
    RecalcLayout();


	return 0;
}


void CShowSkyView::OnSize(UINT nType, int cx, int cy)
{
	//CBCGPDockingControlBar::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	//m_pDawSky->SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

    TRACE("CShowSkyView::OnSize cx:%d, cy:%d\n", cx, cy);

	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	
	if (m_pFormView->GetSafeHwnd ())
	{
		m_pFormView->SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}

void CShowSkyView::RefreshView(NmeaAllData* data)
{
	try
	{
		//m_pDawSky->RefreshView(data);
		//m_pDawSky->Reset();

        m_pFormView->DealData(data);

	}
	catch (...)
	{
	}
}

void CShowSkyView::Reset(void)
{
	//m_pDawSky->Reset();
}
void CShowSkyView::Clear()
{
	//m_pDawSky->Clear();
}
void CShowSkyView::OnPaint()
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