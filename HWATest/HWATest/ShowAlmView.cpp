// ShowAlmView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowAlmView.h"


CString strAlm[MAXALM] = {"WNa", "health", "toa", "ecc", "δi", "sqrta", "Ω0", "Ωdot", "ω", "m0", "af0", "af1"};
// CShowAlmView

IMPLEMENT_DYNCREATE(CShowAlmView, CHWATestView)

CShowAlmView::CShowAlmView()
{
	m_nSvId = 1;
	m_bLock = false;
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CShowAlmView::~CShowAlmView()
{
	m_nSvId = 1;
	m_bLock = false;
	//m_listCtrl.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CShowAlmView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_ALM_ID, OnChangeSvID)
	ON_CBN_SELENDOK(IDR_ALM_ID, OnChangeSvID)
	ON_COMMAND(IDR_ALM_CLEAR, OnClearView)
	ON_UPDATE_COMMAND_UI(IDR_ALM_CLEAR, OnUpdateClearView)
	ON_COMMAND(IDR_ALM_LOCK, OnLockView)
	ON_UPDATE_COMMAND_UI(IDR_ALM_LOCK, OnUpdateLockView)
END_MESSAGE_MAP()


// CShowAlmView drawing 

void CShowAlmView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CShowAlmView diagnostics

#ifdef _DEBUG
void CShowAlmView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowAlmView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowAlmView message handlers
void CShowAlmView::OnChangeSvID() 
{
	CBCGPToolbarComboBoxButton* pCombobox = DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton,
		m_wndToolBar.GetButton (m_wndToolBar.CommandToIndex (IDR_ALM_ID)));
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	InitColumn();
	m_nSvId = pCombobox->GetCurSel()+1;
	LeaveCriticalSection(&m_BufferCriticalSection);
	//BCGPMessageBox("测试");m_nPosType
}


int CShowAlmView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CHWATestView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect (&rect);	
	// TODO:  Add your specialized creation code here m_colorCtrl
	int i = 0;
	CString str;
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create  !m_wndToolBar.LoadToolBar(IDR_DRAW_RAN_TOOLBAR)
	}
	m_wndToolBar.LoadToolBar(IDR_ALM_TOOLBAR);
	m_wndToolBar.ReplaceButton (IDR_ALM_ID_LABEL, CToolbarLabel(IDR_ALM_ID_LABEL, _T("卫星编号: ")));

	CBCGPToolbarComboBoxButton comboID (IDR_ALM_ID, CImageHash::GetImageOfCommand (IDR_ALM_ID, FALSE), CBS_DROPDOWNLIST);
	for (i=0; i<64; i++)//
	{
		str.Format("%02d", i+1);
		comboID.AddItem (str);
	}
	comboID.SelectItem(0);
	m_wndToolBar.ReplaceButton (IDR_ALM_ID, comboID);

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
void CShowAlmView::InitColumn()
{
	int i=0;
	CString str;
	int count = m_listCtrl.GetHeaderCtrl().GetItemCount();
	for (int i=0;i < count;i++)
	{
		m_listCtrl.DeleteColumn(0);
	}
	m_listCtrl.InsertColumn(0, "参数名称", LVCFMT_LEFT, 80, -1);
	for(i=1; i<MAXFREQ+1; i++)
	{
		m_listCtrl.InsertColumn(i, strFREQ[i-1], LVCFMT_LEFT, 120, -1);
	}
	m_listCtrl.InsertColumn(MAXFREQ+1, "描述", LVCFMT_LEFT, 200, -1);
	for (i= 0; i<MAXALM; i++)//
	{
		m_listCtrl.InsertItem(i, strAlm[i]);
	}
}
void CShowAlmView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listCtrl.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CShowAlmView::RefreshView(BD2_ALM* data)
{
	int id = 0;
	CString str;
	id = data->id;
	int item = BranchToitem(data->branch)+1;
	if(item == 0 || m_nSvId != id)
		return;

	try
	{
		str.Format("%d", data->week);
		m_listCtrl.SetItemText(0, item, str);
		str.Format("%d", data->health);
		m_listCtrl.SetItemText(1, item, str);
		str.Format("%d", data->toa);
		m_listCtrl.SetItemText(2, item, str);
		str.Format("%.8e", data->e);
		m_listCtrl.SetItemText(3, item, str);
		str.Format("%.8e", data->sigma);
		m_listCtrl.SetItemText(4, item, str);
		str.Format("%.8e", data->sqrta);
		m_listCtrl.SetItemText(5, item, str);
		str.Format("%.8e", data->omega0);
		m_listCtrl.SetItemText(6, item, str);
		str.Format("%.8e", data->omegadot);
		m_listCtrl.SetItemText(7, item, str);
		str.Format("%.8e", data->w);
		m_listCtrl.SetItemText(8, item, str);
		str.Format("%.8e", data->m0);
		m_listCtrl.SetItemText(9, item, str);
		str.Format("%.8e", data->af0);
		m_listCtrl.SetItemText(10, item, str);
		str.Format("%.8e", data->af1);
		m_listCtrl.SetItemText(11, item, str);
	}
	catch (...)
	{
	}
}

void CShowAlmView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("卫星历书");
}
void CShowAlmView::Clear()
{
	OnClearView();
}
void CShowAlmView::OnClearView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	InitColumn();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowAlmView::OnUpdateClearView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CShowAlmView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	BD2_ALM* alm = new BD2_ALM;
	memcpy(alm, data->buffer, sizeof(BD2_ALM));
	EnterCriticalSection(&m_BufferCriticalSection);
	if (!m_bLock)
	{
		RefreshView(alm);
	}
	LeaveCriticalSection(&m_BufferCriticalSection);
	delete alm;
}

void CShowAlmView::OnLockView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bLock = !m_bLock;
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowAlmView::OnUpdateLockView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bLock);
}

