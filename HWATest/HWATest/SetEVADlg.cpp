// SetEVADlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetEVADlg.h"


// CSetEVADlg dialog

IMPLEMENT_DYNAMIC(CSetEVADlg, CBCGPDialog)

CSetEVADlg::CSetEVADlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetEVADlg::IDD, pParent)
{

}

CSetEVADlg::~CSetEVADlg()
{
}

void CSetEVADlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetEVADlg, CBCGPDialog)
END_MESSAGE_MAP()


// CSetEVADlg message handlers

BOOL CSetEVADlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
