#include "StdAfx.h"
#include "FileStore.h"

CFileStore::CFileStore(void)
{
	m_bOpen = FALSE;
	m_storeData.clear();
	m_pWriteThread = NULL;
	InitializeCriticalSection(&m_Lock);
}

CFileStore::~CFileStore(void)
{
	Close();
}

bool CFileStore::Open(CString strName, UINT flag)
{
	BOOL bRun = m_file.Open(strName, flag);
	if (bRun)
	{
		m_bOpen = TRUE;
		m_bStartWrite = TRUE;
		m_pWriteThread = AfxBeginThread(WriteDataPro, this);//开启数据存储线程
	}
	return bRun;
}
void CFileStore::Write(char* pBuff, int len)
{
	if (m_bOpen)
	{
		EnterCriticalSection(&m_Lock);
		FilePackData* pData = new FilePackData;
		pData->pBuffer = (char*)malloc(len*sizeof(char));
		memcpy(pData->pBuffer, pBuff, len);
		pData->nLength = len;
		m_storeData.push_back(pData);
		LeaveCriticalSection(&m_Lock);
	}
}
void CFileStore::Close()
{
	m_bOpen = FALSE;
	m_bStartWrite = FALSE;
	m_pWriteThread = NULL;
	//PostThreadMessage(m_pWriteThread->m_nThreadID)
	if(m_file.m_pStream != NULL)
	{
		m_file.Close();
	}
}

UINT CFileStore::WriteDataPro(LPVOID lparm)
{
	CFileStore* pFile = (CFileStore*)lparm;
	UINT ret = pFile->_WriteDataPro();

	return ret;
}
UINT CFileStore::_WriteDataPro()
{
	while (m_bStartWrite)
	{
		EnterCriticalSection(&m_Lock);
		try
		{
			if (m_storeData.size() > 0)
			{
				FilePackData* pData =  m_storeData.front();
				m_storeData.pop_front();
				if (pData)
				{
					if(m_bOpen)//当文件已经打开时，才存储
						m_file.Write(pData->pBuffer, pData->nLength);
					if (pData->pBuffer)
						free(pData->pBuffer);
					delete pData;
				}
			}
		}
		catch (...)
		{
			
		}
		LeaveCriticalSection(&m_Lock);
		Sleep(10);
	}
	return 0;
}