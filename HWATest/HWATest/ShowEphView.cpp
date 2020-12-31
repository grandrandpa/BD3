// ShowEphView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowEphView.h"


CString strEph[MAXEPH] = {"week","tow","rootA", "Δa", "adot", "Δn", "ndot", "iode", "toe", "m0", "ecc", "ω", "omega0", "i0", "omegadot", "idot", "cis", "cic", "crs", "crc", "cus", "cuc", "iodc", "toc", "a0", "a1", "a2", "tgd1", "tgd2", "tgd3"};

// CShowEphView

IMPLEMENT_DYNCREATE(CShowEphView, CHWATestView)

CShowEphView::CShowEphView()
: m_nSvId(1)
{
	m_bLock = false;
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CShowEphView::~CShowEphView()
{
	m_bLock = false;
	//m_listCtrl.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CShowEphView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_EPH_ID, OnChangeSvID)
	ON_CBN_SELENDOK(IDR_EPH_ID, OnChangeSvID)
	ON_COMMAND(IDR_EPH_CLEAR, OnClearView)
	ON_UPDATE_COMMAND_UI(IDR_EPH_CLEAR, OnUpdateClearView)
	ON_COMMAND(IDR_EPH_LOCK, OnLockView)
	ON_UPDATE_COMMAND_UI(IDR_EPH_LOCK, OnUpdateLockView)
END_MESSAGE_MAP()


// CShowEphView drawing

void CShowEphView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CShowEphView diagnostics

#ifdef _DEBUG
void CShowEphView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowEphView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowEphView message handlers
void CShowEphView::OnChangeSvID() 
{
	CBCGPToolbarComboBoxButton* pCombobox = DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton,
		m_wndToolBar.GetButton (m_wndToolBar.CommandToIndex (IDR_EPH_ID)));
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	InitColumn();
	m_nSvId = pCombobox->GetCurSel() + 1;
	LeaveCriticalSection(&m_BufferCriticalSection);
	//BCGPMessageBox("测试");m_nPosType
}

int CShowEphView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	m_wndToolBar.LoadToolBar(IDR_EPH_TOOLBAR);
	m_wndToolBar.ReplaceButton (IDR_EPH_ID_LABEL, CToolbarLabel(IDR_EPH_ID_LABEL, _T("卫星编号: ")));

	CBCGPToolbarComboBoxButton comboID (IDR_EPH_ID, CImageHash::GetImageOfCommand (IDR_EPH_ID, FALSE), CBS_DROPDOWNLIST);
	for (i=0; i<64; i++)//
	{
		str.Format("%02d", i+1);
		comboID.AddItem (str);
	}
	comboID.SelectItem(0);
	m_wndToolBar.ReplaceButton (IDR_EPH_ID, comboID);

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
void CShowEphView::InitColumn()
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
	for (i= 0; i<MAXEPH; i++)//
	{
		m_listCtrl.InsertItem(i, strEph[i]);
	}
}
void CShowEphView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listCtrl.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CShowEphView::RefreshView(BD2_EPH* data)
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
		str.Format("%0.8e", data->sqrta);
		m_listCtrl.SetItemText(2, item, (data->system == SYSTEM_BD1)?str:"-");
		str.Format("%0.8e", data->deltaA);
		m_listCtrl.SetItemText(3, item, (data->system == SYSTEM_BD2)?str:"-");
		str.Format("%0.8e", data->Adot);
		m_listCtrl.SetItemText(4, item, (data->system == SYSTEM_BD2)?str:"-");
		str.Format("%0.8e", data->deltaN);
		m_listCtrl.SetItemText(5, item, str);
		str.Format("%0.8e", data->Ndot);
		m_listCtrl.SetItemText(6, item, (data->system == SYSTEM_BD2)?str:"-");
		str.Format("%d", data->iode);
		m_listCtrl.SetItemText(7, item, str);
		str.Format("%0.8e", data->toe);
		m_listCtrl.SetItemText(8, item, str);
		str.Format("%0.8e", data->m0);
		m_listCtrl.SetItemText(9, item, str);
		str.Format("%0.8e", data->e);
		m_listCtrl.SetItemText(10, item, str);
		str.Format("%0.8e", data->w);
		m_listCtrl.SetItemText(11, item, str);
		str.Format("%0.8e", data->omega0);
		m_listCtrl.SetItemText(12, item, str);
		str.Format("%0.8e", data->i0);
		m_listCtrl.SetItemText(13, item, str);
		str.Format("%0.8e", data->omegadot);
		m_listCtrl.SetItemText(14, item, str);
		str.Format("%0.8e", data->idot);
		m_listCtrl.SetItemText(15, item, str);
		str.Format("%0.8e", data->cis);
		m_listCtrl.SetItemText(16, item, str);
		str.Format("%0.8e", data->cic);
		m_listCtrl.SetItemText(17, item, str);
		str.Format("%0.8e", data->crs);
		m_listCtrl.SetItemText(18, item, str);
		str.Format("%0.8e", data->crc);
		m_listCtrl.SetItemText(19, item, str);
		str.Format("%0.8e", data->cus);
		m_listCtrl.SetItemText(20, item, str);
		str.Format("%0.8e", data->cuc);
		m_listCtrl.SetItemText(21, item, str);
		str.Format("%d", data->iodc);
		m_listCtrl.SetItemText(22, item, str);
		str.Format("%0.8e", data->toc);
		m_listCtrl.SetItemText(23, item, str);
		str.Format("%0.8e", data->af0);
		m_listCtrl.SetItemText(24, item, str);
		str.Format("%0.8e", data->af1);
		m_listCtrl.SetItemText(25, item, str);
		str.Format("%0.8e", data->af2);
		m_listCtrl.SetItemText(26, item, str);
		str.Format("%0.8e", data->tgd1);
		m_listCtrl.SetItemText(27, item, str);
		str.Format("%0.8e", data->tgd2);
		m_listCtrl.SetItemText(28, item, str);
		str.Format("%0.8e", data->tgd3);
		m_listCtrl.SetItemText(29, item, (data->system == SYSTEM_BD2)?str:"-");
	}
	catch (...)
	{
	}
}
void CShowEphView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("卫星星历");
}

void CShowEphView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	BD2_EPH* eph = new BD2_EPH;
	memcpy(eph, data->buffer, sizeof(BD2_EPH));
	EnterCriticalSection(&m_BufferCriticalSection);
	if (!m_bLock)
	{
		RefreshView(eph);
	}
	LeaveCriticalSection(&m_BufferCriticalSection);
	delete eph;
}
void CShowEphView::Clear()
{
	OnClearView();
}
void CShowEphView::OnClearView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	InitColumn();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowEphView::OnUpdateClearView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CShowEphView::OnLockView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bLock = !m_bLock;
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowEphView::OnUpdateLockView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bLock);
}

