// SetIONDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetIONDlg.h"


// CSetIONDlg dialog

IMPLEMENT_DYNAMIC(CSetIONDlg, CBCGPDialog)

CSetIONDlg::CSetIONDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetIONDlg::IDD, pParent)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CSetIONDlg::~CSetIONDlg()
{
}

void CSetIONDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ION, m_cmbIon);
	DDX_Control(pDX, IDC_COMBO_TRO, m_cmbTro);
	DDX_Control(pDX, IDC_COMBO_ALT, m_cmbAlt);
}

BEGIN_MESSAGE_MAP(CSetIONDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_CHECK_ION, &CSetIONDlg::OnBnClickedBtnCheckIon)
	ON_BN_CLICKED(IDC_BTN_SET_ION, &CSetIONDlg::OnBnClickedBtnSetIon)
END_MESSAGE_MAP()


// CSetIONDlg message handlers

BOOL CSetIONDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_cmbIon.AddString("0-不修正");
	m_cmbIon.AddString("1-修正");
	m_cmbTro.AddString("0-不修正");
	m_cmbTro.AddString("1-修正");
	m_cmbAlt.AddString("0-不修正");
	m_cmbAlt.AddString("1-修正");
	m_cmbIon.SetCurSel(0);
	m_cmbTro.SetCurSel(0);
	m_cmbAlt.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetIONDlg::OnBnClickedBtnCheckIon()
{
	// TODO: Add your control notification handler code here
}

void CSetIONDlg::OnBnClickedBtnSetIon()
{
	// TODO: Add your control notification handler code here
	SETION data;
	data.altFlag = m_cmbAlt.GetCurSel();
	data.ionFlag = m_cmbIon.GetCurSel();
	data.troFlag = m_cmbTro.GetCurSel();
	theApp.m_winLinkApp.SetupIONRequest(data);
	BCGPMessageBox("设置参数成功");
}
