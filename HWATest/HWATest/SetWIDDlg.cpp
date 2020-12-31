// SetWIDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetWIDDlg.h"


// CSetWIDDlg dialog

IMPLEMENT_DYNAMIC(CSetWIDDlg, CBCGPDialog)

CSetWIDDlg::CSetWIDDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetWIDDlg::IDD, pParent)
	, m_nID(0)
	, m_nBranch(0)
	, m_nBandwidth(0)
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE);

}

CSetWIDDlg::~CSetWIDDlg()
{
}

void CSetWIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WID_ID, m_cmbID);
	DDX_Control(pDX, IDC_COMBO_WID_BRANCH, m_cmbBranch);
	DDX_Control(pDX, IDC_COMBO_WID_BANDWIDTH, m_cmbBandwidth);
	DDX_CBIndex(pDX, IDC_COMBO_WID_ID, m_nID);
	DDX_CBIndex(pDX, IDC_COMBO_WID_BRANCH, m_nBranch);
	DDX_CBIndex(pDX, IDC_COMBO_WID_BANDWIDTH, m_nBandwidth);
}


BEGIN_MESSAGE_MAP(CSetWIDDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_WID_DEFAULT, &CSetWIDDlg::OnBnClickedBtnWidDefault)
	ON_BN_CLICKED(IDC_BTN_WID_SET, &CSetWIDDlg::OnBnClickedBtnWidSet)
	ON_BN_CLICKED(IDC_BTN_WID_CHECK, &CSetWIDDlg::OnBnClickedBtnWidCheck)
	ON_CBN_SELCHANGE(IDC_COMBO_WID_BRANCH, &CSetWIDDlg::OnCbnSelchangeComboWidBranch)
END_MESSAGE_MAP()


// CSetWIDDlg message handlers

BOOL CSetWIDDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here m_cmbBandwidth
	int i=0;
	CString str;
	for (i=0; i<64; i++)
	{
		str.Format("%02d", i+1);
		m_cmbID.InsertString(i, str);
	}
	m_cmbID.SetCurSel(0);

	for(i=0; i<MAXFREQ; i++)
	{
		m_cmbBranch.InsertString(i, strFREQ[i]);
	}
	m_cmbBranch.SetCurSel(0);

	//m_cmbBandwidth.InsertString(0, "信号全部带宽");//量化为 MHz
	//m_cmbBandwidth.InsertString(1, "信号主瓣带宽");
	//m_cmbBandwidth.InsertString(2, "2倍信号主瓣带宽");
	//m_cmbBandwidth.InsertString(3, "3倍信号主瓣带宽");
	m_cmbBandwidth.InsertString(0, "4MHz");
	m_cmbBandwidth.InsertString(1, "16MHz");
	m_cmbBandwidth.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetWIDDlg::OnCbnSelchangeComboWidBranch()
{
	// TODO: Add your control notification handler code here
	int index = m_cmbBranch.GetCurSel();
	m_cmbBandwidth.ResetContent();
	switch (index)
	{
	case 0:
		m_cmbBandwidth.InsertString(0, "4MHz");
		m_cmbBandwidth.InsertString(1, "16MHz");
		break;
	case 1:
		m_cmbBandwidth.InsertString(0, "4MHz");
		m_cmbBandwidth.InsertString(1, "16MHz");
		break;
	case 2:
		m_cmbBandwidth.InsertString(0, "8MHz");
		m_cmbBandwidth.InsertString(1, "16MHz");
		m_cmbBandwidth.InsertString(2, "40MHz");
		break;
	case 3:
		m_cmbBandwidth.InsertString(0, "32MHz");
		m_cmbBandwidth.InsertString(1, "40MHz");
		break;
	case 4:
		m_cmbBandwidth.InsertString(0, "20MHz");
		m_cmbBandwidth.InsertString(1, "40MHz");
		break;
	case 5:
		m_cmbBandwidth.InsertString(0, "20MHz");
		m_cmbBandwidth.InsertString(1, "40MHz");
		break;
	case 6:
		m_cmbBandwidth.InsertString(0, "50MHz");
		m_cmbBandwidth.InsertString(1, "70MHz");
		break;
	case 7:
		m_cmbBandwidth.InsertString(0, "20MHz");
		m_cmbBandwidth.InsertString(1, "40MHz");
		break;
	case 8:
		m_cmbBandwidth.InsertString(0, "20MHz");
		m_cmbBandwidth.InsertString(1, "40MHz");
		break;
	case 9:
		m_cmbBandwidth.InsertString(0, "10MHz");
		m_cmbBandwidth.InsertString(1, "20MHz");
		break;
	case 10:
		m_cmbBandwidth.InsertString(0, "20MHz");
		m_cmbBandwidth.InsertString(1, "40MHz");
		break;
	case 11:
		m_cmbBandwidth.InsertString(0, "20MHz");
		m_cmbBandwidth.InsertString(1, "40MHz");
		break;
	case 12:
		m_cmbBandwidth.InsertString(0, "16MHz");
		m_cmbBandwidth.InsertString(1, "32MHz");
		break;
	default:
		break;
	}
	m_cmbBandwidth.SetCurSel(0);
}

void CSetWIDDlg::OnBnClickedBtnWidDefault()
{
	// TODO: Add your control notification handler code here
	m_cmbID.SetCurSel(0);
	m_cmbBranch.SetCurSel(0);
	m_cmbBandwidth.SetCurSel(0);
}

void CSetWIDDlg::OnBnClickedBtnWidSet()
{
	// TODO: Add your control notification handler code here
	SETWID data;
	GetBandwidth(&data);
	theApp.m_winLinkApp.SetupWIDRequest(data);
	BCGPMessageBox("参数设置成功");
}

void CSetWIDDlg::OnBnClickedBtnWidCheck()
{
	// TODO: Add your control notification handler code here
}

void CSetWIDDlg::GetBandwidth(SETWID* data)
{
	UpdateData(TRUE);
	data->id = m_nID+1;
	data->branch = ItemToBranch(m_nBranch);
	data->width = m_nBandwidth;
}

void CSetWIDDlg::SetBandwidth(SETWID data)
{
	m_nID = data.id - 1;
	m_nBranch = BranchToitem(data.branch);
	m_nBandwidth = data.width;
	UpdateData(FALSE);

	BCGPMessageBox("参数查询成功");
}
void CSetWIDDlg::Reset()
{

}
