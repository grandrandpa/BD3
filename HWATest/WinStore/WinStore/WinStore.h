// WinStore.h : main header file for the WinStore DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "FileStore.h"


#ifdef HWA_SAVE_EXPORTS
#define HWA_SAVE_API __declspec(dllexport)
#else
#define HWA_SAVE_API __declspec(dllimport)
#endif

// CWinStoreApp
// See WinStore.cpp for the implementation of this class
//

class HWA_SAVE_API CWinStoreApp
{
public:
	CWinStoreApp();
	~CWinStoreApp();
private:
	LPVOID m_pSaveFile;
// Overrides
public:
	bool Open(CString strName, int protocol);
	void Write(char* pBuff, int len);
	void Close();
};
