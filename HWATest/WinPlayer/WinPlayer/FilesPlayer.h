#pragma once
#include "WinStruct.h"
#include "WinProtocol.h"
#include "WinListener.h"

#define READ_LENGTH 1024

// CFilesPlayer
// See PlayFiles.cpp for the implementation of this class
//

class CFilesPlayer
{
public:
	CFilesPlayer();
	~CFilesPlayer();
// Overrides
private:
	bool		m_bOpen;//文件是否被打开
	bool		m_bIsThreadPause;//暂停
	int			m_nProtocol; //协议
	double		m_nFileLength;//get file length
	double		m_nCurPosition;//当前位置
	bool		m_bStartThread; //线程是否开启
	bool		m_bStopThread;
	CWinThread* m_pStartPlayThread;//线程句柄
	HANDLE		m_hFileOpenMtx;//
	CString		m_strFileName;
private:
	CStdioFile m_filePlay; //文件句柄
	CWinProtocolApp m_wndProtocolApp;
public:
	CHostListener* GetListener(){ return m_wndProtocolApp.GetListener(); }
	void Reset();
	void CreatePlayer(int protocol);
	void Load(CString strFileName){m_strFileName = strFileName; }
	bool Open(CString strFileName);
	void Close();
	void Seek(int pos);
	int  GetPos();
	bool GetThreadStatus(){return m_bStartThread; }
	bool GetPauseStatus(){return m_bIsThreadPause; }
	void startPlay();//开始播放文件
	void pausePlay();//暂停播放文件
	void stopPlay();//停止播放文件
private:
	static UINT StartFilePlayThread(LPVOID lparm);//文件播放线程
	UINT _StartFilePlayThread();//创建文件播放线程
};
