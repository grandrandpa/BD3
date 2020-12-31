// ShowSivView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowSivView.h"


// CShowSivView

IMPLEMENT_DYNCREATE(CShowSivView, CHWATestView)

CShowSivView::CShowSivView()
: m_nBranch(0)
{
	m_bLock = false;
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CShowSivView::~CShowSivView()
{
	m_bLock = false;
	//m_listCtrl.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CShowSivView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_SIV_CLEAR, &CShowSivView::OnClearView)
	ON_UPDATE_COMMAND_UI(IDR_SIV_CLEAR, &CShowSivView::OnUpdateClearView)
	ON_COMMAND(IDR_SIV_LOCK, OnLockView)
	ON_UPDATE_COMMAND_UI(IDR_SIV_LOCK, OnUpdateLockView)
END_MESSAGE_MAP()


// CShowSivView drawing

void CShowSivView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CShowSivView diagnostics

#ifdef _DEBUG
void CShowSivView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowSivView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowSivView message handlers

int CShowSivView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CHWATestView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	int i = 0; 
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create  !m_wndToolBar.LoadToolBar(IDR_DRAW_RAN_TOOLBAR)
	}
	m_wndToolBar.LoadToolBar(IDR_SIV_TOOLBAR);
	//m_wndToolBar.ReplaceButton (IDR_SIV_TIM, CToolbarLabel(IDR_SIV_TIM, _T("当前时刻：2015/08/08 16:21:35")));

	dwStyle = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL|LVS_REPORT;
	m_listCtrl.m_bVisualManagerStyle = true;
	if (!m_listCtrl.Create(dwStyle, CRect(rectDummy.left, rectDummy.top+30, rectDummy.right, rectDummy.bottom-30), this, 1))
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
	m_listCtrl.InsertColumn(0, "序号", LVCFMT_CENTER, 60, -1);
	m_listCtrl.InsertColumn(1, "卫星号", LVCFMT_CENTER, 100, -1);
	m_listCtrl.InsertColumn(2, "仰角(度)", LVCFMT_CENTER, 100, -1);
	m_listCtrl.InsertColumn(3, "方位角(度)", LVCFMT_CENTER, 100, -1);
	m_listCtrl.InsertColumn(4, "信号强度(dBHz/dBm)", LVCFMT_CENTER, 120, -1);

	return 0;
}

void CShowSivView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listCtrl.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CShowSivView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("卫星信息");
}

void CShowSivView::OnChangeBranch() 
{
	CBCGPToolbarComboBoxButton* pCombobox = DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton,
		m_wndToolBar.GetButton (m_wndToolBar.CommandToIndex (IDR_SIV_BRANCH)));
	EnterCriticalSection(&m_BufferCriticalSection);
	m_nBranch = pCombobox->GetCurSel();
	LeaveCriticalSection(&m_BufferCriticalSection);
	//BCGPMessageBox("测试");m_nPosType
}
void CShowSivView::Clear()
{
	OnClearView();
}
void CShowSivView::OnClearView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowSivView::OnUpdateClearView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CShowSivView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	BD2_GSV* result = new BD2_GSV;
	memcpy(result, data->buffer, sizeof(BD2_GSV));
	EnterCriticalSection(&m_BufferCriticalSection);
	if (!m_bLock)
	{
		RefreshView(result);
	}
	LeaveCriticalSection(&m_BufferCriticalSection);
	delete result;
}

void CShowSivView::RefreshView(BD2_GSV* data)
{
	int id = 0;
	CString str;
	int count = data->num;
	try
	{
		m_listCtrl.DeleteAllItems();
		for (int i=0; i<count; i++)
		{
			id = data->id[i];
			str.Format("%02d", i);
			m_listCtrl.InsertItem(i, str);
			str.Format("%02d", id);
			m_listCtrl.SetItemText(i, 1, str);
			str.Format("%.1f", data->elv[i]);
			m_listCtrl.SetItemText(i, 2, str);
			str.Format("%.1f", data->azi[i]);
			m_listCtrl.SetItemText(i, 3, str);
			str.Format("%.1f/%.1f", data->snr[i], (data->snr[i]-173));
			m_listCtrl.SetItemText(i, 4, str);
		}
	}
	catch (...)
	{
	}
}

void CShowSivView::OnLockView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bLock = !m_bLock;
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowSivView::OnUpdateLockView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bLock);
}
