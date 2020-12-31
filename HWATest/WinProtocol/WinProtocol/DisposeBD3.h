#pragma once
#include "DisposeBase.h"
#include "nmea.h"
#include "WinConstant.h"

class CDisposeBD3 : public CDisposeBase
{
public:
	CDisposeBD3(void);
	~CDisposeBD3(void);
	int FindHead(char* buf, int len);
	void DisposeIndex(int index);
public:
	virtual void DisposeData(char* buf, int len);//处理数据
	//参数设置
	virtual int PacketBDIData(char* pBuff, const SETREF& data);//初始化
	virtual int PacketTIMData(char* pBuff, const SETTIM& data);//线缆时延
	virtual int PacketCHAData(char* pBuff, const SETCHA& data);//通道参数
	virtual int PacketCOMData(char* pBuff, const SETCOM& data);//串口
	virtual int PacketMODData(char* pBuff, const SETMOD& data);//模式
	virtual int PacketWORKMODData(char* pBuff, const WORKMOD& data);//工作模式
	virtual int PacketISTData(char* pBuff, const SETIST& data);//入站信号发射
	virtual int PacketLOGData(char* pBuff, const SETLOG& data);//输出
	virtual int PacketPOSData(char* pBuff, const SETPOS& data);//位置
	virtual int PacketWIDData(char* pBuff, const SETWID& data);//
	virtual int PacketREFData(char* pBuff, const SETREF& data);//系统参数
	virtual int PacketMUTData(char* pBuff, const SETMUT& data);//
	virtual int PacketEACData(char* pBuff, const SETEAC& data);//
	virtual int PacketBGTData(char* pBuff, const SETBGT& data);//
	virtual int PacketTTFData(char* pBuff, const SETTTF& data);//
	virtual int PacketSTAData(char* pBuff, const SETSTA& data);//
	virtual int PacketSTSData(char* pBuff, const SETSTS& data);//
	virtual int PacketEVAData(char* pBuff, const SETEVA& data);//
	virtual int PacketTMDData(char* pBuff, const SETTMD& data);
	virtual int PacketACQData(char* pBuff, const SETACQ& data);//捕获模式
	virtual int PacketTRKData(char* pBuff, const SETTRK& data);//跟踪模式
	virtual int PacketBD2POSData(char* pBuff, const BD2_POS& data);
	virtual int PacketIONData(char* pBuff, const SETION& data);//电离层修正
	virtual int PacketPILOTData(char* pBuff, const SETPILOT& data);//数据导频
	virtual int PacketACKData(char* pBuff, const SETACK& data);//查询模式

    //BD3//
    virtual int PacketEPQData(char* pBuff, const SETEPQ& data);
    virtual int PacketTCQData(char* pBuff, const SETTCQ& data);
    virtual int PacketQRQData(char* pBuff, const SETQRQ& data);
    virtual int SendCMDEvent(char* pBuff, int len);

public://解析数据
	void DisposeGNREF(char* buf, int len);
	void DisposeGNMOD(char* buf, int len);
	void DisposeGNCOM(char* buf, int len);
	void DisposeGNRAN(char* buf, int len);
	void DisposeGNPOS(char* buf, int len);
	void DisposeGNXPV(char* buf, int len);
	void DisposeGNTIM(char* buf, int len);
	void DisposeGNSTA(char* buf, int len);
	void DisposeGNGSV(char* buf, int len);
	void DisposeGNGBS(char* buf, int len);

	void DisposeBDCHD(char* buf, int len);//信道译码信息
	void DisposeBDPAO(char* buf, int len);//电文页面播发顺序和历书播发顺序


	//一期
	void DisposeBDEPH(char* buf, int len);
	void DisposeBDALM(char* buf, int len);
	void DisposeBDJAL(char* buf, int len);
	void DisposeBDION(char* buf, int len);
	void DisposeGNCOD(char* buf, int len);
	//二期
	void DisposeBSEPH(char* buf, int len);
	void DisposeBSALM(char* buf, int len);
	void DisposeBSJAL(char* buf, int len);
	void DisposeBSION(char* buf, int len);
	//
	void DisposeSETMOD(u1* buf, int len);


    void AnalyzeNmeaData(char *start_buffer, int length);

    int CalCheckVal(char *pData, int len);
    int CheckData(char *start);
    void strToTime(int time_clk);
    void strToTime1(std::string time_date);

    CString HexToString(char *hex, int len);

private:
    struct nmea_GSA save_GSA;
    struct nmea_GGA save_GGA;
    struct nmea_GSV save_GSV;
    struct nmea_GLL save_GLL;
    struct nmea_RMC save_RMC;

    struct nmea_char_data_save nmea_char_save;
};
