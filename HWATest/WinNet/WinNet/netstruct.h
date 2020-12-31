#pragma once

#ifdef HWA_NET_EXPORTS
#define HWA_NET_API __declspec(dllexport)
#else
#define HWA_NET_API __declspec(dllimport)
#endif


#define NET_LENGTH 2048
typedef struct SocketPackageData
{
	int type;
	SOCKET	skt; //SOCKET句柄
	int		nPort;//端口
	char*	pBuffer;//数据缓存
	int		nLength;//数据长度
	SocketPackageData()
	{
		type = 0;
		nPort	= 0;
		pBuffer = NULL;
		nLength = 0;
		skt		= INVALID_SOCKET;
	}
}SocketPackageData;

typedef struct SocketLinkData
{
	//BOOL bIsCntServer;
	BOOL bIsRecProAlive;	//
	CWinThread* pRecThread;	//
	SocketLinkData(){
		//bIsCntServer = FALSE;
		bIsRecProAlive = FALSE;
		pRecThread = NULL;
	}

}SocketLinkData,*PSocketLinkData;

