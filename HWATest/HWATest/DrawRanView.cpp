// DrawRanView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "DrawRanView.h"


// CDrawRanView
#define DAY_SECOND 86400

IMPLEMENT_DYNCREATE(CDrawRanView, CHWATestView)

CDrawRanView::CDrawRanView()
: m_nRanType(1)
, m_bLock(false)
{
	m_nBranch = 0;
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CDrawRanView::~CDrawRanView()
{
}

BEGIN_MESSAGE_MAP(CDrawRanView, CHWATestView)//
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_DRAW_RAN_ID, OnChangeLineType)
	ON_CBN_SELENDOK(IDR_DRAW_RAN_ID, OnChangeLineType)
	ON_COMMAND(IDR_DRAW_RAN_CLEAR, Clear)
	ON_CBN_SELENDOK(IDR_DRAW_RAN_CLEAR, Clear)
	ON_COMMAND(IDR_DRAW_RAN_LOCK, OnClickLock)
	ON_UPDATE_COMMAND_UI(IDR_DRAW_RAN_LOCK, OnUpdateLock)
END_MESSAGE_MAP()


// CDrawRanView drawing

void CDrawRanView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CDrawRanView diagnostics

#ifdef _DEBUG
void CDrawRanView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CDrawRanView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDrawRanView message handlers

int CDrawRanView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CHWATestView::OnCreate(lpCreateStruct) == -1)
		return -1;


	int i=0,j=0;
	CString str;
	// TODO:  Add your specialized creation code here
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create  
	}
	m_wndToolBar.LoadToolBar(IDR_DRAW_RAN_TOOLBAR);
	m_wndToolBar.ReplaceButton (IDR_DRAW_RAN_LABEL, CToolbarLabel(IDR_DRAW_RAN_LABEL, _T("���Ǻ�: ")));

	CBCGPToolbarComboBoxButton comboButton (IDR_DRAW_RAN_ID, CImageHash::GetImageOfCommand (IDR_DRAW_RAN_ID, FALSE), CBS_DROPDOWNLIST);
	for (i=0; i<MAXCHANNELS; i++)
	{
		str.Format("%02d", i+1);
		comboButton.AddItem (str);
	}
	comboButton.SelectItem(0);
	m_wndToolBar.ReplaceButton (IDR_DRAW_RAN_ID, comboButton);

	CRect rect, rectLine;
	rect.SetRectEmpty();
	CRect RectTab(rect.left, rect.top+30, rect.Width(), rect.Height()-30);
	if (!m_wndTabs.Create (CBCGPTabWnd::STYLE_3D_VS2005, RectTab, this, 1, CBCGPBaseTabWnd::LOCATION_TOP))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}
	m_wndTabs.GetClientRect(&rectLine);
	m_wndChart[0].Create(rect, &m_wndTabs, DRAW_MODE_LINE, MAXFREQ, 300);
	m_wndChart[1].Create(rect, &m_wndTabs, DRAW_MODE_LINE, MAXFREQ, 300);
	m_wndChart[2].Create(rect, &m_wndTabs, DRAW_MODE_LINE, MAXFREQ, 300);

	m_wndChart[0].SetTitle("α������ͼ");
	m_wndChart[0].SetUintDotSpanY("��");
	m_wndChart[0].SetAxisNumSumAfterDotY(4);
	m_wndChart[0].SetYAxisName("α��");
	m_wndChart[0].SetXAxisName("ʱ��");

	m_wndChart[1].SetTitle("�ز���λ����ͼ");
	m_wndChart[1].SetUintDotSpanY("��");
	m_wndChart[1].SetAxisNumSumAfterDotY(4);
	m_wndChart[1].SetYAxisName("�ز���λ");
	m_wndChart[1].SetXAxisName("ʱ��");

	m_wndChart[2].SetTitle("����������ͼ");
	m_wndChart[2].SetUintDotSpanY("HZ");
	m_wndChart[2].SetAxisNumSumAfterDotY(4);
	m_wndChart[2].SetYAxisName("������");
	m_wndChart[2].SetXAxisName("ʱ��");
	for (i=0; i<3; i++)
	{
		for (j=0; j<MAXFREQ; j++)
		{
			m_wndChart[i].SetChName(j, strFREQ[j]);
		}
	}

	m_wndTabs.AddTab(&m_wndChart[0], "α������");
	m_wndTabs.AddTab(&m_wndChart[1], "�ز���λ����");
	m_wndTabs.AddTab(&m_wndChart[2], "����������");

	return 0;
}

void CDrawRanView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndTabs.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CDrawRanView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("�۲�������");
}
void CDrawRanView::OnClickLock()
{
	m_bLock = !m_bLock;
	m_wndChart[0].SetVisible(m_bLock);
	m_wndChart[1].SetVisible(m_bLock);
	m_wndChart[2].SetVisible(m_bLock);
}
void CDrawRanView::OnUpdateLock(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bLock);
}
void CDrawRanView::OnChangeLineType() 
{
	CBCGPToolbarComboBoxButton* pCombobox = DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton,
		m_wndToolBar.GetButton (m_wndToolBar.CommandToIndex (IDR_DRAW_RAN_ID)));
	EnterCriticalSection(&m_BufferCriticalSection);
	m_nRanType = pCombobox->GetCurSel()+1;
	m_wndChart[0].Clean();
	m_wndChart[1].Clean();
	m_wndChart[2].Clean();
	LeaveCriticalSection(&m_BufferCriticalSection);
	//BCGPMessageBox("����");
}

void CDrawRanView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	int SvId=0,branch=0;
	if(m_bLock)
		return;
	BD2_RAN* result = new BD2_RAN;
	memcpy(result, data->buffer, sizeof(BD2_RAN));

	branch = BranchToitem(result->branch);
	EnterCriticalSection(&m_BufferCriticalSection);
	for (int i=0; i<result->numuse; i++)
	{
		SvId = result->svId[i];
		if (SvId == m_nRanType)
		{
			m_wndChart[0].InsertData(branch, result->ran[i].x);
			m_wndChart[1].InsertData(branch, result->ran[i].y);
			m_wndChart[2].InsertData(branch, result->ran[i].z);
		}
	}
	LeaveCriticalSection(&m_BufferCriticalSection);

	/*if(data->buffer)
		free(data->buffer);*/
	delete result;
}

void CDrawRanView::Clear(void)
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_wndChart[0].Clean();
	m_wndChart[1].Clean();
	m_wndChart[2].Clean();
	LeaveCriticalSection(&m_BufferCriticalSection);
}
