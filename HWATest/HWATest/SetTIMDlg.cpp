// SetTIMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetTIMDlg.h"


// CSetTIMDlg dialog

IMPLEMENT_DYNAMIC(CSetTIMDlg, CBCGPDialog)

CSetTIMDlg::CSetTIMDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetTIMDlg::IDD, pParent)
	, m_nDelay(0)
	, m_nZero(0)
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE);

}

CSetTIMDlg::~CSetTIMDlg()
{
}

void CSetTIMDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TIM_DELAY, m_editDelay);
	DDX_Control(pDX, IDC_EDIT_TIM_ZERO, m_editZero);
	DDX_Text(pDX, IDC_EDIT_TIM_DELAY, m_nDelay);
	DDX_Text(pDX, IDC_EDIT_TIM_ZERO, m_nZero);
}


BEGIN_MESSAGE_MAP(CSetTIMDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_TIM_DEFAULT, &CSetTIMDlg::OnBnClickedBtnTimDefault)
	ON_BN_CLICKED(IDC_BTN_TIM_SET, &CSetTIMDlg::OnBnClickedBtnTimSet)
	ON_BN_CLICKED(IDC_BTN_TIM_CHECK, &CSetTIMDlg::OnBnClickedBtnTimCheck)
END_MESSAGE_MAP()


// CSetTIMDlg message handlers

BOOL CSetTIMDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_editDelay.SetWindowText("0.0");
	m_editZero.SetWindowText("0.0");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetTIMDlg::OnBnClickedBtnTimDefault()
{
	// TODO: Add your control notification handler code here
	m_editDelay.SetWindowText("0.0");
	m_editZero.SetWindowText("0.0");
}

void CSetTIMDlg::OnBnClickedBtnTimSet()
{
	// TODO: Add your control notification handler code here
	SETTIM data;
	GetCableDelay(&data);
	theApp.m_winLinkApp.SetupTIMRequest(data);
	BCGPMessageBox("参数设置成功");
}

void CSetTIMDlg::OnBnClickedBtnTimCheck()
{
	// TODO: Add your control notification handler code here
}

void CSetTIMDlg::GetCableDelay(SETTIM* data)
{
	UpdateData(TRUE);
	data->delay = m_nDelay;
	data->zeroVal = m_nZero;
}

void CSetTIMDlg::SetCableDelay(SETTIM data)
{
	CString str;
	str.Format("%.0f", data.delay);
	m_editDelay.SetWindowText(str);
	str.Format("%.0f", data.zeroVal);
	m_editZero.SetWindowText(str);
}
void CSetTIMDlg::Reset()
{

}
