#pragma once
#pragma warning(disable:4251)

#ifdef HWA_LISTENER_EXPORTS
#define HWA_LISTENER_API __declspec(dllexport)
#else
#define HWA_LISTENER_API __declspec(dllimport)
#endif

#define MSG_USER_BASE								(WM_USER+1000)
#define MSG_ANSWER_INFORMATION_COD					(MSG_USER_BASE+0)//����ԭʼ��������
#define MSG_ANSWER_INFORMATION_EPH					(MSG_USER_BASE+1)//����������Ϣ
#define MSG_ANSWER_INFORMATION_ION					(MSG_USER_BASE+2)//���ǵ�������
#define MSG_ANSWER_INFORMATION_ALM					(MSG_USER_BASE+3)//����������Ϣ
#define MSG_ANSWER_INFORMATION_JAL					(MSG_USER_BASE+4)//���Ǽ�Լ������Ϣ
#define MSG_ANSWER_INFORMATION_COM					(MSG_USER_BASE+5)//�˿�������Ϣ
#define MSG_ANSWER_INFORMATION_MOD					(MSG_USER_BASE+6)//��λ��ʱģʽ��Ϣ
#define MSG_ANSWER_INFORMATION_POS					(MSG_USER_BASE+7)//��λ�����ٽ����Ϣ
#define MSG_ANSWER_INFORMATION_RAN					(MSG_USER_BASE+8)//α�ࡢ�ز�����������Ϣ
#define MSG_ANSWER_INFORMATION_REF					(MSG_USER_BASE+9)//ʱ�ղο���Ϣ
#define MSG_ANSWER_INFORMATION_SIV					(MSG_USER_BASE+10)//������Ϣ
#define MSG_ANSWER_INFORMATION_STA					(MSG_USER_BASE+11)//�ն˹���״̬��Ϣ
#define MSG_ANSWER_INFORMATION_TIM					(MSG_USER_BASE+12)//��ʱ�����Ϣ
#define MSG_ANSWER_INFORMATION_XPV					(MSG_USER_BASE+13)//�ѿ������궨λ�����ٽ����Ϣ
#define MSG_ANSWER_INFORMATION_SRC					(MSG_USER_BASE+14)//ԭʼ����
#define MSG_ANSWER_INFORMATION_SNR					(MSG_USER_BASE+15)//�ź�ǿ��
#define MSG_ANSWER_INFORMATION_SKY					(MSG_USER_BASE+16)//�ǿ�ͼ
#define MSG_ANSWER_INFORMATION_GBS					(MSG_USER_BASE+17)//���������
#define MSG_ANSWER_INFORMATION_FRAME				(MSG_USER_BASE+18)//
#define MSG_ANSWER_INFORMATION_SIM					(MSG_USER_BASE+30)//SIM����Ϣ
#define MSG_ANSWER_INFORMATION_VER					(MSG_USER_BASE+31)//�汾����Ϣ
#define MSG_ANSWER_INFORMATION_TEST					(MSG_USER_BASE+32)
#define MSG_ANSWER_INFORMATION_CHD					(MSG_USER_BASE+33)//�ŵ�������Ϣ
//��λ����λ����
#define MSG_ANSWER_POSITION_MOD					(MSG_USER_BASE+100)//���ö�λģʽ
#define MSG_ANSWER_POSITION_EPH					(MSG_USER_BASE+101)//����������Ϣ
#define MSG_ANSWER_POSITION_ION					(MSG_USER_BASE+102)//���ǵ�������
#define MSG_ANSWER_POSITION_ALM					(MSG_USER_BASE+103)//����������Ϣ
#define MSG_ANSWER_POSITION_JAL					(MSG_USER_BASE+104)//���Ǽ�Լ������Ϣ
#define MSG_ANSWER_POSITION_POS					(MSG_USER_BASE+105)//�ѿ������궨λ�����ٽ����Ϣ
#define MSG_ANSWER_POSITION_RAN					(MSG_USER_BASE+106)//α�ࡢ�ز�����������Ϣ

//GGA��λ��Ϣ
#define MSG_SHOW_GGA_POS_INFO					(MSG_USER_BASE+107)//GGA 

//ģ����
#define MSG_EMULATOR_SETUP_BDI					(MSG_USER_BASE+200)//
#define MSG_EMULATOR_SETUP_REF					(MSG_USER_BASE+201)//
#define MSG_EMULATOR_SETUP_MOD					(MSG_USER_BASE+202)//���ö�λģʽ
#define MSG_EMULATOR_SETUP_COM					(MSG_USER_BASE+203)//
#define MSG_EMULATOR_SETUP_LOG					(MSG_USER_BASE+204)//
#define MSG_EMULATOR_SETUP_TIM					(MSG_USER_BASE+205)//
#define MSG_EMULATOR_SETUP_POS					(MSG_USER_BASE+206)//
#define MSG_EMULATOR_SETUP_CHA					(MSG_USER_BASE+207)//
#define MSG_EMULATOR_SETUP_WID					(MSG_USER_BASE+208)//
#define MSG_EMULATOR_SETUP_MUT					(MSG_USER_BASE+209)//
#define MSG_EMULATOR_SETUP_EAC					(MSG_USER_BASE+210)//
#define MSG_EMULATOR_SETUP_BGT					(MSG_USER_BASE+211)//
#define MSG_EMULATOR_SETUP_TTF					(MSG_USER_BASE+212)//
#define MSG_EMULATOR_SETUP_STA					(MSG_USER_BASE+213)//
#define MSG_EMULATOR_SETUP_STS					(MSG_USER_BASE+214)//
#define MSG_EMULATOR_SETUP_EVA					(MSG_USER_BASE+215)//

//�̱�������view��ʾ
#define MSG_SHOW_CMD_VIEW					(MSG_USER_BASE+300)//CMD INFO


class HWA_LISTENER_API CBasicListener
{
protected:
	CBasicListener(){}
	virtual ~CBasicListener(){}
public:
	virtual LRESULT OnAnswerInfoCOD(WPARAM wParam, LPARAM lParam){return true; }//����ԭʼ��������
	virtual LRESULT OnAnswerInfoEPH(WPARAM wParam, LPARAM lParam){return true; }//����������Ϣ
	virtual LRESULT OnAnswerInfoION(WPARAM wParam, LPARAM lParam){return true; }//���ǵ�������
	virtual LRESULT OnAnswerInfoALM(WPARAM wParam, LPARAM lParam){return true; }//����������Ϣ
	virtual LRESULT OnAnswerInfoJAL(WPARAM wParam, LPARAM lParam){return true; }//���Ǽ�Լ������Ϣ
	virtual LRESULT OnAnswerInfoCOM(WPARAM wParam, LPARAM lParam){return true; }//�˿�������Ϣ
	virtual LRESULT OnAnswerInfoMOD(WPARAM wParam, LPARAM lParam){return true; }//��λ��ʱģʽ��Ϣ
	virtual LRESULT OnAnswerInfoPOS(WPARAM wParam, LPARAM lParam){return true; }//��λ�����ٽ����Ϣ
	virtual LRESULT OnAnswerInfoRAN(WPARAM wParam, LPARAM lParam){return true; }//α�ࡢ�ز�����������Ϣ
	virtual LRESULT OnAnswerInfoREF(WPARAM wParam, LPARAM lParam){return true; }//ʱ�ղο���Ϣ
	virtual LRESULT OnAnswerInfoGSV(WPARAM wParam, LPARAM lParam){return true; }//������Ϣ	
	virtual LRESULT OnAnswerInfoSTA(WPARAM wParam, LPARAM lParam){return true; }//�ն˹���״̬��Ϣ
	virtual LRESULT OnAnswerInfoTIM(WPARAM wParam, LPARAM lParam){return true; }//��ʱ�����Ϣ
	virtual LRESULT OnAnswerInfoXPV(WPARAM wParam, LPARAM lParam){return true; }//�ѿ������궨λ�����ٽ����Ϣ
	virtual LRESULT OnAnswerInfoSRC(WPARAM wParam, LPARAM lParam){return true; }//ԭʼ����
	virtual LRESULT OnAnswerInfoSNR(WPARAM wParam, LPARAM lParam){return true; }//�ź�ǿ��
	virtual LRESULT OnAnswerInfoSKY(WPARAM wParam, LPARAM lParam){return true; }//�ǿ�ͼ
	virtual LRESULT OnAnswerInfoGBS(WPARAM wParam, LPARAM lParam){return true; }//���������
	virtual LRESULT OnAnswerInfoFrame(WPARAM wParam, LPARAM lParam){return true; }//һ֡ԭʼ����
	virtual LRESULT OnAnswerInfoSIM(WPARAM wParam, LPARAM lParam){return true; }//SIM����Ϣ
	virtual LRESULT OnAnswerInfoVER(WPARAM wParam, LPARAM lParam){return true; }//�汾����Ϣ
	virtual LRESULT OnAnswerInfoPAO(WPARAM wParam, LPARAM lParam){return true; }
	virtual LRESULT OnAnswerInfoCHD(WPARAM wParam, LPARAM lParam){return true; }//�ŵ�������Ϣ

	//��λ����
	virtual LRESULT OnAnswerCalPositionMOD(WPARAM wParam, LPARAM lParam){return true; }//���ö�λģʽ
	virtual LRESULT OnAnswerCalPositionPOS(WPARAM wParam, LPARAM lParam){return true; }//�ѿ������궨λ�����ٽ����Ϣ
	virtual LRESULT OnAnswerCalPositionEPH(WPARAM wParam, LPARAM lParam){return true; }//����������Ϣ
	virtual LRESULT OnAnswerCalPositionION(WPARAM wParam, LPARAM lParam){return true; }//���ǵ�������
	virtual LRESULT OnAnswerCalPositionALM(WPARAM wParam, LPARAM lParam){return true; }//����������Ϣ
	virtual LRESULT OnAnswerCalPositionJAL(WPARAM wParam, LPARAM lParam){return true; }//���Ǽ�Լ������Ϣ
	virtual LRESULT OnAnswerCalPositionRAN(WPARAM wParam, LPARAM lParam){return true; }//α�ࡢ�ز�����������Ϣ
	//ģ����
	virtual LRESULT OnEmulatorSetupMOD(WPARAM wParam, LPARAM lParam){return true; }//���ö�λģʽ
	virtual LRESULT OnEmulatorSetupLOG(WPARAM wParam, LPARAM lParam){return true; }//�������
	virtual LRESULT OnEmulatorSetupSTA(WPARAM wParam, LPARAM lParam){return true; }//���õ��Ʒ�ʽ
};
