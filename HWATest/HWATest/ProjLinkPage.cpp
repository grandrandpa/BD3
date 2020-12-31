// ProjLinkPage.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ProjLinkPage.h"


// CProjLinkPage dialog

IMPLEMENT_DYNAMIC(CProjLinkPage, CBCGPPropertyPage)

CProjLinkPage::CProjLinkPage()
	: CBCGPPropertyPage(CProjLinkPage::IDD)
	, m_bConnectType(FALSE)
	, m_nBaud(3)
	, m_nSocketPort(8080)
	, m_dwIP(0)
	, m_strComPort(_T(""))
{
	EnableVisualManagerStyle();
}

CProjLinkPage::~CProjLinkPage()
{
}

void CProjLinkPage::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_COM, m_bConnectType);
	DDX_Control(pDX, IDC_COMBO_COM_BAUD, m_cmbBaud);
	DDX_Control(pDX, IDC_COMBO_COM_PORT, m_cmbPort);
	DDX_Control(pDX, IDC_EDIT_SOCKET_PORT, m_editPort);
	//	DDX_Control(pDX, IDC_NETADDRESS_SOCKET_IP, m_addressIP);
	DDX_CBIndex(pDX, IDC_COMBO_COM_BAUD, m_nBaud);
	DDX_Text(pDX, IDC_EDIT_SOCKET_PORT, m_nSocketPort);
	DDX_Text(pDX, IDC_ADDRESS_SOCKET_IP, m_dwIP);
	DDX_CBString(pDX, IDC_COMBO_COM_PORT, m_strComPort);
	DDX_Control(pDX, IDC_ADDRESS_SOCKET_IP, m_editIP);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL, m_cmbProtocol);
}


BEGIN_MESSAGE_MAP(CProjLinkPage, CBCGPPropertyPage)
	ON_BN_CLICKED(IDC_RADIO_COM, &CProjLinkPage::OnBnClickedRadioCom)
	ON_BN_CLICKED(IDC_RADIO_SOCKET, &CProjLinkPage::OnBnClickedRadioSocket)
END_MESSAGE_MAP()


// CProjLinkPage message handlers

BOOL CProjLinkPage::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	CString str;
	DWORD dwIP=0;
	int temp = 0, item = 0;
	char buf[MAX_PATH];
	GetSerialPorts(IDC_COMBO_COM_PORT);
	for (int i=0; i<MAXBAUD; i++)
	{
		str.Format("%d", bauds[i]);
		m_cmbBaud.AddString(str);
	}
	m_cmbProtocol.AddString("�ı�Э��");
	m_cmbProtocol.AddString("������Э��");
    m_cmbProtocol.AddString("0183Э��");
	item = GetPrivateProfileInt("CONNECT", "protocol", 2, theApp.m_strConfigPath);
	m_cmbProtocol.SetCurSel((item>0)?(item-1):0);
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
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

BOOL CProjLinkPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	CBCGPPropertySheet* pSheet = (CBCGPPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_FINISH);

	return CBCGPPropertyPage::OnSetActive();
}

BOOL CProjLinkPage::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class
	CString str;
	int protocol=0;
	UpdateData(TRUE);
	protocol = m_cmbProtocol.GetCurSel();
    WritePrivateProfileString("Product", "Protocol", (protocol==0)?"1":((protocol==1)?"2":"3"), theApp.m_strProjFile);
	WritePrivateProfileString("CONNECT", "protocol", (protocol==0)?"1":((protocol==1)?"2":"3"), theApp.m_strConfigPath);
	//�˿�����
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

	return CBCGPPropertyPage::OnWizardFinish();
}

// �Զ���ȡ����
int CProjLinkPage::GetSerialPorts(UINT nID)
{
	//��������ʱ��ȡȫ�����ô��� 4     
	HANDLE  hCom;    
	int i = 0, k = 0;
	CString str;  
	((CComboBox *)GetDlgItem(nID))->ResetContent();  
	for (i = 1;i <= 256;i++)     
	{//�˳���֧��16������        
		str.Format("\\\\.\\COM%d",i);         
		hCom = CreateFile(str, 0, 0, 0,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,0);      
		if(INVALID_HANDLE_VALUE != hCom )        
		{//�ܴ򿪸ô��ڣ�����Ӹô���           
			CloseHandle(hCom);            
			str = str.Mid(4);            
			((CComboBox *)GetDlgItem(nID))->AddString(str);                           
		}    
	}     
	i = ((CComboBox *)GetDlgItem(nID))->GetCount();   
	if (i == 0)
	{
		//���Ҳ������ô�������á��򿪴��ڡ�����
		((CComboBox *)GetDlgItem(nID))->EnableWindow(FALSE);
	}     
	else  
	{         
		k = ((CComboBox *)GetDlgItem((nID)))->GetCount();         
		((CComboBox *)GetDlgItem(nID))->SetCurSel(k - 1);
	}

	return i;
}

void CProjLinkPage::OnBnClickedRadioCom()
{
	// TODO: Add your control notification handler code here
	m_cmbPort.EnableWindow(TRUE);
	m_cmbBaud.EnableWindow(TRUE);
	m_editPort.EnableWindow(FALSE);
	m_editIP.EnableWindow(FALSE);
}

void CProjLinkPage::OnBnClickedRadioSocket()
{
	// TODO: Add your control notification handler code here
	m_cmbPort.EnableWindow(FALSE);
	m_cmbBaud.EnableWindow(FALSE);
	m_editPort.EnableWindow(TRUE);
	m_editIP.EnableWindow(TRUE);
}
