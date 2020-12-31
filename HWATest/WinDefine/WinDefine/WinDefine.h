// WinDefine.h : main header file for the WinDefine DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWinDefineApp
// See WinDefine.cpp for the implementation of this class
//

class CWinDefineApp : public CWinApp
{
public:
	CWinDefineApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
