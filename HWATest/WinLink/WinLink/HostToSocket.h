#pragma once
#include "Link2Port.h"

class CHostToSocket : public Link2Port, CSerialSocket
{
public:
	CHostToSocket(void);
	~CHostToSocket(void);
public:
	virtual CHostListener* GetListener();
	virtual bool Open(int Port, DWORD dwRate, int protocol);//ע��ʵ��
	virtual void Close();
	virtual bool GetStatus();
	virtual void CompleteRecData(char* buf, int len);
	virtual void Reset();
	//��������
	virtual int SetupTIMRequest(const SETTIM& data);//����ʱ��
	virtual int SetupCHARequest(const SETCHA& data);//ͨ������
	virtual int SetupCOMRequest(const SETCOM& data);//����
	virtual int SetupMODRequest(const SETMOD& data);//ģʽ
	virtual int SetupWORKRequest(const WORKMOD& data);//����ģʽ
	virtual int SetupISTRequest(const SETIST& data);//��վ�źŷ���
	virtual int SetupLOGRequest(const SETLOG& data);//���
	virtual int SetupPOSRequest(const SETPOS& data);//λ��
	virtual int SetupWIDRequest(const SETWID& data);//
	virtual int SetupREFRequest(const SETREF& data);//ϵͳ����

	virtual int SetupBDIRequest(const SETREF& data);
	virtual int SetupMUTRequest(const SETMUT& data);
	virtual int SetupEACRequest(const SETEAC& data);
	virtual int SetupBGTRequest(const SETBGT& data);
	virtual int SetupTTFRequest(const SETTTF& data);
	virtual int SetupSTARequest(const SETSTA& data);
	virtual int SetupSTSRequest(const SETSTS& data);
	virtual int SetupEVARequest(const SETEVA& data);
	virtual int SetupTMDRequest(const SETTMD& data);
	virtual int AnswerPOSRequest(const BD2_POS& data);

	virtual int SetupACQRequest(const SETACQ& data);
	virtual int SetupTRKRequest(const SETTRK& data);
	virtual int SetupIONRequest(const SETION& data);
	virtual int SetupPILOTRequest(const SETPILOT& data);
	virtual int SetupACKRequest(const SETACK& data);

    //BD3//
    virtual int SetupEPQRequest(const SETEPQ& data);
    virtual int SetupTCQRequest(const SETTCQ& data);
    virtual int SetupQRQRequest(const SETQRQ& data){ return 0;}

    virtual int SendCmdRequest(std::string& data) {return 0;};
};
