#pragma once
#include <ws2tcpip.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include "netstruct.h"

class HWA_NET_API CSocketServer
{
public:
	CSocketServer(void);
	~CSocketServer(void);
private:
	bool						m_bExit;
	BOOL						m_bDisposePro;	//数据处理
	BOOL						m_bSendPro;		//数据发送
	BOOL						m_bRecvPro;		//数据接收
	SOCKET						m_LinkSocket;
	SOCKET						m_connect_socket;
	list<SocketPackageData*>	m_SendDataList; //数据发送队列
	list<SocketPackageData*>	m_RecvDataList; //数据接收队列

	HANDLE m_hSendListMtx;//数据发送事件句柄
	HANDLE m_hRecvListMtx;//数据接收事件句柄
	CWinThread* m_hSendPro;//数据发送线程句柄
	CWinThread* m_hRecvPro;//数据发送线程句柄
	CWinThread* m_hDisposePro;//数据发送线程句柄

private:
	SOCKET	GetSocket();
	void    StartAllThread();
	static UINT RecvClientDataThread(LPVOID lparm);//数据接收线程
	UINT _RecvClientDataThread(SOCKET skt);
	static UINT OnRecvDataDispose(LPVOID lparm);//数据处理线程
	UINT _OnRecvDataDispose();
	static UINT OnSendDataThread(LPVOID lparm);//数据发送线程
	UINT _OnSendDataThread();
public:
	virtual void CompleteRecData(char* buf, int len) = 0;//数据接收处理函数
	virtual void Reset() = 0;
	BOOL	Open(int nPort);
	void	Close();
	void Destroy(void);
	void	SendData(char* buf, int len);
};
