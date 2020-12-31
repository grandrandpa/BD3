#pragma once
#include <string.h>
#include "WinStruct.h"
#include "WinConstEph.h"
#include "HostListener.h"
#include "tools.h"
#include "WinCrc.h"

#define SATID_BASE	30
class CDisposeBase
{
public:
	CDisposeBase(void);
	~CDisposeBase(void);
public:
	int  m_chLen;//�������ݳ���
	int	 m_nFrame;//
	int m_nlines;//��
	char m_chBuffer[BUFF_LEN]; //��������ʱ�Ļ���
	int m_SvIdErr[MAXCHANNELS];
	DisposeState	m_CmdState;
public:
	BD2_GSV	m_packSKY;
	BD2_GSV	m_packGSV;
	CHostListener m_Listener;
public:
	void Reset();
	CHostListener*	GetListener(){return &m_Listener; }
	virtual void DisposeData(char* buf, int len) = 0;//��������
private://��������
public://���ݴ��
	//��������
	virtual int PacketBDIData(char* pBuff, const SETREF& data) = 0;//��ʼ��
	virtual int PacketTIMData(char* pBuff, const SETTIM& data) = 0;//����ʱ��
	virtual int PacketCHAData(char* pBuff, const SETCHA& data) = 0;//ͨ������
	virtual int PacketCOMData(char* pBuff, const SETCOM& data) = 0;//����
	virtual int PacketMODData(char* pBuff, const SETMOD& data) = 0;//ģʽ
	virtual int PacketWORKMODData(char* pBuff, const WORKMOD& data) = 0;//����ģʽ	
	virtual int PacketISTData(char* pBuff, const SETIST& data) = 0;//��վ�źŷ���	
	virtual int PacketLOGData(char* pBuff, const SETLOG& data) = 0;//���
	virtual int PacketPOSData(char* pBuff, const SETPOS& data) = 0;//λ��
	virtual int PacketWIDData(char* pBuff, const SETWID& data) = 0;//
	virtual int PacketREFData(char* pBuff, const SETREF& data) = 0;//ϵͳ����
	virtual int PacketMUTData(char* pBuff, const SETMUT& data) = 0;//
	virtual int PacketEACData(char* pBuff, const SETEAC& data) = 0;//
	virtual int PacketBGTData(char* pBuff, const SETBGT& data) = 0;//
	virtual int PacketTTFData(char* pBuff, const SETTTF& data) = 0;//
	virtual int PacketSTAData(char* pBuff, const SETSTA& data) = 0;//
	virtual int PacketSTSData(char* pBuff, const SETSTS& data) = 0;//
	virtual int PacketEVAData(char* pBuff, const SETEVA& data) = 0;//
	virtual int PacketTMDData(char* pBuff, const SETTMD& data) = 0;//��ʱģʽ
	virtual int PacketACQData(char* pBuff, const SETACQ& data) = 0;//����ģʽ
	virtual int PacketTRKData(char* pBuff, const SETTRK& data) = 0;//����ģʽ
	virtual int PacketBD2POSData(char* pBuff, const BD2_POS& data) = 0;//λ��
	virtual int PacketIONData(char* pBuff, const SETION& data) = 0;//���������
	virtual int PacketPILOTData(char* pBuff, const SETPILOT& data) = 0;//���ݵ�Ƶ
	virtual int PacketACKData(char* pBuff, const SETACK& data) = 0;//��ѯģʽ

    //BD3//
    virtual int PacketEPQData(char* pBuff, const SETEPQ& data) = 0; //��λ����
    virtual int PacketTCQData(char* pBuff, const SETTCQ& data) = 0;
    virtual int PacketQRQData(char* pBuff, const SETQRQ& data) = 0;
    virtual int SendCMDEvent(char* pBuff, int len) = 0;
};
