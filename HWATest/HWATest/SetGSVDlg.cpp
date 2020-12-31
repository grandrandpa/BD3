// SetGSVDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetGSVDlg.h"


// CSetGSVDlg dialog

IMPLEMENT_DYNAMIC(CSetGSVDlg, CBCGPDialog)

CSetGSVDlg::CSetGSVDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetGSVDlg::IDD, pParent)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CSetGSVDlg::~CSetGSVDlg()
{
}

void CSetGSVDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_GSV, m_wndListCtrl);
	DDX_Control(pDX, IDC_CHECK_ALL, m_CheckAll);
}


BEGIN_MESSAGE_MAP(CSetGSVDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_CHECK_ALL, &CSetGSVDlg::OnBnClickedCheckAll)
END_MESSAGE_MAP()


// CSetGSVDlg message handlers

BOOL CSetGSVDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CString strText;
	DWORD dwStyle = m_wndListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_wndListCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wndListCtrl.SetExtendedStyle(dwStyle);
	m_wndListCtrl.InsertColumn(0, "卫星号", LVCFMT_CENTER, 80);
	m_wndListCtrl.InsertColumn(1, "卫星类型", LVCFMT_RIGHT, 250);
	for(int i=0; i<64; i++)
	{
		strText.Format("%02d", i+1);
		m_wndListCtrl.InsertItem(i, strText);
		if (i<5)
		{
			m_wndListCtrl.SetItemText(i, 1, "GEO");
		} 
		else if (i<10)
		{
			m_wndListCtrl.SetItemText(i, 1, "IGSO");
		} 
		else if(i<30)
		{
			m_wndListCtrl.SetItemText(i, 1, "MEO");
		}
		else if (i<32)
		{
			strText.Format("I%dS", i-29);
			m_wndListCtrl.SetItemText(i, 1, strText);
		} 
		else
		{
			strText.Format("M%dS", i-31);
			m_wndListCtrl.SetItemText(i, 1, strText);
		}
	}
	int length=0,item=0,count=0;
	char buf[MAX_PATH], output[MAX_PATH];
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	ZeroMemory(output, sizeof(char)*MAX_PATH);
	strText = "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,";
	GetPrivateProfileString("POSMOD", "SatSel", strText, buf, MAX_PATH, theApp.m_strProjFile);
	length = strlen(buf);
	count = Pack_SplitChars(buf, length, (u1*)output);
	for (int i=0; i<count; i++)
	{
		item = output[i]-1;
		if(item < 0)
			continue;
		m_wndListCtrl.SetCheck(item, 1);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetGSVDlg::OnBnClickedCheckAll()
{
	// TODO: Add your control notification handler code here
	int bcheck = m_CheckAll.GetCheck();
	int count = m_wndListCtrl.GetItemCount();
	for (int i=0; i<count; i++)
	{
		m_wndListCtrl.SetCheck(i, bcheck);
	}
}

void CSetGSVDlg::SaveConfigure()
{
	// TODO: Add your control notification handler code here
	int flag = 0;
	CString strText, strTemp;
	strTemp.Empty();
	strText.Empty();
	int count = m_wndListCtrl.GetItemCount();
	for (int i=0; i<count; i++)
	{
		if (m_wndListCtrl.GetCheck(i))
		{
			strTemp.Format("%d,", i+1);
			strText += strTemp;
		}
	}
	WritePrivateProfileString("POSMOD", "SatSel", strText, theApp.m_strProjFile);
}
void CSetGSVDlg::Reset()
{
	m_CheckAll.SetCheck(TRUE);
	OnBnClickedCheckAll();
}