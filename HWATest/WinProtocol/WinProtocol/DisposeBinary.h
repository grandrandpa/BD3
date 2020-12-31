#pragma once
#include "DisposeBase.h"


class CDisposeBinary : public CDisposeBase
{
public:
	CDisposeBinary(void);
	~CDisposeBinary(void);
private:
	void DisposeIndex(int index);
	int FindHead(u1* buf, int len);
public:
	virtual void DisposeData(char* buf, int len);//��������
	//��������
	virtual int PacketBDIData(char* pBuff, const SETREF& data);//��ʼ��
	virtual int PacketTIMData(char* pBuff, const SETTIM& data);//����ʱ��
	virtual int PacketCHAData(char* pBuff, const SETCHA& data);//ͨ������
	virtual int PacketCOMData(char* pBuff, const SETCOM& data);//����
	virtual int PacketMODData(char* pBuff, const SETMOD& data);//ģʽ
	virtual int PacketWORKMODData(char* pBuff, const WORKMOD& data);//����ģʽ
	virtual int PacketISTData(char* pBuff, const SETIST& data);//��վ�źŷ���
	virtual int PacketLOGData(char* pBuff, const SETLOG& data);//���
	virtual int PacketPOSData(char* pBuff, const SETPOS& data);//λ��
	virtual int PacketWIDData(char* pBuff, const SETWID& data);//
	virtual int PacketREFData(char* pBuff, const SETREF& data);//ϵͳ����
	virtual int PacketMUTData(char* pBuff, const SETMUT& data);//
	virtual int PacketEACData(char* pBuff, const SETEAC& data);//
	virtual int PacketBGTData(char* pBuff, const SETBGT& data);//
	virtual int PacketTTFData(char* pBuff, const SETTTF& data);//
	virtual int PacketSTAData(char* pBuff, const SETSTA& data);//
	virtual int PacketSTSData(char* pBuff, const SETSTS& data);//
	virtual int PacketEVAData(char* pBuff, const SETEVA& data);//
	virtual int PacketTMDData(char* pBuff, const SETTMD& data);//��ʱģʽ
	virtual int PacketACQData(char* pBuff, const SETACQ& data);//����ģʽ
	virtual int PacketTRKData(char* pBuff, const SETTRK& data);//����ģʽ
	virtual int PacketBD2POSData(char* pBuff, const BD2_POS& data);//
	virtual int PacketIONData(char* pBuff, const SETION& data);//���������
	virtual int PacketPILOTData(char* pBuff, const SETPILOT& data);//���ݵ�Ƶ
	virtual int PacketACKData(char* pBuff, const SETACK& data);//��ѯģʽ

    //BD3//
    virtual int PacketEPQData(char* pBuff, const SETEPQ& data);
    virtual int PacketTCQData(char* pBuff, const SETTCQ& data){return 0;}
    virtual int PacketQRQData(char* pBuff, const SETQRQ& data) {return 0;}
    virtual int SendCMDEvent(char* pBuff, int len) { return 0;}

protected://��������
	void DisposeGNREF(u1* buf, int len);
	void DisposeGNMOD(u1* buf, int len);
	void DisposeGNCOM(u1* buf, int len);
	void DisposeGNRAN(u1* buf, int len);
	void DisposeGNPOS(u1* buf, int len);
	void DisposeGNXPV(u1* buf, int len);
	void DisposeGNTIM(u1* buf, int len);
	void DisposeGNSTA(u1* buf, int len);
	void DisposeGNGSV(u1* buf, int len);
	void DisposeGNGBS(u1* buf, int len);

	void DisposeBDCHD(u1* buf, int len);//�ŵ�������Ϣ
	void DisposeBDPAO(u1* buf, int len);//����ҳ�沥��˳������鲥��˳��



	//һ��
	void DisposeBDEPH(u1* buf, int len);
	void DisposeBDALM(u1* buf, int len);
	void DisposeBDJAL(u1* buf, int len);
	void DisposeBDION(u1* buf, int len);
	void DisposeGNCOD(u1* buf, int len);
	//����
	void DisposeBSEPH(u1* buf, int len);
	void DisposeBSALM(u1* buf, int len);
	void DisposeBSJAL(u1* buf, int len);
	void DisposeBSION(u1* buf, int len);
	//
	void DisposeSETMOD(u1* buf, int len);
	void DisposeSETLOG(u1* buf, int len);
	void DisposeSETSTA(u1* buf, int len);
	void DisposeBDSIM(u1* buf, int len);
	void DisposeBDVER(u1* buf, int len);
};
