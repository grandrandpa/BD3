// WinProtocol.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "WinProtocol.h"

// CWinProtocolApp construction
CWinProtocolApp::CWinProtocolApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_pDispose = NULL;
}

// The one and only CWinProtocolApp object
CWinProtocolApp::~CWinProtocolApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	DestroyObject();
}
void CWinProtocolApp::CreateObject(int protocol)
{
	switch (protocol)
	{
	case PROTOCOL_NONE:
		m_pDispose = NULL;
		break;
	case PROTOCOL_NMEA:
		m_pDispose = new CDisposeNMEA;
		break;
	case PROTOCOL_BINARY:
		m_pDispose = new CDisposeBinary;
		break;
    case PROTOCOL_BD3:
        m_pDispose = new CDisposeBD3;
		break;

	default:
		m_pDispose = NULL;
		break;
	}
}
void CWinProtocolApp::DestroyObject()
{
	Reset();
	m_pDispose = NULL;
}
void CWinProtocolApp::Reset()
{
	if(m_pDispose != NULL)
		m_pDispose->Reset();
}

void CWinProtocolApp::DisposeData(char* buf, int len)//处理数据
{
	if(m_pDispose != NULL)
		m_pDispose->DisposeData(buf, len);
}
//参数设置
int CWinProtocolApp::PacketBDIData(char* pBuff, const SETREF& data)//初始化
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketBDIData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketTIMData(char* pBuff, const SETTIM& data)//线缆时延
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketTIMData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketCHAData(char* pBuff, const SETCHA& data)//通道参数
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketCHAData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketCOMData(char* pBuff, const SETCOM& data)//串口
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketCOMData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketMODData(char* pBuff, const SETMOD& data)//模式
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketMODData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketWORKMODData(char* pBuff, const WORKMOD& data)//工作模式
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketWORKMODData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}

int CWinProtocolApp::PacketISTData(char* pBuff, const SETIST& data)//工作模式
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketISTData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}

int CWinProtocolApp::PacketLOGData(char* pBuff, const SETLOG& data)//输出
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketLOGData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketPOSData(char* pBuff, const SETPOS& data)//位置
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketPOSData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketWIDData(char* pBuff, const SETWID& data)//
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketWIDData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketREFData(char* pBuff, const SETREF& data)//系统参数
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketREFData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketMUTData(char* pBuff, const SETMUT& data)//
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketMUTData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketEACData(char* pBuff, const SETEAC& data)//
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketEACData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketBGTData(char* pBuff, const SETBGT& data)//
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketBGTData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketTTFData(char* pBuff, const SETTTF& data)//
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketTTFData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketSTAData(char* pBuff, const SETSTA& data)//
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketSTAData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketSTSData(char* pBuff, const SETSTS& data)//
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketSTSData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketEVAData(char* pBuff, const SETEVA& data)//
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketEVAData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketTMDData(char* pBuff, const SETTMD& data)
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketTMDData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
int CWinProtocolApp::PacketBD2POSData(char* pBuff, const BD2_POS& data)
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketBD2POSData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}

int CWinProtocolApp::PacketACQData(char* pBuff, const SETACQ& data)//
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketACQData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketTRKData(char* pBuff, const SETTRK& data)
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketTRKData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketIONData(char* pBuff, const SETION& data)
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketIONData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}

int CWinProtocolApp::PacketPILOTData(char* pBuff, const SETPILOT& data)
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketPILOTData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}
int CWinProtocolApp::PacketACKData(char* pBuff, const SETACK& data)//查询模式
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketACKData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}

int CWinProtocolApp::PacketEPQData(char* pBuff, const SETEPQ& data)
{
	if(m_pDispose != NULL)
		return m_pDispose->PacketEPQData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}


int CWinProtocolApp::PacketTCQData(char* pBuff, const SETTCQ& data)
{
    if(m_pDispose != NULL)
		return m_pDispose->PacketTCQData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}

int CWinProtocolApp::PacketQRQData(char* pBuff, const SETQRQ& data)
{
    if(m_pDispose != NULL)
		return m_pDispose->PacketQRQData(pBuff, data);
	else
		return FALSE;
	return TRUE;
}

int CWinProtocolApp::SendCmdData(char* pBuff, int len)
{
    if(m_pDispose != NULL)
		return m_pDispose->SendCMDEvent(pBuff, len);
	else
		return FALSE;
	return TRUE;
}