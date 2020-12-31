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
	UINT8				m_bHgtEnable;//�߳��쳣�Ƿ����
	UINT8				m_bIonEnable;//������ӳ��Ƿ����
	UINT8				m_bTroEnable;//�������ӳ��Ƿ����
	CString				m_strProjFile;
	double				m_dTotalSeconds;
	//��ǰ������������
	BD2_EPOCH			m_epochData;
	BD2_LS_EPOCH		m_epochLeast;
	//////////////////////////////////
	BD2_UNION_POS_MODE	m_uniPOS;//���϶�λ
	BD2_NORMAL_POS_MODE m_normalPOS;//��ͨ��λģʽ
	BD2_POS_SEL_SAT		m_selSat;//ѡ��λ����
	//���ݴ��˳��B1I/B1Q/B1C/B1A/B2a/B2b/B2/B3I/B3Q/B3C/B3A/Bs/B3AE
	BD2_EPH				m_calEPH[MAX_FREQ][MAXCHANNELS];
	BD2_ION				m_calION[MAX_FREQ][MAXCHANNELS];
	BD2_RAN				m_calRAN[MAX_FREQ];
	//��λ���
	BD2_POS				m_calPOS;
private:
	void Reset();
	void Destroy();
	int GetConfig(CString strFile, BD2_NORMAL_POS_MODE* norMOD);
	//�����û����ջ�λ��
	//int CalReceiverPosition(BD2_EPOCH* epoch);
	int CalReceiverNormalPos(BD2_EPOCH* epoch);//��Ƶ��˫Ƶ����Ƶ��λ
	// Overrides
	void AddEphRadio(BD2_EPH* eph);
	void AddIonRadio(BD2_ION* ion);
public:
	void LoadConfig(CString strFile);
	CCalPosListener* GetListener(){ return &m_Listener; }
	void Clear();
public:
	virtual LRESULT OnAnswerCalPositionMOD(WPARAM wParam, LPARAM lParam);//���ö�λģʽ
	virtual LRESULT OnAnswerCalPositionEPH(WPARAM wParam, LPARAM lParam);//����������Ϣ
	virtual LRESULT OnAnswerCalPositionION(WPARAM wParam, LPARAM lParam);//���ǵ�������
	virtual LRESULT OnAnswerCalPositionALM(WPARAM wParam, LPARAM lParam);//����������Ϣ
	virtual LRESULT OnAnswerCalPositionJAL(WPARAM wParam, LPARAM lParam);//���Ǽ�Լ������Ϣ
	virtual LRESULT OnAnswerCalPositionRAN(WPARAM wParam, LPARAM lParam);//α�ࡢ�ز�����������Ϣ
};
