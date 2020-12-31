// SetStaticDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetStaticDlg.h"


// CSetStaticDlg dialog

IMPLEMENT_DYNAMIC(CSetStaticDlg, CBCGPDialog)

CSetStaticDlg::CSetStaticDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetStaticDlg::IDD, pParent)
	, m_bCheckStatic(FALSE)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CSetStaticDlg::~CSetStaticDlg()
{
}

void CSetStaticDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_POS, m_checkPos);
	DDX_Control(pDX, IDC_CHECK_RAN, m_checkRan);
	DDX_Control(pDX, IDC_CHECK_SNR, m_checkSnr);
	DDX_Control(pDX, IDC_CHECK_START, m_checkStart);
	DDX_Radio(pDX, IDC_RADIO_STATIC, m_bCheckStatic);
}

BEGIN_MESSAGE_MAP(CSetStaticDlg, CBCGPDialog)
END_MESSAGE_MAP()


// CSetStaticDlg message handlers

BOOL CSetStaticDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetStaticDlg::SaveConfigure()
{
	UpdateData(TRUE);
	int flag = 0;
	if(theApp.m_strProjFile.IsEmpty())
		return;
	flag = m_checkPos.GetCheck();
	WritePrivateProfileString("STATIC", "pos", flag?"1":"0", theApp.m_strProjFile);
	flag = m_checkRan.GetCheck();
	WritePrivateProfileString("STATIC", "ran", flag?"1":"0", theApp.m_strProjFile);
	flag = m_checkSnr.GetCheck();
	WritePrivateProfileString("STATIC", "snr", flag?"1":"0", theApp.m_strProjFile);
	flag = m_checkStart.GetCheck();
	WritePrivateProfileString("STATIC", "start", flag?"1":"0", theApp.m_strProjFile);
	WritePrivateProfileString("STATIC", "dynamic", m_bCheckStatic?"0":"1", theApp.m_strProjFile);
}
void CSetStaticDlg::Reset()
{

}
