// SetEACDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetEACDlg.h"


// CSetEACDlg dialog

IMPLEMENT_DYNAMIC(CSetEACDlg, CBCGPDialog)

CSetEACDlg::CSetEACDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetEACDlg::IDD, pParent)
	, m_nID(0)
	, m_nPilotID(0)
	, m_nPilotBranch(0)
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE, TRUE);
}

CSetEACDlg::~CSetEACDlg()
{
}

void CSetEACDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ID, m_cmbID);
	DDX_Control(pDX, IDC_COMBO_ID_PILOT, m_cmbPilotID);
	DDX_Control(pDX, IDC_COMBO_BRANCH_PILOT, m_cmbPilotBranch);
	DDX_CBIndex(pDX, IDC_COMBO_ID, m_nID);
	DDX_CBIndex(pDX, IDC_COMBO_ID_PILOT, m_nPilotID);
	DDX_CBIndex(pDX, IDC_COMBO_BRANCH_PILOT, m_nPilotBranch);
}


BEGIN_MESSAGE_MAP(CSetEACDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_SET, &CSetEACDlg::OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CSetEACDlg message handlers

BOOL CSetEACDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int i=0;
	CString str;
	for (i=0; i<64; i++)
	{
		str.Format("%02d", i+1);
		m_cmbID.AddString(str);
		m_cmbPilotID.AddString(str);
	}
	m_cmbID.SetCurSel(m_nID);
	m_cmbPilotID.SetCurSel(m_nPilotID);


	for(i=0; i<MAXFREQ; i++)
	{
		m_cmbPilotBranch.InsertString(i, strFREQ[i]);
	}
	m_cmbPilotBranch.SetCurSel(m_nPilotBranch);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetEACDlg::OnBnClickedBtnSet()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SETEAC data;
	data.id = m_nID+1;
	data.pilotId = m_nPilotID+1;
	data.pilotBranch = ItemToBranch(m_nPilotBranch);

	theApp.m_winLinkApp.SetupEACRequest(data);
	BCGPMessageBox("参数设置成功");
}
void CSetEACDlg::Reset()
{
	m_nID = 0;
	m_nPilotID = 0;
	m_nPilotBranch = 0;
	UpdateData(FALSE);
}