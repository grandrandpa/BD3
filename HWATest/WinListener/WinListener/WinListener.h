// WinListener.h : main header file for the WinListener DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWinListenerApp
// See WinListener.cpp for the implementation of this class
//
#include "HostListener.h"

class HWA_LISTENER_API CWinListenerApp
{
public:
	CWinListenerApp();
	~CWinListenerApp();
private:
	LPVOID m_pListener;
// Overrides
public:
	CHostListener* GetListener();
	LRESULT OnAnswerInfoCOD(WPARAM wParam, LPARAM lParam);//����ԭʼ��������
	LRESULT OnAnswerInfoEPH(WPARAM wParam, LPARAM lParam);//����������Ϣ
	LRESULT OnAnswerInfoION(WPARAM wParam, LPARAM lParam);//���ǵ�������
	LRESULT OnAnswerInfoALM(WPARAM wParam, LPARAM lParam);//����������Ϣ
	LRESULT OnAnswerInfoJAL(WPARAM wParam, LPARAM lParam);//���Ǽ�Լ������Ϣ
	LRESULT OnAnswerInfoCOM(WPARAM wParam, LPARAM lParam);//�˿�������Ϣ
	LRESULT OnAnswerInfoMOD(WPARAM wParam, LPARAM lParam);//��λ��ʱģʽ��Ϣ
	LRESULT OnAnswerInfoPOS(WPARAM wParam, LPARAM lParam);//��λ�����ٽ����Ϣ
	LRESULT OnAnswerInfoRAN(WPARAM wParam, LPARAM lParam);//α�ࡢ�ز�����������Ϣ
	LRESULT OnAnswerInfoREF(WPARAM wParam, LPARAM lParam);//ʱ�ղο���Ϣ
	LRESULT OnAnswerInfoGSV(WPARAM wParam, LPARAM lParam);//������Ϣ
	LRESULT OnAnswerInfoSTA(WPARAM wParam, LPARAM lParam);//�ն˹���״̬��Ϣ
	LRESULT OnAnswerInfoTIM(WPARAM wParam, LPARAM lParam);//��ʱ�����Ϣ
	LRESULT OnAnswerInfoXPV(WPARAM wParam, LPARAM lParam);//�ѿ������궨λ�����ٽ����Ϣ
	LRESULT OnAnswerInfoSRC(WPARAM wParam, LPARAM lParam);//ԭʼ����
	LRESULT OnAnswerInfoSNR(WPARAM wParam, LPARAM lParam);//ԭʼ����
	LRESULT OnAnswerInfoSKY(WPARAM wParam, LPARAM lParam);//ԭʼ����
	LRESULT OnAnswerInfoGBS(WPARAM wParam, LPARAM lParam);//���������
	LRESULT OnAnswerInfoFrame(WPARAM wParam, LPARAM lParam);//һ֡ԭʼ����
	LRESULT OnAnswerInfoPAO(WPARAM wParam, LPARAM lParam);	
	LRESULT OnAnswerInfoCHD(WPARAM wParam, LPARAM lParam);//�ŵ�������Ϣ	
};
