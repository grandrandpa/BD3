#include "StdAfx.h"
#include "HostToEmulator.h"

CHostToEmulator::CHostToEmulator(void)
{
}

CHostToEmulator::~CHostToEmulator(void)
{
}
bool CHostToEmulator::Open(int Port, DWORD dwRate, int protocol)//×¢²áÊµÀý
{
	m_bLinkStatus = ConnectServer(Port, dwRate);

	return m_bLinkStatus;
}
void CHostToEmulator::Close()
{
	Destroy();
	m_nProtocol = 0;
	m_bLinkStatus = false;
}
bool CHostToEmulator::GetStatus()
{
	return IsOpen();
}
void CHostToEmulator::CompleteRecData(char* buf, int len)
{
}
void CHostToEmulator::Reset()
{
}
