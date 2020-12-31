#pragma once
#include "BasicListener.hpp"
#include "CompListener.hpp"

class HWA_LISTENER_API CCalPosListener : public CompListener<CBasicListener>
{
public:
	CCalPosListener(void);
	~CCalPosListener(void);
public:
	//��λ����
	virtual LRESULT OnAnswerCalPositionMOD(WPARAM wParam, LPARAM lParam);//���ö�λģʽ
	virtual LRESULT OnAnswerCalPositionPOS(WPARAM wParam, LPARAM lParam);//�ѿ������궨λ�����ٽ����Ϣ
	virtual LRESULT OnAnswerCalPositionEPH(WPARAM wParam, LPARAM lParam);//����������Ϣ
	virtual LRESULT OnAnswerCalPositionION(WPARAM wParam, LPARAM lParam);//���ǵ�������
	virtual LRESULT OnAnswerCalPositionALM(WPARAM wParam, LPARAM lParam);//����������Ϣ
	virtual LRESULT OnAnswerCalPositionJAL(WPARAM wParam, LPARAM lParam);//���Ǽ�Լ������Ϣ
	virtual LRESULT OnAnswerCalPositionRAN(WPARAM wParam, LPARAM lParam);//α�ࡢ�ز�����������Ϣ
};
