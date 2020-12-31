// AnimationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "AnimationDlg.h"


// CAnimationDlg dialog

IMPLEMENT_DYNAMIC(CAnimationDlg, CBCGPDialog)

CAnimationDlg::CAnimationDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CAnimationDlg::IDD, pParent)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CAnimationDlg::~CAnimationDlg()
{
}

void CAnimationDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAnimationDlg, CBCGPDialog)
END_MESSAGE_MAP()


// CAnimationDlg message handlers

BOOL CAnimationDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
