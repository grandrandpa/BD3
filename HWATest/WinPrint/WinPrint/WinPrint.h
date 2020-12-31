// WinPrint.h : main header file for the WinPrint DLL
//

#pragma once
#include "PrintFile.h"
#include "PrintData.h"

// CWinPrintApp
// See WinPrint.cpp for the implementation of this class
//
#ifdef HWA_PRINT_EXPORTS
#define HWA_PRINT_API __declspec(dllexport)
#else
#define HWA_PRINT_API __declspec(dllimport)
#endif


class HWA_PRINT_API CWinPrintApp : public CBasicListener
{
public:
	CWinPrintApp();
	~CWinPrintApp();
	// Overrides
private:
	bool m_bSave;
	CString strProjPath;
	CPrintFile m_wndPrint;
	CPrintData m_printData;
	int			m_globalWeek;
	double		m_globalTow;
public:
	void Start();
	void LoadConfig(CString strDatabase, CString strConfigPath);
	void Stop();
private:
	virtual LRESULT OnAnswerInfoCOD(WPARAM wParam, LPARAM lParam);//����ԭʼ��������
	virtual LRESULT OnAnswerInfoEPH(WPARAM wParam, LPARAM lParam);//����������Ϣ
	virtual LRESULT OnAnswerInfoION(WPARAM wParam, LPARAM lParam);//���ǵ�������
	virtual LRESULT OnAnswerInfoALM(WPARAM wParam, LPARAM lParam);//����������Ϣ
	virtual LRESULT OnAnswerInfoJAL(WPARAM wParam, LPARAM lParam);//���Ǽ�Լ������Ϣ
	virtual LRESULT OnAnswerInfoCOM(WPARAM wParam, LPARAM lParam);//�˿�������Ϣ
	virtual LRESULT OnAnswerInfoMOD(WPARAM wParam, LPARAM lParam);//��λ��ʱģʽ��Ϣ
	virtual LRESULT OnAnswerInfoPOS(WPARAM wParam, LPARAM lParam);//��λ�����ٽ����Ϣ
	virtual LRESULT OnAnswerInfoRAN(WPARAM wParam, LPARAM lParam);//α�ࡢ�ز�����������Ϣ
	virtual LRESULT OnAnswerInfoREF(WPARAM wParam, LPARAM lParam);//ʱ�ղο���Ϣ
	virtual LRESULT OnAnswerInfoGSV(WPARAM wParam, LPARAM lParam);//������Ϣ
	virtual LRESULT OnAnswerInfoSTA(WPARAM wParam, LPARAM lParam);//�ն˹���״̬��Ϣ
	virtual LRESULT OnAnswerInfoTIM(WPARAM wParam, LPARAM lParam);//��ʱ�����Ϣ
	virtual LRESULT OnAnswerInfoXPV(WPARAM wParam, LPARAM lParam);//�ѿ������궨λ�����ٽ����Ϣ
	virtual LRESULT OnAnswerInfoGBS(WPARAM wParam, LPARAM lParam);//���������
	virtual LRESULT OnAnswerInfoPAO(WPARAM wParam, LPARAM lParam);	
	virtual LRESULT OnAnswerInfoCHD(WPARAM wParam, LPARAM lParam);		//�ŵ�������Ϣ

    virtual LRESULT OnUpdataInfoAllGSV(WPARAM wParam, LPARAM lParam);//������Ϣ
};
