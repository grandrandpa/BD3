#include "StdAfx.h"
#include "NetUnits.h"

CNetUnits::CNetUnits(void)
{
}

CNetUnits::~CNetUnits(void)
{
}

int CNetUnits::SocketInit(void)
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

int CNetUnits::SocketExit(void)
{
	return WSACleanup();
}

SOCKET CNetUnits::SocketCreate(int af, int type, int protocol)
{
	return socket(af, type, protocol);
}

void CNetUnits::SocketDestroy(SOCKET skt)
{
	if( skt != SOCKET_ERROR )
		closesocket( skt );
}

int CNetUnits::SocketConnect(SOCKET skt, char* strip, unsigned int port, int timeout)
{
	struct sockaddr_in addr;
	u_long unblock = 1;
	fd_set rset;
	struct timeval tv;
	unsigned int len=0;

	memset( &addr, 0, sizeof(addr) );
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(strip);
	addr.sin_port = htons(port);
	//addr.sin_addr.s_addr = dwIP;

	len = sizeof(struct sockaddr);

	if( timeout < 0 )
		return connect( skt, (struct sockaddr*)&addr, len );

	//设置为非阻塞状态，非缓冲
	if( ioctlsocket(skt, FIONBIO, &unblock ) < 0 )
		return -1;

	//开始连接
	connect( skt, (struct sockaddr *)&addr, sizeof(addr) );

	//等待连接返回
	tv.tv_sec = timeout/1000;
	tv.tv_usec = (timeout%1000)*1000;
	FD_ZERO( &rset );
	FD_SET((u_int)skt, &rset );
	if( select( skt+1, 0, &rset, 0, &tv ) <= 0 )
	{
		//int error = WSAGetLastError();
		return -1;
	}
	
	//设回阻塞模式
	unblock = 0;
	return ioctlsocket( skt, FIONBIO, &unblock );
}

int CNetUnits::SocketBind(SOCKET skt, char* strip, unsigned int port)
{
	struct sockaddr_in addr;
	memset( &addr, 0, sizeof(addr) );
	addr.sin_family = AF_INET;
	if (strip==NULL || strlen(strip)==0)
		addr.sin_addr.s_addr = INADDR_ANY;
	else
		addr.sin_addr.s_addr = inet_addr(strip);
	//if(0 != port)
	{
		addr.sin_port = htons(port);
	}
	
	return bind( skt, (struct sockaddr *)&addr, sizeof(addr) );
}

int CNetUnits::SocketListen(SOCKET skt, int max)
{
	return listen( skt, max );
}

SOCKET CNetUnits::SocketAccept(SOCKET skt, char* strip, unsigned int* port)
{
	struct sockaddr_in from;
	int slen = sizeof(from);

	/*等待CLIENT的连接*/
	skt = accept( (SOCKET)skt, (struct sockaddr *)&from, &slen );
	if( 0 <= skt )
	{
		sprintf(strip, "%s", inet_ntoa( from.sin_addr));
		*port = ntohs( from.sin_port );
	}
	return skt;
}

int CNetUnits::SocketIoctl(SOCKET skt, int type, unsigned long* val)
{
	return 0;
}

int CNetUnits::SocketOpt(SOCKET skt, int level, int optname, const char* optval, int optlen)
{
	return setsockopt(skt, level, optname, optval, optlen );
}

int CNetUnits::SocketSelect(int maxfd, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, int timeout)
{
	struct timeval tv;

	if( 0 <= timeout )
	{
		tv.tv_sec = timeout;
		tv.tv_usec = timeout*1000;
		return select( maxfd, readfds, writefds, exceptfds, &tv );
	}
	else
		return select( maxfd, readfds, writefds, exceptfds, NULL );
}

int CNetUnits::SocketSend(SOCKET skt, char* buf, int size, int timeout)
{
	if( timeout < 0 )
	{
		return send( skt, (char*)buf, size, 0 );
	}
	else 
	{
		int i=0;
		int tempSize = size;
		while (tempSize>0)
		{
			//tv.tv_sec = timeout/1000;
			//tv.tv_usec = (timeout%1000)*1000;
			//FD_ZERO( &wset );
			//FD_SET( (u_int)skt, &wset );
			//if( select( skt+1, 0, &wset, 0, &tv ) <= 0 )
			//{
			//	//printf("\n sockt use select() error!\n");
			//	return 0;
			//} //zcy modify

			//保证数据全部都发送完毕
			int ret = send( skt, &(buf[i]), tempSize, 0);
			if( ret == 0 || ret == SOCKET_ERROR)
			{
				//printf("\n sockt use send() error!\n");
				return -1;
			}
			i += ret;
			tempSize -= ret;
		}
	}

	return size;
}

int CNetUnits::SocketRecv(SOCKET skt, char* buf, int size, int timeout)
{
	int iLeft = size;
	int   nread = -1;
	char *ptr=(char *)buf;

	struct timeval tv;
	int nRet = 0;
	fd_set	 readfds;

	if (NULL == skt)
	{
		return FALSE;
	}

	while (iLeft>4096)
	{
		FD_ZERO(&readfds);
		FD_SET(skt, &readfds);
		tv.tv_sec = timeout;
		tv.tv_usec = timeout*1000;
		nRet = select(skt + 1, &readfds, NULL, NULL, &tv);
		if (nRet > 0)
		{
			nread = recv(skt, ptr, 4096, 0);
			if (nread < 0)
			{
				if (errno == EINTR)
				{
					nread=0;
					continue;
				}
				else
				{
					return -1;
					
				}
			}
			else if( nread == 0 )
			{
				return 0;
			}

			iLeft -= nread;
			ptr += nread;
		}
        else if(nRet == 0)
        {
            return 0;
        }
		else
		{
			break ;
		}
	}
	while(iLeft > 0 )
	{
		FD_ZERO(&readfds);
		FD_SET(skt, &readfds);
		tv.tv_sec = timeout;
		tv.tv_usec = timeout*1000;
		nRet = select(skt + 1, &readfds, NULL, NULL, &tv);
		if (nRet > 0)
		{
			nread = recv(skt, ptr, size, 0);
			if (nread < 0)
			{
				if (errno == EINTR)
				{
					nread=0;
					break;
				}
				else
				{
		//		Log(_T("recv Data Error! nread < 0,lastError=%d,//SocketRecv"),WSAGetLastError());

					return -1;
				}
			}
			else if( nread == 0 )
			{
		//		Log(_T("recv Data Error! nread == 0,lastError=%d,//SocketRecv"),WSAGetLastError());
				return -1;
			}

			iLeft -= nread;
			ptr += nread;
		}
        else if(nRet == 0)
        {
            return 0;
        }
		// else
		{
			break ;
		}
        break;
	}
	return nread;
}
/* 加入多播组, ip必须是组播地址 */
int CNetUnits::SocketJoin(SOCKET skt, char* strip)
{
	int ttl = 127;
	int fFlag = 1;
	struct ip_mreq mreq;

	memset( &mreq, 0, sizeof(mreq) );
	mreq.imr_multiaddr.s_addr = inet_addr(strip);
	mreq.imr_interface.s_addr = INADDR_ANY;

	// 下面是缺省优化参数 
	setsockopt( skt, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&ttl, sizeof(ttl) );
	setsockopt( skt, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&fFlag, sizeof(fFlag) );

	//加入多播组
	return setsockopt( skt, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq) );
}
/* 退出组播组, ip必须是组播地址  */
int CNetUnits::SocketDrop(SOCKET skt, char* strip)
{
	struct ip_mreq mreq;
	memset( &mreq, 0, sizeof(mreq) );
	mreq.imr_multiaddr.s_addr = inet_addr(strip);
	mreq.imr_interface.s_addr = INADDR_ANY;
	return setsockopt( skt, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mreq, sizeof(mreq) );
}

int CNetUnits::SocketSendto(SOCKET skt, char* strip, unsigned int port, char* buf, int size, int timeout)
{
	struct timeval tv;
	//	uint32_t unblock = 1;
	fd_set wset;

	struct sockaddr_in sn;
	int slen = sizeof(sn);

	memset( &sn, 0, sizeof(sn) );
	slen = sizeof(sn);
	sn.sin_family = AF_INET;
	sn.sin_addr.s_addr = inet_addr(strip);
	sn.sin_port=  htons(port);

	if( timeout < 0 )
		return sendto( skt, (char*)buf, size, 0, (struct sockaddr *)&sn, slen );
	else 
	{
		tv.tv_sec = timeout/1000;
		tv.tv_usec = (timeout%1000)*1000;
		FD_ZERO( &wset );
		FD_SET( (u_int)skt, &wset );
		if( select( skt+1, 0, &wset, 0, &tv ) <= 0 )
			return 0;

		size = sendto( skt, (char*)buf, size, 0, (struct sockaddr *)&sn, slen );
		if( size<=0 )
			return -1;

		return size;
	}
}

int CNetUnits::SocketRecvfrom(SOCKET skt, char* strip, unsigned int* port, char* buf, int size, int timeout)
{
	struct timeval tv;
	//	uint32_t unblock = 1;
	fd_set rset;

	struct sockaddr_in from;
	socklen_t slen = sizeof( from );

	memset( &from, 0, sizeof(from) );


	if( timeout < 0 )
		return recvfrom( skt, (char*)buf, size, 0, (struct sockaddr *)&from, &slen );
	else
	{
		tv.tv_sec = timeout/1000;
		tv.tv_usec = (timeout%1000)*1000;
		FD_ZERO( &rset );
		FD_SET( (u_int)skt, &rset );
		if( select( skt+1, &rset, 0, 0, &tv ) <= 0 )
			return 0;

		slen = recvfrom( skt, (char*)buf, size, 0, (struct sockaddr *)&from, &slen );
		if( slen==0 )
			return -1;

		sprintf(strip, "%s", inet_ntoa( from.sin_addr) );
		*port = ntohs( from.sin_port );

		return slen;
	}
}

int CNetUnits::SocketGetLastError(void)
{
	return WSAGetLastError();
}

void CNetUnits::GetHostIp(char* ip)
{
	char Name[255];
	PHOSTENT hostinfo;
	if(gethostname (Name, sizeof(Name)) == 0)
	{ 
		//如果成功地将本地主机名存放入由name参数指定的缓冲区中 
		if((hostinfo = gethostbyname(Name)) != NULL) 
		{ 
			strncpy(ip,inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list),32);
		}
	}
}

int CNetUnits::GetHostPort(SOCKET skt)
{
	SOCKADDR_IN VASAddr;
	int nPort = 0;
	int iAddrLen = sizeof(VASAddr);
	if (skt == NULL)
	{
		nPort = 0;
	}
	else
	{
		getsockname(skt, (SOCKADDR *)&VASAddr, &iAddrLen);
		nPort = ntohs( VASAddr.sin_port);
	}
	return nPort;
}
