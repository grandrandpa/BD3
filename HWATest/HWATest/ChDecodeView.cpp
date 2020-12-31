//#include "StdAfx.h"
//#include "HWATest.h"
//#include "ChDecodeView.h"
//
//
//
//// ChDecodeView
//
//IMPLEMENT_DYNCREATE(ChDecodeView, CHWATestView)
//
//ChDecodeView::ChDecodeView()
//: m_nBranch(0)
//{
//	m_bLock = false;
//	InitializeCriticalSection(&m_BufferCriticalSection);
//}
//
//ChDecodeView::~ChDecodeView()
//{
//	m_bLock = false;
//	//m_listCtrl.DeleteAllItems();
//}
//
//BEGIN_MESSAGE_MAP(ChDecodeView, CHWATestView)
//	ON_WM_CREATE()
//	ON_WM_SIZE()
//	ON_COMMAND(IDR_RAN_BRANCH, OnChangeBranch)
//	ON_CBN_SELENDOK(IDR_RAN_BRANCH, OnChangeBranch)
//	ON_COMMAND(IDR_RAN_CLEAR, OnClearView)
//	ON_UPDATE_COMMAND_UI(IDR_RAN_CLEAR, OnUpdateClearView)
//	ON_COMMAND(IDR_RAN_LOCK, OnLockView)
//	ON_UPDATE_COMMAND_UI(IDR_RAN_LOCK, OnUpdateLockView)
//END_MESSAGE_MAP()
//
//
//// ChDecodeView drawing
//
//void ChDecodeView::OnDraw(CDC* pDC)
//{
//	CDocument* pDoc = GetDocument();
//	// TODO: add draw code here
//}
//
//
//// ChDecodeView diagnostics
//
//#ifdef _DEBUG
//void ChDecodeView::AssertValid() const
//{
//	CHWATestView::AssertValid();
//}
//
//#ifndef _WIN32_WCE
//void ChDecodeView::Dump(CDumpContext& dc) const
//{
//	CHWATestView::Dump(dc);
//}
//#endif
//#endif //_DEBUG
//
//
//// ChDecodeView message handlers
//void ChDecodeView::OnChangeBranch() 
//{
//	EnterCriticalSection(&m_BufferCriticalSection);
//	CBCGPToolbarComboBoxButton* pCombobox = DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton,
//		m_wndToolBar.GetButton (m_wndToolBar.CommandToIndex (IDR_RAN_BRANCH)));
//	m_listCtrl.DeleteAllItems();
//	m_nBranch = pCombobox->GetCurSel();
//	LeaveCriticalSection(&m_BufferCriticalSection);
//	//BCGPMessageBox("测试");m_nPosType
//}
//
//
//int ChDecodeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CHWATestView::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	CRect rect;
//	GetClientRect (&rect);	
//	// TODO:  Add your specialized creation code here
//	int i = 0;
//	CString str;
//	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
//	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle))
//	{
//		TRACE0("Failed to create toolbar\n");
//		return -1;      // fail to create  !m_wndToolBar.LoadToolBar(IDR_DRAW_RAN_TOOLBAR)
//	}
//	m_wndToolBar.LoadToolBar(IDR_RAN_TOOLBAR);
//	m_wndToolBar.ReplaceButton (IDR_RAN_BRANCH_LABEL, CToolbarLabel(IDR_RAN_BRANCH_LABEL, _T("信号分量: ")));
//
//	CBCGPToolbarComboBoxButton comboBranch (IDR_RAN_BRANCH, CImageHash::GetImageOfCommand (IDR_RAN_BRANCH, FALSE), CBS_DROPDOWNLIST);
//	for (i=0; i<MAXFREQ; i++)//
//	{
//		comboBranch.AddItem (strFREQ[i]);
//	}
//	comboBranch.SelectItem(0);
//	m_wndToolBar.ReplaceButton (IDR_RAN_BRANCH, comboBranch);
//
//	dwStyle = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL|LVS_REPORT;
//	CRect chartRect(rect.left,rect.top+30,rect.Width (),rect.Height()-30);
//	m_listCtrl.m_bVisualManagerStyle = true;
//	if (!m_listCtrl.Create(dwStyle, chartRect, this, 1))
//	{
//		TRACE0("未能创建列表窗口\n");
//		return -1;      // 未能创建
//	}
//	/*m_listCtrl.SetBkColor(RGB(227,239,255));
//	m_listCtrl.SetTextBkColor(RGB(227,239,255));
//	m_listCtrl.SetTextColor(RGB(0,0,255));*/
//	dwStyle = m_listCtrl.GetExtendedStyle();
//	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER;// | LVS_EX_CHECKBOXES;//item前生成checkbox控件
//	m_listCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
//	m_listCtrl.SetExtendedStyle(dwStyle);
//	InitColumn();
//
//	return 0;
//}
//void ChDecodeView::InitColumn()
//{
//	int i = 0;
//	CString str;
//	m_listCtrl.InsertColumn(0, "周计数", LVCFMT_CENTER, 60, -1);
//	m_listCtrl.InsertColumn(1, "周内秒计数", LVCFMT_LEFT, 120, -1);
//	m_listCtrl.InsertColumn(2, "信号分量", LVCFMT_LEFT, 80, -1);
//	m_listCtrl.InsertColumn(3, "卫星编号", LVCFMT_LEFT, 80, -1);
//	m_listCtrl.InsertColumn(4, "电文类型", LVCFMT_LEFT, 80, -1);
//	m_listCtrl.InsertColumn(5, "子帧号或页面类型", LVCFMT_LEFT, 150, -1);
//	m_listCtrl.InsertColumn(6, "信道编码方式", LVCFMT_LEFT, 120, -1);
//	m_listCtrl.InsertColumn(7, "译码是否通过", LVCFMT_LEFT, 100, -1);
//	m_listCtrl.InsertColumn(8, "误码个数", LVCFMT_LEFT, 120, -1);
//}
//void ChDecodeView::OnSize(UINT nType, int cx, int cy)
//{
//	CHWATestView::OnSize(nType, cx, cy);
//
//	// TODO: Add your message handler code here
//	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
//	m_listCtrl.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
//}
//
//void ChDecodeView::RefreshView(BD2_CHD* data)
//{
//	CString str;
//	double temp=0;
//	int id = 0, SvId=0, chId=0;
//	int index = BranchToitem(data->branch);
//	if(index == -1 || m_nBranch != index)
//		return;
//	//int count = data->numuse;
//	try
//	{
//		m_listCtrl.DeleteAllItems();
//
//
//		str.Format("%u", data->week);
//		m_listCtrl.InsertItem(0, str);
//		str.Format("%u", data->tow);
//		m_listCtrl.SetItemText(0, 1, str);
//
//		str.Format("%s", strFREQ[index]);
//		m_listCtrl.SetItemText(0, 2, str);		
//		str.Format("%02d", data->svID);
//		m_listCtrl.SetItemText(0, 3, str);
//
//		str = "";
//		int iNavType = data->NavType;
//		if(iNavType == 0)
//				str = "B-CNAV1";
//		else if(iNavType == 1)
//				str = "B-CNAV2";
//		else if(iNavType == 2)
//				str = "B-CNAV3";
//		else if(iNavType == 3)
//				str = "B-ANAV";
//		else if(iNavType == 4)
//				str = "B-CINAV";
//		else if(iNavType == 5)
//				str = "B-AINAV";
//		m_listCtrl.SetItemText(0, 4, str);
//
//		str.Format("%d", data->SubfameIdorMessType);
//		m_listCtrl.SetItemText(0, 5, str);
//
//
//
//		//信道编码方式
//		str.Empty();
//		unsigned int iResult = (data->Decodeinfo>>5)&0x07;
//		if(iResult == 0)
//				str = "LDPC64(96,48)";
//		else if(iNavType == 1)
//				str = "LDPC64(88,44)";
//		else if(iNavType == 2)
//				str = "LDPC64(200,100)";
//		else if(iNavType == 3)
//				str = "LDPC64(162,81)";
//		else if(iNavType == 4)
//				str = "TURBO(600,300)";
//		m_listCtrl.SetItemText(0, 5, str);
//
//
//		//译码是否通过
//		str.Empty();
//		iResult = (data->Decodeinfo>>4)&0x01;
//		if(iResult == 0)
//				str = "不通过";
//		else if(iNavType == 1)
//				str = "通过";
//		m_listCtrl.SetItemText(0, 7, str);
//
//		//误码个数
//		str.Empty();
//		iResult = (data->Decodeinfo>>0)&0x0F;
//		str.Format("%d", iResult);
//		m_listCtrl.SetItemText(0, 8, str);
//				
//	}
//	catch (...)
//	{
//	}
//}
//void ChDecodeView::OnInitialUpdate()
//{
//	CHWATestView::OnInitialUpdate();
//
//	// TODO: Add your specialized code here and/or call the base class
//	GetParent()->SetWindowText("信道译码信息");
//}
//
//void ChDecodeView::OnUpdateAllViews(CGlobalVariant* data, int type)
//{
//	BD2_CHD* ran = new BD2_CHD;
//	memcpy(ran, data->buffer, sizeof(BD2_CHD));
//	EnterCriticalSection(&m_BufferCriticalSection);
//	if (!m_bLock)
//	{
//		RefreshView(ran);
//	}
//	LeaveCriticalSection(&m_BufferCriticalSection);
//	delete ran;
//}
//void ChDecodeView::Clear()
//{
//	OnClearView();
//}
//void ChDecodeView::OnClearView() 
//{
//	int i = 0;
//	CString str;
//	EnterCriticalSection(&m_BufferCriticalSection);
//	m_listCtrl.DeleteAllItems();
//	LeaveCriticalSection(&m_BufferCriticalSection);
//}
//
//void ChDecodeView::OnUpdateClearView(CCmdUI* pCmdUI) 
//{
//	pCmdUI->Enable(TRUE);
//}
//
//void ChDecodeView::OnLockView() 
//{
//	EnterCriticalSection(&m_BufferCriticalSection);
//	m_bLock = !m_bLock;
//	LeaveCriticalSection(&m_BufferCriticalSection);
//}
//
//void ChDecodeView::OnUpdateLockView(CCmdUI* pCmdUI) 
//{
//	pCmdUI->SetCheck(m_bLock);
//}
//
// ShowAlmView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ChDecodeView.h"


CString strChd[MAXCHD] = {"周计数", "周内秒计数", "电文类型", "子帧号或页面类型", "信道编码方式", "译码是否通过", "误码个数"};
// ChDecodeView

IMPLEMENT_DYNCREATE(ChDecodeView, CHWATestView)

ChDecodeView::ChDecodeView()
{
	m_nSvId = 1;
	m_bLock = false;
	InitializeCriticalSection(&m_BufferCriticalSection);
}

ChDecodeView::~ChDecodeView()
{
	m_nSvId = 1;
	m_bLock = false;
	//m_listCtrl.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(ChDecodeView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_CHD_ID, OnChangeSvID)
	ON_CBN_SELENDOK(IDR_CHD_ID, OnChangeSvID)
	ON_COMMAND(IDR_CHD_CLEAR, OnClearView)
	ON_UPDATE_COMMAND_UI(IDR_CHD_CLEAR, OnUpdateClearView)
	ON_COMMAND(IDR_CHD_LOCK, OnLockView)
	ON_UPDATE_COMMAND_UI(IDR_CHD_LOCK, OnUpdateLockView)
END_MESSAGE_MAP()


// ChDecodeView drawing 

void ChDecodeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// ChDecodeView diagnostics

#ifdef _DEBUG
void ChDecodeView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void ChDecodeView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// ChDecodeView message handlers
void ChDecodeView::OnChangeSvID() 
{
	CBCGPToolbarComboBoxButton* pCombobox = DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton,
		m_wndToolBar.GetButton (m_wndToolBar.CommandToIndex (IDR_CHD_ID)));
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	InitColumn();
	m_nSvId = pCombobox->GetCurSel()+1;
	LeaveCriticalSection(&m_BufferCriticalSection);
	//BCGPMessageBox("测试");m_nPosType
}


int ChDecodeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	m_wndToolBar.LoadToolBar(IDR_CHD_TOOLBAR);
	m_wndToolBar.ReplaceButton (IDR_CHD_ID_LABEL, CToolbarLabel(IDR_CHD_ID_LABEL, _T("卫星编号: ")));

	CBCGPToolbarComboBoxButton comboID (IDR_CHD_ID, CImageHash::GetImageOfCommand (IDR_CHD_ID, FALSE), CBS_DROPDOWNLIST);
	for (i=0; i<64; i++)//
	{
		str.Format("%02d", i+1);
		comboID.AddItem (str);
	}
	comboID.SelectItem(0);
	m_wndToolBar.ReplaceButton (IDR_CHD_ID, comboID);

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
void ChDecodeView::InitColumn()
{
	int i=0;
	CString str;
	int count = m_listCtrl.GetHeaderCtrl().GetItemCount();
	for (int i=0;i < count;i++)
	{
		m_listCtrl.DeleteColumn(0);
	}
	m_listCtrl.InsertColumn(0, "参数名称", LVCFMT_LEFT, 120, -1);
	for(i=1; i<MAXFREQ+1; i++)
	{
		m_listCtrl.InsertColumn(i, strFREQ[i-1], LVCFMT_LEFT, 120, -1);
	}
	m_listCtrl.InsertColumn(MAXFREQ+1, "描述", LVCFMT_LEFT, 200, -1);
	for (i= 0; i<MAXCHD; i++)//
	{
		m_listCtrl.InsertItem(i, strChd[i]);
	}
}
void ChDecodeView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listCtrl.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void ChDecodeView::RefreshView(BD2_CHD* data)
{
	int id = 0;
	CString str;
	id = data->svID;
	int item = BranchToitem(data->branch)+1;
	if(item == 0 || m_nSvId != id)
		return;

	try
	{

		str.Format("%u", data->week);
		m_listCtrl.SetItemText(0, item, str);
		str.Format("%u", data->tow);
		m_listCtrl.SetItemText(1, item, str);
		str = "";
		int iNavType = data->NavType;
		if(iNavType == 0)
				str = "B-CNAV1";
		else if(iNavType == 1)
				str = "B-CNAV2";
		else if(iNavType == 2)
				str = "B-CNAV3";
		else if(iNavType == 3)
				str = "B-ANAV";
		else if(iNavType == 4)
				str = "B-CINAV";
		else if(iNavType == 5)
				str = "B-AINAV";
		m_listCtrl.SetItemText(2, item, str);

		str.Format("%d", data->SubfameIdorMessType);
		m_listCtrl.SetItemText(3, item, str);


		//信道编码方式
		str.Empty();
		unsigned int iResult = (data->Decodeinfo>>5)&0x07;
		if(iResult == 0)
				str = "LDPC64(96,48)";
		else if(iResult == 1)
				str = "LDPC64(88,44)";
		else if(iResult == 2)
				str = "LDPC64(200,100)";
		else if(iResult == 3)
				str = "LDPC64(162,81)";
		else if(iResult == 4)
				str = "TURBO(600,300)";
		m_listCtrl.SetItemText(4, item, str);


		//译码是否通过
		str.Empty();
		iResult = (data->Decodeinfo>>4)&0x01;
		if(iResult == 0)
				str = "不通过";
		else if(iResult == 1)
				str = "通过";
		m_listCtrl.SetItemText(5, item, str);

		//误码个数
		str.Empty();
		iResult = (data->Decodeinfo>>0)&0x0F;
		str.Format("%d", iResult);
		m_listCtrl.SetItemText(6, item, str);
		
	}
	catch (...)
	{
	}
}

void ChDecodeView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("信道译码信息");
}
void ChDecodeView::Clear()
{
	OnClearView();
}
void ChDecodeView::OnClearView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	InitColumn();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void ChDecodeView::OnUpdateClearView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void ChDecodeView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	BD2_CHD* alm = new BD2_CHD;
	memcpy(alm, data->buffer, sizeof(BD2_CHD));
	EnterCriticalSection(&m_BufferCriticalSection);
	if (!m_bLock)
	{
		RefreshView(alm);
	}
	LeaveCriticalSection(&m_BufferCriticalSection);
	delete alm;
}

void ChDecodeView::OnLockView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bLock = !m_bLock;
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void ChDecodeView::OnUpdateLockView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bLock);
}

