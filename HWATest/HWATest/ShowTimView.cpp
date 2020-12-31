// ShowTimView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowTimView.h"


// CShowTimView

IMPLEMENT_DYNCREATE(CShowTimView, CHWATestView)

CShowTimView::CShowTimView()
{
	m_bLock = false;
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CShowTimView::~CShowTimView()
{
	m_bLock = false;
	//m_listCtrl.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CShowTimView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_TIM_CLEAR, OnClearView)
	ON_UPDATE_COMMAND_UI(IDR_TIM_CLEAR, OnUpdateClearView)
	ON_COMMAND(IDR_TIM_LOCK, OnLockView)
	ON_UPDATE_COMMAND_UI(IDR_TIM_LOCK, OnUpdateLockView)
END_MESSAGE_MAP()


// CShowTimView drawing

void CShowTimView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CShowTimView diagnostics

#ifdef _DEBUG
void CShowTimView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowTimView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG

// CShowTimView message handlers
int CShowTimView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CHWATestView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect (rect);	
	// TODO:  Add your specialized creation code here
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create  !m_wndToolBar.LoadToolBar(IDR_DRAW_RAN_TOOLBAR)
	}
	m_wndToolBar.LoadToolBar(IDR_TIM_TOOLBAR);

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

	m_listCtrl.InsertColumn(0, "周数/周内秒", LVCFMT_CENTER, 100, -1);
	m_listCtrl.InsertColumn(1, "解算模式", LVCFMT_CENTER, 80, -1);
	m_listCtrl.InsertColumn(2, "授时模式", LVCFMT_CENTER, 80, -1);
	m_listCtrl.InsertColumn(3, "军用标准时间", LVCFMT_CENTER, 200, -1);
	m_listCtrl.InsertColumn(4, "闰秒", LVCFMT_CENTER, 80, -1);
	m_listCtrl.InsertColumn(5, "本地钟差(ns)", LVCFMT_CENTER, 80, -1);
	m_listCtrl.InsertColumn(6, "参与授时卫星", LVCFMT_CENTER, 250, -1);

	return 0;
}

void CShowTimView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listCtrl.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CShowTimView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("授时信息");
}

void CShowTimView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	BD2_TIME* tim = new BD2_TIME;
	memcpy(tim, data->buffer, sizeof(BD2_TIME));
	EnterCriticalSection(&m_BufferCriticalSection);
	if (!m_bLock)
	{
		RefreshView(tim);
	}
	LeaveCriticalSection(&m_BufferCriticalSection);
	delete tim;
}
void CShowTimView::RefreshView(BD2_TIME* tim)
{
	CString str,strTemp;
	int i=0, mode=0, num=0;
	num = tim->num;
	mode = ModeToItem(tim->posMod);
	try
	{
		if (m_listCtrl.GetItemCount() > MAX_LINE)
		{
			m_listCtrl.DeleteAllItems();
		}
		str.Format("%d/%.1f", tim->week, tim->tow);
		m_listCtrl.InsertItem(0, str);
		str.Format("%s", (mode == -1)?"NONE":strMODE[mode]);
		m_listCtrl.SetItemText(0, 1, str);
		str.Format("%s", (tim->timMod == 0)?"单星授时":((tim->timMod == 1)?"定点授时":"普通授时"));
		m_listCtrl.SetItemText(0, 2, str);
		str.Format("%04d/%02d/%02d-%02d:%02d:%02d", tim->year, tim->month, tim->day, tim->hour, tim->minute, tim->second);
		m_listCtrl.SetItemText(0, 3, str);
		str.Format("%02d", tim->Leap);
		m_listCtrl.SetItemText(0, 4, str);
		str.Format("%.1f", tim->clkErr);
		m_listCtrl.SetItemText(0, 5, str);
		str.Empty();
		for (i=0; i<num; i++)
		{
			strTemp.Format("%d,", tim->svId[i]);
			str += strTemp;
		}
		m_listCtrl.SetItemText(0, 6, str);
	}
	catch (...)
	{
	}
}
void CShowTimView::Clear()
{
	OnClearView();
}
void CShowTimView::OnClearView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowTimView::OnUpdateClearView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CShowTimView::OnLockView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bLock = !m_bLock;
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowTimView::OnUpdateLockView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bLock);
}

