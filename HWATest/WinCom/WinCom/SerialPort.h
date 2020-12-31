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
	SOCKET	skt; //SOCKET���
	int		nPort;//�˿�
	char*	pBuffer;//���ݻ���
	int		nLength;//���ݳ���
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
	// ͨѶ�豸���
	HANDLE m_hCom;
	// �첽I/O��
	OVERLAPPED m_oRead;
	// �첽I/Oд
	OVERLAPPED m_oWrite;
	// ���ڶ��߳�
	CWinThread* m_pReadComThread;
	// ����д�߳�
	CWinThread* m_pWriteComThread;
	BOOL m_bThreadStart;//�߳�
private:
	BOOL m_bRecvDataPro;//���ݽ���
	static UINT ReadComThread(LPVOID lparm);//���ݽ����߳�
	UINT _ReadComThread();//

	
	//���ݷ����߳�
	BOOL m_bSendDataPro;//���ݷ���
	static UINT WriteComThread(LPVOID lparm);//���ݷ����߳�
	UINT _WriteComThread();

	//���ݴ���
	CWinThread* m_hDisposePro;//���ݴ����߳̾��
	BOOL m_bDisposePro;//���ݴ���
	static UINT DisposeDataPro(LPVOID lparm);
	UINT _DisposeDataPro();
	
	std::list<ComPackageData*> m_SendList; //���ݷ��Ͷ���
	HANDLE m_hSendListMtx;//���ݷ����¼����

	std::list<ComPackageData*> m_RecvList; //���ݽ��ն���
	HANDLE m_hRecvListMtx;//���ݽ����¼����
protected:
	virtual void CompleteRecData(char* buf, int len) = 0;
	virtual void Reset() = 0;
	bool WriteBuffer(const char* pBuff, int len);
	int ReadBuffer(char* pBuff, int len);
	bool CreateComPort(int Port, DWORD dwBaudRate, BYTE bByteSize, BYTE bParity, BYTE bStopBits);
public:
	bool ConnectServer(int Port, DWORD dwBaudRate = 115200, BYTE bByteSize=8, BYTE bParity=NOPARITY, BYTE bStopBits=ONESTOPBIT);
	// ����
	void Destroy(void);
	void SendData(char* pBuff, int len);
	//
	bool IsOpen();
};
