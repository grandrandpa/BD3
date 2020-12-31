#pragma once
#include "WinStruct.h"
#include "WinListener.h"
#include "SerialPort.h"
#include "SerialSocket.h"
#include "WinProtocol.h"

class Link2Port
{
public:
	int m_nProtocol;
	bool m_bLinkStatus;
	CWinProtocolApp m_wndProtocolApp;
public:
	virtual CHostListener* GetListener() = 0;
	virtual bool Open(int Port, DWORD dwRate, int protocol) = 0;//ע��ʵ��
	virtual void Close() = 0;
	virtual bool GetStatus() = 0;
	//��������
	virtual int SetupTIMRequest(const SETTIM& data) = 0;//����ʱ��
	virtual int SetupCHARequest(const SETCHA& data) = 0;//ͨ������
	virtual int SetupCOMRequest(const SETCOM& data) = 0;//����
	virtual int SetupMODRequest(const SETMOD& data) = 0;//ģʽ
	virtual int SetupWORKRequest(const WORKMOD& data)=0;//����ģʽ
	virtual int SetupISTRequest(const SETIST& data)=0;//��վ�źŷ���
	virtual int SetupLOGRequest(const SETLOG& data) = 0;//���
	virtual int SetupPOSRequest(const SETPOS& data) = 0;//λ��
	virtual int SetupWIDRequest(const SETWID& data) = 0;//
	virtual int SetupREFRequest(const SETREF& data) = 0;//ϵͳ����

	virtual int SetupBDIRequest(const SETREF& data) = 0;
	virtual int SetupMUTRequest(const SETMUT& data) = 0;
	virtual int SetupEACRequest(const SETEAC& data) = 0;
	virtual int SetupBGTRequest(const SETBGT& data) = 0;
	virtual int SetupTTFRequest(const SETTTF& data) = 0;
	virtual int SetupSTARequest(const SETSTA& data) = 0;
	virtual int SetupSTSRequest(const SETSTS& data) = 0;
	virtual int SetupEVARequest(const SETEVA& data) = 0;
	virtual int SetupTMDRequest(const SETTMD& data) = 0;

	virtual int SetupACQRequest(const SETACQ& data) = 0;
	virtual int SetupTRKRequest(const SETTRK& data) = 0;
	virtual int SetupIONRequest(const SETION& data) = 0;
	virtual int SetupPILOTRequest(const SETPILOT& data) = 0;
	virtual int SetupACKRequest(const SETACK& data) = 0;
	//���ݷ���
	virtual int AnswerPOSRequest(const BD2_POS& data) = 0;

    //BD3//
    virtual int SetupEPQRequest(const SETEPQ& data) = 0;
    virtual int SetupTCQRequest(const SETTCQ& data) = 0;
    virtual int SetupQRQRequest(const SETQRQ& data) = 0;


    //
    virtual int SendCmdRequest(std::string& data) = 0;
};
