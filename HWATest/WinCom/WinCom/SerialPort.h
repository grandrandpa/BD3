#pragma once
#include "afx.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <process.h>

#ifdef HWA_COM_EXPORTS
#define HWA_COM_API __declspec(dllexport)
#else
#define HWA_COM_API __declspec(dllimport)
#endif

#define SAFE_DELETE(p) {if(p){delete p; p=NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p){delete p; p=NULL;}}
#define PORT_LENGTH 2048
typedef struct ComPackageData
{
	int type;
	SOCKET	skt; //SOCKET句柄
	int		nPort;//端口
	char*	pBuffer;//数据缓存
	int		nLength;//数据长度
	ComPackageData()
	{
		type = 0;
		nPort	= 0;
		pBuffer = NULL;
		nLength = 0;
		skt		= INVALID_SOCKET;
	}
}ComPackageData;

#pragma warning(disable:4251)
class HWA_COM_API CSerialPort
{
public:
	CSerialPort(void);
	~CSerialPort(void);
private:
	// 通讯设备句柄
	HANDLE m_hCom;
	// 异步I/O读
	OVERLAPPED m_oRead;
	// 异步I/O写
	OVERLAPPED m_oWrite;
	// 串口读线程
	CWinThread* m_pReadComThread;
	// 串口写线程
	CWinThread* m_pWriteComThread;
	BOOL m_bThreadStart;//线程
private:
	BOOL m_bRecvDataPro;//数据接收
	static UINT ReadComThread(LPVOID lparm);//数据接收线程
	UINT _ReadComThread();//

	
	//数据发送线程
	BOOL m_bSendDataPro;//数据发送
	static UINT WriteComThread(LPVOID lparm);//数据发送线程
	UINT _WriteComThread();

	//数据处理
	CWinThread* m_hDisposePro;//数据处理线程句柄
	BOOL m_bDisposePro;//数据处理
	static UINT DisposeDataPro(LPVOID lparm);
	UINT _DisposeDataPro();
	
	std::list<ComPackageData*> m_SendList; //数据发送队列
	HANDLE m_hSendListMtx;//数据发送事件句柄

	std::list<ComPackageData*> m_RecvList; //数据接收队列
	HANDLE m_hRecvListMtx;//数据接收事件句柄
protected:
	virtual void CompleteRecData(char* buf, int len) = 0;
	virtual void Reset() = 0;
	bool WriteBuffer(const char* pBuff, int len);
	int ReadBuffer(char* pBuff, int len);
	bool CreateComPort(int Port, DWORD dwBaudRate, BYTE bByteSize, BYTE bParity, BYTE bStopBits);
public:
	bool ConnectServer(int Port, DWORD dwBaudRate = 115200, BYTE bByteSize=8, BYTE bParity=NOPARITY, BYTE bStopBits=ONESTOPBIT);
	// 销毁
	void Destroy(void);
	void SendData(char* pBuff, int len);
	//
	bool IsOpen();
};
