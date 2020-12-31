// ShowIonView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowIonView.h"


CString strIon[MAXION] = {"week","tow","A1", "B", "α0", "α1", "α2", "α3", "β0", "β1", "β2", "β3", "γ0", "γ1", "γ2", "γ3","af1", "af2", "af3", "af4", "af5", "af6", "af7", "af8", "af9"};
// CShowIonView

IMPLEMENT_DYNCREATE(CShowIonView, CHWATestView)

CShowIonView::CShowIonView()
: m_nSvId(1)
{
	m_bLock = false;
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CShowIonView::~CShowIonView()
{
	m_bLock = false;
	//m_listCtrl.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CShowIonView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_ION_ID, OnChangeSvID)
	ON_CBN_SELENDOK(IDR_ION_ID, OnChangeSvID)
	ON_COMMAND(IDR_ION_CLEAR, OnClearView)
	ON_UPDATE_COMMAND_UI(IDR_ION_CLEAR, OnUpdateClearView)
	ON_COMMAND(IDR_ION_LOCK, OnLockView)
	ON_UPDATE_COMMAND_UI(IDR_ION_LOCK, OnUpdateLockView)
END_MESSAGE_MAP()


// CShowIonView drawing

void CShowIonView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CShowIonView diagnostics

#ifdef _DEBUG
void CShowIonView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowIonView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowIonView message handlers
void CShowIonView::OnChangeSvID() 
{
	CBCGPToolbarComboBoxButton* pCombobox = DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton,
		m_wndToolBar.GetButton (m_wndToolBar.CommandToIndex (IDR_ION_ID)));
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	InitColumn();
	m_nSvId = pCombobox->GetCurSel() + 1;
	LeaveCriticalSection(&m_BufferCriticalSection);
	//BCGPMessageBox("测试");m_nPosType
}


int CShowIonView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	m_wndToolBar.LoadToolBar(IDR_ION_TOOLBAR);
	m_wndToolBar.ReplaceButton (IDR_ION_ID_LABEL, CToolbarLabel(IDR_ION_ID_LABEL, _T("卫星编号: ")));

	CBCGPToolbarComboBoxButton comboID (IDR_ION_ID, CImageHash::GetImageOfCommand (IDR_ION_ID, FALSE), CBS_DROPDOWNLIST);
	for (i=0; i<64; i++)//
	{
		str.Format("%02d", i+1);
		comboID.AddItem (str);
	}
	comboID.SelectItem(0);
	m_wndToolBar.ReplaceButton (IDR_ION_ID, comboID);

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
void CShowIonView::InitColumn()
{
	int i=0;
	CString str;
	int count = m_listCtrl.GetHeaderCtrl().GetItemCount();
	for (int i=0;i < count;i++)
	{
		m_listCtrl.DeleteColumn(0);
	}
	m_listCtrl.InsertColumn(0, "参数名称", LVCFMT_LEFT, 60, -1);
	for(i=1; i<MAXFREQ+1; i++)
	{
		m_listCtrl.InsertColumn(i, strFREQ[i-1], LVCFMT_LEFT, 120, -1);
	}
	m_listCtrl.InsertColumn(MAXFREQ+1, "描述", LVCFMT_LEFT, 200, -1);
	for (i= 0; i<MAXION; i++)//
	{
		m_listCtrl.InsertItem(i, strIon[i]);
	}
}
void CShowIonView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listCtrl.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CShowIonView::RefreshView(BD2_ION* data)
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
		str.Format("%.0f", data->tow);
		m_listCtrl.SetItemText(1, item, str);
		str.Format("%.8e", data->A1);
		m_listCtrl.SetItemText(2, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%.8e", data->B);
		m_listCtrl.SetItemText(3, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%.8e", data->alpha0);
		m_listCtrl.SetItemText(4, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%.8e", data->alpha1);
		m_listCtrl.SetItemText(5, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%.8e", data->alpha2);
		m_listCtrl.SetItemText(6, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%.8e", data->alpha3);
		m_listCtrl.SetItemText(7, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%.8e", data->beta0);
		m_listCtrl.SetItemText(8, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%.8e", data->beta1);
		m_listCtrl.SetItemText(9, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%.8e", data->beta2);
		m_listCtrl.SetItemText(10, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%.8e", data->beta3);
		m_listCtrl.SetItemText(11, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%.8e", data->gamma0);
		m_listCtrl.SetItemText(12, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%.8e", data->gamma1);
		m_listCtrl.SetItemText(13, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%.8e", data->gamma2);
		m_listCtrl.SetItemText(14, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%.8e", data->gamma3);
		m_listCtrl.SetItemText(15, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%.8e", data->af1);
		m_listCtrl.SetItemText(16, item, (data->system == SYSTEM_BD2)?str:"-");
		str.Format("%.8e", data->af2);
		m_listCtrl.SetItemText(17, item, (data->system == SYSTEM_BD2)?str:"-");
		str.Format("%.8e", data->af3);
		m_listCtrl.SetItemText(18, item, (data->system == SYSTEM_BD2)?str:"-");
		str.Format("%.8e", data->af4);
		m_listCtrl.SetItemText(19, item, (data->system == SYSTEM_BD2)?str:"-");
		str.Format("%.8e", data->af5);
		m_listCtrl.SetItemText(20, item, (data->system == SYSTEM_BD2)?str:"-");
		str.Format("%.8e", data->af6);
		m_listCtrl.SetItemText(21, item, (data->system == SYSTEM_BD2)?str:"-");
		str.Format("%.8e", data->af7);
		m_listCtrl.SetItemText(22, item, (data->system == SYSTEM_BD2)?str:"-");
		str.Format("%.8e", data->af8);
		m_listCtrl.SetItemText(23, item, (data->system == SYSTEM_BD2)?str:"-");
		str.Format("%.8e", data->af9);
		m_listCtrl.SetItemText(24, item, (data->system == SYSTEM_BD2)?str:"-");
	}
	catch (...)
	{
	}
}

void CShowIonView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("电离层信息");
}

void CShowIonView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	BD2_ION* ion = new BD2_ION;
	memcpy(ion, data->buffer, sizeof(BD2_ION));
	EnterCriticalSection(&m_BufferCriticalSection);
	if (!m_bLock)
	{
		RefreshView(ion);
	}
	LeaveCriticalSection(&m_BufferCriticalSection);
	delete ion;
}
void CShowIonView::Clear()
{
	OnClearView();
}
void CShowIonView::OnClearView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	InitColumn();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowIonView::OnUpdateClearView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CShowIonView::OnLockView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bLock = !m_bLock;
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowIonView::OnUpdateLockView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bLock);
}


