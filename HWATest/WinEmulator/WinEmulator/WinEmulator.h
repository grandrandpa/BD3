// WinEmulator.h : main header file for the WinEmulator DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWinEmulatorApp
// See WinEmulator.cpp for the implementation of this class
//

class CWinEmulatorApp : public CWinApp
{
public:
	CWinEmulatorApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
