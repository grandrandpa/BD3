#pragma once
#include "BasicListener.hpp"
#include "CompListener.hpp"

class HWA_LISTENER_API CHostListener : public CompListener<CBasicListener>
{
public:
	CHostListener(void);
	~CHostListener(void);
public:
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
	virtual LRESULT OnAnswerInfoSRC(WPARAM wParam, LPARAM lParam);//ԭʼ����
	virtual LRESULT OnAnswerInfoSNR(WPARAM wParam, LPARAM lParam);//ԭʼ����
	virtual LRESULT OnAnswerInfoSKY(WPARAM wParam, LPARAM lParam);//ԭʼ����
	virtual LRESULT OnAnswerInfoGBS(WPARAM wParam, LPARAM lParam);//���������
	virtual LRESULT OnAnswerInfoFrame(WPARAM wParam, LPARAM lParam);//һ֡ԭʼ����
	virtual LRESULT OnAnswerInfoSIM(WPARAM wParam, LPARAM lParam);//SIM����Ϣ
	virtual LRESULT OnAnswerInfoVER(WPARAM wParam, LPARAM lParam);//�汾����Ϣ
	virtual LRESULT OnAnswerInfoCHD(WPARAM wParam, LPARAM lParam);//�ŵ�������Ϣ
	virtual LRESULT OnAnswerInfoPAO(WPARAM wParam, LPARAM lParam);//����ҳ�沥��˳������鲥��˳��

	virtual LRESULT OnEmulatorSetupMOD(WPARAM wParam, LPARAM lParam);//���ö�λģʽ
	virtual LRESULT OnEmulatorSetupLOG(WPARAM wParam, LPARAM lParam);//�������
	virtual LRESULT OnEmulatorSetupSTA(WPARAM wParam, LPARAM lParam);//���õ��Ʒ�ʽ


    virtual LRESULT OnShowCmdView(WPARAM wParam, LPARAM lParam);//����EPQ
    virtual LRESULT OnUpdateGGAPOSView(WPARAM wParam, LPARAM lParam);//����GGA��POS��Ϣ

};
