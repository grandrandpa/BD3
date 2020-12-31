// SetDrawDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetDrawDlg.h"


// CSetDrawDlg dialog

IMPLEMENT_DYNAMIC(CSetDrawDlg, CBCGPDialog)

CSetDrawDlg::CSetDrawDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetDrawDlg::IDD, pParent)
	, m_nPointCount(100)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CSetDrawDlg::~CSetDrawDlg()
{
}

void CSetDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ZOOM, m_CheckZoom);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_nPointCount);
	//DDV_MinMaxInt(pDX, m_nPointCount, 100, 5000);
}


BEGIN_MESSAGE_MAP(CSetDrawDlg, CBCGPDialog)
END_MESSAGE_MAP()


// CSetDrawDlg message handlers

BOOL CSetDrawDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int bZoom = 0;
	char buf[MAX_PATH];
	GetPrivateProfileString("Draw", "PointCount", "100", buf, MAX_PATH, theApp.m_strProjFile);
	m_nPointCount = atoi(buf);
	GetPrivateProfileString("Draw", "PointCount", "0", buf, MAX_PATH, theApp.m_strProjFile);
	bZoom = atoi(buf);
	m_CheckZoom.SetCheck(bZoom);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CSetDrawDlg::SaveConfigure()
{
	int bZoom = 0;
	CString strText;
	UpdateData(TRUE);
	if(theApp.m_strProjFile.IsEmpty())
		return;
	strText.Format("%d", m_nPointCount);
	WritePrivateProfileString("Draw", "PointCount", strText, theApp.m_strProjFile);
	bZoom = m_CheckZoom.GetCheck();
	WritePrivateProfileString("Draw", "PointCount", bZoom?"1":"0", theApp.m_strProjFile);
}
void CSetDrawDlg::Reset()
{

}