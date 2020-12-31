// WinLink.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "WinLink.h"

// CWinLinkApp construction
CWinLinkApp::CWinLinkApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_bLink = false;
	m_pLink2Port = NULL;
}
CWinLinkApp::~CWinLinkApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	if(m_pLink2Port)
		delete m_pLink2Port;
	m_pLink2Port = NULL;
}

// The one and only CWinLinkApp object
CHostListener* CWinLinkApp::GetListener()
{
	if(m_pLink2Port != NULL)
		return m_pLink2Port->GetListener();
	else
		return NULL;
}
bool CWinLinkApp::CreateComm(int port, DWORD baud, int protocol)
{
	m_pLink2Port = new CHostToComm;
	if(m_pLink2Port != NULL)
		m_bLink = m_pLink2Port->Open(port, baud, protocol);
	else
		m_bLink = FALSE;
	return m_bLink;
}
bool CWinLinkApp::CreateSocket(int port, DWORD dwIP, int protocol)
{
	m_pLink2Port = new CHostToSocket;
	if(m_pLink2Port != NULL)
		m_bLink = m_pLink2Port->Open(port, dwIP, protocol);
	else
		m_bLink = FALSE;
	return m_bLink;
}
bool CWinLinkApp::Open(bool isCom, int Port, DWORD dwRate, int protocol)//注册实例
{
	if (isCom)//
	{
		m_pLink2Port = new CHostToComm;
	} 
	else
	{
		m_pLink2Port = new CHostToSocket;
	}
	if(m_pLink2Port != NULL)
		m_bLink = m_pLink2Port->Open(Port, dwRate, protocol);
	else
		m_bLink = FALSE;
	return m_bLink;
}
void CWinLinkApp::Close()
{
	if(!m_bLink)
		return;
	m_bLink = false;
	if(m_pLink2Port != NULL)
		m_pLink2Port->Close();
	m_pLink2Port = NULL;
}
bool CWinLinkApp::GetStatus()
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->GetStatus();
	else
		return FALSE;
	return true;
}
//参数设置
int CWinLinkApp::SetupTIMRequest(const SETTIM& data)//线缆时延
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupTIMRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupCHARequest(const SETCHA& data)//通道参数
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupCHARequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupCOMRequest(const SETCOM& data)//串口
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupCOMRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupMODRequest(const SETMOD& data)//模式
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupMODRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupWORKRequest(const WORKMOD& data)//工作模式
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupWORKRequest(data);	
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupISTRequest(const SETIST& data)//工作模式
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupISTRequest(data);	
	else
		return FALSE;
	return true;
}


int CWinLinkApp::SetupLOGRequest(const SETLOG& data)//输出
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupLOGRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupPOSRequest(const SETPOS& data)//位置
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupPOSRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupWIDRequest(const SETWID& data)//
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupWIDRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupREFRequest(const SETREF& data)//系统参数
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupREFRequest(data);
	else
		return FALSE;
	return true;
}

int CWinLinkApp::SetupBDIRequest(const SETREF& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupBDIRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupMUTRequest(const SETMUT& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupMUTRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupEACRequest(const SETEAC& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupEACRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupBGTRequest(const SETBGT& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupBGTRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupTTFRequest(const SETTTF& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupTTFRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupSTARequest(const SETSTA& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupSTARequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupSTSRequest(const SETSTS& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupSTSRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupEVARequest(const SETEVA& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupEVARequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupTMDRequest(const SETTMD& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupTMDRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::AnswerPOSRequest(const BD2_POS& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->AnswerPOSRequest(data);
	else
		return FALSE;
	return true;
}

int CWinLinkApp::SetupACQRequest(const SETACQ& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupACQRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupTRKRequest(const SETTRK& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupTRKRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupIONRequest(const SETION& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupIONRequest(data);
	else
		return FALSE;
	return true;
}

int CWinLinkApp::SetupPILOTRequest(const SETPILOT& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupPILOTRequest(data);
	else
		return FALSE;
	return true;
}
int CWinLinkApp::SetupACKRequest(const SETACK& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupACKRequest(data);
	else
		return FALSE;
	return true;
}


int CWinLinkApp::SetupEPQRequest(const SETEPQ& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupEPQRequest(data);
	else
		return FALSE;
	return true;
}

int CWinLinkApp::SetupTCQRequest(const SETTCQ& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupTCQRequest(data);
	else
		return FALSE;
	return true;
}

int CWinLinkApp::SetupQRQRequest(const SETQRQ& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SetupQRQRequest(data);
	else
		return FALSE;
	return true;
}

int CWinLinkApp::SendCmdRequest(std::string& data)
{
	if(!m_bLink)
		return false;
	if(m_pLink2Port != NULL)
		return m_pLink2Port->SendCmdRequest(data);
	else
		return FALSE;
	return true;
}