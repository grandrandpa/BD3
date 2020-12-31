#pragma once
#include "BasicListener.hpp"
#include "CompListener.hpp"

class HWA_LISTENER_API CHostListener : public CompListener<CBasicListener>
{
public:
	CHostListener(void);
	~CHostListener(void);
public:
	virtual LRESULT OnAnswerInfoCOD(WPARAM wParam, LPARAM lParam);//卫星原始导航电文
	virtual LRESULT OnAnswerInfoEPH(WPARAM wParam, LPARAM lParam);//卫星星历信息
	virtual LRESULT OnAnswerInfoION(WPARAM wParam, LPARAM lParam);//卫星电离层参数
	virtual LRESULT OnAnswerInfoALM(WPARAM wParam, LPARAM lParam);//卫星历书信息
	virtual LRESULT OnAnswerInfoJAL(WPARAM wParam, LPARAM lParam);//卫星简约历书信息
	virtual LRESULT OnAnswerInfoCOM(WPARAM wParam, LPARAM lParam);//端口速率信息
	virtual LRESULT OnAnswerInfoMOD(WPARAM wParam, LPARAM lParam);//定位授时模式信息
	virtual LRESULT OnAnswerInfoPOS(WPARAM wParam, LPARAM lParam);//定位、测速结果信息
	virtual LRESULT OnAnswerInfoRAN(WPARAM wParam, LPARAM lParam);//伪距、载波、多普勒信息
	virtual LRESULT OnAnswerInfoREF(WPARAM wParam, LPARAM lParam);//时空参考信息
	virtual LRESULT OnAnswerInfoGSV(WPARAM wParam, LPARAM lParam);//卫星信息
	virtual LRESULT OnAnswerInfoSTA(WPARAM wParam, LPARAM lParam);//终端工作状态信息
	virtual LRESULT OnAnswerInfoTIM(WPARAM wParam, LPARAM lParam);//授时结果信息
	virtual LRESULT OnAnswerInfoXPV(WPARAM wParam, LPARAM lParam);//笛卡尔坐标定位、测速结果信息
	virtual LRESULT OnAnswerInfoSRC(WPARAM wParam, LPARAM lParam);//原始数据
	virtual LRESULT OnAnswerInfoSNR(WPARAM wParam, LPARAM lParam);//原始数据
	virtual LRESULT OnAnswerInfoSKY(WPARAM wParam, LPARAM lParam);//原始数据
	virtual LRESULT OnAnswerInfoGBS(WPARAM wParam, LPARAM lParam);//自主完好性
	virtual LRESULT OnAnswerInfoFrame(WPARAM wParam, LPARAM lParam);//一帧原始数据
	virtual LRESULT OnAnswerInfoSIM(WPARAM wParam, LPARAM lParam);//SIM卡信息
	virtual LRESULT OnAnswerInfoVER(WPARAM wParam, LPARAM lParam);//版本卡信息
	virtual LRESULT OnAnswerInfoCHD(WPARAM wParam, LPARAM lParam);//信道译码信息
	virtual LRESULT OnAnswerInfoPAO(WPARAM wParam, LPARAM lParam);//电文页面播发顺序和历书播发顺序

	virtual LRESULT OnEmulatorSetupMOD(WPARAM wParam, LPARAM lParam);//设置定位模式
	virtual LRESULT OnEmulatorSetupLOG(WPARAM wParam, LPARAM lParam);//设置输出
	virtual LRESULT OnEmulatorSetupSTA(WPARAM wParam, LPARAM lParam);//设置调制方式


    virtual LRESULT OnShowCmdView(WPARAM wParam, LPARAM lParam);//设置EPQ
    virtual LRESULT OnUpdateGGAPOSView(WPARAM wParam, LPARAM lParam);//更新GGA的POS信息

};
