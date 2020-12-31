// SetSATDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetSATDlg.h"


// CSetSATDlg dialog

IMPLEMENT_DYNAMIC(CSetSATDlg, CBCGPDialog)

CSetSATDlg::CSetSATDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetSATDlg::IDD, pParent)
	, m_strTips(_T(""))
	, m_strSelectedSVID(_T(""))
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CSetSATDlg::~CSetSATDlg()
{
}

void CSetSATDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SAT, m_wndListCtrl);
	DDX_Text(pDX, IDC_STATIC_TIPS, m_strTips);
	DDX_Control(pDX, IDC_CHECK_ALL, m_CheckAll);
}


BEGIN_MESSAGE_MAP(CSetSATDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_CHECK_ALL, &CSetSATDlg::OnBnClickedCheckAll)
	ON_BN_CLICKED(IDOK, &CSetSATDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetSATDlg message handlers

BOOL CSetSATDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CString strText;
	DWORD dwStyle = m_wndListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_wndListCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wndListCtrl.SetExtendedStyle(dwStyle);
	m_wndListCtrl.InsertColumn(0, "卫星号", LVCFMT_LEFT, 80);
	m_wndListCtrl.InsertColumn(1, "卫星类型", LVCFMT_RIGHT, 150);
	for(int i=0; i<35; i++)
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
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetSATDlg::OnBnClickedCheckAll()
{
	// TODO: Add your control notification handler code here
	int bcheck = m_CheckAll.GetCheck();
	int count = m_wndListCtrl.GetItemCount();
	for (int i=0; i<count; i++)
	{
		m_wndListCtrl.SetCheck(i, bcheck);
	}
}

void CSetSATDlg::SetTips(CString strTips)
{
	m_strTips = strTips;
}

void CSetSATDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString strText;
	m_strSelectedSVID.Empty();
	int count = m_wndListCtrl.GetItemCount();
	for (int i=0; i<count; i++)
	{
		if (m_wndListCtrl.GetCheck(i))
		{
			strText.Format("%d,", i+1);
			m_strSelectedSVID += strText;
		}
	}
	CBCGPDialog::OnOK();
}
void CSetSATDlg::SaveConfigure()
{

}
void CSetSATDlg::Reset()
{

}