// SetWORKMODDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetWORKMODDlg.h"



// CSetWORKMODDlg dialog

IMPLEMENT_DYNAMIC(CSetWORKMODDlg, CBCGPDialog)

CSetWORKMODDlg::CSetWORKMODDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetWORKMODDlg::IDD, pParent)
	, m_nMode(0)
	, m_nsvstart(0)
	, m_nsvend(0)
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE);
}

CSetWORKMODDlg::~CSetWORKMODDlg()
{
}

void CSetWORKMODDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_WORKMOD, m_cmbMode);
	DDX_CBIndex(pDX, IDC_COMBO_WORKMOD, m_nMode);
	DDX_Control(pDX, IDC_COMBO_SATEID_START, m_cmbsvstart);
	DDX_CBIndex(pDX, IDC_COMBO_SATEID_START, m_nsvstart);
	DDX_Control(pDX, IDC_COMBO_SATEID_END, m_cmbsvend);
	DDX_CBIndex(pDX, IDC_COMBO_SATEID_END, m_nsvend);
}


BEGIN_MESSAGE_MAP(CSetWORKMODDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_WORK_SET, &CSetWORKMODDlg::OnBnClickedBtnWorkSet)
END_MESSAGE_MAP()


// CSetWORKMODDlg message handlers


BOOL CSetWORKMODDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int i=0;
	CString str;
	for (i=0; i<64; i++)
	{
		str.Format("%02d", i+1);
		m_cmbsvstart.InsertString(i, str);
		m_cmbsvend.InsertString(i, str);
	}
	m_cmbsvstart.SetCurSel(0);
	m_cmbsvend.SetCurSel(0);


	m_cmbMode.InsertString(0, "星地对接模式");
	m_cmbMode.InsertString(1, "对天模式");
	m_cmbMode.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CSetWORKMODDlg::OnBnClickedBtnWorkSet()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	WORKMOD data;
	GetWorkData(&data);
	theApp.m_winLinkApp.SetupWORKRequest(data);
	BCGPMessageBox("参数设置成功");
}


void CSetWORKMODDlg::GetWorkData(WORKMOD* data)
{
	UpdateData(TRUE);
	if (m_cmbMode.GetCurSel()==0)//星地对接模式
	{
		data->mode = 0x00;
	} 
	else//对天模式
	{
		data->mode = 0xFF;
	}
	data->svstart = m_nsvstart+1;
	data->svend	= m_nsvend+1;
	
}
