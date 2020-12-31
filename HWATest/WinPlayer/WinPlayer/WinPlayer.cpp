// WinPlayer.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "WinPlayer.h"

// CWinPlayerApp construction
CWinPlayerApp::CWinPlayerApp()
{
	// TODO: add construction code here,
}
CWinPlayerApp::~CWinPlayerApp()
{
	// TODO: add construction code here,
	delete m_pFilePlayer;
	m_pFilePlayer = NULL;
}
void CWinPlayerApp::CreatePlayer(int protocol)
{
	m_pFilePlayer = new CFilesPlayer;
	CFilesPlayer* pPlayer = (CFilesPlayer*)m_pFilePlayer;
	pPlayer->CreatePlayer(protocol);
	pPlayer->Reset();
}
CHostListener* CWinPlayerApp::GetListener()
{
	if (m_pFilePlayer == NULL)
		return NULL;
	CFilesPlayer* pPlayer = (CFilesPlayer*)m_pFilePlayer;
	return pPlayer->GetListener();
}
// The one and only CWinPlayerApp object
void CWinPlayerApp::Load(CString strFileName)
{
	if (m_pFilePlayer == NULL)
		return;
	CFilesPlayer* pPlayer = (CFilesPlayer*)m_pFilePlayer;
	pPlayer->Load(strFileName);
}
bool CWinPlayerApp::Open(CString strFileName)
{
	if (m_pFilePlayer == NULL)
		return false;
	CFilesPlayer* pPlayer = (CFilesPlayer*)m_pFilePlayer;
	return pPlayer->Open(strFileName);
}
bool CWinPlayerApp::GetPauseStatus()
{
	if (m_pFilePlayer == NULL)
		return false;
	CFilesPlayer* pPlayer = (CFilesPlayer*)m_pFilePlayer;
	return pPlayer->GetPauseStatus();
}
bool CWinPlayerApp::GetPlayStatus()
{
	if (m_pFilePlayer == NULL)
		return false;
	CFilesPlayer* pPlayer = (CFilesPlayer*)m_pFilePlayer;
	return pPlayer->GetThreadStatus();
}
void CWinPlayerApp::Close()
{
	if (m_pFilePlayer == NULL)
		return;
	CFilesPlayer* pPlayer = (CFilesPlayer*)m_pFilePlayer;
	pPlayer->Close();
}
void CWinPlayerApp::Seek(int pos)
{
	if (m_pFilePlayer == NULL)
		return;
	CFilesPlayer* pPlayer = (CFilesPlayer*)m_pFilePlayer;
	pPlayer->Seek(pos);
}
int  CWinPlayerApp::GetPos()
{
	if (m_pFilePlayer == NULL)
		return 0;
	CFilesPlayer* pPlayer = (CFilesPlayer*)m_pFilePlayer;
	return pPlayer->GetPos();
}
void CWinPlayerApp::startPlay()//开始播放文件
{
	if (m_pFilePlayer == NULL)
		return;
	CFilesPlayer* pPlayer = (CFilesPlayer*)m_pFilePlayer;
	pPlayer->startPlay();
}
void CWinPlayerApp::pausePlay()//暂停播放文件
{
	if (m_pFilePlayer == NULL)
		return;
	CFilesPlayer* pPlayer = (CFilesPlayer*)m_pFilePlayer;
	pPlayer->pausePlay();
}
void CWinPlayerApp::stopPlay()//停止播放文件
{
	if (m_pFilePlayer == NULL)
		return;
	CFilesPlayer* pPlayer = (CFilesPlayer*)m_pFilePlayer;
	pPlayer->stopPlay();
}
