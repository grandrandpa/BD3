// SetCHADlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetCHADlg.h"


// CSetCHADlg dialog

IMPLEMENT_DYNAMIC(CSetCHADlg, CBCGPDialog)

CSetCHADlg::CSetCHADlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetCHADlg::IDD, pParent)
	, m_nID(0)
	, m_nBranch(0)
	, m_nPilot(0)
	, m_nCHID(0)
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE);

}

CSetCHADlg::~CSetCHADlg()
{
}

void CSetCHADlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CHA_ID, m_cmbID);
	DDX_Control(pDX, IDC_COMBO_CHA_BRANCH, m_cmbBranch);
	DDX_Control(pDX, IDC_COMBO_CHA_PILOT, m_cmbPilot);
	DDX_Control(pDX, IDC_COMBO_CHA_CHID, m_cmbCHID);
	DDX_CBIndex(pDX, IDC_COMBO_CHA_ID, m_nID);
	DDX_CBIndex(pDX, IDC_COMBO_CHA_BRANCH, m_nBranch);
	DDX_CBIndex(pDX, IDC_COMBO_CHA_PILOT, m_nPilot);
	DDX_CBIndex(pDX, IDC_COMBO_CHA_CHID, m_nCHID);
}


BEGIN_MESSAGE_MAP(CSetCHADlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_CHA_DEFAULT, &CSetCHADlg::OnBnClickedBtnChaDefault)
	ON_BN_CLICKED(IDC_BTN_CHA_SET, &CSetCHADlg::OnBnClickedBtnChaSet)
	ON_BN_CLICKED(IDC_BTN_CHA_CHECK, &CSetCHADlg::OnBnClickedBtnChaCheck)
END_MESSAGE_MAP()


// CSetCHADlg message handlers

BOOL CSetCHADlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int i=0;
	CString str;
	for (i=0; i<64; i++)
	{
		str.Format("%02d", i+1);
		m_cmbID.InsertString(i, str);
		m_cmbCHID.InsertString(i, str);
	}
	m_cmbID.SetCurSel(0);
	m_cmbCHID.SetCurSel(0);

	for(i=0; i<MAXFREQ; i++)
	{
		m_cmbBranch.InsertString(i, strFREQ[i]);
	}
	m_cmbBranch.SetCurSel(0);

	m_cmbPilot.InsertString(0, "无");
	m_cmbPilot.InsertString(1, "数据通道");
	m_cmbPilot.InsertString(2, "导频通道");
	m_cmbPilot.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetCHADlg::OnBnClickedBtnChaDefault()
{
	// TODO: Add your control notification handler code here
}

void CSetCHADlg::OnBnClickedBtnChaSet()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SETCHA data;
	GetChannel(&data);
	theApp.m_winLinkApp.SetupCHARequest(data);
	BCGPMessageBox("参数设置成功");
}

void CSetCHADlg::OnBnClickedBtnChaCheck()
{
	// TODO: Add your control notification handler code here
}

void CSetCHADlg::GetChannel(SETCHA* data)
{
	UpdateData(TRUE);
	data->id = m_nID+1;
	data->branch = ItemToBranch(m_nBranch);
	data->pilot = m_nPilot;
	data->chId = m_nCHID+1;
}

void CSetCHADlg::SetChannel(SETCHA data)
{
	m_nID = data.id-1;
	m_nBranch = BranchToitem(data.branch);
	m_nPilot = data.pilot;
	m_nCHID = data.chId-1;
	UpdateData(FALSE);
	BCGPMessageBox("参数查询成功");
}
void CSetCHADlg::Reset()
{
	m_nID = 0;
	m_nBranch = 0;
	m_nPilot = 0;
	m_nCHID = 0;
	UpdateData(FALSE);
}