// SetBGTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetBGTDlg.h"


// CSetBGTDlg dialog

IMPLEMENT_DYNAMIC(CSetBGTDlg, CBCGPDialog)

CSetBGTDlg::CSetBGTDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetBGTDlg::IDD, pParent)
	, m_nGnssID(0)
	, m_nGnssWn(0)
	, m_nGnssT0(0)
	, m_dbGnssA0(0)
	, m_dbGnssA1(0)
	, m_dbGnssA2(0)
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE, TRUE);
}

CSetBGTDlg::~CSetBGTDlg()
{
}

void CSetBGTDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ID, m_editGnssID);
	DDX_Control(pDX, IDC_EDIT_WN, m_editGnssWn);
	DDX_Control(pDX, IDC_EDIT_T0, m_editGnssT0);
	DDX_Control(pDX, IDC_EDIT_A0, m_editGnssA0);
	DDX_Control(pDX, IDC_EDIT_A1, m_editGnssA1);
	DDX_Control(pDX, IDC_EDIT_A2, m_editGnssA2);
	DDX_Text(pDX, IDC_EDIT_ID, m_nGnssID);
	DDX_Text(pDX, IDC_EDIT_WN, m_nGnssWn);
	DDX_Text(pDX, IDC_EDIT_T0, m_nGnssT0);
	DDX_Text(pDX, IDC_EDIT_A0, m_dbGnssA0);
	DDX_Text(pDX, IDC_EDIT_A1, m_dbGnssA1);
	DDX_Text(pDX, IDC_EDIT_A2, m_dbGnssA2);
}


BEGIN_MESSAGE_MAP(CSetBGTDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_SET_BGT, &CSetBGTDlg::OnBnClickedBtnSetBgt)
END_MESSAGE_MAP()


// CSetBGTDlg message handlers

BOOL CSetBGTDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetBGTDlg::OnBnClickedBtnSetBgt()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SETBGT data;
	data.id = m_nGnssID;
	data.wn = m_nGnssWn;
	data.t0 = m_nGnssT0;
	data.a0 = m_dbGnssA0;
	data.a1 = m_dbGnssA1;
	data.a2 = m_dbGnssA2;
	theApp.m_winLinkApp.SetupBGTRequest(data);
	BCGPMessageBox("参数设置成功");
}
void CSetBGTDlg::Reset()
{
	m_nGnssID = 0;
	m_nGnssWn = 0;
	m_nGnssT0 = 0;
	m_dbGnssA0 = 0;
	m_dbGnssA1 = 0;
	m_dbGnssA2 = 0;
	UpdateData(FALSE);
}