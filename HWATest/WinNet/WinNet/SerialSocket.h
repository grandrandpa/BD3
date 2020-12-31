#pragma once
#include <ws2tcpip.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include "netstruct.h"

class HWA_NET_API CSerialSocket
{
public:
	CSerialSocket(void);
	~CSerialSocket(void);
private:
	LPVOID m_pNetUnit;
	void ThreadExit(){m_bExit = false;}
public:
	virtual void CompleteRecData(char* buf, int len) = 0;
	virtual void Reset() = 0;
	//连接服务器
	int ConnectServer(char* serverIp,unsigned int serverPort,unsigned short localPort = 13003,int nType = 0);
	void DisconnectServer(SOCKET skt);//释放连接// 销毁
	void Destroy(void);
	//获得空闲skt
	SOCKET GetIdleSocket();
	int SendData(char* strSndCmd, int iLen);//检索一个空闲的SOCKET发送
	bool IsOpen();
private:
	SOCKET	m_LinkSocket;
	int SocketStartup();//socket 初始化
	int SocketExit(void);//清理套接字占用的资源
private:
	//发送数据()
	int SendData(SOCKET linkSkt,char* strSndCmd, int iLen);
	//接收数据
	bool m_bExit;//是否退出
	void StartRecServerData(SOCKET skt);
	static UINT RecServerDataPro(LPVOID lparm);//数据接收线程
	UINT _RecServerDataPro(SOCKET skt);

	//数据发送线程
	BOOL m_nStartSend;
	static UINT SendDataPro(LPVOID lparm);//数据发送线程
	UINT _SendDataPro(SOCKET skt);
	CWinThread* m_hSendPro;//数据发送线程句柄
	BOOL m_bSendDataPro;//数据发送
	//数据处理
	CWinThread* m_hDisposePro;//数据处理线程句柄
	BOOL m_bDisposePro;//数据处理
	static UINT DisposeDataPro(LPVOID lparm);
	UINT _DisposeDataPro();

	//发送数据到上层
	int SendDisposeResult(void* data,u_short eventType);

	map<SOCKET, SocketLinkData> m_LkInfoList;
	HANDLE m_hLkInfoListMtx;

	list<SocketPackageData*> m_SendList; //数据发送队列
	HANDLE m_hSendListMtx;//数据发送事件句柄

	list<SocketPackageData*> m_RecvList; //数据接收队列
	HANDLE m_hRecvListMtx;//数据接收事件句柄

};

typedef struct SThreadData
{
	CSerialSocket* mainObj;
	SOCKET skt;
	SThreadData()
	{
		skt = 0;
		mainObj = NULL;
	} 
}SThreadData;
