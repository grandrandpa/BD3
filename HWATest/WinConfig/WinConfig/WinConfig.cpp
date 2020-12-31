// WinConfig.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "WinConfig.h"

// CWinConfigApp construction
CWinConfigApp::CWinConfigApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}
CWinConfigApp::~CWinConfigApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}
// The one and only CWinConfigApp object

int CWinConfigApp::GetLinkConfig(SETSOCKET* skt, SETCOM* com, CString strName)
{
	int type=0;
	char buf[20];
	ZeroMemory(buf, sizeof(char)*20);
	GetPrivateProfileString("CONNECT", "type", "0", buf, MAX_PATH, strName);
	type = atoi(buf);
	ZeroMemory(buf, sizeof(char)*20);
	GetPrivateProfileString("CONNECT", "protocol", "0", buf, MAX_PATH, strName);
	com->protocol = atoi(buf);
	skt->protocol = atoi(buf);
	ZeroMemory(buf, sizeof(char)*20);
	GetPrivateProfileString("COMM", "port", "0", buf, MAX_PATH, strName);
	com->com = atoi(buf);
	ZeroMemory(buf, sizeof(char)*20);
	GetPrivateProfileString("COMM", "baud", "115200", buf, MAX_PATH, strName);
	com->baud = atoi(buf);
	ZeroMemory(buf, sizeof(char)*20);
	GetPrivateProfileString("SOCKET", "ip", "192.168.0.1", buf, MAX_PATH, strName);
	skt->dwIP = strtoul(buf, NULL, 10);
	ZeroMemory(buf, sizeof(char)*20);
	GetPrivateProfileString("SOCKET", "port", "9084", buf, MAX_PATH, strName);
	skt->port = atoi(buf);

	return type;
}

