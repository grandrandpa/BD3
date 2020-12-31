// ShowPosView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowGgaPosView.h"


// CShowGgaPosView

IMPLEMENT_DYNCREATE(CShowGgaPosView, CHWATestView)

CShowGgaPosView::CShowGgaPosView()
    : m_nPosType(0)
{
	m_bLock = false;
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CShowGgaPosView::~CShowGgaPosView()
{
	m_bLock = false;
	//m_listCtrl.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CShowGgaPosView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_POS_CLEAR, OnClearView)
	ON_UPDATE_COMMAND_UI(IDR_POS_CLEAR, OnUpdateClearView)
	ON_COMMAND(IDR_POS_LOCK, OnLockView)
	ON_UPDATE_COMMAND_UI(IDR_POS_LOCK, OnUpdateLockView)
END_MESSAGE_MAP()


// CShowGgaPosView drawing

void CShowGgaPosView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CShowGgaPosView diagnostics

#ifdef _DEBUG
void CShowGgaPosView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowGgaPosView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowGgaPosView message handlers
int CShowGgaPosView::OnCreate(LPCREATESTRUCT lpCreateStruct)
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
	m_wndToolBar.LoadToolBar(IDR_POS_TOOLBAR);

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
void CShowGgaPosView::InitColumn()
{
	m_listCtrl.InsertColumn(0, "时间", LVCFMT_LEFT, 220, -1);
	m_listCtrl.InsertColumn(1, "纬度(度)", LVCFMT_LEFT, 130, -1);
    m_listCtrl.InsertColumn(2, "纬度方向", LVCFMT_LEFT, 100, -1);
	m_listCtrl.InsertColumn(3, "经度(度)", LVCFMT_LEFT, 130, -1);
    m_listCtrl.InsertColumn(4, "经度方向", LVCFMT_LEFT, 100, -1);
	m_listCtrl.InsertColumn(5, "高程(m)", LVCFMT_LEFT, 80, -1);
	m_listCtrl.InsertColumn(6, "参与定位可用卫星数", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(7, "HDOP", LVCFMT_LEFT, 50, -1);
	m_listCtrl.InsertColumn(8, "VDOP", LVCFMT_LEFT, 50, -1);
	m_listCtrl.InsertColumn(9, "PDOP", LVCFMT_LEFT, 50, -1);

	//m_listCtrl.InsertColumn(15, "解算使用的卫星号", LVCFMT_LEFT, 250, -1);
}

void CShowGgaPosView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listCtrl.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CShowGgaPosView::RefreshView(NmeaAllData* data)
{
	int i=0, index=0;
	CString str,strTemp;

    int count = m_listCtrl.GetItemCount();
    m_listCtrl.EnsureVisible(count, FALSE);
    SCROLLINFO inf;
    m_listCtrl.GetScrollInfo(SB_VERT,&inf,SIF_ALL);
	if (inf.nMax > (int)inf.nPage) //MAX_LINE
	{
		//m_listCtrl.DeleteAllItems();
        m_listCtrl.SetScrollPos(SB_VERT,inf.nMax,TRUE);
	}
    //m_listCtrl.SendMessage(LVM_SCROLL,0,65535);
    m_listCtrl.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);

    if (inf.nMax > (int)inf.nPage + MAX_LINE)
    {
        m_listCtrl.DeleteItem(1);
    }

	try
	{
        str.Format("%02d:%02d:%02.2f", data->UTC.hour, data->UTC.minute, data->UTC.second);
        m_listCtrl.InsertItem(0, str);

        m_listCtrl.SetItemText(0, 1, data->Latitude);
        str.Format("%c", data->N_S);
        m_listCtrl.SetItemText(0, 2, str);

        m_listCtrl.SetItemText(0, 3, data->Longitude);
        str.Format("%c", data->E_W);
        m_listCtrl.SetItemText(0, 4, str);

        m_listCtrl.SetItemText(0, 5, data->Altitude);

        switch(data->sys)
        {
        case GP:
            m_listCtrl.SetItemText(0, 6, data->GP_in_use);
            break;
        case BD:
            m_listCtrl.SetItemText(0, 6, data->BD_in_use);
            break;

        case GL:
            m_listCtrl.SetItemText(0, 6, data->GL_in_use);
            break;

        case GA:
            m_listCtrl.SetItemText(0, 6, data->GA_in_use);
            break;

        case GN:
            m_listCtrl.SetItemText(0, 6, data->GN_in_use);
            break;

        default:
            break;
        }
		m_listCtrl.SetItemText(0, 7, data->HDOP);
        int len = strlen(data->VDOP);
        if(len == 0)
        {
            m_listCtrl.SetItemText(0, 8, "0");
        }
        else
        {
            m_listCtrl.SetItemText(0, 8, data->VDOP);
        }
        m_listCtrl.SetItemText(0, 9, data->PDOP);
	}
	catch (...)
	{
	}
}

void CShowGgaPosView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("定位");
}

void CShowGgaPosView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	//BD2_POS* pos = new BD2_POS;
    NmeaAllData* pos = new NmeaAllData();
    memset(pos, 0, sizeof(NmeaAllData));
	memcpy(pos, data->buffer, sizeof(NmeaAllData));
	EnterCriticalSection(&m_BufferCriticalSection);
	if (!m_bLock)
	{
		RefreshView(pos);
	}
	LeaveCriticalSection(&m_BufferCriticalSection);
	delete pos;
}
void CShowGgaPosView::Clear()
{
	OnClearView();
}
void CShowGgaPosView::OnClearView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowGgaPosView::OnUpdateClearView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CShowGgaPosView::OnLockView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bLock = !m_bLock;
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowGgaPosView::OnUpdateLockView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bLock);
}

