// SetPortDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetPortDlg.h"


// CSetPortDlg dialog

IMPLEMENT_DYNAMIC(CSetPortDlg, CBCGPDialog)

CSetPortDlg::CSetPortDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetPortDlg::IDD, pParent)
	, m_nBaud(3)
	, m_strComPort(_T(""))
	, m_nSocketPort(8080)
	, m_dwIP(0)
	, m_bConnectType(FALSE)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CSetPortDlg::~CSetPortDlg()
{
}

void CSetPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COM_BAUD, m_cmbBaud);
	DDX_Control(pDX, IDC_COMBO_COM_PORT, m_cmbPort);
	DDX_Control(pDX, IDC_EDIT_SOCKET_PORT, m_editPort);
	DDX_Control(pDX, IDC_ADDRESS_SOCKET_IP, m_editIP);
	DDX_CBIndex(pDX, IDC_COMBO_COM_BAUD, m_nBaud);
	DDX_CBString(pDX, IDC_COMBO_COM_PORT, m_strComPort);
	DDX_Text(pDX, IDC_EDIT_SOCKET_PORT, m_nSocketPort);
	DDV_MinMaxInt(pDX, m_nSocketPort, 0, 65535);
	DDX_IPAddress(pDX, IDC_ADDRESS_SOCKET_IP, m_dwIP);
	DDX_Radio(pDX, IDC_RADIO_COM, m_bConnectType);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL, m_cmbProtocol);
}


BEGIN_MESSAGE_MAP(CSetPortDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_RADIO_COM, &CSetPortDlg::OnBnClickedRadioCom)
	ON_BN_CLICKED(IDC_RADIO_SOCKET, &CSetPortDlg::OnBnClickedRadioSocket)
	ON_BN_CLICKED(IDOK, &CSetPortDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetPortDlg message handlers

BOOL CSetPortDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CString str;
	DWORD dwIP=0;
	int temp = 0, item = 0;
	GetSerialPorts(IDC_COMBO_COM_PORT);
	for (int i=0; i<MAXBAUD; i++)
	{
		str.Format("%d", bauds[i]);
		m_cmbBaud.AddString(str);
	}
	m_cmbProtocol.AddString("文本协议");
	m_cmbProtocol.AddString("二进制协议");
    m_cmbProtocol.AddString("0183协议");
	item = GetPrivateProfileInt("CONNECT", "protocol", 1, theApp.m_strConfigPath);
	m_cmbProtocol.SetCurSel((item>0)?(item-1):0);
	theApp.m_nConnectType = GetPrivateProfileInt("CONNECT", "type", 0, theApp.m_strConfigPath);
	m_bConnectType = (theApp.m_nConnectType == 0)?FALSE:TRUE;
	UpdateData(FALSE);
	if (m_bConnectType)
	{
		m_cmbPort.EnableWindow(FALSE);
		m_cmbBaud.EnableWindow(FALSE);
		m_editPort.EnableWindow(TRUE);
		m_editIP.EnableWindow(TRUE);
	} 
	else
	{
		m_cmbPort.EnableWindow(TRUE);
		m_cmbBaud.EnableWindow(TRUE);
		m_editPort.EnableWindow(FALSE);
		m_editIP.EnableWindow(FALSE);
	}

	item = GetPrivateProfileInt("COMM", "port", 0, theApp.m_strConfigPath);
	str.Format("COM%d", item);
	item = m_cmbPort.FindString(0, str);
	if(item != CB_ERR)
		m_cmbPort.SetCurSel(item);
	item = GetPrivateProfileInt("COMM", "baud", 115200, theApp.m_strConfigPath);
	str.Format("%d", item);
	item = m_cmbBaud.FindString(0, str);
	if(item != CB_ERR)
		m_cmbBaud.SetCurSel(item);
	item = GetPrivateProfileInt("SOCKET", "port", 9804, theApp.m_strConfigPath);
	str.Format("%d", item);
	m_editPort.SetWindowText(str);
	dwIP = GetPrivateProfileInt("SOCKET", "ip", 0, theApp.m_strConfigPath);
	m_editIP.SetAddress(dwIP);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetPortDlg::OnBnClickedRadioCom()
{
	// TODO: Add your control notification handler code here
	m_cmbPort.EnableWindow(TRUE);
	m_cmbBaud.EnableWindow(TRUE);
	m_editPort.EnableWindow(FALSE);
	m_editIP.EnableWindow(FALSE);
}

void CSetPortDlg::OnBnClickedRadioSocket()
{
	// TODO: Add your control notification handler code here
	m_cmbPort.EnableWindow(FALSE);
	m_cmbBaud.EnableWindow(FALSE);
	m_editPort.EnableWindow(TRUE);
	m_editIP.EnableWindow(TRUE);
}

// 自动获取串口
int CSetPortDlg::GetSerialPorts(UINT nID)
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

void CSetPortDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CString str;
	int protocol=0;
	UpdateData(TRUE);

	protocol = m_cmbProtocol.GetCurSel();
	WritePrivateProfileString("Product", "Protocol", (protocol==0)?"1":((protocol==1)?"2":"3"), theApp.m_strProjFile);
	WritePrivateProfileString("CONNECT", "protocol", (protocol==0)?"1":((protocol==1)?"2":"3"), theApp.m_strConfigPath);
	//端口连接
	theApp.m_nConnectType = m_bConnectType?1:0;
	WritePrivateProfileString("CONNECT", "type", m_bConnectType?"1":"0", theApp.m_strConfigPath);
	str.Format("%s", m_strComPort.Mid(3));
	WritePrivateProfileString("COMM", "port", str, theApp.m_strConfigPath);
	str.Format("%d", bauds[m_nBaud]);
	WritePrivateProfileString("COMM", "baud", str, theApp.m_strConfigPath);
	str.Format("%u", m_dwIP);
	WritePrivateProfileString("SOCKET", "ip", str, theApp.m_strConfigPath);
	str.Format("%u", m_nSocketPort);
	WritePrivateProfileString("SOCKET", "port", str, theApp.m_strConfigPath);

	CBCGPDialog::OnOK();
}
