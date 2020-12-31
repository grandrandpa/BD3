// ShowRanView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowRanView.h"


// CShowRanView

IMPLEMENT_DYNCREATE(CShowRanView, CHWATestView)

CShowRanView::CShowRanView()
: m_nBranch(0)
{
	m_bLock = false;
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CShowRanView::~CShowRanView()
{
	m_bLock = false;
	//m_listCtrl.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CShowRanView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_RAN_BRANCH, OnChangeBranch)
	ON_CBN_SELENDOK(IDR_RAN_BRANCH, OnChangeBranch)
	ON_COMMAND(IDR_RAN_CLEAR, OnClearView)
	ON_UPDATE_COMMAND_UI(IDR_RAN_CLEAR, OnUpdateClearView)
	ON_COMMAND(IDR_RAN_LOCK, OnLockView)
	ON_UPDATE_COMMAND_UI(IDR_RAN_LOCK, OnUpdateLockView)
END_MESSAGE_MAP()


// CShowRanView drawing

void CShowRanView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CShowRanView diagnostics

#ifdef _DEBUG
void CShowRanView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowRanView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowRanView message handlers
void CShowRanView::OnChangeBranch() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	CBCGPToolbarComboBoxButton* pCombobox = DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton,
		m_wndToolBar.GetButton (m_wndToolBar.CommandToIndex (IDR_RAN_BRANCH)));
	m_listCtrl.DeleteAllItems();
	m_nBranch = pCombobox->GetCurSel();
	LeaveCriticalSection(&m_BufferCriticalSection);
	//BCGPMessageBox("测试");m_nPosType
}


int CShowRanView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	m_wndToolBar.LoadToolBar(IDR_RAN_TOOLBAR);
	m_wndToolBar.ReplaceButton (IDR_RAN_BRANCH_LABEL, CToolbarLabel(IDR_RAN_BRANCH_LABEL, _T("信号分量: ")));

	CBCGPToolbarComboBoxButton comboBranch (IDR_RAN_BRANCH, CImageHash::GetImageOfCommand (IDR_RAN_BRANCH, FALSE), CBS_DROPDOWNLIST);
	for (i=0; i<MAXFREQ; i++)//
	{
		comboBranch.AddItem (strFREQ[i]);
	}
	comboBranch.SelectItem(0);
	m_wndToolBar.ReplaceButton (IDR_RAN_BRANCH, comboBranch);

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
void CShowRanView::InitColumn()
{
	int i = 0;
	CString str;
	m_listCtrl.InsertColumn(0, "通道编号", LVCFMT_CENTER, 60, -1);
	m_listCtrl.InsertColumn(1, "周数/周内秒", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(2, "可用卫星数", LVCFMT_LEFT, 80, -1);
	m_listCtrl.InsertColumn(3, "信号分量", LVCFMT_LEFT, 80, -1);
	m_listCtrl.InsertColumn(4, "卫星编号", LVCFMT_LEFT, 80, -1);
	m_listCtrl.InsertColumn(5, "伪距(米)", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(6, "载波相位(周)", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(7, "多普勒(Hz)", LVCFMT_LEFT, 100, -1);
	m_listCtrl.InsertColumn(8, "信号强度(dBHz/dBm)", LVCFMT_LEFT, 120, -1);
	//m_listCtrl.InsertColumn(9, "CCBF", LVCFMT_LEFT, 100, -1);
	m_listCtrl.InsertColumn(9, "伪距历元差", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(10, "载波相位历元差", LVCFMT_LEFT, 120, -1);
}
void CShowRanView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listCtrl.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CShowRanView::RefreshView(BD2_RAN* data)
{
	CString str;
	double temp=0;
	int id = 0, SvId=0, chId=0;
	int index = BranchToitem(data->branch);
	if(index == -1 || m_nBranch != index)
		return;
	int count = data->numuse;
	try
	{
		m_listCtrl.DeleteAllItems();
		for (int i=0; i<count; i++)
		{
			SvId = data->svId[i];
			chId = (data->status1[i] >> 3)&0x3FF;
			str.Format("%02d", chId);
			m_listCtrl.InsertItem(i, str);
			str.Format("%d/%.1f", data->week, data->tow);
			m_listCtrl.SetItemText(i, 1, str);



			str.Format("%02d", data->numuse);
			//add by cy 20180714
			if((index>=2 && index<=4 )|| index==10 || index ==11)//针对B1C，B2a，B1A，B3A，B3AE信号分量分别显示不同信息
			{
				str.Format("%02d", data->numuse/2);
			}


			m_listCtrl.SetItemText(i, 2, str);

			str.Format("%s", strFREQ[index]);
			//add by cy 20180714
			if((index>=2 && index<=4 )|| index==10 || index ==11)//针对B1C，B2a，B1A，B3A，B3AE信号分量分别显示不同信息
			{
				if(i<count/2)				
					str.Format("%s%s", strFREQ[index],"_data");				
				else
					str.Format("%s%s", strFREQ[index],"_pilot");
			}
			//
			m_listCtrl.SetItemText(i, 3, str);

			str.Format("%02d", SvId);
			m_listCtrl.SetItemText(i, 4, str);
			str.Format("%.3f", data->ran[i].x);
			m_listCtrl.SetItemText(i, 5, str);
			str.Format("%.6f", data->ran[i].y);
			m_listCtrl.SetItemText(i, 6, str);
			str.Format("%.3f", data->ran[i].z);
			m_listCtrl.SetItemText(i, 7, str);
			temp = data->snr[i];
			str.Format("%.1f/%.1f", temp, (temp-173));
			m_listCtrl.SetItemText(i, 8, str);
			/*str.Format("%08X", data->status[i]&0xFFFFFFFF);
			m_listCtrl.SetItemText(i, 9, str);*/

			//伪距历元差，载波相位历元差 add by cy 20180714
			str.Format("%.6f", data->daltapseudos[i]);
			m_listCtrl.SetItemText(i, 9, str);
			str.Format("%.6f", data->deltacarriers[i]);
			m_listCtrl.SetItemText(i, 10, str);


		
		}
	}
	catch (...)
	{
	}
}
void CShowRanView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("原始观测量");
}

void CShowRanView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	BD2_RAN* ran = new BD2_RAN;
	memcpy(ran, data->buffer, sizeof(BD2_RAN));
	EnterCriticalSection(&m_BufferCriticalSection);
	if (!m_bLock)
	{
		RefreshView(ran);
	}
	LeaveCriticalSection(&m_BufferCriticalSection);
	delete ran;
}
void CShowRanView::Clear()
{
	OnClearView();
}
void CShowRanView::OnClearView() 
{
	int i = 0;
	CString str;
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowRanView::OnUpdateClearView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CShowRanView::OnLockView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bLock = !m_bLock;
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowRanView::OnUpdateLockView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bLock);
}

