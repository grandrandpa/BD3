// WinPlayer.h : main header file for the WinPlayer DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "FilesPlayer.h"


#ifdef HWA_PLAYER_EXPORTS
#define HWA_PLAYER_API __declspec(dllexport)
#else
#define HWA_PLAYER_API __declspec(dllimport)
#endif

// CWinPlayerApp
// See WinPlayer.cpp for the implementation of this class
//
#pragma warning(disable:4251)

class HWA_PLAYER_API CWinPlayerApp
{
public:
	CWinPlayerApp();
	~CWinPlayerApp();

// Overrides
private:
	LPVOID		m_pFilePlayer;
public:
	void CreatePlayer(int protocol);
	CHostListener* GetListener();
	void Load(CString strFileName);
	bool Open(CString strFileName);//���ļ�
	bool GetPauseStatus();
	bool GetPlayStatus();
	void Close();//�ر��ļ�
	void Seek(int pos);//������ʼλ��
	int  GetPos();//��ǰλ��
	void startPlay();//��ʼ�����ļ�
	void pausePlay();//��ͣ�����ļ�
	void stopPlay();//ֹͣ�����ļ�
};
