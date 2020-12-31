// SetSTADlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetSTADlg.h"


// CSetSTADlg dialog

IMPLEMENT_DYNAMIC(CSetSTADlg, CBCGPDialog)

CSetSTADlg::CSetSTADlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetSTADlg::IDD, pParent)
	, m_nSta(0)
{

}

CSetSTADlg::~CSetSTADlg()
{
}

void CSetSTADlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_STA, m_cmbSta);
	DDX_CBIndex(pDX, IDC_COMBO_STA, m_nSta);
}


BEGIN_MESSAGE_MAP(CSetSTADlg, CBCGPDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_STA, &CSetSTADlg::OnCbnSelchangeComboSta)
END_MESSAGE_MAP()


// CSetSTADlg message handlers

BOOL CSetSTADlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_cmbSta.AddString("0��B3C_BPSK(5)");
	m_cmbSta.AddString("1��B3C_BOC(15,2.5)");
	m_cmbSta.AddString("2��B2a_TD-AltBOC");
	m_cmbSta.AddString("3��B2a_AltBOC");
	m_cmbSta.AddString("4��B2b_TD-AltBOC");
	m_cmbSta.AddString("5��B2b_AltBOC");
	m_cmbSta.AddString("6��B2_TD-AltBOC");
	m_cmbSta.AddString("7��B2_AltBOC");
	m_cmbSta.AddString("8��B1A_TDDM");
	m_cmbSta.AddString("9��B1A_BCO(14,2)");
	m_cmbSta.AddString("10��B3A_BPSK(10)");
	m_cmbSta.AddString("11��B3AE_BPSK(10)");
	m_cmbSta.SetCurSel(m_nSta);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetSTADlg::OnCbnSelchangeComboSta()
{
	// TODO: Add your control notification handler code here
}
