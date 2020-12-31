// ShowXpvView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowXpvView.h"


// CShowXpvView
CString strLabels[] = {"定位模式", "周数/周内秒", "跟踪卫星", "可用卫星", "纬度(度)", "经度(度)", "高程(m)", "水平速度(m/s)", "垂直速度(m/s)", "本地钟差(ns)", "HDOP", "VDOP","PDOP", "TDOP", "GDOP", "使用卫星"};
IMPLEMENT_DYNCREATE(CShowXpvView, CHWATestView)

CShowXpvView::CShowXpvView()
{
	m_bLock = false;
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CShowXpvView::~CShowXpvView()
{
	m_bLock = false;
	//m_listCtrl.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CShowXpvView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_XPV_CLEAR, OnClearView)
	ON_UPDATE_COMMAND_UI(IDR_XPV_CLEAR, OnUpdateClearView)
	ON_COMMAND(IDR_XPV_LOCK, OnLockView)
	ON_UPDATE_COMMAND_UI(IDR_XPV_LOCK, OnUpdateLockView)
END_MESSAGE_MAP()


// CShowXpvView drawing

void CShowXpvView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CShowXpvView diagnostics

#ifdef _DEBUG
void CShowXpvView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowXpvView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowXpvView message handlers

int CShowXpvView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CHWATestView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	int i = 0;
	CRect rect;
	GetClientRect (&rect);	
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create  !m_wndToolBar.LoadToolBar(IDR_DRAW_RAN_TOOLBAR)
	}
	m_wndToolBar.LoadToolBar(IDR_XPV_TOOLBAR);

	m_listCtrl.m_bVisualManagerStyle = true;
	dwStyle = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL|LVS_REPORT;
	CRect chartRect(rect.left,rect.top+30,rect.Width (),rect.Height()-30);
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
	m_listCtrl.InsertColumn(0, strLabels[0], LVCFMT_LEFT, 70, -1);//
	m_listCtrl.InsertColumn(1, strLabels[1], LVCFMT_LEFT, 100, -1);//
	m_listCtrl.InsertColumn(2, strLabels[2], LVCFMT_LEFT, 60, -1);
	m_listCtrl.InsertColumn(3, strLabels[3], LVCFMT_LEFT, 60, -1);
	m_listCtrl.InsertColumn(4, strLabels[4], LVCFMT_LEFT, 100, -1);
	m_listCtrl.InsertColumn(5, strLabels[5], LVCFMT_LEFT, 100, -1);
	m_listCtrl.InsertColumn(6, strLabels[6], LVCFMT_LEFT, 80, -1);
	m_listCtrl.InsertColumn(7, strLabels[7], LVCFMT_LEFT, 100, -1);
	m_listCtrl.InsertColumn(8, strLabels[8], LVCFMT_LEFT, 100, -1);
	m_listCtrl.InsertColumn(9, strLabels[9], LVCFMT_LEFT, 100, -1);
	m_listCtrl.InsertColumn(10, strLabels[10], LVCFMT_LEFT, 50, -1);
	m_listCtrl.InsertColumn(11, strLabels[11], LVCFMT_LEFT, 50, -1);
	m_listCtrl.InsertColumn(12, strLabels[12], LVCFMT_LEFT, 50, -1);
	m_listCtrl.InsertColumn(13, strLabels[13], LVCFMT_LEFT, 50, -1);
	m_listCtrl.InsertColumn(14, strLabels[14], LVCFMT_LEFT, 50, -1);
	m_listCtrl.InsertColumn(15, strLabels[15], LVCFMT_LEFT, 250, -1);
	InitListCtrl();

	return 0;
}
void CShowXpvView::InitListCtrl()// 
{
	int i = 0;
	for (i=0; i<MAXMODE; i++)
	{
		m_listCtrl.InsertItem(i, strMODE[i]);
	}
}
void CShowXpvView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listCtrl.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CShowXpvView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("上位机定位");
}

void CShowXpvView::RefreshView(BD2_POS* data, int type)
{
	int item = 0, id = 0;
	CString str,strTemp;
	item = ModeToItem(data->mode);
	if(item == -1 || item > 20)
		return;
	try
	{
		str.Format("%d/%.1f", data->week, data->tow);
		m_listCtrl.SetItemText(item, 1, str);
		str.Format("%d", data->num);
		m_listCtrl.SetItemText(item, 2, str);
		str.Format("%d", data->numuse);
		m_listCtrl.SetItemText(item, 3, str);
		str.Format("%.8f", data->blh.lat);
		m_listCtrl.SetItemText(item, 4, str);
		str.Format("%.8f", data->blh.lon);
		m_listCtrl.SetItemText(item, 5, str);
		str.Format("%.3f", data->blh.alt);
		m_listCtrl.SetItemText(item, 6, str);
		str.Format("%.3f", data->speed.x);
		m_listCtrl.SetItemText(item, 7, str);
		str.Format("%.3f", data->speed.y);
		m_listCtrl.SetItemText(item, 8, str);
		str.Format("%.1f", data->clock);
		m_listCtrl.SetItemText(item, 9, str);
		str.Format("%.1f", data->dop.hdop);
		m_listCtrl.SetItemText(item, 10, str);
		str.Format("%.1f", data->dop.vdop);
		m_listCtrl.SetItemText(item, 11, str);
		str.Format("%.1f", data->dop.pdop);
		m_listCtrl.SetItemText(item, 12, str);
		str.Format("%.1f", data->dop.tdop);
		m_listCtrl.SetItemText(item, 13, str);
		str.Format("%.1f", data->dop.gdop);
		m_listCtrl.SetItemText(item, 14, str);
		str.Empty();
		for (int i=0; i<data->numuse; i++)
		{
			id = data->Ids[i];
			strTemp.Format("%02d,", id);
			str += strTemp;
		}
		m_listCtrl.SetItemText(item, 15, str);
	}
	catch (...)
	{
		
	}
}
void CShowXpvView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	BD2_POS* pos = new BD2_POS;
	memcpy(pos, data->buffer, sizeof(BD2_POS));
	EnterCriticalSection(&m_BufferCriticalSection);
	if (!m_bLock)
	{
		RefreshView(pos, type);
	}
	LeaveCriticalSection(&m_BufferCriticalSection);
	delete pos;
}
void CShowXpvView::Clear()
{
	OnClearView();
}
void CShowXpvView::OnClearView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	InitListCtrl();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowXpvView::OnUpdateClearView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CShowXpvView::OnLockView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bLock = !m_bLock;
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowXpvView::OnUpdateLockView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bLock);
}
