#include "StdAfx.h"
#include "HostToComm.h"
#include "string.h"

CHostToComm::CHostToComm(void)
{
	m_nProtocol = 0;
	m_bLinkStatus = false;
}

CHostToComm::~CHostToComm(void)
{
	Destroy();
	m_bLinkStatus = false;
}

CHostListener* CHostToComm::GetListener()
{
	return m_wndProtocolApp.GetListener();
}
bool CHostToComm::Open(int Port, DWORD dwRate, int protocol)//注册实例
{
	m_nProtocol = protocol;
	m_wndProtocolApp.CreateObject(protocol);
	m_bLinkStatus = ConnectServer(Port, dwRate);

	return m_bLinkStatus;
}
void CHostToComm::Close()
{
	Destroy();
	m_nProtocol = 0;
	m_bLinkStatus = false;
	m_wndProtocolApp.DestroyObject();
}
bool CHostToComm::GetStatus()
{
	return IsOpen();
}
void CHostToComm::CompleteRecData(char* buf, int len)
{
	if (m_bLinkStatus)
	{
		m_wndProtocolApp.DisposeData(buf, len);
	}
}
void CHostToComm::Reset()
{
	m_wndProtocolApp.Reset();
}
//参数设置
int CHostToComm::SetupTIMRequest(const SETTIM& data)//线缆时延
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
int CHostToComm::SetupCHARequest(const SETCHA& data)//通道参数
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
int CHostToComm::SetupCOMRequest(const SETCOM& data)//串口
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
int CHostToComm::SetupMODRequest(const SETMOD& data)//模式
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
int CHostToComm::SetupWORKRequest(const WORKMOD& data)//工作模式
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

int CHostToComm::SetupISTRequest(const SETIST& data)//入站信号发射
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


int CHostToComm::SetupLOGRequest(const SETLOG& data)//输出
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
int CHostToComm::SetupPOSRequest(const SETPOS& data)//位置
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
int CHostToComm::SetupWIDRequest(const SETWID& data)//
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
int CHostToComm::SetupREFRequest(const SETREF& data)//系统参数
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

int CHostToComm::SetupBDIRequest(const SETREF& data)
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
int CHostToComm::SetupMUTRequest(const SETMUT& data)
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
int CHostToComm::SetupEACRequest(const SETEAC& data)
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
int CHostToComm::SetupBGTRequest(const SETBGT& data)
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
int CHostToComm::SetupTTFRequest(const SETTTF& data)
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
int CHostToComm::SetupSTARequest(const SETSTA& data)
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
int CHostToComm::SetupSTSRequest(const SETSTS& data)
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
int CHostToComm::SetupEVARequest(const SETEVA& data)
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
int CHostToComm::SetupTMDRequest(const SETTMD& data)
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
int CHostToComm::AnswerPOSRequest(const BD2_POS& data)
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

int CHostToComm::SetupACQRequest(const SETACQ& data)
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
int CHostToComm::SetupTRKRequest(const SETTRK& data)
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
int CHostToComm::SetupIONRequest(const SETION& data)
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

int CHostToComm::SetupPILOTRequest(const SETPILOT& data)
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

int CHostToComm::SetupACKRequest(const SETACK& data)
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

int CHostToComm::SetupEPQRequest(const SETEPQ& data)
{
	int len = 0;
	char buff[1024];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketEPQData(buff, data);
		SendData(buff, len);
	}
	return len;
}

int CHostToComm::SetupTCQRequest(const SETTCQ& data)
{
	int len = 0;
	char buff[2048];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketTCQData(buff, data);
		SendData(buff, len);
	}
	return len;
}

int CHostToComm::SetupQRQRequest(const SETQRQ& data)
{
    int len = 0;
	char buff[128];
	ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
		len = m_wndProtocolApp.PacketQRQData(buff, data);
		SendData(buff, len);
	}
	return len;
}

int CHostToComm::SendCmdRequest(std::string& data)
{
    int len = data.length();
	char *buff = const_cast<char*>(data.c_str());
	//ZeroMemory(buff, sizeof(buff));
	if (m_bLinkStatus)
	{
        m_wndProtocolApp.SendCmdData(buff, len);
		SendData(buff, len);
	}
	return len;
}