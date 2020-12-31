// SetPilotDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetPilotDlg.h"


// CSetPilotDlg dialog

IMPLEMENT_DYNAMIC(CSetPilotDlg, CBCGPDialog)

CSetPilotDlg::CSetPilotDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetPilotDlg::IDD, pParent)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CSetPilotDlg::~CSetPilotDlg()
{
}

void CSetPilotDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PILOT_ACQ, m_cmbPilot);
	DDX_Control(pDX, IDC_COMBO_PILOT_TRACK, m_cmbTrack);
	DDX_Control(pDX, IDC_COMBO_ACQ_BRANCH, m_cmbAcqBranch);
	DDX_Control(pDX, IDC_COMBO_TRACK_BRANCH, m_cmbTrackBranch);
}


BEGIN_MESSAGE_MAP(CSetPilotDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_SET_PILOT_TRACK, &CSetPilotDlg::OnBnClickedBtnSetPilotTrack)
	ON_BN_CLICKED(IDC_BTN_SET_PILOT_ACQ, &CSetPilotDlg::OnBnClickedBtnSetPilotAcq)
END_MESSAGE_MAP()


// CSetPilotDlg message handlers

BOOL CSetPilotDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	int i=0;
	// TODO:  Add extra initialization here
	m_cmbPilot.AddString("数据模式");
	m_cmbPilot.AddString("导频模式");
	m_cmbPilot.AddString("联合模式");
	m_cmbPilot.SetCurSel(0);

	m_cmbTrack.AddString("数据模式");
	m_cmbTrack.AddString("导频模式");
	m_cmbTrack.AddString("联合模式");
	m_cmbTrack.SetCurSel(0);
	for (i=2; i<MAXFREQ; i++)
	{
		if (i!=7 && i!= 8)
		{
			m_cmbAcqBranch.AddString(strFREQ[i]);
			m_cmbTrackBranch.AddString(strFREQ[i]);
		}
	}
	m_cmbAcqBranch.SetCurSel(0);
	m_cmbTrackBranch.SetCurSel(0);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetPilotDlg::OnBnClickedBtnSetPilotTrack()
{
	// TODO: Add your control notification handler code here 
	SETPILOT data;
	CString strText;
	ZeroMemory(&data, sizeof(SETPILOT));
	m_cmbTrackBranch.GetWindowText(strText);
	data.ID = SET_TRK_PILOT;
	data.branch = GetBranch(strText);
	data.mode = m_cmbTrack.GetCurSel();
	theApp.m_winLinkApp.SetupPILOTRequest(data);
	BCGPMessageBox("参数设置成功");
}

void CSetPilotDlg::OnBnClickedBtnSetPilotAcq()
{
	// TODO: Add your control notification handler code here
	SETPILOT data;
	CString strText;
	ZeroMemory(&data, sizeof(SETPILOT));
	m_cmbAcqBranch.GetWindowText(strText);
	data.ID = SET_ACQ_PILOT;
	data.branch = GetBranch(strText);
	data.mode = m_cmbPilot.GetCurSel();
	theApp.m_winLinkApp.SetupPILOTRequest(data);
	BCGPMessageBox("参数设置成功");
}
int CSetPilotDlg::GetBranch(CString strText)
{
	int branch=0;

	if("B1I" == strText)
	{
		branch = 1;
	}
	else if("B1Q" == strText)
	{
		branch = 2;
	}
	else if("B1C" == strText)
	{
		branch = 3;
	}
	else if("B1A" == strText)
	{
		branch = 4;
	}
	else if("B2a" == strText)
	{
		branch = 13;
	}
	else if("B2b" == strText)
	{
		branch = 14;
	}
	else if("B2" == strText)
	{
		branch = 15;
	}
	else if("B3I" == strText)
	{
		branch = 21;
	}
	else if("B3Q" == strText)
	{
		branch = 22;
	}
	else if("B3C" == strText)
	{
		branch = 23;
	}
	else if("B3A" == strText)
	{
		branch = 24;
	}
	else if("B3AE" == strText)
	{
		branch = 25;
	}
	else if("Bs" == strText)
	{
		branch = 31;
	}
	return branch;
}
