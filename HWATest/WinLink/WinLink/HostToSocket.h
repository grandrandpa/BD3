#pragma once
#include "Link2Port.h"

class CHostToSocket : public Link2Port, CSerialSocket
{
public:
	CHostToSocket(void);
	~CHostToSocket(void);
public:
	virtual CHostListener* GetListener();
	virtual bool Open(int Port, DWORD dwRate, int protocol);//注册实例
	virtual void Close();
	virtual bool GetStatus();
	virtual void CompleteRecData(char* buf, int len);
	virtual void Reset();
	//参数设置
	virtual int SetupTIMRequest(const SETTIM& data);//线缆时延
	virtual int SetupCHARequest(const SETCHA& data);//通道参数
	virtual int SetupCOMRequest(const SETCOM& data);//串口
	virtual int SetupMODRequest(const SETMOD& data);//模式
	virtual int SetupWORKRequest(const WORKMOD& data);//工作模式
	virtual int SetupISTRequest(const SETIST& data);//入站信号发射
	virtual int SetupLOGRequest(const SETLOG& data);//输出
	virtual int SetupPOSRequest(const SETPOS& data);//位置
	virtual int SetupWIDRequest(const SETWID& data);//
	virtual int SetupREFRequest(const SETREF& data);//系统参数

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
