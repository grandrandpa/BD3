// outputbar.cpp : implementation of the COutputBar class
//

#include "stdafx.h"
#include "HWATest.h"
#include "outputbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputList

COutputList::COutputList()
{
}

COutputList::~COutputList()
{
}


BEGIN_MESSAGE_MAP(COutputList, CBCGPListBox)
	//{{AFX_MSG_MAP(COutputList)
	ON_WM_CONTEXTMENU()
	//ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	//ON_COMMAND(ID_VIEW_OUTPUT, OnViewOutput)
	ON_WM_WINDOWPOSCHANGING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList message handlers

void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point) 
{
   CMenu menu;
   menu.LoadMenu(IDR_POPUP_OUTPUT);

   CMenu* pSumMenu = menu.GetSubMenu(0);

   if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CBCGPMDIFrameWnd)))
   {
	   CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;

	   if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
         return;

      ((CBCGPMDIFrameWnd*)AfxGetMainWnd())->OnShowPopupMenu (pPopupMenu);
      UpdateDialogControls(this, FALSE);
   }

   SetFocus ();
}

void COutputList::OnEditCopy() 
{
	TRACE0(_T("Copy output\n"));
}

void COutputList::OnEditClear() 
{
	TRACE0(_T("Clear output\n"));
    //int index = GetCurSel();
    //DeleteString(index);
    ResetContent();//clear all
}

void COutputList::OnOutputGotoError() 
{
	// TODO: Add your command handler code here
	
}

void COutputList::OnViewOutput() 
{
	CBCGPDockingControlBar* pParentBar = DYNAMIC_DOWNCAST (CBCGPDockingControlBar, GetOwner ());
	CMDIFrameWnd* pMainFrame = DYNAMIC_DOWNCAST (CMDIFrameWnd, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
        //pMainFrame->ShowControlBar(pParentBar, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}



/////////////////////////////////////////////////////////////////////////////
// COutputBar

BEGIN_MESSAGE_MAP(COutputBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(COutputBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputBar construction/destruction

COutputBar::COutputBar()
{
	// TODO: add one-time construction code here
}

COutputBar::~COutputBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// COutputBar message handlers

int COutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();
	// Create list windows.
	//const DWORD dwViewStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL; LBS_NOSEL
    const DWORD dwViewStyle = LBS_NOINTEGRALHEIGHT | LBS_NOSEL | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS;
	m_wndList.m_bVisualManagerStyle = TRUE;
	if (!m_wndList.Create (dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("Failed to create output view\n");
		return -1;      // fail to create
	}
	//AddString("调试信息输出窗口");
	// Attach list windows to tab:

    UpdateFonts();

	return 0;
}

void COutputBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	m_wndList.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputBar::AddString(CString strText)
{
	//m_wndList.AddString(strText);
    //m_wndList.DeleteString(1);
}

void COutputBar::UpdateFonts()
{
	m_wndList.SetFont (&globalData.fontRegular);
}

void COutputBar::ShowDataToWindow(CString dataText)
{
	m_wndList.AddString (dataText);
	int ncount = m_wndList.GetCount();
	if(ncount>0)
    {
		//m_wndList.SetCurSel(ncount-1);
        m_wndList.SetTopIndex(ncount-1);
    }

}