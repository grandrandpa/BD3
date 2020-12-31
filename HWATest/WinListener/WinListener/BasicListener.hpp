#pragma once
#pragma warning(disable:4251)

#ifdef HWA_LISTENER_EXPORTS
#define HWA_LISTENER_API __declspec(dllexport)
#else
#define HWA_LISTENER_API __declspec(dllimport)
#endif

#define MSG_USER_BASE								(WM_USER+1000)
#define MSG_ANSWER_INFORMATION_COD					(MSG_USER_BASE+0)//卫星原始导航电文
#define MSG_ANSWER_INFORMATION_EPH					(MSG_USER_BASE+1)//卫星星历信息
#define MSG_ANSWER_INFORMATION_ION					(MSG_USER_BASE+2)//卫星电离层参数
#define MSG_ANSWER_INFORMATION_ALM					(MSG_USER_BASE+3)//卫星历书信息
#define MSG_ANSWER_INFORMATION_JAL					(MSG_USER_BASE+4)//卫星简约历书信息
#define MSG_ANSWER_INFORMATION_COM					(MSG_USER_BASE+5)//端口速率信息
#define MSG_ANSWER_INFORMATION_MOD					(MSG_USER_BASE+6)//定位授时模式信息
#define MSG_ANSWER_INFORMATION_POS					(MSG_USER_BASE+7)//定位、测速结果信息
#define MSG_ANSWER_INFORMATION_RAN					(MSG_USER_BASE+8)//伪距、载波、多普勒信息
#define MSG_ANSWER_INFORMATION_REF					(MSG_USER_BASE+9)//时空参考信息
#define MSG_ANSWER_INFORMATION_SIV					(MSG_USER_BASE+10)//卫星信息
#define MSG_ANSWER_INFORMATION_STA					(MSG_USER_BASE+11)//终端工作状态信息
#define MSG_ANSWER_INFORMATION_TIM					(MSG_USER_BASE+12)//授时结果信息
#define MSG_ANSWER_INFORMATION_XPV					(MSG_USER_BASE+13)//笛卡尔坐标定位、测速结果信息
#define MSG_ANSWER_INFORMATION_SRC					(MSG_USER_BASE+14)//原始数据
#define MSG_ANSWER_INFORMATION_SNR					(MSG_USER_BASE+15)//信号强度
#define MSG_ANSWER_INFORMATION_SKY					(MSG_USER_BASE+16)//星空图
#define MSG_ANSWER_INFORMATION_GBS					(MSG_USER_BASE+17)//自主完好性
#define MSG_ANSWER_INFORMATION_FRAME				(MSG_USER_BASE+18)//
#define MSG_ANSWER_INFORMATION_SIM					(MSG_USER_BASE+30)//SIM卡信息
#define MSG_ANSWER_INFORMATION_VER					(MSG_USER_BASE+31)//版本卡信息
#define MSG_ANSWER_INFORMATION_TEST					(MSG_USER_BASE+32)
#define MSG_ANSWER_INFORMATION_CHD					(MSG_USER_BASE+33)//信道译码信息
//上位机定位计算
#define MSG_ANSWER_POSITION_MOD					(MSG_USER_BASE+100)//设置定位模式
#define MSG_ANSWER_POSITION_EPH					(MSG_USER_BASE+101)//卫星星历信息
#define MSG_ANSWER_POSITION_ION					(MSG_USER_BASE+102)//卫星电离层参数
#define MSG_ANSWER_POSITION_ALM					(MSG_USER_BASE+103)//卫星历书信息
#define MSG_ANSWER_POSITION_JAL					(MSG_USER_BASE+104)//卫星简约历书信息
#define MSG_ANSWER_POSITION_POS					(MSG_USER_BASE+105)//笛卡尔坐标定位、测速结果信息
#define MSG_ANSWER_POSITION_RAN					(MSG_USER_BASE+106)//伪距、载波、多普勒信息

//GGA定位信息
#define MSG_SHOW_GGA_POS_INFO					(MSG_USER_BASE+107)//GGA 

//模拟器
#define MSG_EMULATOR_SETUP_BDI					(MSG_USER_BASE+200)//
#define MSG_EMULATOR_SETUP_REF					(MSG_USER_BASE+201)//
#define MSG_EMULATOR_SETUP_MOD					(MSG_USER_BASE+202)//设置定位模式
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

//短报文设置view显示
#define MSG_SHOW_CMD_VIEW					(MSG_USER_BASE+300)//CMD INFO


class HWA_LISTENER_API CBasicListener
{
protected:
	CBasicListener(){}
	virtual ~CBasicListener(){}
public:
	virtual LRESULT OnAnswerInfoCOD(WPARAM wParam, LPARAM lParam){return true; }//卫星原始导航电文
	virtual LRESULT OnAnswerInfoEPH(WPARAM wParam, LPARAM lParam){return true; }//卫星星历信息
	virtual LRESULT OnAnswerInfoION(WPARAM wParam, LPARAM lParam){return true; }//卫星电离层参数
	virtual LRESULT OnAnswerInfoALM(WPARAM wParam, LPARAM lParam){return true; }//卫星历书信息
	virtual LRESULT OnAnswerInfoJAL(WPARAM wParam, LPARAM lParam){return true; }//卫星简约历书信息
	virtual LRESULT OnAnswerInfoCOM(WPARAM wParam, LPARAM lParam){return true; }//端口速率信息
	virtual LRESULT OnAnswerInfoMOD(WPARAM wParam, LPARAM lParam){return true; }//定位授时模式信息
	virtual LRESULT OnAnswerInfoPOS(WPARAM wParam, LPARAM lParam){return true; }//定位、测速结果信息
	virtual LRESULT OnAnswerInfoRAN(WPARAM wParam, LPARAM lParam){return true; }//伪距、载波、多普勒信息
	virtual LRESULT OnAnswerInfoREF(WPARAM wParam, LPARAM lParam){return true; }//时空参考信息
	virtual LRESULT OnAnswerInfoGSV(WPARAM wParam, LPARAM lParam){return true; }//卫星信息	
	virtual LRESULT OnAnswerInfoSTA(WPARAM wParam, LPARAM lParam){return true; }//终端工作状态信息
	virtual LRESULT OnAnswerInfoTIM(WPARAM wParam, LPARAM lParam){return true; }//授时结果信息
	virtual LRESULT OnAnswerInfoXPV(WPARAM wParam, LPARAM lParam){return true; }//笛卡尔坐标定位、测速结果信息
	virtual LRESULT OnAnswerInfoSRC(WPARAM wParam, LPARAM lParam){return true; }//原始数据
	virtual LRESULT OnAnswerInfoSNR(WPARAM wParam, LPARAM lParam){return true; }//信号强度
	virtual LRESULT OnAnswerInfoSKY(WPARAM wParam, LPARAM lParam){return true; }//星空图
	virtual LRESULT OnAnswerInfoGBS(WPARAM wParam, LPARAM lParam){return true; }//自主完好性
	virtual LRESULT OnAnswerInfoFrame(WPARAM wParam, LPARAM lParam){return true; }//一帧原始数据
	virtual LRESULT OnAnswerInfoSIM(WPARAM wParam, LPARAM lParam){return true; }//SIM卡信息
	virtual LRESULT OnAnswerInfoVER(WPARAM wParam, LPARAM lParam){return true; }//版本卡信息
	virtual LRESULT OnAnswerInfoPAO(WPARAM wParam, LPARAM lParam){return true; }
	virtual LRESULT OnAnswerInfoCHD(WPARAM wParam, LPARAM lParam){return true; }//信道译码信息

	//定位计算
	virtual LRESULT OnAnswerCalPositionMOD(WPARAM wParam, LPARAM lParam){return true; }//设置定位模式
	virtual LRESULT OnAnswerCalPositionPOS(WPARAM wParam, LPARAM lParam){return true; }//笛卡尔坐标定位、测速结果信息
	virtual LRESULT OnAnswerCalPositionEPH(WPARAM wParam, LPARAM lParam){return true; }//卫星星历信息
	virtual LRESULT OnAnswerCalPositionION(WPARAM wParam, LPARAM lParam){return true; }//卫星电离层参数
	virtual LRESULT OnAnswerCalPositionALM(WPARAM wParam, LPARAM lParam){return true; }//卫星历书信息
	virtual LRESULT OnAnswerCalPositionJAL(WPARAM wParam, LPARAM lParam){return true; }//卫星简约历书信息
	virtual LRESULT OnAnswerCalPositionRAN(WPARAM wParam, LPARAM lParam){return true; }//伪距、载波、多普勒信息
	//模拟器
	virtual LRESULT OnEmulatorSetupMOD(WPARAM wParam, LPARAM lParam){return true; }//设置定位模式
	virtual LRESULT OnEmulatorSetupLOG(WPARAM wParam, LPARAM lParam){return true; }//设置输出
	virtual LRESULT OnEmulatorSetupSTA(WPARAM wParam, LPARAM lParam){return true; }//设置调制方式
};
