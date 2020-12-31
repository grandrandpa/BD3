// SetLocalDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetLocalDlg.h"


// CSetLocalDlg dialog

IMPLEMENT_DYNAMIC(CSetLocalDlg, CBCGPDialog)

CSetLocalDlg::CSetLocalDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetLocalDlg::IDD, pParent)
	, m_strSatElv(_T("5.0"))
	, m_strPosAlt(_T("60.00"))
	, m_strPosLat(_T("40.00"))
	, m_strPosLon(_T("116.00"))
{
	EnableVisualManagerStyle();
}

CSetLocalDlg::~CSetLocalDlg()
{
}

void CSetLocalDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ELV, m_editElv);
	DDX_Control(pDX, IDC_COMBO_POS_TYPE, m_cmbLocalType);
	DDX_Control(pDX, IDC_EDIT_ALT_TIPS, m_editAltTips);
	DDX_Control(pDX, IDC_EDIT_LAT_TIPS, m_editLatTips);
	DDX_Control(pDX, IDC_EDIT_LON_TIPS, m_editLonTips);
	DDX_Control(pDX, IDC_EDIT_POS_ALT, m_editAlt);
	DDX_Control(pDX, IDC_EDIT_POS_LAT, m_editLat);
	DDX_Control(pDX, IDC_EDIT_POS_LON, m_editLon);
	DDX_Text(pDX, IDC_EDIT_ELV, m_strSatElv);
	DDX_Text(pDX, IDC_EDIT_POS_ALT, m_strPosAlt);
	DDX_Text(pDX, IDC_EDIT_POS_LAT, m_strPosLat);
	DDX_Text(pDX, IDC_EDIT_POS_LON, m_strPosLon);
}


BEGIN_MESSAGE_MAP(CSetLocalDlg, CBCGPDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_POS_TYPE, &CSetLocalDlg::OnCbnSelchangeComboPosType)
END_MESSAGE_MAP()


// CSetLocalDlg message handlers

BOOL CSetLocalDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int type=0;
	m_editLatTips.SetWindowText("纬度(度):");//
	m_editLonTips.SetWindowText("经度(度):");//m_editLatTips
	m_editAltTips.SetWindowText("高程(米):");//m_editLonTips
	m_cmbLocalType.AddString("BLH形式");
	m_cmbLocalType.AddString("XYZ形式");
	m_cmbLocalType.SetCurSel(0);
	char buf[MAX_PATH];
	if (!theApp.m_strProjFile.IsEmpty())
	{
		ZeroMemory(buf, sizeof(char)*MAX_PATH);
		type = GetPrivateProfileInt("Local", "type", 0, theApp.m_strProjFile);
		m_cmbLocalType.SetCurSel(type);
		ZeroMemory(buf, sizeof(char)*MAX_PATH);
		GetPrivateProfileString("Local", "lat", "40.00", buf, MAX_PATH, theApp.m_strProjFile);
		m_strPosLat = CString(buf);
		ZeroMemory(buf, sizeof(char)*MAX_PATH);
		GetPrivateProfileString("Local", "lon", "116.00", buf, MAX_PATH, theApp.m_strProjFile);
		m_strPosLon = CString(buf);
		ZeroMemory(buf, sizeof(char)*MAX_PATH);
		GetPrivateProfileString("Local", "alt", "60.00", buf, MAX_PATH, theApp.m_strProjFile);
		m_strPosAlt = CString(buf);
		ZeroMemory(buf, sizeof(char)*MAX_PATH);
		GetPrivateProfileString("Local", "elv", "5.0", buf, MAX_PATH, theApp.m_strProjFile);
		m_strSatElv = CString(buf);
	}
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetLocalDlg::OnCbnSelchangeComboPosType()
{
	// TODO: Add your control notification handler code here
	int nSel = m_cmbLocalType.GetCurSel();
	if (nSel == 1)
	{
		m_editAltTips.SetWindowText("X(米):");
		m_editLatTips.SetWindowText("Y(米):");
		m_editLonTips.SetWindowText("Z(米):");
	} 
	else
	{
		m_editAltTips.SetWindowText("高程(米):");//高程
		m_editLatTips.SetWindowText("纬度(度):");//纬度
		m_editLonTips.SetWindowText("经度(度):");//经度
	}
}

void CSetLocalDlg::SaveConfigure()
{
	int type=0;
	UpdateData(TRUE);
	type = m_cmbLocalType.GetCurSel();
	if(theApp.m_strProjFile.IsEmpty())
		return;
	WritePrivateProfileString("Local", "type", type?"1":"0", theApp.m_strProjFile);
	WritePrivateProfileString("Local", "lat", m_strPosLat, theApp.m_strProjFile);
	WritePrivateProfileString("Local", "lon", m_strPosLon, theApp.m_strProjFile);
	WritePrivateProfileString("Local", "alt", m_strPosAlt, theApp.m_strProjFile);
	WritePrivateProfileString("Local", "elv", m_strSatElv, theApp.m_strProjFile);
}
void CSetLocalDlg::Reset()
{
	m_strPosLat.Empty();
	m_strPosLon.Empty();
	m_strPosAlt.Empty();
	m_strSatElv.Empty();
	UpdateData(FALSE);
}