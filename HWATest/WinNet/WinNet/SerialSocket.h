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
	//���ӷ�����
	int ConnectServer(char* serverIp,unsigned int serverPort,unsigned short localPort = 13003,int nType = 0);
	void DisconnectServer(SOCKET skt);//�ͷ�����// ����
	void Destroy(void);
	//��ÿ���skt
	SOCKET GetIdleSocket();
	int SendData(char* strSndCmd, int iLen);//����һ�����е�SOCKET����
	bool IsOpen();
private:
	SOCKET	m_LinkSocket;
	int SocketStartup();//socket ��ʼ��
	int SocketExit(void);//�����׽���ռ�õ���Դ
private:
	//��������()
	int SendData(SOCKET linkSkt,char* strSndCmd, int iLen);
	//��������
	bool m_bExit;//�Ƿ��˳�
	void StartRecServerData(SOCKET skt);
	static UINT RecServerDataPro(LPVOID lparm);//���ݽ����߳�
	UINT _RecServerDataPro(SOCKET skt);

	//���ݷ����߳�
	BOOL m_nStartSend;
	static UINT SendDataPro(LPVOID lparm);//���ݷ����߳�
	UINT _SendDataPro(SOCKET skt);
	CWinThread* m_hSendPro;//���ݷ����߳̾��
	BOOL m_bSendDataPro;//���ݷ���
	//���ݴ���
	CWinThread* m_hDisposePro;//���ݴ����߳̾��
	BOOL m_bDisposePro;//���ݴ���
	static UINT DisposeDataPro(LPVOID lparm);
	UINT _DisposeDataPro();

	//�������ݵ��ϲ�
	int SendDisposeResult(void* data,u_short eventType);

	map<SOCKET, SocketLinkData> m_LkInfoList;
	HANDLE m_hLkInfoListMtx;

	list<SocketPackageData*> m_SendList; //���ݷ��Ͷ���
	HANDLE m_hSendListMtx;//���ݷ����¼����

	list<SocketPackageData*> m_RecvList; //���ݽ��ն���
	HANDLE m_hRecvListMtx;//���ݽ����¼����

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
