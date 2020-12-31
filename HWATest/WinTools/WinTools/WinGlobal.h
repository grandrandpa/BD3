#pragma once
#include "datatype.h"

class HWA_TOOL_API CWinGlobal
{
public:
	CWinGlobal(void);
	~CWinGlobal(void);
public:
	static HWND m_hMainWnd;
	static HWND GetMainWndHandle(void);
	static void SetMainWndHandle(HWND hWnd);
};
