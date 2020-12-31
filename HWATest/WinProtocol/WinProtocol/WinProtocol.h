// WinProtocol.h : main header file for the WinProtocol DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "DisposeNMEA.h"
#include "DisposeBinary.h"
#include "DisposeBD3.h"


#ifdef HWA_PROTOCOL_EXPORTS
#define HWA_PROTOCOL_API __declspec(dllexport)
#else
#define HWA_PROTOCOL_API __declspec(dllimport)
#endif

// CWinProtocolApp
// See WinProtocol.cpp for the implementation of this class
//

class HWA_PROTOCOL_API CWinProtocolApp
{
public:
	CWinProtocolApp();
	~CWinProtocolApp();

// Overrides
private:
	CDisposeBase*  m_pDispose;
public:
	void CreateObject(int protocol);
	void DestroyObject();
public:
	void Reset();
	CHostListener*	GetListener(){return m_pDispose->GetListener(); }
	void DisposeData(char* buf, int len);//��������
	//��������
	int PacketBDIData(char* pBuff, const SETREF& data);//��ʼ��
	int PacketTIMData(char* pBuff, const SETTIM& data);//����ʱ��
	int PacketCHAData(char* pBuff, const SETCHA& data);//ͨ������
	int PacketCOMData(char* pBuff, const SETCOM& data);//����
	int PacketMODData(char* pBuff, const SETMOD& data);//ģʽ
	int PacketWORKMODData(char* pBuff, const WORKMOD& data);//����ģʽ
	int PacketISTData(char* pBuff, const SETIST& data);//��վ�źŷ���
	int PacketLOGData(char* pBuff, const SETLOG& data);//���
	int PacketPOSData(char* pBuff, const SETPOS& data);//λ��
	int PacketWIDData(char* pBuff, const SETWID& data);//
	int PacketREFData(char* pBuff, const SETREF& data);//ϵͳ����
	int PacketMUTData(char* pBuff, const SETMUT& data);//
	int PacketEACData(char* pBuff, const SETEAC& data);//
	int PacketBGTData(char* pBuff, const SETBGT& data);//
	int PacketTTFData(char* pBuff, const SETTTF& data);//
	int PacketSTAData(char* pBuff, const SETSTA& data);//
	int PacketSTSData(char* pBuff, const SETSTS& data);//
	int PacketEVAData(char* pBuff, const SETEVA& data);//
	int PacketTMDData(char* pBuff, const SETTMD& data);
	int PacketACQData(char* pBuff, const SETACQ& data);//
	int PacketTRKData(char* pBuff, const SETTRK& data);
	int PacketBD2POSData(char* pBuff, const BD2_POS& data);
	int PacketIONData(char* pBuff, const SETION& data);
	int PacketPILOTData(char* pBuff, const SETPILOT& data);
	int PacketACKData(char* pBuff, const SETACK& data);//��ѯģʽ

    //BD3
    int PacketEPQData(char* pBuff, const SETEPQ& data);
    int PacketTCQData(char* pBuff, const SETTCQ& data);
    int PacketQRQData(char* pBuff, const SETQRQ& data);

    int SendCmdData(char* pBuff, int len);
};
