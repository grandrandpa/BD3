// SetMUTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetMUTDlg.h"


// CSetMUTDlg dialog

IMPLEMENT_DYNAMIC(CSetMUTDlg, CBCGPDialog)

CSetMUTDlg::CSetMUTDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetMUTDlg::IDD, pParent)
	, m_nTTFMod(0)
	, m_nEVAValue(0)
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE, TRUE);
}

CSetMUTDlg::~CSetMUTDlg()
{
}

void CSetMUTDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_TTF_MOD, m_cmbTTFMod);
	DDX_Control(pDX, IDC_EDIT_EVA_VALUE, m_editEVAValue);
	DDX_CBIndex(pDX, IDC_COMBO_TTF_MOD, m_nTTFMod);
	DDX_Text(pDX, IDC_EDIT_EVA_VALUE, m_nEVAValue);
}

BEGIN_MESSAGE_MAP(CSetMUTDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_SET_TTF, &CSetMUTDlg::OnBnClickedBtnSetTtf)
	ON_BN_CLICKED(IDC_BTN_SET_EVA, &CSetMUTDlg::OnBnClickedBtnSetEva)
END_MESSAGE_MAP()

// CSetMUTDlg message handlers
BOOL CSetMUTDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_cmbTTFMod.AddString("0���ն�������λ");
	m_cmbTTFMod.AddString("1��������");
	m_cmbTTFMod.AddString("2��������");
	m_cmbTTFMod.AddString("3��������");
	m_cmbTTFMod.AddString("4������������");
	m_cmbTTFMod.AddString("5������������");
	m_cmbTTFMod.AddString("6���۲�������");
	m_cmbTTFMod.AddString("7���ྶ���ƹ���");
	m_cmbTTFMod.SetCurSel(m_nTTFMod);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetMUTDlg::OnBnClickedBtnSetTtf()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SETTTF data;
	data.mod = m_nTTFMod;
	theApp.m_winLinkApp.SetupTTFRequest(data);

	BCGPMessageBox("�������óɹ�");
}

void CSetMUTDlg::OnBnClickedBtnSetEva()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SETEVA data;
	data.elv = m_nEVAValue;
	theApp.m_winLinkApp.SetupEVARequest(data);
	BCGPMessageBox("�������óɹ�");
}

void CSetMUTDlg::Reset()
{
	m_nTTFMod = 0;
	m_nEVAValue = 0;
	UpdateData(FALSE);
}