// ShowPosView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowPosView.h"


// CShowPosView

IMPLEMENT_DYNCREATE(CShowPosView, CHWATestView)

CShowPosView::CShowPosView()
: m_nPosType(0)
{
	m_bLock = false;
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CShowPosView::~CShowPosView()
{
	m_bLock = false;
	//m_listCtrl.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CShowPosView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_POS_CLEAR, OnClearView)
	ON_UPDATE_COMMAND_UI(IDR_POS_CLEAR, OnUpdateClearView)
	ON_COMMAND(IDR_POS_LOCK, OnLockView)
	ON_UPDATE_COMMAND_UI(IDR_POS_LOCK, OnUpdateLockView)
END_MESSAGE_MAP()


// CShowPosView drawing

void CShowPosView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CShowPosView diagnostics

#ifdef _DEBUG
void CShowPosView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowPosView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowPosView message handlers
int CShowPosView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CHWATestView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect (&rect);	
	// TODO:  Add your specialized creation code here
	int i = 0;
	CString str;
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create  !m_wndToolBar.LoadToolBar(IDR_DRAW_RAN_TOOLBAR)
	}
	m_wndToolBar.LoadToolBar(IDR_POS_TOOLBAR);

	dwStyle = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL|LVS_REPORT;
	CRect chartRect(rect.left,rect.top+30,rect.Width (),rect.Height()-30);
	m_listCtrl.m_bVisualManagerStyle = true;
	if (!m_listCtrl.Create(dwStyle, chartRect, this, 1))
	{
		TRACE0("未能创建列表窗口\n");
		return -1;      // 未能创建
	}
	/*m_listCtrl.SetBkColor(RGB(227,239,255));
	m_listCtrl.SetTextBkColor(RGB(227,239,255));
	m_listCtrl.SetTextColor(RGB(0,0,255));*/
	dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER;// | LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_listCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.SetExtendedStyle(dwStyle);
	InitColumn();

	return 0;
}
void CShowPosView::InitColumn()
{
	m_listCtrl.InsertColumn(0, "周数/周内秒", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(1, "解算模式", LVCFMT_LEFT, 60, -1);
	m_listCtrl.InsertColumn(2, "跟踪卫星数", LVCFMT_LEFT, 70, -1);
	m_listCtrl.InsertColumn(3, "可用卫星数", LVCFMT_LEFT, 70, -1);
	m_listCtrl.InsertColumn(4, "纬度(度)", LVCFMT_LEFT, 100, -1);
	m_listCtrl.InsertColumn(5, "经度(度)", LVCFMT_LEFT, 100, -1);
	m_listCtrl.InsertColumn(6, "高程(m)", LVCFMT_LEFT, 80, -1);
	m_listCtrl.InsertColumn(7, "水平速度(m/s)", LVCFMT_LEFT, 100, -1);
	m_listCtrl.InsertColumn(8, "垂直速度(m/s)", LVCFMT_LEFT, 100, -1);
	m_listCtrl.InsertColumn(9, "本地钟差(ns)", LVCFMT_LEFT, 100, -1);
	m_listCtrl.InsertColumn(10, "HDOP", LVCFMT_LEFT, 50, -1);
	m_listCtrl.InsertColumn(11, "VDOP", LVCFMT_LEFT, 50, -1);
	m_listCtrl.InsertColumn(12, "PDOP", LVCFMT_LEFT, 50, -1);
	m_listCtrl.InsertColumn(13, "TDOP", LVCFMT_LEFT, 50, -1);
	m_listCtrl.InsertColumn(14, "GDOP", LVCFMT_LEFT, 50, -1);
	m_listCtrl.InsertColumn(15, "解算使用的卫星号", LVCFMT_LEFT, 250, -1);
}

void CShowPosView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listCtrl.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CShowPosView::RefreshView(BD2_POS* data)
{
	int i=0, index=0;
	CString str,strTemp;
	if (m_listCtrl.GetItemCount() > MAX_LINE)
	{
		m_listCtrl.DeleteAllItems();
	}
	index = ModeToItem(data->mode);
	try
	{
		str.Format("%d/%.1f", data->week, data->tow);
		m_listCtrl.InsertItem(0, str);
		str.Format("%s", (index > 25)?"无解算":strMODE[index]);
		m_listCtrl.SetItemText(0, 1, str);
		str.Format("%02d", data->num);
		m_listCtrl.SetItemText(0, 2, str);
		str.Format("%02d", data->numuse);
		m_listCtrl.SetItemText(0, 3, str);
		str.Format("%.8f", data->blh.lat);
		m_listCtrl.SetItemText(0, 4, str);
		str.Format("%.8f", data->blh.lon);
		m_listCtrl.SetItemText(0, 5, str);
		str.Format("%.3f", data->blh.alt);
		m_listCtrl.SetItemText(0, 6, str);
		str.Format("%.3f", data->speed.x);
		m_listCtrl.SetItemText(0, 7, str);
		str.Format("%.3f", data->speed.y);
		m_listCtrl.SetItemText(0, 8, str);
		str.Format("%.1f", data->clock);
		m_listCtrl.SetItemText(0, 9, str);
		str.Format("%.1f", data->dop.hdop);
		m_listCtrl.SetItemText(0, 10, str);
		str.Format("%.1f", data->dop.vdop);
		m_listCtrl.SetItemText(0, 11, str);
		str.Format("%.1f", data->dop.pdop);
		m_listCtrl.SetItemText(0, 12, str);
		str.Format("%.1f", data->dop.tdop);
		m_listCtrl.SetItemText(0, 13, str);
		str.Format("%.1f", data->dop.gdop);
		m_listCtrl.SetItemText(0, 14, str);
		str = "";
		for (i=0; i<data->numuse; i++)
		{
			index = data->Ids[i];
			strTemp.Format("%02d,", index);
			str += strTemp;
		}
		m_listCtrl.SetItemText(0, 15, str);
	}
	catch (...)
	{
	}
}

void CShowPosView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("终端定位");
}

void CShowPosView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	BD2_POS* pos = new BD2_POS;
	memcpy(pos, data->buffer, sizeof(BD2_POS));
	EnterCriticalSection(&m_BufferCriticalSection);
	if (!m_bLock)
	{
		RefreshView(pos);
	}
	LeaveCriticalSection(&m_BufferCriticalSection);
	delete pos;
}
void CShowPosView::Clear()
{
	OnClearView();
}
void CShowPosView::OnClearView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowPosView::OnUpdateClearView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CShowPosView::OnLockView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bLock = !m_bLock;
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowPosView::OnUpdateLockView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bLock);
}

