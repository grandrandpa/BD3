// SetTimModDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetTimModDlg.h"


// CSetTimModDlg dialog

IMPLEMENT_DYNAMIC(CSetTimModDlg, CBCGPDialog)

CSetTimModDlg::CSetTimModDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetTimModDlg::IDD, pParent)
	, m_bRadioSingle(FALSE)
	, m_dAlt(0)
	, m_dLatDegree(0)
	, m_dLatCent(0)
	, m_dLatSec(0)
	, m_dLonDegree(0)
	, m_dLonCent(0)
	, m_dLonSec(0)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CSetTimModDlg::~CSetTimModDlg()
{
}

void CSetTimModDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_SINGLE, m_bRadioSingle);
	DDX_Control(pDX, IDC_CHECK_CURRENT, m_checkPos);
	DDX_Control(pDX, IDC_COMBO_ID, m_cmbSatID);
	DDX_Control(pDX, IDC_EDIT_ALT, m_editAlt);
	DDX_Control(pDX, IDC_EDIT_LAT_DEGREE, m_editLatDegree);
	DDX_Control(pDX, IDC_EDIT_LAT_CENT, m_editLatCent);
	DDX_Control(pDX, IDC_EDIT_LAT_SEC, m_editLatSec);
	DDX_Control(pDX, IDC_EDIT_LON_DEGREE, m_editLonDegree);
	DDX_Control(pDX, IDC_EDIT_LON_CENT, m_editLonCent);
	DDX_Control(pDX, IDC_EDIT_LON_SEC, m_editLonSec);
	DDX_Control(pDX, IDC_BTN_GET_LOCAL, m_btnGetLocal);
	DDX_Text(pDX, IDC_EDIT_ALT, m_dAlt);
	DDX_Text(pDX, IDC_EDIT_LAT_DEGREE, m_dLatDegree);
	DDX_Text(pDX, IDC_EDIT_LAT_CENT, m_dLatCent);
	DDX_Text(pDX, IDC_EDIT_LAT_SEC, m_dLatSec);
	DDX_Text(pDX, IDC_EDIT_LON_DEGREE, m_dLonDegree);
	DDX_Text(pDX, IDC_EDIT_LON_CENT, m_dLonCent);
	DDX_Text(pDX, IDC_EDIT_LON_SEC, m_dLonSec);
	DDX_Control(pDX, IDC_COMBO_BRANCH, m_cmbBranch);
}


BEGIN_MESSAGE_MAP(CSetTimModDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_GET_LOCAL, &CSetTimModDlg::OnBnClickedBtnGetLocal)
	ON_BN_CLICKED(IDC_BTN_SET, &CSetTimModDlg::OnBnClickedBtnSet)
	ON_BN_CLICKED(IDC_RADIO_SINGLE, &CSetTimModDlg::OnBnClickedRadioSingle)
	ON_BN_CLICKED(IDC_RADIO_MORE, &CSetTimModDlg::OnBnClickedRadioMore)
	ON_BN_CLICKED(IDC_CHECK_CURRENT, &CSetTimModDlg::OnBnClickedCheckCurrent)
END_MESSAGE_MAP()


// CSetTimModDlg message handlers

BOOL CSetTimModDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int i=0;
	CString strText;
	for (i=0; i<64; i++)
	{
		strText.Format("%d", i+1);
		m_cmbSatID.AddString(strText);
	}
	m_cmbSatID.SetCurSel(0);
	for (i=0; i<MAXFREQ; i++)
	{
		m_cmbBranch.AddString(strFREQ[i]);
	}
	m_cmbBranch.SetCurSel(0);
	LoadConfig();
	OnBnClickedRadioSingle();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CSetTimModDlg::LoadConfig()
{
	CString strText;
	double degree=0,cent=0, sec = 0;

	GetDegree(theApp.m_CurPosition.lat, &degree, &cent, &sec);
	strText.Format("%.0f", degree);
	m_editLatDegree.SetWindowText(strText);
	strText.Format("%.0f", cent);
	m_editLatCent.SetWindowText(strText);
	strText.Format("%.4f", sec);
	m_editLatSec.SetWindowText(strText);

	GetDegree(theApp.m_CurPosition.lon, &degree, &cent, &sec);
	strText.Format("%.0f", degree);
	m_editLonDegree.SetWindowText(strText);
	strText.Format("%.0f", cent);
	m_editLonCent.SetWindowText(strText);
	strText.Format("%.4f", sec);
	m_editLonSec.SetWindowText(strText);

	strText.Format("%f", theApp.m_CurPosition.alt);
	m_editAlt.SetWindowText(strText);

}
void CSetTimModDlg::GetConfig(SETTMD* data)
{
	UpdateData(TRUE);
	data->mode = (m_bRadioSingle)?1:0;
	data->svId = m_cmbSatID.GetCurSel()+1;
	data->branch = ItemToBranch(m_cmbBranch.GetCurSel());
	data->flag = (m_bRadioSingle)?((m_checkPos.GetCheck())?1:0):0;
	if (m_checkPos.GetCheck() || !m_bRadioSingle)
	{
		data->lat = m_dLatDegree + (m_dLatCent + m_dLatSec/60.0)/60.0;
		data->lon = m_dLonDegree + (m_dLonCent + m_dLonSec/60.0)/60.0;
		data->alt = m_dAlt;
	} 
	else
	{
		data->lat = 0;
		data->lon = 0;
		data->alt = 0;
	}
}
void CSetTimModDlg::OnBnClickedBtnGetLocal()
{
	// TODO: Add your control notification handler code here
	LoadConfig();
}

void CSetTimModDlg::OnBnClickedBtnSet()
{
	// TODO: Add your control notification handler code here
	SETTMD data;
	GetConfig(&data);
	theApp.m_winLinkApp.SetupTMDRequest(data);
	BCGPMessageBox("参数设置成功");
}
void CSetTimModDlg::GetDegree(double data, double *degree, double *cent, double *sec)
{
	unsigned int b0=0,b1=0,b2=0;
	double a0=0,a1=0,a2=0,a3=0;
	b0 = data;
	a0 = data - b0;
	a1 = a0*60;
	b1 = a1;
	a2 = a1 - b1;
	a3 = a2*60;
	*degree = b0;
	*cent = b1;
	*sec = a3;
}
void CSetTimModDlg::OnBnClickedRadioSingle()
{
	// TODO: Add your control notification handler code here
	m_checkPos.EnableWindow(FALSE);
	m_cmbSatID.EnableWindow(TRUE);
	m_cmbBranch.EnableWindow(TRUE);
	m_btnGetLocal.EnableWindow(TRUE);
	m_editLatDegree.EnableWindow(TRUE);
	m_editLatCent.EnableWindow(TRUE);
	m_editLatSec.EnableWindow(TRUE);

	m_editLonDegree.EnableWindow(TRUE);
	m_editLonCent.EnableWindow(TRUE);
	m_editLonSec.EnableWindow(TRUE);
	m_editAlt.EnableWindow(TRUE);
}

void CSetTimModDlg::OnBnClickedRadioMore()
{
	// TODO: Add your control notification handler code here
	m_checkPos.EnableWindow(TRUE);
	m_cmbSatID.EnableWindow(FALSE);
	m_cmbBranch.EnableWindow(FALSE);
	m_btnGetLocal.EnableWindow(FALSE);
	m_editLatDegree.EnableWindow(FALSE);
	m_editLatCent.EnableWindow(FALSE);
	m_editLatSec.EnableWindow(FALSE);
	m_editLonDegree.EnableWindow(FALSE);
	m_editLonCent.EnableWindow(FALSE);
	m_editLonSec.EnableWindow(FALSE);
	m_editAlt.EnableWindow(FALSE);
}

void CSetTimModDlg::OnBnClickedCheckCurrent()
{
	// TODO: Add your control notification handler code here
	if (m_checkPos.GetCheck())
	{
		m_cmbSatID.EnableWindow(FALSE);
		m_cmbBranch.EnableWindow(FALSE);
		m_btnGetLocal.EnableWindow(TRUE);
		m_editLatDegree.EnableWindow(TRUE);
		m_editLatCent.EnableWindow(TRUE);
		m_editLatSec.EnableWindow(TRUE);
		m_editLonDegree.EnableWindow(TRUE);
		m_editLonCent.EnableWindow(TRUE);
		m_editLonSec.EnableWindow(TRUE);
		m_editAlt.EnableWindow(TRUE);
	} 
	else
	{
		m_cmbSatID.EnableWindow(FALSE);
		m_cmbBranch.EnableWindow(FALSE);
		m_btnGetLocal.EnableWindow(FALSE);
		m_editLatDegree.EnableWindow(FALSE);
		m_editLatCent.EnableWindow(FALSE);
		m_editLatSec.EnableWindow(FALSE);
		m_editLonDegree.EnableWindow(FALSE);
		m_editLonCent.EnableWindow(FALSE);
		m_editLonSec.EnableWindow(FALSE);
		m_editAlt.EnableWindow(FALSE);
	}
}
void CSetTimModDlg::Reset()
{

}
