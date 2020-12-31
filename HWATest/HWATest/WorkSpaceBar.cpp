// workspace.cpp : implementation of the CWorkSpaceBar class
//

#include "stdafx.h"
#include "HWATest.h"
#include "WorkSpaceBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nBorderSize = 1;
/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar

BEGIN_MESSAGE_MAP(CWorkSpaceBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CWorkSpaceBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_NOTIFY(NM_CLICK, IDD_USER_VIEW_TREECTRL, &CWorkSpaceBar::OnNMClickTreeCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar construction/destruction

CWorkSpaceBar::CWorkSpaceBar()
{
	// TODO: add one-time construction code here
}

CWorkSpaceBar::~CWorkSpaceBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar message handlers

int CWorkSpaceBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	// Create tree windows.
	// TODO: create your own tab windows here:
	const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_CHECKBOXES;
	m_wndTree.m_bVisualManagerStyle = TRUE;
	if (!m_wndTree.Create (dwViewStyle, rectDummy, this, IDD_USER_VIEW_TREECTRL))
	{
		TRACE0("Failed to create workspace view\n");
		return -1;      // fail to create
	}

	// Setup trees content:
	HTREEITEM hRoot = m_wndTree.InsertItem (_T("上位机定位模式选择"));
	m_wndTree.InsertItem (_T("B1I"), hRoot);
	m_wndTree.InsertItem (_T("B1Q"), hRoot);
	m_wndTree.InsertItem (_T("B1C"), hRoot);
	m_wndTree.InsertItem (_T("B1A"), hRoot);
	m_wndTree.InsertItem (_T("B2a"), hRoot);
	m_wndTree.InsertItem (_T("B2b"), hRoot);
	m_wndTree.InsertItem (_T("B2"), hRoot);
	m_wndTree.InsertItem (_T("B3I"), hRoot);
	m_wndTree.InsertItem (_T("B3Q"), hRoot);
	m_wndTree.InsertItem (_T("B3C"), hRoot);
	m_wndTree.InsertItem (_T("B3A"), hRoot);
	m_wndTree.InsertItem (_T("Bs"), hRoot);
	m_wndTree.InsertItem (_T("B3AE"), hRoot);
	m_wndTree.InsertItem (_T("B1C+B3C"), hRoot);
	m_wndTree.InsertItem (_T("B1Q+B3Q"), hRoot);
	m_wndTree.InsertItem (_T("B1A+B3A"), hRoot);
	m_wndTree.InsertItem (_T("Bs+B3A"), hRoot);
	m_wndTree.InsertItem (_T("B1C+B2a"), hRoot);
	m_wndTree.InsertItem (_T("B1C+B2+B3C"), hRoot);
	m_wndTree.Expand(hRoot, TVE_EXPAND);
	//SetChildCheckbox(hRoot);

	return 0;
}

void CWorkSpaceBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	// Tab control should cover a whole client area:
	m_wndTree.SetWindowPos (NULL, nBorderSize, nBorderSize, cx - 2 * nBorderSize, cy - 2 * nBorderSize,
		SWP_NOACTIVATE | SWP_NOZORDER);
}

void CWorkSpaceBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rectTree;
	m_wndTree.GetWindowRect (rectTree);
	ScreenToClient (rectTree);

	rectTree.InflateRect (nBorderSize, nBorderSize);

	dc.Draw3dRect (rectTree, globalData.clrBarShadow, globalData.clrBarShadow);
}

void CWorkSpaceBar::OnNMClickTreeCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CPoint point;
	UINT uFlag;                                 //接收有关点击测试的信息的整数
	HTREEITEM hTree;
	BOOL bCheck = FALSE;
	CString str = "";
	unsigned long mode = 0;
	GetCursorPos(&point);                        //获取屏幕鼠标坐标
	m_wndTree.ScreenToClient(&point);           //转化成客户坐标
	hTree = m_wndTree.HitTest(point, &uFlag);    //返回与CtreeTtrl关联的光标的当前位置和句柄
	if((TVHT_NOWHERE & uFlag))
		return;

	if (hTree && (TVHT_ONITEMSTATEICON & uFlag))  //点中复选框 //定位模式选择
	{
		bCheck = m_wndTree.GetCheck(hTree);      //获取当前复选状态
		if("B1I" == m_wndTree.GetItemText(hTree))
		{
			//BCGPMessageBox(bCheck?"TRUE":"FALSE");
			WritePrivateProfileString("POSMOD", "B1I", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B1Q" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B1Q", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B1C" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B1C", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B1A" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B1A", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B2a" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B2a", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B2b" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B2b", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B2" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B2", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B3I" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B3I", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B3Q" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B3Q", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B3C" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B3C", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B3A" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B3A", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("Bs" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "Bs", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B3AE" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B3AE", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B1C+B3C" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B1CB3C", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B1Q+B3Q" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B1QB3Q", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B1A+B3A" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B1AB3A", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("Bs+B3A" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "BsB3A", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B1C+B2a" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B1CB2a", bCheck?"0":"1", theApp.m_strConfigPath);
		}
		else if("B1C+B2+B3C" == m_wndTree.GetItemText(hTree))
		{
			WritePrivateProfileString("POSMOD", "B1CB2B3C", bCheck?"0":"1", theApp.m_strConfigPath);
		}
	}

	*pResult = 0;
}

void CWorkSpaceBar::SetChildCheckbox(HTREEITEM hTree)
{
	int bCheck = 0;
	CString strText = "";
	m_wndTree.Expand(hTree,TVE_EXPAND);
	hTree = m_wndTree.GetChildItem(hTree);  //获取子项句柄
	while (hTree)
	{
		hTree = m_wndTree.GetNextSiblingItem(hTree);    //获取兄弟的句柄
		if("B1I" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B1I", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B1Q" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B1Q", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B1C" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B1C", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B1A" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B1A", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B2a" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B2a", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B2b" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B2b", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B2" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B2", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B3I" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B3I", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B3Q" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B3Q", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B3C" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B3C", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B3A" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B3A", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("Bs" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "Bs", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B3AE" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B3AE", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B1C+B3C" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B1CB3C", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B1Q+B3Q" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B1QB3Q", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B1A+B3A" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B1AB3A", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("Bs+B3A" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "BsB3A", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B1C+B2a" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B1CB2a", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
		else if("B1C+B2+B3C" == m_wndTree.GetItemText(hTree))
		{
			bCheck = GetPrivateProfileInt("POSMOD", "B1CB2B3C", 0, theApp.m_strConfigPath);
			m_wndTree.SetCheck(hTree, bCheck);
		}
	}
}
