// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "LoginDlg.h"


// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CBCGPDialog)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CLoginDlg::IDD, pParent)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CBCGPDialog)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg message handlers

BOOL CLoginDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
}
