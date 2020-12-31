// WinLink.h : main header file for the WinLink DLL
//

#pragma once
#include "resource.h"		// main symbols
#include "HostToComm.h"
#include "HostToSocket.h"

#ifdef HWA_LINK_EXPORTS
#define HWA_LINK_API __declspec(dllexport)
#else
#define HWA_LINK_API __declspec(dllimport)
#endif

class HWA_LINK_API CWinLinkApp
{
public:
	CWinLinkApp();
	~CWinLinkApp();
// Overrides
private:
	bool		m_bLink;
	Link2Port* m_pLink2Port;
public:
	CHostListener* GetListener();
	bool CreateComm(int port, DWORD baud, int protocol);
	bool CreateSocket(int port, DWORD dwIP, int protocol);
	bool Open(bool isCom, int Port, DWORD dwRate, int protocol);//注册实例
	void Close();
	bool GetStatus();
	//参数设置
	int SetupTIMRequest(const SETTIM& data);//线缆时延
	int SetupCHARequest(const SETCHA& data);//通道参数
	int SetupCOMRequest(const SETCOM& data);//串口
	int SetupMODRequest(const SETMOD& data);//模式
	int SetupWORKRequest(const WORKMOD& data);//工作模式
	int SetupISTRequest(const SETIST& data);//入站信号发射
	int SetupLOGRequest(const SETLOG& data);//输出
	int SetupPOSRequest(const SETPOS& data);//位置
	int SetupWIDRequest(const SETWID& data);//
	int SetupREFRequest(const SETREF& data);//系统参数

	int SetupBDIRequest(const SETREF& data);
	int SetupMUTRequest(const SETMUT& data);
	int SetupEACRequest(const SETEAC& data);
	int SetupBGTRequest(const SETBGT& data);
	int SetupTTFRequest(const SETTTF& data);
	int SetupSTARequest(const SETSTA& data);
	int SetupSTSRequest(const SETSTS& data);
	int SetupEVARequest(const SETEVA& data);
	int SetupTMDRequest(const SETTMD& data);

	int SetupACQRequest(const SETACQ& data);
	int SetupTRKRequest(const SETTRK& data);
	int SetupIONRequest(const SETION& data);
	int SetupPILOTRequest(const SETPILOT& data);
	int SetupACKRequest(const SETACK& data);

	int AnswerPOSRequest(const BD2_POS& data);

    //BD3//
    int SetupEPQRequest(const SETEPQ& data);
    int SetupTCQRequest(const SETTCQ& data);
    int SetupQRQRequest(const SETQRQ& data);

    int SendCmdRequest(std::string& data);
};
