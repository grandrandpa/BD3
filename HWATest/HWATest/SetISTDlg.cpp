// SetISTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetISTDlg.h"



// CSetISTDlg dialog

IMPLEMENT_DYNAMIC(CSetISTDlg, CBCGPDialog)

CSetISTDlg::CSetISTDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetISTDlg::IDD, pParent)
	, m_nfp(0)
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE);
}

CSetISTDlg::~CSetISTDlg()
{
}

void CSetISTDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_IST, m_fp);
	DDX_CBIndex(pDX, IDC_COMBO_IST, m_nfp);
}


BEGIN_MESSAGE_MAP(CSetISTDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_IST_SET, &CSetISTDlg::OnBnClickedBtnIstSet)
END_MESSAGE_MAP()


// CSetISTDlg message handlers


void CSetISTDlg::OnBnClickedBtnIstSet()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SETIST data;
	data.fp = m_fp.GetCurSel();
	theApp.m_winLinkApp.SetupISTRequest(data);
	BCGPMessageBox("参数设置成功");
}


BOOL CSetISTDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();
	// TODO:  Add extra initialization here
	m_fp.InsertString(0, "1614.26MHz");
	m_fp.InsertString(1, "1618.34MHz");
	m_fp.InsertString(2, "1624.524MHz");
	m_fp.InsertString(3, "1673.628MHz");
	m_fp.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
