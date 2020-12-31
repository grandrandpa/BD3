#pragma once
#include "BasicListener.hpp"
#include "CompListener.hpp"

class HWA_LISTENER_API CCalPosListener : public CompListener<CBasicListener>
{
public:
	CCalPosListener(void);
	~CCalPosListener(void);
public:
	//定位计算
	virtual LRESULT OnAnswerCalPositionMOD(WPARAM wParam, LPARAM lParam);//设置定位模式
	virtual LRESULT OnAnswerCalPositionPOS(WPARAM wParam, LPARAM lParam);//笛卡尔坐标定位、测速结果信息
	virtual LRESULT OnAnswerCalPositionEPH(WPARAM wParam, LPARAM lParam);//卫星星历信息
	virtual LRESULT OnAnswerCalPositionION(WPARAM wParam, LPARAM lParam);//卫星电离层参数
	virtual LRESULT OnAnswerCalPositionALM(WPARAM wParam, LPARAM lParam);//卫星历书信息
	virtual LRESULT OnAnswerCalPositionJAL(WPARAM wParam, LPARAM lParam);//卫星简约历书信息
	virtual LRESULT OnAnswerCalPositionRAN(WPARAM wParam, LPARAM lParam);//伪距、载波、多普勒信息
};
