// PlayFiles.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "FilesPlayer.h"

// CFilesPlayer

CFilesPlayer::CFilesPlayer()
{
	// TODO: add construction code here
	m_bOpen = false;
	m_bIsThreadPause = false;
	m_bStartThread = false;
	m_nCurPosition = 0;
	m_nFileLength = 0;
	m_strFileName.Empty();
	m_pStartPlayThread = NULL;
	m_hFileOpenMtx = CreateMutex(NULL, FALSE, NULL);
}

CFilesPlayer::~CFilesPlayer()
{
	m_bOpen = false;
	m_bIsThreadPause = false;
	m_bStartThread = false;
	m_nFileLength = 0;
	m_pStartPlayThread = NULL;
	m_hFileOpenMtx = NULL;
	if (m_bOpen && m_filePlay.m_pStream != NULL)
		m_filePlay.Close();
}
void CFilesPlayer::Reset()
{
	m_bOpen = false;
	m_bIsThreadPause = false;
	m_bStartThread = false;
	m_nCurPosition = 0;
	m_nFileLength = 0;
	m_strFileName.Empty();
	m_pStartPlayThread = NULL;
}
void CFilesPlayer::CreatePlayer(int protocol)
{
	m_nProtocol = protocol;
	m_wndProtocolApp.CreateObject(protocol);
}
bool CFilesPlayer::Open(CString strFileName)
{
	bool bRun = false;

	if (m_nProtocol == PROTOCOL_NMEA)//NMEA
	{
		bRun = m_filePlay.Open(strFileName, CFile::typeText | CFile::modeRead);
	}
	else if (m_nProtocol == PROTOCOL_BINARY)//Binary
	{
		bRun = m_filePlay.Open(strFileName, CFile::typeBinary | CFile::modeRead);
	}
	if (!bRun)
		return false;
	m_bOpen = true;
	m_nFileLength = m_filePlay.GetLength()*1.0;//get file length

	return bRun;
}
void CFilesPlayer::Close()
{
	m_bOpen = false;
	if (m_filePlay.m_pStream != NULL)
		m_filePlay.Close();
}
void CFilesPlayer::Seek(int pos)
{
	double rate = pos / 100.0;
	double percent = m_nCurPosition*1.0 / m_nFileLength;
	if(pos < 0 || pos > 100)
		return;
	//WaitForSingleObject(m_hFileOpenMtx, INFINITE);
	m_bOpen = false;
	if (rate <= 0 || rate >= 100)
	{
		m_filePlay.SeekToBegin();
		m_nCurPosition = m_nFileLength;
	} 
	else if (rate > percent)
	{
		m_filePlay.Seek((ULONGLONG)(m_nFileLength*(rate-percent)), CFile::current);
		m_nCurPosition = (m_nFileLength*rate);
	}
	else if (rate < percent)
	{
		m_filePlay.Seek((ULONGLONG)(m_nFileLength*(rate-percent)), CFile::current);
		m_nCurPosition = (m_nFileLength*rate);
	}
	m_bOpen = true;
	//ReleaseMutex(m_hFileOpenMtx);
}
int  CFilesPlayer::GetPos()
{
	int pos = 0;
	if(m_nFileLength <= 0)
		return 0;
	if(m_nCurPosition >= m_nFileLength)
		return 100;
	pos = (int)(m_nCurPosition*100 / m_nFileLength);

	return pos;
}

void CFilesPlayer::startPlay()
{
	if (m_bIsThreadPause)
	{
		m_bIsThreadPause = false;
		m_pStartPlayThread->ResumeThread();
	}
	else
	{
		stopPlay();//如果已经开启线程，则结束线程
		m_nCurPosition = 0;
		m_bStartThread = true;
		m_pStartPlayThread = AfxBeginThread(StartFilePlayThread, this);
	}
}
void CFilesPlayer::pausePlay()
{
	if (!m_bIsThreadPause && m_pStartPlayThread != NULL)
	{
		m_bIsThreadPause = true;
		m_pStartPlayThread->SuspendThread();
	}
}
void CFilesPlayer::stopPlay()
{
	m_bStartThread = false;
	m_bIsThreadPause = false;
	/*if(m_pStartPlayThread != NULL)
	{
		PostThreadMessage(m_pStartPlayThread->m_nThreadID, MSG_PLAY_FILE_STOP, 0, 0);
		m_pStartPlayThread = NULL;
	}*/
}
UINT CFilesPlayer::StartFilePlayThread(LPVOID lparm)
{
	CFilesPlayer* pTheApp = (CFilesPlayer*)lparm;
	return pTheApp->_StartFilePlayThread();
}
UINT CFilesPlayer::_StartFilePlayThread()
{
	int len = 0;
	double val = 0; 
	CString strText;
	char buff[READ_LENGTH];
	ZeroMemory(buff, sizeof(char)*READ_LENGTH);
	m_nCurPosition = 0;
	m_bStopThread = FALSE;
	while (m_bStartThread)
	{
		try
		{
			if (m_bOpen)
			{
				len = m_filePlay.Read(buff, READ_LENGTH);
				if (len > 0)
				{
					m_wndProtocolApp.DisposeData(buff, len);
					m_nCurPosition += len;
				}
				else//当文件读完以后，停止回放
				{
					m_bStartThread = false;
					m_bIsThreadPause = false;
					m_nCurPosition = m_nFileLength;
					m_filePlay.SeekToBegin();//回到起点
					break;
				}
			}
		}
		catch (...)
		{

		}
		Sleep(5);
	}
	return 0;
}
/*
UINT CFilesPlayer::StartFilePlayThread(LPVOID lparm)
{
int len = 0;
double val = 0; 
CString strText;
char buff[READ_LENGTH];
ZeroMemory(buff, sizeof(char)*READ_LENGTH);
CFilesPlayer* pTheApp = (CFilesPlayer*)lparm;
pTheApp->m_nCurPosition = 0;
pTheApp->m_bStopThread = FALSE;
while (pTheApp->m_bStartThread)
{
//WaitForSingleObject(pTheApp->m_hFileOpenMtx, INFINITE);
try
{
if (pTheApp->m_bOpen)
{
len = pTheApp->m_filePlay.Read(buff, READ_LENGTH);
if (len > 0)
{
pTheApp->m_wndProtocolApp.DisposeData(buff, len);
pTheApp->m_nCurPosition += len;
}
else//当文件读完以后，停止回放
{
pTheApp->m_bStartThread = false;
pTheApp->m_bIsThreadPause = false;
pTheApp->m_nCurPosition = pTheApp->m_nFileLength;
pTheApp->m_filePlay.SeekToBegin();//回到起点
break;
}
}
}
catch (...)
{

}
//ReleaseMutex(pTheApp->m_hFileOpenMtx);
Sleep(5);
}
return 0;

//return pTheApp->_StartFilePlayThread();
}
*/
