#include "StdAfx.h"
#include "SerialPort.h"

CSerialPort::CSerialPort(void)//
	: m_hCom(NULL)
{
	m_bThreadStart = false;

	m_bSendDataPro = false;
	m_SendList.clear();//发送数据队列
	m_hSendListMtx = CreateMutex(NULL,FALSE,NULL);

	m_bRecvDataPro = false;
	m_RecvList.clear();//接收数据队列
	m_hRecvListMtx = CreateMutex(NULL,FALSE,NULL);
	m_bDisposePro = false;
}

CSerialPort::~CSerialPort(void)
{
	Destroy();
	if (m_hSendListMtx)
	{
		CloseHandle(m_hSendListMtx);
	}
	if (m_hRecvListMtx)
	{
		CloseHandle(m_hRecvListMtx);
	}
}

// 销毁
void CSerialPort::Destroy(void)
{
	m_bThreadStart = false;
	m_bSendDataPro = false;
	m_bRecvDataPro = false;
	m_bDisposePro = false;
	m_hDisposePro = NULL;
	m_pReadComThread = NULL;
	m_pWriteComThread = NULL;
	if(m_SendList.size() > 0)
	{
		m_SendList.clear();
	}
	if(m_RecvList.size() > 0)
	{
		m_RecvList.clear();
	}
	if(m_hCom)
	{
		CloseHandle(m_hCom);
		m_hCom = NULL;
	}
	if(m_oRead.hEvent)
	{
		CloseHandle(m_oRead.hEvent);
		m_oRead.hEvent = NULL;
	}
	if(m_oWrite.hEvent)
	{
		CloseHandle(m_oWrite.hEvent);
		m_oWrite.hEvent = NULL;
	}
}

bool CSerialPort::IsOpen()
{
	return m_bThreadStart;
}

bool CSerialPort::ConnectServer(int Port, DWORD dwBaudRate, BYTE bByteSize, BYTE bParity, BYTE bStopBits)
{
	if(!CreateComPort(Port, dwBaudRate, bByteSize, bParity, bStopBits))
	{
		Destroy();
		return false;
	}
	m_bDisposePro = true;
	m_bThreadStart = true;
	m_bSendDataPro = true;
	m_bRecvDataPro = true;
	m_pReadComThread = AfxBeginThread(ReadComThread, this);
	m_pWriteComThread = AfxBeginThread(WriteComThread, this);
	m_hDisposePro = AfxBeginThread(DisposeDataPro, this);
	

	return true;
}

UINT CSerialPort::DisposeDataPro(LPVOID lparm)
{
	CSerialPort* ObjMain = (CSerialPort*)lparm;
	return ObjMain->_DisposeDataPro();
}

UINT CSerialPort::_DisposeDataPro()
{
	int len = 0;
	while(m_bDisposePro)
	{
		WaitForSingleObject(m_hRecvListMtx,INFINITE);
		len = m_RecvList.size();
		if (len > 0)
		{
			ComPackageData* pData = m_RecvList.front();
			m_RecvList.pop_front();
			if (pData)
			{
				this->CompleteRecData(pData->pBuffer, pData->nLength);//处理数据
				if(pData->pBuffer)
					free(pData->pBuffer);
				delete pData;
			}
		}
		ReleaseMutex(m_hRecvListMtx);
		Sleep(2);
	}
	return 0;
}

UINT CSerialPort::ReadComThread(LPVOID lparm)//数据接收线程
{
	CSerialPort* ObjMain = (CSerialPort*)lparm;
	return ObjMain->_ReadComThread();
}

UINT CSerialPort::_ReadComThread()//数据接收
{
	char recBuf[PORT_LENGTH];
	int recLen = 0;
	while(m_bRecvDataPro)
	{
		ZeroMemory(recBuf, sizeof(char)*PORT_LENGTH);
		recLen = ReadBuffer(recBuf, PORT_LENGTH);
		if (recLen > 0)
		{
			WaitForSingleObject(m_hRecvListMtx,INFINITE);
			ComPackageData* pData = new ComPackageData();
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

void CSerialPort::SendData(char* pBuff, int len)
{
	WaitForSingleObject(m_hSendListMtx,INFINITE);
	ComPackageData* pData = new ComPackageData();
	pData->pBuffer = (char*)malloc(len*sizeof(char));
	memcpy(pData->pBuffer, pBuff, len);
	pData->nLength = len;
	this->m_SendList.push_back(pData); //将数据加入到发送队列
	ReleaseMutex(m_hSendListMtx);
}

UINT CSerialPort::WriteComThread(LPVOID lparm)//数据发送线程
{
	CSerialPort* ObjMain = (CSerialPort*)lparm;
	return ObjMain->_WriteComThread();
}

UINT CSerialPort::_WriteComThread()//数据发送
{
	while(m_bSendDataPro)
	{
		WaitForSingleObject(m_hSendListMtx,INFINITE);
		if (m_SendList.size() > 0)
		{
			ComPackageData* pData = m_SendList.front();
			m_SendList.pop_front();
			if (pData)
			{
				WriteBuffer(pData->pBuffer, pData->nLength);
				if(pData->pBuffer)
					free(pData->pBuffer);
				delete pData;
			}
		}
		ReleaseMutex(m_hSendListMtx);
		Sleep(2);
	}
	return 0;
}

bool CSerialPort::CreateComPort(int Port, DWORD dwBaudRate, BYTE bByteSize, BYTE bParity, BYTE bStopBits)
{
	ASSERT(m_hCom == NULL);
	COMMTIMEOUTS CommTimeOuts;
	char chCom[10] = "\0";
	sprintf_s(chCom, "\\\\.\\COM%d", Port);
	m_hCom = CreateFile((LPCSTR)chCom, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if(m_hCom == INVALID_HANDLE_VALUE)
		return false;

	//设置缓存区长度
	SetupComm(m_hCom,4096,4096);
	//清除I/O缓冲区长度
	PurgeComm(m_hCom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 500;
	SetCommTimeouts(m_hCom, &CommTimeOuts);

	DCB dcb;
	dcb.DCBlength = sizeof(DCB);
	GetCommState(m_hCom, &dcb);
	dcb.BaudRate = dwBaudRate;
	dcb.ByteSize = bByteSize;
	dcb.Parity = bParity;
	dcb.StopBits = bStopBits;

	dcb.fOutxCtsFlow = false;//检测发送控制
	dcb.fDtrControl = DTR_CONTROL_DISABLE;

	dcb.fTXContinueOnXoff = 1;
	//Setup software flow control
	dcb.fInX = dcb.fOutX = 0;
	dcb.XonChar = '\021';
	dcb.XoffChar = '\023';
	dcb.XonLim = 2048;
	dcb.XoffLim = 512;
	dcb.fBinary = true;//是否允许二进制模式
	dcb.fParity = 0;   //奇偶校验是否允许

	//改变串口设置
	if(!SetCommState(m_hCom,&dcb))
		return false;
	SetCommMask(m_hCom,EV_CTS | EV_DSR);
	m_oWrite.Offset = 0;
	m_oWrite.OffsetHigh = 0;
	m_oRead.Offset = 0;
	m_oRead.OffsetHigh = 0;
	m_oRead.hEvent = CreateEvent(NULL,true,false,NULL);
	if(m_oRead.hEvent == NULL)
		return false;
	m_oWrite.hEvent = CreateEvent(NULL,true,false,NULL);
	if(m_oWrite.hEvent == NULL)
		return false;

	return true;
}

bool CSerialPort::WriteBuffer(const char* pBuff, int len)
{
	BOOL fWriteState;
	DWORD dwBytesWritten;
	DWORD dwErrorFlags;
	DWORD dwError;
	COMSTAT ComStat;

	fWriteState = WriteFile(m_hCom,pBuff,len,&dwBytesWritten,&m_oWrite);
	if(!fWriteState)
	{
		dwError = GetLastError();
		if(dwError == ERROR_IO_PENDING)
		{
			while(!GetOverlappedResult(m_hCom,&m_oWrite,&dwBytesWritten,true))
			{
				dwError = GetLastError();
				if(dwError == ERROR_IO_INCOMPLETE)
				{
					continue;
				}
				else
				{
					ClearCommError(m_hCom,&dwErrorFlags,&ComStat);
					break;
				}
			}
		}
		else if(dwError == ERROR_INVALID_HANDLE)
		{
			return false;
		}
		else
		{
			ClearCommError(m_hCom,&dwErrorFlags,&ComStat);
			return true;
		}
	}
	return true;
}

int CSerialPort::ReadBuffer(char* pBuff, int len)
{
	BOOL fReadState;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	DWORD dwLength;
	DWORD dwError;

	ClearCommError(m_hCom,&dwErrorFlags,&ComStat);
	dwLength = min((DWORD)len,ComStat.cbInQue);
	if(dwLength>0)
	{
		fReadState = ReadFile(m_hCom,pBuff,dwLength,&dwLength,&m_oRead);
		if(!fReadState)
		{
			dwError = GetLastError();
			if(dwError == ERROR_IO_PENDING)
			{
				while(!GetOverlappedResult(m_hCom,&m_oRead,&dwLength,true))
				{
					dwError = GetLastError();
					if(dwError == ERROR_IO_INCOMPLETE)
					{
						continue;
					}
					else
					{
						ClearCommError(m_hCom,&dwErrorFlags,&ComStat);
						break; 
					}
				}
			}
			else if(dwError == ERROR_INVALID_HANDLE)
			{
				dwLength = -1;
			}
			else
			{
				dwLength = 0;
				ClearCommError(m_hCom,&dwErrorFlags,&ComStat);
			}
		}
	}
	return dwLength;
}
