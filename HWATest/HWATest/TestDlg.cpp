// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "TestDlg.h"


// CTestDlg dialog

IMPLEMENT_DYNAMIC(CTestDlg, CBCGPDialog)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CTestDlg::IDD, pParent)
	, m_strPort(_T(""))
	, m_strBaud(_T(""))
{
	m_nPort = 0;
	m_nBaud = 0;
	EnableVisualManagerStyle(TRUE, TRUE);
}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_LINK, m_btnCheck);
	DDX_Control(pDX, IDC_COMBO_BAUD, m_cmbBaud);
	DDX_Control(pDX, IDC_COMBO_PORT, m_cmbPort);
	DDX_CBString(pDX, IDC_COMBO_PORT, m_strPort);
	DDX_CBString(pDX, IDC_COMBO_BAUD, m_strBaud);
}


BEGIN_MESSAGE_MAP(CTestDlg, CBCGPDialog)
	ON_BN_CLICKED(IDOK, &CTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_LINK, &CTestDlg::OnBnClickedCheckLink)
END_MESSAGE_MAP()


// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CString str;
	GetSerialPorts(IDC_COMBO_PORT);
	for (int i=0; i<MAXBAUD; i++)
	{
		str.Format("%d", bauds[i]);
		m_cmbBaud.AddString(str);
	}
	m_cmbBaud.SetCurSel(7);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE 
}

// 自动获取串口
int CTestDlg::GetSerialPorts(UINT nID)
{
	//程序启动时获取全部可用串口 4     
	HANDLE  hCom;    
	int i = 0, k = 0;
	CString str;  
	((CComboBox *)GetDlgItem(nID))->ResetContent();  
	for (i = 1;i <= 256;i++)     
	{//此程序支持16个串口        
		str.Format("\\\\.\\COM%d",i);         
		hCom = CreateFile(str, 0, 0, 0,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,0);      
		if(INVALID_HANDLE_VALUE != hCom )        
		{//能打开该串口，则添加该串口           
			CloseHandle(hCom);            
			str = str.Mid(4);            
			((CComboBox *)GetDlgItem(nID))->AddString(str);                           
		}    
	}     
	i = ((CComboBox *)GetDlgItem(nID))->GetCount();   
	if (i == 0)
	{
		//若找不到可用串口则禁用“打开串口”功能
		((CComboBox *)GetDlgItem(nID))->EnableWindow(FALSE);
	}     
	else  
	{         
		k = ((CComboBox *)GetDlgItem((nID)))->GetCount();         
		((CComboBox *)GetDlgItem(nID))->SetCurSel(k - 1);
	}

	return i;
}

void CTestDlg::OnBnClickedCheckLink()
{
	// TODO: Add your control notification handler code here
}

void CTestDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_nPort = atoi(m_strPort.Mid(3));
	m_nBaud = atoi(m_strBaud);

	CBCGPDialog::OnOK();
}
