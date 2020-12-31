// WinStore.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "WinStore.h"

// CWinStoreApp construction
CWinStoreApp::CWinStoreApp()
{
	// TODO: add construction code here,
	m_pSaveFile = NULL;
}

CWinStoreApp::~CWinStoreApp()
{
	// TODO: add construction code here,
	Close();
	delete m_pSaveFile;
	m_pSaveFile = NULL;
}

bool CWinStoreApp::Open(CString strName, int protocol)
{
	bool flag = false;
	m_pSaveFile = new CFileStore;
	CFileStore* pStore = (CFileStore*)m_pSaveFile;
	if(pStore == NULL)
		return false;
	if (protocol == 2)
		flag = pStore->Open(strName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	else if (protocol == 1)
		flag = pStore->Open(strName, CFile::modeCreate | CFile::modeWrite | CFile::typeText);

	return flag;
}
void CWinStoreApp::Write(char* pBuff, int len)
{
	CFileStore* pStore = (CFileStore*)m_pSaveFile;
	if(pStore == NULL)
		return;
	pStore->Write(pBuff, len);
}
void CWinStoreApp::Close()
{
	CFileStore* pStore = (CFileStore*)m_pSaveFile;
	if(pStore == NULL)
		return;
	pStore->Close();
	m_pSaveFile = NULL;
}

