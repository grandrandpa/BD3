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
	bool		m_bOpen;//�ļ��Ƿ񱻴�
	bool		m_bIsThreadPause;//��ͣ
	int			m_nProtocol; //Э��
	double		m_nFileLength;//get file length
	double		m_nCurPosition;//��ǰλ��
	bool		m_bStartThread; //�߳��Ƿ���
	bool		m_bStopThread;
	CWinThread* m_pStartPlayThread;//�߳̾��
	HANDLE		m_hFileOpenMtx;//
	CString		m_strFileName;
private:
	CStdioFile m_filePlay; //�ļ����
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
	void startPlay();//��ʼ�����ļ�
	void pausePlay();//��ͣ�����ļ�
	void stopPlay();//ֹͣ�����ļ�
private:
	static UINT StartFilePlayThread(LPVOID lparm);//�ļ������߳�
	UINT _StartFilePlayThread();//�����ļ������߳�
};
