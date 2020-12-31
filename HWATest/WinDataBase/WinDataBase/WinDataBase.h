// WinDataBase.h : main header file for the WinDataBase DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWinDataBaseApp
// See WinDataBase.cpp for the implementation of this class
//

class CWinDataBaseApp : public CWinApp
{
public:
	CWinDataBaseApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
