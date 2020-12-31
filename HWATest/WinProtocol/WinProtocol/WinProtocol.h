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
	void DisposeData(char* buf, int len);//处理数据
	//参数设置
	int PacketBDIData(char* pBuff, const SETREF& data);//初始化
	int PacketTIMData(char* pBuff, const SETTIM& data);//线缆时延
	int PacketCHAData(char* pBuff, const SETCHA& data);//通道参数
	int PacketCOMData(char* pBuff, const SETCOM& data);//串口
	int PacketMODData(char* pBuff, const SETMOD& data);//模式
	int PacketWORKMODData(char* pBuff, const WORKMOD& data);//工作模式
	int PacketISTData(char* pBuff, const SETIST& data);//入站信号发射
	int PacketLOGData(char* pBuff, const SETLOG& data);//输出
	int PacketPOSData(char* pBuff, const SETPOS& data);//位置
	int PacketWIDData(char* pBuff, const SETWID& data);//
	int PacketREFData(char* pBuff, const SETREF& data);//系统参数
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
	int PacketACKData(char* pBuff, const SETACK& data);//查询模式

    //BD3
    int PacketEPQData(char* pBuff, const SETEPQ& data);
    int PacketTCQData(char* pBuff, const SETTCQ& data);
    int PacketQRQData(char* pBuff, const SETQRQ& data);

    int SendCmdData(char* pBuff, int len);
};
