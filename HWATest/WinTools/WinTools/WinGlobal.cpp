#include "StdAfx.h"
#include "WinGlobal.h"

HWND CWinGlobal::m_hMainWnd = NULL;
CWinGlobal::CWinGlobal(void)
{
}

CWinGlobal::~CWinGlobal(void)
{
}

HWND CWinGlobal::GetMainWndHandle()
{
	return m_hMainWnd;
}

void CWinGlobal::SetMainWndHandle(HWND hWnd)
{
	ASSERT(::IsWindow(hWnd));
	m_hMainWnd = hWnd;
}
