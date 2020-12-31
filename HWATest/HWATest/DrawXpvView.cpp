// DrawXpvView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "DrawXpvView.h"


// CDrawXpvView

IMPLEMENT_DYNCREATE(CDrawXpvView, CHWATestView)

CDrawXpvView::CDrawXpvView()
{

}

CDrawXpvView::~CDrawXpvView()
{
}

BEGIN_MESSAGE_MAP(CDrawXpvView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDrawXpvView drawing

void CDrawXpvView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CDrawXpvView diagnostics

#ifdef _DEBUG
void CDrawXpvView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CDrawXpvView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDrawXpvView message handlers

int CDrawXpvView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CHWATestView::OnCreate(lpCreateStruct) == -1)
		return -1;

	int i=0,j=0;
	CString str;
	CRect rect, rectLine;
	rect.SetRectEmpty();
	// TODO:  Add your specialized creation code here
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create  
	}
	//
	CRect RectTab(rect.left, rect.top+30, rect.Width(), rect.Height()-30);
	if (!m_wndTabs.Create (CBCGPTabWnd::STYLE_3D_VS2005, RectTab, this, 1, CBCGPBaseTabWnd::LOCATION_TOP))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}
	m_wndTabs.GetClientRect(&rectLine);
	//////////////////////////////////////////////////////////////////////////
	m_wndChart[0].Create(rect, &m_wndTabs, DRAW_MODE_LINE, MAXMODE, 300);
	m_wndChart[1].Create(rect, &m_wndTabs, DRAW_MODE_LINE, MAXMODE, 300);
	m_wndChart[2].Create(rect, &m_wndTabs, DRAW_MODE_LINE, MAXMODE, 300);
	m_wndChart[3].Create(rect, &m_wndTabs, DRAW_MODE_LINE, MAXMODE, 300);
	m_wndChart[4].Create(rect, &m_wndTabs, DRAW_MODE_LINE, MAXMODE, 300);
	m_wndChart[5].Create(rect, &m_wndTabs, DRAW_MODE_LINE, MAXMODE, 300);
	//
	m_wndChart[0].SetTitle("经纬曲线图");
	m_wndChart[0].SetUintDotSpanX("度(°)");
	m_wndChart[0].SetUintDotSpanY("度(°)");
	m_wndChart[0].SetAxisNumSumAfterDotX(6);
	m_wndChart[0].SetAxisNumSumAfterDotY(6);
	//
	m_wndChart[1].SetTitle("纬度曲线图");
	m_wndChart[1].SetUintDotSpanY("度(°)");
	m_wndChart[1].SetAxisNumSumAfterDotY(6);
	//
	m_wndChart[2].SetTitle("经度曲线图");
	m_wndChart[2].SetUintDotSpanY("度(°)");
	m_wndChart[2].SetAxisNumSumAfterDotY(6);
	//
	m_wndChart[3].SetTitle("高程曲线图");
	m_wndChart[3].SetUintDotSpanY("米(m)");
	m_wndChart[3].SetAxisNumSumAfterDotY(6);
	//
	m_wndChart[4].SetTitle("水平速度曲线图");
	m_wndChart[4].SetUintDotSpanY("m/s");
	m_wndChart[4].SetAxisNumSumAfterDotY(6);
	//
	m_wndChart[5].SetTitle("垂直速度曲线图");
	m_wndChart[5].SetUintDotSpanY("m/s");
	m_wndChart[5].SetAxisNumSumAfterDotY(6);
	for (i=0; i<6; i++)
	{
		m_wndChart[i].SetChName(0, "终端机定位");
		for (j=1; j<MAXMODE; j++)
		{
			m_wndChart[i].SetChName(j, strMODE[j]);
		}
	}

	m_wndTabs.AddTab(&m_wndChart[0], "经纬曲线图");
	m_wndTabs.AddTab(&m_wndChart[1], "纬度曲线图");
	m_wndTabs.AddTab(&m_wndChart[2], "经度曲线图");
	m_wndTabs.AddTab(&m_wndChart[3], "高程曲线图");
	m_wndTabs.AddTab(&m_wndChart[4], "水平速度曲线图");
	m_wndTabs.AddTab(&m_wndChart[5], "垂直速度曲线图");

	return 0;
}

void CDrawXpvView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}

void CDrawXpvView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("上位机定位曲线");
}
void CDrawXpvView::Clear(void)
{
	EnterCriticalSection(&m_BufferCriticalSection);
	LeaveCriticalSection(&m_BufferCriticalSection);
}
void CDrawXpvView::OnClickLock()
{
	m_bLock = !m_bLock;
}
void CDrawXpvView::OnUpdateLock(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bLock);
}
void CDrawXpvView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	EnterCriticalSection(&m_BufferCriticalSection);
	LeaveCriticalSection(&m_BufferCriticalSection);

	if(data->buffer)
		free(data->buffer);
}
