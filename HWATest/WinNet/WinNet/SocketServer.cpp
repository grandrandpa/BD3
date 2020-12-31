#include "StdAfx.h"
#include "SocketServer.h"

CSocketServer::CSocketServer(void)
{
	m_bExit = false;
	m_bRecvPro = false;
	m_bSendPro = false;
	m_bDisposePro = false;
	m_LinkSocket = NULL;
	m_hSendPro = NULL;
	m_hRecvPro = NULL;
	m_hDisposePro = NULL;
	m_SendDataList.clear();//发送数据队列
	m_hSendListMtx = CreateMutex(NULL,FALSE,NULL);
	m_RecvDataList.clear();//接收数据队列
	m_hRecvListMtx = CreateMutex(NULL,FALSE,NULL);
}

CSocketServer::~CSocketServer(void)
{
	m_bExit = FALSE;
	m_RecvDataList.clear();//接收数据队列
	m_SendDataList.clear();//发送数据队列
	CloseHandle(m_hSendListMtx);
	CloseHandle(m_hRecvListMtx);
}

SOCKET CSocketServer::GetSocket()
{
	return 0;
}
BOOL CSocketServer::Open(int nPort)
{
	char lRetVal=0;
	WSADATA wsaData;
	SOCKADDR_IN local;
	WORD version = MAKEWORD(2, 0);

	/*Startup*/
	lRetVal = WSAStartup(version, &wsaData);
	if (0 != lRetVal)
	{
		printf("WSAStartup() failed.\n");
		return FALSE;
	}

	/*创建Mc与Mm的socket套接字*/
	m_LinkSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == m_LinkSocket)
	{
		printf("m_Socket == INVALID_SOCKET.\n");
		Close();
		return FALSE;
	}

	/*绑定Client与Server的端口号*/
	local.sin_family            = AF_INET;
	local.sin_port                = htons(nPort);
	local.sin_addr.S_un.S_addr    = INADDR_ANY;

	lRetVal = bind(m_LinkSocket, (SOCKADDR *)&local, sizeof(local));
	if (0 != lRetVal)
	{
		printf("bind() return %d\n", lRetVal);
		Close();
		return FALSE;
	}

	/*listen*/
	lRetVal = listen(m_LinkSocket, 10);
	if (0 != lRetVal)
	{
		printf("listen() failed.\n");
		Close();
		return FALSE;
	}

	return TRUE;
}
void CSocketServer::Close()
{
	m_bRecvPro = false;
	m_bSendPro = false;
	m_bDisposePro = false;
	if (INVALID_SOCKET != m_LinkSocket)
	{
		closesocket(m_LinkSocket);
		m_LinkSocket = INVALID_SOCKET;
	}

	WSACleanup();
}
void CSocketServer::Destroy(void)
{

}
void CSocketServer::StartAllThread()
{
	m_bRecvPro = true;
	m_bSendPro = true;
	m_bDisposePro = true;

	//开启数据线程
	m_hSendPro = AfxBeginThread(OnSendDataThread,this);
	m_hRecvPro = AfxBeginThread(RecvClientDataThread,this);
	m_hDisposePro = AfxBeginThread(OnRecvDataDispose,this);

}
void CSocketServer::SendData(char* buf, int len)
{
	//加入发送队列
	WaitForSingleObject(m_hSendListMtx,INFINITE);

	SocketPackageData* pData = new SocketPackageData;
	pData->pBuffer = (char*)malloc(len*sizeof(char));
	pData->nLength = len;
	pData->skt = m_connect_socket;
	memcpy(pData->pBuffer, buf, len);
	this->m_SendDataList.push_back(pData); //将数据加入到发送队列

	ReleaseMutex(m_hSendListMtx);
}

UINT CSocketServer::RecvClientDataThread(LPVOID lparm)//数据接收线程
{
	CSocketServer* mianObj = (CSocketServer*)lparm;
	
	return mianObj->_RecvClientDataThread(mianObj->m_LinkSocket);
}
UINT CSocketServer::_RecvClientDataThread(SOCKET skt)
{
	char buffer[1024];
	sockaddr_in client;
	fd_set fdMmSocket,fdMmRead;
	int lAddrLen = sizeof(client);
	int lRetVal=0,lFdCount=0,lRcvNum=0;

	FD_ZERO(&fdMmRead);
	FD_ZERO(&fdMmSocket);

	FD_SET(skt, &fdMmSocket);
	while(m_bRecvPro)
	{
		/*查询套接字集*/
		fdMmRead = fdMmSocket;
		lRetVal = select(NULL, &fdMmRead, NULL, NULL, NULL);
		if (lRetVal <= 0)
		{
			printf("RecvClientDataThread(): select failed.\n");
			break;
		}
		/*遍历查询结果*/
		for (lFdCount = 0; lFdCount < (int)(fdMmSocket.fd_count); lFdCount++)
		{
			/*有套接字*/
			if (FD_ISSET(fdMmSocket.fd_array[lFdCount], &fdMmRead))
			{
				/*客户端发起新的连接请求*/
				if (fdMmSocket.fd_array[lFdCount] == skt)
				{
					SOCKET stMmConnectSocket = accept(skt, (sockaddr *)&client, &lAddrLen);

					/*add new connection to fd*/
					FD_SET(stMmConnectSocket, &fdMmSocket);
					m_connect_socket = stMmConnectSocket;
					printf("\n\n****************************************************\n");
					printf("new connection: ip = %s, port = %d.\n", inet_ntoa(client.sin_addr), client.sin_port);
					printf("****************************************************\n\n");
				}
				else
				{
					lRcvNum = recv(fdMmSocket.fd_array[lFdCount], buffer, 1024, 0);
					if (lRcvNum > 0)/*接收到Mm的消息*/
					{
						WaitForSingleObject(m_hRecvListMtx,INFINITE);

						SocketPackageData* pData = new SocketPackageData;
						pData->pBuffer = (char*)malloc(lRcvNum*sizeof(char));
						pData->skt = fdMmSocket.fd_array[lFdCount];
						pData->nLength = lRcvNum;
						memcpy(pData->pBuffer, buffer, lRcvNum);
						m_RecvDataList.push_back(pData); //将数据加入到发送队列

						ReleaseMutex(m_hRecvListMtx);
					}
					else
					{
						closesocket(fdMmSocket.fd_array[lFdCount]);
						FD_CLR(fdMmSocket.fd_array[lFdCount], &fdMmSocket);
					}
				}
			}
		}

		Sleep(2);
	}
	return 0;
}
UINT CSocketServer::OnRecvDataDispose(LPVOID lparm)
{
	CSocketServer* mianObj = (CSocketServer*)lparm;

	return mianObj->_OnRecvDataDispose();
}
UINT CSocketServer::_OnRecvDataDispose()
{
	while(m_bDisposePro)
	{
		WaitForSingleObject(m_hRecvListMtx,INFINITE);
		if (m_RecvDataList.size() > 0)
		{
			SocketPackageData* pData = m_RecvDataList.front();
			m_RecvDataList.pop_front();
			if (pData)
			{
				this->CompleteRecData(pData->pBuffer, pData->nLength);//处理数据
				if (pData->pBuffer)
					free(pData->pBuffer);
				delete pData;
			}
		}
		ReleaseMutex(m_hRecvListMtx);
		Sleep(2);
	}
	return 0;
}
UINT CSocketServer::OnSendDataThread(LPVOID lparm)//数据发送线程
{
	CSocketServer* mianObj = (CSocketServer*)lparm;

	return mianObj->_OnSendDataThread();
}
UINT CSocketServer::_OnSendDataThread()
{
	while (m_bSendPro)
	{
		WaitForSingleObject(m_hSendListMtx,INFINITE);

		if (m_SendDataList.size() > 0)
		{
			SocketPackageData* pData = m_SendDataList.front();
			m_SendDataList.pop_front();
			if (pData)
			{
				send(pData->skt,pData->pBuffer,pData->nLength,0);
				if (pData->pBuffer)
					free(pData->pBuffer);
				delete pData;
			}
		}

		ReleaseMutex(m_hSendListMtx);
		Sleep(2);
	}
	return 0;
}
