// WinConfig.h : main header file for the WinConfig DLL
//

#pragma once
//#include "resource.h"		// main symbols
#include "WinStruct.h"

#ifdef HWA_CONFIG_EXPORTS
#define HWA_CONFIG_API __declspec(dllexport)
#else
#define HWA_CONFIG_API __declspec(dllimport)
#endif


// CWinConfigApp
// See WinConfig.cpp for the implementation of this class
//

class HWA_CONFIG_API CWinConfigApp
{
public:
	CWinConfigApp();
	~CWinConfigApp();
// Overrides
public:
	int GetLinkConfig(SETSOCKET* skt, SETCOM* com, CString strName);
};
