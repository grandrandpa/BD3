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
	BOOL						m_bDisposePro;	//���ݴ���
	BOOL						m_bSendPro;		//���ݷ���
	BOOL						m_bRecvPro;		//���ݽ���
	SOCKET						m_LinkSocket;
	SOCKET						m_connect_socket;
	list<SocketPackageData*>	m_SendDataList; //���ݷ��Ͷ���
	list<SocketPackageData*>	m_RecvDataList; //���ݽ��ն���

	HANDLE m_hSendListMtx;//���ݷ����¼����
	HANDLE m_hRecvListMtx;//���ݽ����¼����
	CWinThread* m_hSendPro;//���ݷ����߳̾��
	CWinThread* m_hRecvPro;//���ݷ����߳̾��
	CWinThread* m_hDisposePro;//���ݷ����߳̾��

private:
	SOCKET	GetSocket();
	void    StartAllThread();
	static UINT RecvClientDataThread(LPVOID lparm);//���ݽ����߳�
	UINT _RecvClientDataThread(SOCKET skt);
	static UINT OnRecvDataDispose(LPVOID lparm);//���ݴ����߳�
	UINT _OnRecvDataDispose();
	static UINT OnSendDataThread(LPVOID lparm);//���ݷ����߳�
	UINT _OnSendDataThread();
public:
	virtual void CompleteRecData(char* buf, int len) = 0;//���ݽ��մ�����
	virtual void Reset() = 0;
	BOOL	Open(int nPort);
	void	Close();
	void Destroy(void);
	void	SendData(char* buf, int len);
};
