// ShowGbsView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowGbsView.h"


// CShowGbsView

IMPLEMENT_DYNCREATE(CShowGbsView, CHWATestView)

CShowGbsView::CShowGbsView()
{
	m_bLock = false;
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CShowGbsView::~CShowGbsView()
{
	m_bLock = false;
	//m_listCtrl.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CShowGbsView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_GBS_CLEAR, OnClear)
	ON_UPDATE_COMMAND_UI(IDR_GBS_CLEAR, OnUpdateClear)
	ON_COMMAND(IDR_GBS_LOCK, OnLockView)
	ON_UPDATE_COMMAND_UI(IDR_GBS_LOCK, OnUpdateLockView)
END_MESSAGE_MAP()


// CShowGbsView drawing

void CShowGbsView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CShowGbsView diagnostics

#ifdef _DEBUG
void CShowGbsView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowGbsView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowGbsView message handlers 

int CShowGbsView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CHWATestView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CRect rect;
	rect.SetRectEmpty();
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create  !m_wndToolBar.LoadToolBar(IDR_DRAW_RAN_TOOLBAR)
	}
	m_wndToolBar.LoadToolBar(IDR_GBS_TOOLBAR);
	CBCGPToolbarButton btnClear(IDR_GBS_CLEAR, CImageHash::GetImageOfCommand (IDR_GBS_CLEAR, FALSE));
	m_wndToolBar.ReplaceButton (IDR_GBS_CLEAR, btnClear);

	dwStyle = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL|LVS_REPORT;
	m_listCtrl.m_bVisualManagerStyle = true;
	CRect Rectlist(rect.left, rect.top+30, rect.Width(), rect.Height()-30);
	if (!m_listCtrl.Create(dwStyle, Rectlist, this, 1))
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
	m_listCtrl.InsertColumn(0, "周计数", LVCFMT_LEFT, 80, -1);
	m_listCtrl.InsertColumn(1, "周内秒", LVCFMT_LEFT, 80, -1);
	m_listCtrl.InsertColumn(2, "纬度值的预计误差", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(3, "经度值的预计误差", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(4, "高度值的预计误差", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(5, "可能故障卫星编号", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(6, "故障卫星漏检概率", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(7, "故障卫星估计偏差", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(8, "偏执估算的标准偏差", LVCFMT_LEFT, 120, -1);

	return 0;
}

void CShowGbsView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listCtrl.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CShowGbsView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("自主完好性");
}
void CShowGbsView::Clear()
{
	OnClear();
}
void CShowGbsView::OnClear() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowGbsView::OnUpdateClear(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CShowGbsView::RefreshView(BD2_GBS* gbs)
{
	int flag=0;
	CString str;
	if (gbs->idErr <=0 || gbs->idErr > 64)
		flag = 1;
	if (m_listCtrl.GetItemCount() > MAX_LINE)
	{
		m_listCtrl.DeleteAllItems();
	}
	try
	{
		str.Format("%d", gbs->week);
		m_listCtrl.InsertItem(0, str);
		str.Format("%.1f", gbs->tow);
		m_listCtrl.SetItemText(0, 1, str);
		str.Format("%.3f", gbs->latErr);
		m_listCtrl.SetItemText(0, 2, flag?"--":str);
		str.Format("%.3f", gbs->lonErr);
		m_listCtrl.SetItemText(0, 3, flag?"--":str);
		str.Format("%.3f", gbs->altErr);
		m_listCtrl.SetItemText(0, 4, flag?"--":str);
		str.Format("%d", gbs->idErr);
		m_listCtrl.SetItemText(0, 5, flag?"--":str);
		str.Format("%.3f", gbs->checkErr);
		m_listCtrl.SetItemText(0, 6, flag?"--":str);
		str.Format("%.3f", gbs->evaluateErr);
		m_listCtrl.SetItemText(0, 7, flag?"--":str);
		str.Format("%.3f", gbs->offset);
		m_listCtrl.SetItemText(0, 8, flag?"--":str);
	}
	catch (...)
	{
	}
	
}

void CShowGbsView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	BD2_GBS* gbs = new BD2_GBS;
	memcpy(gbs, data->buffer, sizeof(BD2_GBS));
	EnterCriticalSection(&m_BufferCriticalSection);
	if (!m_bLock)
	{
		RefreshView(gbs);
	}
	LeaveCriticalSection(&m_BufferCriticalSection);
	delete gbs;
}

void CShowGbsView::OnLockView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bLock = !m_bLock;
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowGbsView::OnUpdateLockView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bLock);
}
