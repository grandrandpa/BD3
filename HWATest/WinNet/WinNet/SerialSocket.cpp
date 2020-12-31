#include "StdAfx.h"
#include "SerialSocket.h"


typedef map<SOCKET,SocketLinkData>::iterator lkMIter;
CSerialSocket::CSerialSocket(void)
{
	m_bSendDataPro = false;
	m_nStartSend = false;
	m_bDisposePro = false;
	m_bExit = false;
	m_hSendPro = NULL;
	m_hDisposePro = NULL;

	m_LinkSocket = NULL;
	m_hLkInfoListMtx = CreateMutex(NULL,FALSE,NULL);
	m_SendList.clear();//发送数据队列
	m_hSendListMtx = CreateMutex(NULL,FALSE,NULL);
	m_RecvList.clear();//接收数据队列
	m_hRecvListMtx = CreateMutex(NULL,FALSE,NULL);
}

CSerialSocket::~CSerialSocket(void)
{
	Destroy();
	CloseHandle(m_hLkInfoListMtx);
	CloseHandle(m_hSendListMtx);
	CloseHandle(m_hRecvListMtx);
	m_nStartSend = FALSE;
}

bool CSerialSocket::IsOpen()
{
	return m_bExit;
}
int CSerialSocket::SocketStartup()
{
	int nErr = 0;  
	WSADATA wsaData;
	WORD wVersionRequested;

	wVersionRequested=MAKEWORD(2,2);  
	nErr=WSAStartup(wVersionRequested,&wsaData);  
	if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wHighVersion)!=2)  
	{  
		WSACleanup();  
		return  FALSE;  
	}
	return nErr;
}
int CSerialSocket::SocketExit(void)
{
	return WSACleanup();
}

//连接服务器
int CSerialSocket::ConnectServer(char* serverIp,unsigned int serverPort,unsigned short localPort,int nType)
{
	int len=0;
	sockaddr_in addr;
	u_long unblock = 1;
	SocketStartup();

	len = sizeof(struct sockaddr);
	memset( &addr, 0, sizeof(addr) );
	m_LinkSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if( m_LinkSocket != INVALID_SOCKET )
	{
		int nRet = 0;
		/*if (localPort > 0)
		{
			addr.sin_addr.s_addr = INADDR_ANY;
			addr.sin_port = htons(localPort);
			nRet = bind( skt, (struct sockaddr *)&addr, sizeof(addr) );
		}*/

		memset( &addr, 0, sizeof(addr) );
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(serverIp);
		addr.sin_port = htons(serverPort);

		//设置为非阻塞状态，非缓冲
		/*if( ioctlsocket(skt, FIONBIO, &unblock ) < 0 )
			return -1;*/
		//开始连接
		nRet = connect( m_LinkSocket, (struct sockaddr *)&addr, sizeof(sockaddr) );
		if(nRet ==  SOCKET_ERROR)
		{
			CString strLog;
			int nErrRet = WSAGetLastError();
			strLog.Format(_T("Connect错误，错误号%d"), nErrRet);
			closesocket(m_LinkSocket);
			WSACleanup();
			return 0;
		}
		else
		{
			m_bExit = true;
			WaitForSingleObject(m_hLkInfoListMtx,INFINITE);
			StartRecServerData(m_LinkSocket);//start recv data  here close socket
			ReleaseMutex(m_hLkInfoListMtx);

			return 1;
		}
	}
	else
	{
		WSACleanup();
		return 0;
	}

	return 1;
}
void CSerialSocket::Destroy(void)
{
	m_bExit = false;
	m_bSendDataPro = false;
	m_nStartSend = false;
	m_bDisposePro = false;
	m_hSendPro = NULL;
	m_hDisposePro = NULL;
	closesocket(m_LinkSocket);
	m_LinkSocket = NULL;
	WaitForSingleObject(m_hLkInfoListMtx,INFINITE);
	m_SendList.clear();//发送数据队列
	m_RecvList.clear();//接收数据队列
	ReleaseMutex(m_hLkInfoListMtx);
}
//关闭连接
void CSerialSocket::DisconnectServer(SOCKET skt)
{
	if(INVALID_SOCKET != skt)
	{
		if( skt != SOCKET_ERROR )
			closesocket( skt );
	}
}

void CSerialSocket::StartRecServerData(SOCKET skt)
{
	//开启数据接收线程
	SThreadData* trdData = new SThreadData;
	trdData->skt = skt;
	trdData->mainObj = this;
	AfxBeginThread(RecServerDataPro,trdData);
	
	//开启数据发送线程
	if (!m_nStartSend)
	{
		m_nStartSend = TRUE;
		m_bSendDataPro = TRUE;
		m_bDisposePro = TRUE;
		m_hSendPro = AfxBeginThread(SendDataPro,trdData);//开启数据发送线程
		m_hDisposePro = AfxBeginThread(DisposeDataPro,this);//开启数据处理线程
		/*if(!m_hSendPro || !m_hDisposePro)
		{
		}*/
	}
	delete trdData;
}

UINT CSerialSocket::RecServerDataPro(LPVOID lparm)
{
	SThreadData* trdData = (SThreadData*)lparm;
	UINT ret = trdData->mainObj->_RecServerDataPro(trdData->skt);
	delete trdData;
	return ret;
}
/*
	执行部分，接收数据
*/
UINT CSerialSocket::_RecServerDataPro(SOCKET skt)
{
	int recLen = 0;
	char recBuf[NET_LENGTH];
	while(m_bExit)
	{
		ZeroMemory(recBuf, sizeof(char)*NET_LENGTH);
		recLen = recv(skt, recBuf, NET_LENGTH, 0);
		if( recLen > 0)
		{
				//this->CompleteRecData(recBuf, recLen);
			WaitForSingleObject(m_hRecvListMtx,INFINITE);

			SocketPackageData* pData = new SocketPackageData;
			pData->skt = skt;
			pData->pBuffer = (char*)malloc(recLen*sizeof(char));
			memcpy(pData->pBuffer, recBuf, recLen);
			pData->nLength = recLen;
			this->m_RecvList.push_back(pData); //将数据加入到发送队列

			ReleaseMutex(m_hRecvListMtx);
		}
		Sleep(2);
	}
	return 0;
}
UINT CSerialSocket::DisposeDataPro(LPVOID lparm)
{
	CSerialSocket* pMainObj = (CSerialSocket*)lparm;
	return pMainObj->_DisposeDataPro();//Dispose data
	return 0;
}

UINT CSerialSocket::_DisposeDataPro()
{
	while(m_bDisposePro)
	{
		WaitForSingleObject(m_hRecvListMtx,INFINITE);
		if (m_RecvList.size() > 0)
		{
			SocketPackageData* pData = m_RecvList.front();
			m_RecvList.pop_front();
			if (pData)
			{
				this->CompleteRecData(pData->pBuffer, pData->nLength);//处理数据
				if (pData->pBuffer)
					free(pData->pBuffer);
				delete pData;
			}
		}
		/*else
		{
			this->Reset();
		}*/
		ReleaseMutex(m_hRecvListMtx);
		Sleep(2);
	}
	return 0;
}

//发送数据
int CSerialSocket::SendData(SOCKET linkSk,char* strSndCmd, int iLen)/*t*/
{
    if(INVALID_SOCKET==linkSk)
		return -1;
	
	//加入发送队列
	WaitForSingleObject(m_hSendListMtx,INFINITE);

	SocketPackageData* pData = new SocketPackageData;

	WaitForSingleObject(m_hLkInfoListMtx,INFINITE);
	pData->skt = linkSk;
    ReleaseMutex(m_hLkInfoListMtx);

	pData->pBuffer = (char*)malloc(iLen*sizeof(char));
	memcpy(pData->pBuffer, strSndCmd, iLen);
	pData->nLength = iLen;
	this->m_SendList.push_back(pData); //将数据加入到发送队列

	ReleaseMutex(m_hSendListMtx);

	return FALSE;
}
//发送数据
int CSerialSocket::SendData(char* strSndCmd, int iLen)
{
	if (m_LinkSocket != INVALID_SOCKET)
	{
		return SendData(m_LinkSocket,strSndCmd,iLen);
	}
	return -2;
}

//获得空闲skt,功能暂时未完成
SOCKET CSerialSocket::GetIdleSocket()
{
	SOCKET skt = INVALID_SOCKET;

	WaitForSingleObject(m_hLkInfoListMtx,INFINITE);
	skt = m_LinkSocket;
	ReleaseMutex(m_hLkInfoListMtx);

	return skt;
}

//数据发送线程
UINT CSerialSocket::SendDataPro(LPVOID lparm)
{
	SThreadData* trdData = (SThreadData*)lparm;
	UINT ret = trdData->mainObj->_SendDataPro(trdData->skt);
	delete trdData;
	return ret;
	//CSerialSocket* pMainObj = (CSerialSocket*)lparm;
	//return pMainObj->_SendDataPro();//send data
}
UINT CSerialSocket::_SendDataPro(SOCKET skt)
{
	while (m_bSendDataPro)
	{
		WaitForSingleObject(m_hSendListMtx,INFINITE);

		if (m_SendList.size() > 0)
		{
			SocketPackageData* pData = m_SendList.front();
			m_SendList.pop_front();
			if (pData)
			{
				send(skt,pData->pBuffer,pData->nLength,0);

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