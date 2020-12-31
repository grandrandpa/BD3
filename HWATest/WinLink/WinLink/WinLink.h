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
	bool Open(bool isCom, int Port, DWORD dwRate, int protocol);//ע��ʵ��
	void Close();
	bool GetStatus();
	//��������
	int SetupTIMRequest(const SETTIM& data);//����ʱ��
	int SetupCHARequest(const SETCHA& data);//ͨ������
	int SetupCOMRequest(const SETCOM& data);//����
	int SetupMODRequest(const SETMOD& data);//ģʽ
	int SetupWORKRequest(const WORKMOD& data);//����ģʽ
	int SetupISTRequest(const SETIST& data);//��վ�źŷ���
	int SetupLOGRequest(const SETLOG& data);//���
	int SetupPOSRequest(const SETPOS& data);//λ��
	int SetupWIDRequest(const SETWID& data);//
	int SetupREFRequest(const SETREF& data);//ϵͳ����

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
