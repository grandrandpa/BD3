// WinCom.h : main header file for the WinCom DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWinComApp
// See WinCom.cpp for the implementation of this class
//

class CWinComApp : public CWinApp
{
public:
	CWinComApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
