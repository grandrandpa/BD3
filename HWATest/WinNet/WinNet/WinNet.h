// WinNet.h : main header file for the WinNet DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWinNetApp
// See WinNet.cpp for the implementation of this class
//

class CWinNetApp : public CWinApp
{
public:
	CWinNetApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
