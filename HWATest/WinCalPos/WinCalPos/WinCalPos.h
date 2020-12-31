// WinCalPos.h : main header file for the WinCalPos DLL
//

#pragma once
#include "CalPosListener.h"
#include "calstruct.h"

int CalBranchToitem(int branch);
class HWA_POS_API CWinCalPosApp : public CBasicListener
{
public:
	CWinCalPosApp();
	~CWinCalPosApp();
private:
	CCalPosListener		m_Listener;
	UINT8				m_nTestPosMod;
	UINT8				m_nTestFlag;
	UINT8				m_nPosType;
	UINT8				m_bUpdateData;
	UINT8				m_bHgtEnable;//高程异常是否可用
	UINT8				m_bIonEnable;//电离层延迟是否可用
	UINT8				m_bTroEnable;//对流层延迟是否可用
	CString				m_strProjFile;
	double				m_dTotalSeconds;
	//当前周数和周内秒
	BD2_EPOCH			m_epochData;
	BD2_LS_EPOCH		m_epochLeast;
	//////////////////////////////////
	BD2_UNION_POS_MODE	m_uniPOS;//联合定位
	BD2_NORMAL_POS_MODE m_normalPOS;//普通定位模式
	BD2_POS_SEL_SAT		m_selSat;//选择定位卫星
	//数据存放顺序：B1I/B1Q/B1C/B1A/B2a/B2b/B2/B3I/B3Q/B3C/B3A/Bs/B3AE
	BD2_EPH				m_calEPH[MAX_FREQ][MAXCHANNELS];
	BD2_ION				m_calION[MAX_FREQ][MAXCHANNELS];
	BD2_RAN				m_calRAN[MAX_FREQ];
	//定位结果
	BD2_POS				m_calPOS;
private:
	void Reset();
	void Destroy();
	int GetConfig(CString strFile, BD2_NORMAL_POS_MODE* norMOD);
	//计算用户接收机位置
	//int CalReceiverPosition(BD2_EPOCH* epoch);
	int CalReceiverNormalPos(BD2_EPOCH* epoch);//单频、双频、三频定位
	// Overrides
	void AddEphRadio(BD2_EPH* eph);
	void AddIonRadio(BD2_ION* ion);
public:
	void LoadConfig(CString strFile);
	CCalPosListener* GetListener(){ return &m_Listener; }
	void Clear();
public:
	virtual LRESULT OnAnswerCalPositionMOD(WPARAM wParam, LPARAM lParam);//设置定位模式
	virtual LRESULT OnAnswerCalPositionEPH(WPARAM wParam, LPARAM lParam);//卫星星历信息
	virtual LRESULT OnAnswerCalPositionION(WPARAM wParam, LPARAM lParam);//卫星电离层参数
	virtual LRESULT OnAnswerCalPositionALM(WPARAM wParam, LPARAM lParam);//卫星历书信息
	virtual LRESULT OnAnswerCalPositionJAL(WPARAM wParam, LPARAM lParam);//卫星简约历书信息
	virtual LRESULT OnAnswerCalPositionRAN(WPARAM wParam, LPARAM lParam);//伪距、载波、多普勒信息
};
