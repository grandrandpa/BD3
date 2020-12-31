// SetTTFDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetTTFDlg.h"


// CSetTTFDlg dialog

IMPLEMENT_DYNAMIC(CSetTTFDlg, CBCGPDialog)

CSetTTFDlg::CSetTTFDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetTTFDlg::IDD, pParent)
{

}

CSetTTFDlg::~CSetTTFDlg()
{
}

void CSetTTFDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetTTFDlg, CBCGPDialog)
END_MESSAGE_MAP()


// CSetTTFDlg message handlers

BOOL CSetTTFDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
