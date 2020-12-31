// SetModualDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetModualDlg.h"


// CSetModualDlg dialog

IMPLEMENT_DYNAMIC(CSetModualDlg, CBCGPDialog)

CSetModualDlg::CSetModualDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetModualDlg::IDD, pParent)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CSetModualDlg::~CSetModualDlg()
{
}

void CSetModualDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODUAL, m_cmbModual);
	DDX_Control(pDX, IDC_EDIT_TIPS, m_staticTips);
}


BEGIN_MESSAGE_MAP(CSetModualDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_SET_MODUAL, &CSetModualDlg::OnBnClickedBtnSetModual)
	ON_CBN_SELCHANGE(IDC_COMBO_MODUAL, &CSetModualDlg::OnCbnSelchangeComboModual)
END_MESSAGE_MAP()


// CSetModualDlg message handlers

BOOL CSetModualDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_cmbModual.AddString("0：B3C_BPSK(5)");
	m_cmbModual.AddString("1：B3C_BOC(15,2.5)");
	m_cmbModual.AddString("2：B2a_TD-AltBOC");
	m_cmbModual.AddString("3：B2a_AltBOC");
	m_cmbModual.AddString("4：B2b_TD-AltBOC");
	m_cmbModual.AddString("5：B2b_AltBOC");
	m_cmbModual.AddString("6：B2_TD-AltBOC");
	m_cmbModual.AddString("7：B2_AltBOC");
	m_cmbModual.AddString("8：B1A_TDDM");
	m_cmbModual.AddString("9：B1A_BCO(14,2)");
	m_cmbModual.AddString("10：B3A_BPSK(10)");
	m_cmbModual.AddString("11：B3AE_BPSK(10)");
	m_cmbModual.SetCurSel(0);
	m_staticTips.SetWindowText("码频率：5.115Mchip/s\r\n载波频率：1278.75MHz");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetModualDlg::OnBnClickedBtnSetModual()
{
	// TODO: Add your control notification handler code here
	SETSTA data;
	data.mod = m_cmbModual.GetCurSel();
	theApp.m_winLinkApp.SetupSTARequest(data);
}

void CSetModualDlg::OnCbnSelchangeComboModual()
{
	// TODO: Add your control notification handler code here
	int index = m_cmbModual.GetCurSel();
	switch (index)
	{
	case 0:
		m_staticTips.SetWindowText("码频率：5.115Mchip/s\r\n载波频率：1278.75MHz");
		break;
	case 1:
		m_staticTips.SetWindowText("码频率：2.575Mchip/s\r\n载波频率：1268.52MHz");
		break;
	case 2:
		m_staticTips.SetWindowText("码频率：10.23Mchip/s\r\n载波频率：1176.45MHz");
		break;
	case 3:
		m_staticTips.SetWindowText("码频率：10.23Mchip/s\r\n载波频率：1176.45MHz");
		break;
	case 4:
		m_staticTips.SetWindowText("码频率：10.23Mchip/s\r\n载波频率：1207.14MHz");
		break;
	case 5:
		m_staticTips.SetWindowText("码频率：10.23Mchip/s\r\n载波频率：1207.14MHz");
		break;
	case 6:
		m_staticTips.SetWindowText("码频率：10.23Mchip/s\r\n载波频率：1207.14MHz");
		break;
	case 7:
		m_staticTips.SetWindowText("码频率：10.23Mchip/s\r\n载波频率：1207.14MHz");
		break;
	case 8:
		m_staticTips.SetWindowText("码频率：2.046Mchip/s\r\n载波频率：1575.42MHz");
		break;
	case 9:
		m_staticTips.SetWindowText("码频率：2.046Mchip/s\r\n载波频率：1575.42MHz");
		break;
	case 10:
		m_staticTips.SetWindowText("码频率：10.23Mchip/s\r\n载波频率：1268.52MHz");
		break;
	case 11:
		m_staticTips.SetWindowText("码频率：10.23Mchip/s\r\n载波频率：1268.52MHz");
		break;
	default:
		break;
	}
}
