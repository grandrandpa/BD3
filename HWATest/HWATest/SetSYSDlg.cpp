// SetSYSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetSYSDlg.h"


// CSetSYSDlg dialog

IMPLEMENT_DYNAMIC(CSetSYSDlg, CBCGPDialog)

CSetSYSDlg::CSetSYSDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetSYSDlg::IDD, pParent)
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE, TRUE);
}

CSetSYSDlg::~CSetSYSDlg()
{
}

void CSetSYSDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SYS_MAIN, m_tabCtrl);
}


BEGIN_MESSAGE_MAP(CSetSYSDlg, CBCGPDialog)
END_MESSAGE_MAP()


// CSetSYSDlg message handlers

BOOL CSetSYSDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rect;
	m_tabCtrl.GetClientRect(rect);
	m_wndPane.Create(IDD_PANE_DIALOG, &m_tabCtrl);
	m_wndPane.MoveWindow(rect);
	m_wndPane.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CSetSYSDlg::Reset()
{

}
