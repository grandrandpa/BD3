// SetSTSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetSTSDlg.h"


// CSetSTSDlg dialog

IMPLEMENT_DYNAMIC(CSetSTSDlg, CBCGPDialog)

CSetSTSDlg::CSetSTSDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetSTSDlg::IDD, pParent)
	, m_nB1(0)
	, m_nB2(0)
	, m_nB3(0)
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE, TRUE);
}

CSetSTSDlg::~CSetSTSDlg()
{
}

void CSetSTSDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_B1, m_cmbB1);
	DDX_Control(pDX, IDC_COMBO_B2, m_cmbB2);
	DDX_Control(pDX, IDC_COMBO_B3, m_cmbB3);
	DDX_CBIndex(pDX, IDC_COMBO_B1, m_nB1);
	DDX_CBIndex(pDX, IDC_COMBO_B2, m_nB2);
	DDX_CBIndex(pDX, IDC_COMBO_B3, m_nB3);
}


BEGIN_MESSAGE_MAP(CSetSTSDlg, CBCGPDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_B1, &CSetSTSDlg::OnCbnSelchangeComboB1)
	ON_CBN_SELCHANGE(IDC_COMBO_B2, &CSetSTSDlg::OnCbnSelchangeComboB2)
	ON_CBN_SELCHANGE(IDC_COMBO_B3, &CSetSTSDlg::OnCbnSelchangeComboB3)
	ON_BN_CLICKED(IDC_BTN_SET, &CSetSTSDlg::OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CSetSTSDlg message handlers

BOOL CSetSTSDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_cmbB1.AddString("0£º²âÊÔ×´Ì¬");
	m_cmbB1.AddString("1£º×´Ì¬Ò»");
	m_cmbB1.AddString("2£º×´Ì¬¶þ");
	m_cmbB1.SetCurSel(m_nB1);

	m_cmbB2.AddString("0£º²âÊÔ×´Ì¬");
	m_cmbB2.AddString("1£º×´Ì¬Ò»");
	m_cmbB2.AddString("2£º×´Ì¬¶þ");
	m_cmbB2.AddString("3£º×´Ì¬Èý");
	m_cmbB2.SetCurSel(m_nB2);

	m_cmbB3.AddString("0£º²âÊÔ×´Ì¬");
	m_cmbB3.AddString("1£º×´Ì¬Ò»");
	m_cmbB3.AddString("2£º×´Ì¬¶þ");
	m_cmbB3.AddString("3£º×´Ì¬Èý");
	m_cmbB3.SetCurSel(m_nB3);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetSTSDlg::OnCbnSelchangeComboB1()
{
	// TODO: Add your control notification handler code here
}

void CSetSTSDlg::OnCbnSelchangeComboB2()
{
	// TODO: Add your control notification handler code here
}

void CSetSTSDlg::OnCbnSelchangeComboB3()
{
	// TODO: Add your control notification handler code here
}

void CSetSTSDlg::OnBnClickedBtnSet()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SETSTS data;
	data.b1 = m_nB1;
	data.b2 = m_nB2;
	data.b3 = m_nB3;
	theApp.m_winLinkApp.SetupSTSRequest(data);
	BCGPMessageBox("²ÎÊýÉèÖÃ³É¹¦");
}

void CSetSTSDlg::Reset()
{

}