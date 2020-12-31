#include "StdAfx.h"
#include "HostToSocket.h"

CHostToSocket::CHostToSocket(void)
{
	m_nProtocol = 0;
	m_bLinkStatus = false;
}

CHostToSocket::~CHostToSocket(void)
{
	Destroy();
	m_bLinkStatus = false;
}

CHostListener* CHostToSocket::GetListener()
{
	return m_wndProtocolApp.GetListener();
}
bool CHostToSocket::Open(int Port, DWORD dwRate, int protocol)//注册实例
{
	char buf[20];
	m_bLinkStatus = false;
	ZeroMemory(buf, sizeof(char)*20);
	sprintf(buf, "%u.%u.%u.%u", (dwRate>>24)&0xFF, (dwRate>>16)&0xFF, (dwRate>>8)&0xFF, dwRate&0xFF);
	m_wndProtocolApp.CreateObject(protocol);
	int status = ConnectServer(buf, Port);
	if(status != 0)
		m_bLinkStatus = true;

	return m_bLinkStatus;
}
void CHostToSocket::Close()
{
	Destroy();
	m_nProtocol = 0;
	m_bLinkStatus = false;
	m_wndProtocolApp.DestroyObject();
}
bool CHostToSocket::GetStatus()
{
	return IsOpen();
}
void CHostToSocket::CompleteRecData(char* buf, int len)
{
	if (m_bLinkStatus)
	{
		m_wndProtocolApp.DisposeData(buf, len);
	}
}
void CHostToSocket::Reset()
{
	m_wndProtocolApp.Reset();
}
//参数设置
int CHostToSocket::SetupTIMRequest(const SETTIM& data)//线缆时延
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketTIMData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupCHARequest(const SETCHA& data)//通道参数
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketCHAData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupCOMRequest(const SETCOM& data)//串口
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketCOMData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupMODRequest(const SETMOD& data)//模式
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketMODData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupWORKRequest(const WORKMOD& data)//工作模式
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketWORKMODData(buff, data);
		SendData(buff, len);
	}
	return len;
}

int CHostToSocket::SetupISTRequest(const SETIST& data)//入站信号发射
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketISTData(buff, data);
		SendData(buff, len);
	}
	return len;
}


int CHostToSocket::SetupLOGRequest(const SETLOG& data)//输出
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketLOGData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupPOSRequest(const SETPOS& data)//位置
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketPOSData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupWIDRequest(const SETWID& data)//
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketWIDData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupREFRequest(const SETREF& data)//系统参数
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketREFData(buff, data);
		SendData(buff, len);
	}
	return len;
}

int CHostToSocket::SetupBDIRequest(const SETREF& data)
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketBDIData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupMUTRequest(const SETMUT& data)
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketMUTData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupEACRequest(const SETEAC& data)
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketEACData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupBGTRequest(const SETBGT& data)
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketBGTData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupTTFRequest(const SETTTF& data)
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketTTFData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupSTARequest(const SETSTA& data)
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketSTAData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupSTSRequest(const SETSTS& data)
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketSTSData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupEVARequest(const SETEVA& data)
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketEVAData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupTMDRequest(const SETTMD& data)
{
	int len = 0;
	char buff[200];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketTMDData(buff, data);
		SendData(buff, len);
	}
	return len;
}
//////////////////////////////////////////////////////////////////////////
int CHostToSocket::AnswerPOSRequest(const BD2_POS& data)
{
	int len = 0;
	char buff[1024];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketBD2POSData(buff, data);
		SendData(buff, len);
	}
	return len;
}

int CHostToSocket::SetupACQRequest(const SETACQ& data)
{
	int len = 0;
	char buff[1024];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketACQData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupTRKRequest(const SETTRK& data)
{
	int len = 0;
	char buff[1024];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketTRKData(buff, data);
		SendData(buff, len);
	}
	return len;
}

int CHostToSocket::SetupIONRequest(const SETION& data)
{
	int len = 0;
	char buff[1024];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketIONData(buff, data);
		SendData(buff, len);
	}
	return len;
}

int CHostToSocket::SetupPILOTRequest(const SETPILOT& data)
{
	int len = 0;
	char buff[1024];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketPILOTData(buff, data);
		SendData(buff, len);
	}
	return len;
}
int CHostToSocket::SetupACKRequest(const SETACK& data)
{
	int len = 0;
	char buff[1024];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketACKData(buff, data);
		SendData(buff, len);
	}
	return len;
}

int CHostToSocket::SetupEPQRequest(const SETEPQ& data)
{
    return 0;
}

int CHostToSocket::SetupTCQRequest(const SETTCQ& data)
{
    return 0;
}