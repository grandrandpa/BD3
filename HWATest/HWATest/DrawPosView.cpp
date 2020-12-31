// DrawPosView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "DrawPosView.h"


// CDrawPosView
#define DAY_SECOND 86400
IMPLEMENT_DYNCREATE(CDrawPosView, CHWATestView)

CDrawPosView::CDrawPosView()
: m_nPosType(0)
, m_bLock(false)
{
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CDrawPosView::~CDrawPosView()
{
}

BEGIN_MESSAGE_MAP(CDrawPosView, CHWATestView)//
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_DRAW_POS_CLEAR, Clear)
	ON_CBN_SELENDOK(IDR_DRAW_POS_CLEAR, Clear)
	ON_COMMAND(IDR_DRAW_POS_LOCK, OnClickLock)
	ON_UPDATE_COMMAND_UI(IDR_DRAW_POS_LOCK, OnUpdateLock)
END_MESSAGE_MAP()

void CDrawPosView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CShowAlmView diagnostics

#ifdef _DEBUG
void CDrawPosView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CDrawPosView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG
// CDrawPosView message handlers
int CDrawPosView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CHWATestView::OnCreate(lpCreateStruct) == -1)
		return -1;

	int i=0,j=0;
	CRect rect, rectLine;
	rect.SetRectEmpty();
	// TODO:  Add your specialized creation code here
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create  !m_wndToolBar.LoadToolBar(IDR_DRAW_RAN_TOOLBAR)IDR_DRAW_POS_POINT_LABEL
	}
	m_wndToolBar.LoadToolBar(IDR_DRAW_POS_TOOLBAR);
	m_wndToolBar.ReplaceButton (IDR_TB_DRAW_POS_TIPS, CToolbarLabel(IDR_TB_DRAW_POS_TIPS, _T("DEV: 主机定位，其他为上位机定位")));

	CRect RectTab(rect.left, rect.top+30, rect.Width(), rect.Height()-30);
	if (!m_wndTabs.Create (CBCGPTabWnd::STYLE_3D_VS2005, RectTab, this, 1, CBCGPBaseTabWnd::LOCATION_TOP))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}
	m_wndTabs.GetClientRect(&rectLine);
	//////////////////////////////////////////////////////////////////////////
	m_wndChart[0].Create(rect, &m_wndTabs, DRAW_MODE_POINTS, MAXMODE, 1000);
	m_wndChart[1].Create(rect, &m_wndTabs, DRAW_MODE_LINE, MAXMODE, 300);
	m_wndChart[2].Create(rect, &m_wndTabs, DRAW_MODE_LINE, MAXMODE, 300);
	m_wndChart[3].Create(rect, &m_wndTabs, DRAW_MODE_LINE, MAXMODE, 300);
	m_wndChart[4].Create(rect, &m_wndTabs, DRAW_MODE_LINE, MAXMODE, 300);
	m_wndChart[5].Create(rect, &m_wndTabs, DRAW_MODE_LINE, MAXMODE, 300);
	//
	m_wndChart[0].SetTitle("经纬曲线图");
	m_wndChart[0].SetUintDotSpanX("度(°)");
	m_wndChart[0].SetUintDotSpanY("度(°)");
	m_wndChart[0].SetAxisNumSumAfterDotX(4);
	m_wndChart[0].SetAxisNumSumAfterDotY(6);
	m_wndChart[0].SetYAxisName("纬度");
	m_wndChart[0].SetXAxisName("经度");
	//
	m_wndChart[1].SetTitle("纬度曲线图");
	m_wndChart[1].SetUintDotSpanY("度(°)");
	m_wndChart[1].SetAxisNumSumAfterDotY(6);
	m_wndChart[1].SetYAxisName("纬度");
	m_wndChart[1].SetXAxisName("时间");
	//
	m_wndChart[2].SetTitle("经度曲线图");
	m_wndChart[2].SetUintDotSpanY("度(°)");
	m_wndChart[2].SetAxisNumSumAfterDotY(6);
	m_wndChart[2].SetYAxisName("经度");
	m_wndChart[2].SetXAxisName("时间");
	//
	m_wndChart[3].SetTitle("高程曲线图");
	m_wndChart[3].SetUintDotSpanY("米(m)");
	m_wndChart[3].SetAxisNumSumAfterDotY(6);
	m_wndChart[3].SetYAxisName("高程");
	m_wndChart[3].SetXAxisName("时间");
	//
	m_wndChart[4].SetTitle("水平速度曲线图");
	m_wndChart[4].SetUintDotSpanY("m/s");
	m_wndChart[4].SetAxisNumSumAfterDotY(6);
	m_wndChart[4].SetYAxisName("水平速度");
	m_wndChart[4].SetXAxisName("时间");
	//
	m_wndChart[5].SetTitle("垂直速度曲线图");
	m_wndChart[5].SetUintDotSpanY("m/s");
	m_wndChart[5].SetAxisNumSumAfterDotY(6);
	m_wndChart[5].SetYAxisName("垂直速度");
	m_wndChart[5].SetXAxisName("时间");
	for (i=0; i<6; i++)
	{
		m_wndChart[i].SetChName(0, "主机");
		for (j=0; j<MAXMODE-1; j++)
		{
			m_wndChart[i].SetChName(j+1, strMODE[j]);
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

void CDrawPosView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndTabs.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CDrawPosView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("定位曲线");
}
void CDrawPosView::OnClickLock()
{
	m_bLock = !m_bLock;
	m_wndChart[0].SetVisible(m_bLock);
	m_wndChart[1].SetVisible(m_bLock);
	m_wndChart[2].SetVisible(m_bLock);
	m_wndChart[3].SetVisible(m_bLock);
	m_wndChart[4].SetVisible(m_bLock);
	m_wndChart[5].SetVisible(m_bLock);
}
void CDrawPosView::OnUpdateLock(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bLock);
}

void CDrawPosView::Clear(void)
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_wndChart[0].Clean();
	m_wndChart[1].Clean();
	m_wndChart[2].Clean();
	m_wndChart[3].Clean();
	m_wndChart[4].Clean();
	m_wndChart[5].Clean();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CDrawPosView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	int mode = 0;
	if(m_bLock)
		return;
	BD2_POS* result = new BD2_POS;
	memcpy(result, data->buffer, sizeof(BD2_POS));

	EnterCriticalSection(&m_BufferCriticalSection);
	try
	{
		if (result->flag)//上位机定位
		{
			mode = ModeToItem(result->mode);
			if (mode != -1)
			{
				m_wndChart[0].InsertData(mode+1, result->blh.lon, result->blh.lat);
				m_wndChart[1].InsertData(mode+1, result->blh.lat);
				m_wndChart[2].InsertData(mode+1, result->blh.lon);
				m_wndChart[3].InsertData(mode+1, result->blh.alt);
				m_wndChart[4].InsertData(mode+1, result->speed.x);
				m_wndChart[5].InsertData(mode+1, result->speed.y);
			}
		} 
		else//下位机定位
		{
			m_wndChart[0].InsertData(0, result->blh.lon, result->blh.lat);
			m_wndChart[1].InsertData(0, result->blh.lat);
			m_wndChart[2].InsertData(0, result->blh.lon);
			m_wndChart[3].InsertData(0, result->blh.alt);
			m_wndChart[4].InsertData(0, result->speed.x);
			m_wndChart[5].InsertData(0, result->speed.y);
		}
	}
	catch (...)
	{

	}
	LeaveCriticalSection(&m_BufferCriticalSection);

	/*if(data->buffer)
		free(data->buffer);*/
	delete result;
}

