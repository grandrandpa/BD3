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
	m_cmbSta.AddString("0£ºB3C_BPSK(5)");
	m_cmbSta.AddString("1£ºB3C_BOC(15,2.5)");
	m_cmbSta.AddString("2£ºB2a_TD-AltBOC");
	m_cmbSta.AddString("3£ºB2a_AltBOC");
	m_cmbSta.AddString("4£ºB2b_TD-AltBOC");
	m_cmbSta.AddString("5£ºB2b_AltBOC");
	m_cmbSta.AddString("6£ºB2_TD-AltBOC");
	m_cmbSta.AddString("7£ºB2_AltBOC");
	m_cmbSta.AddString("8£ºB1A_TDDM");
	m_cmbSta.AddString("9£ºB1A_BCO(14,2)");
	m_cmbSta.AddString("10£ºB3A_BPSK(10)");
	m_cmbSta.AddString("11£ºB3AE_BPSK(10)");
	m_cmbSta.SetCurSel(m_nSta);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetSTADlg::OnCbnSelchangeComboSta()
{
	// TODO: Add your control notification handler code here
}
