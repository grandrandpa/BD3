#include "stdafx.h"
#include "HWATest.h"
#include "DrawTestView.h"


CString strPao[MAXPAO] = {"电文页面", "历书卫星号", "简约历书卫星号"};
// CDrawPAOrderView

IMPLEMENT_DYNCREATE(CDrawPAOrderView, CHWATestView)

CDrawPAOrderView::CDrawPAOrderView()
{
	m_nSvId = 1;
	m_bLock = false;
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CDrawPAOrderView::~CDrawPAOrderView()
{
	m_nSvId = 1;
	m_bLock = false;
	//m_listCtrl.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CDrawPAOrderView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_PAO_ID, OnChangeSvID)
	ON_CBN_SELENDOK(IDR_PAO_ID, OnChangeSvID)
	ON_COMMAND(IDR_PAO_CLEAR, OnClearView)
	ON_UPDATE_COMMAND_UI(IDR_PAO_CLEAR, OnUpdateClearView)
	ON_COMMAND(IDR_PAO_LOCK, OnLockView)
	ON_UPDATE_COMMAND_UI(IDR_PAO_LOCK, OnUpdateLockView)
END_MESSAGE_MAP()


// CDrawPAOrderView drawing 

void CDrawPAOrderView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CDrawPAOrderView diagnostics

#ifdef _DEBUG
void CDrawPAOrderView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CDrawPAOrderView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDrawPAOrderView message handlers
void CDrawPAOrderView::OnChangeSvID() 
{
	CBCGPToolbarComboBoxButton* pCombobox = DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton,
		m_wndToolBar.GetButton (m_wndToolBar.CommandToIndex (IDR_PAO_ID)));
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	InitColumn();
	m_nSvId = pCombobox->GetCurSel()+1;
	LeaveCriticalSection(&m_BufferCriticalSection);
	//BCGPMessageBox("测试");m_nPosType
}


int CDrawPAOrderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	m_wndToolBar.LoadToolBar(IDR_PAO_TOOLBAR);
	m_wndToolBar.ReplaceButton (IDR_PAO_ID_LABEL, CToolbarLabel(IDR_PAO_ID_LABEL, _T("卫星编号: ")));

	CBCGPToolbarComboBoxButton comboID (IDR_PAO_ID, CImageHash::GetImageOfCommand (IDR_PAO_ID, FALSE), CBS_DROPDOWNLIST);
	for (i=0; i<64; i++)//
	{
		str.Format("%02d", i+1);
		comboID.AddItem (str);
	}
	comboID.SelectItem(0);
	m_wndToolBar.ReplaceButton (IDR_PAO_ID, comboID);

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
void CDrawPAOrderView::InitColumn()
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
	for (i= 0; i<MAXPAO; i++)//
	{
		m_listCtrl.InsertItem(i, strPao[i]);
	}
}
void CDrawPAOrderView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listCtrl.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CDrawPAOrderView::RefreshView(BD2_PAORDER* data)
{
	int id = 0;
	CString str;
	id = data->sv;
	int item = BranchToitem(data->branch)+1;
	if(item == 0 || m_nSvId != id)
		return;

	try
	{
		str.Format("%d", data->pageid);//电文页面
		m_listCtrl.SetItemText(0, item, str);


		int   almid = data->almid;
		if(almid>0)
		{
			str.Format("%d", data->almid);//历书卫星号
			m_listCtrl.SetItemText(1, item, str);
		}
			

		CString strTemp;
		str.Empty();
		unsigned int iResult1 = (data->briefalmid>>0)&0xFF;
		if(iResult1>0)
		{
				strTemp.Format("%02d", iResult1);
				str += strTemp +",";
		}
		
		unsigned int iResult2 = (data->briefalmid>>8)&0xFF;
		if(iResult2>0)
		{
				strTemp.Format("%02d", iResult2);
				str += strTemp +",";
		}

		unsigned int iResult3 = (data->briefalmid>>16)&0xFF;
		if(iResult3>0)
		{
				strTemp.Format("%02d", iResult3);
				str += strTemp +",";
		}

		unsigned int iResult4 = (data->briefalmid>>24)&0xFF;
		if(iResult4>0)
		{
				strTemp.Format("%02d", iResult4);
				str += strTemp +",";
		}
		
		if(strlen(str)>0)
			 str = str.Mid(0,strlen(str)-1);
		
		m_listCtrl.SetItemText(2, item, str);//简约历书卫星号
	
	}
	catch (...)
	{
	}
}

void CDrawPAOrderView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("电文页面播发顺序和历书播发顺序");
}
void CDrawPAOrderView::Clear()
{
	OnClearView();
}
void CDrawPAOrderView::OnClearView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	InitColumn();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CDrawPAOrderView::OnUpdateClearView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CDrawPAOrderView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	BD2_PAORDER* alm = new BD2_PAORDER;
	memcpy(alm, data->buffer, sizeof(BD2_PAORDER));
	EnterCriticalSection(&m_BufferCriticalSection);
	if (!m_bLock)
	{
		RefreshView(alm);
	}
	LeaveCriticalSection(&m_BufferCriticalSection);
	delete alm;
}

void CDrawPAOrderView::OnLockView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bLock = !m_bLock;
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CDrawPAOrderView::OnUpdateLockView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bLock);
}

