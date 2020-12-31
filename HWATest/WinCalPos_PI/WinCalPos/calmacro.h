#pragma once

#define CGS2000_A			(6378137.0)        // 地球半长轴（米）
#define CGS2000_F			(1/298.257222101)		// 地球扁率的倒数
#define CGS2000_MIU			(3.986004418E+14)	// 地球引力常数，单位：米^3/秒^2
#define CGS2000_OMEGA_E		(7.2921150E-5)		// 地球自转速率，单位：弧度/秒

#define WGS84_A				(6378137.0)        // 地球半长轴（米）
#define WGS84_F				(1/298.257223563)		// 地球扁率的倒数
#define WGS84_MIU			(3.986005E+14)		// 地球引力常数，单位：米^3/秒^2
#define WGS84_OMEGA_E		(7.2921151467E-5)		// 地球自转速率，单位：弧度/秒


//---------------------------------------------------------------------
// 宏定义 
//---------------------------------------------------------------------
// 返回错误值定义
#define ERROR_POS_SUCCESS		1//定位
#define ERROR_MODE_FAIL			-1//定位模式错误
#define ERROR_EPH_LAGGER		-2//星历出错
#define ERROR_EPH_HEL			-3//星历不健康
#define ERROR_SAT_LESS			-4//卫星数少于4
#define ERROR_POS_INVALID		-5//定位解无效
#define ERROR_INIT_FAIL			-6//初始化错误
#define ERROR_RAN_FAIL			-7//测量数据错误
#define ERROR_MAT_SINGULAR		-8//A矩阵奇异
#define ERROR_ELV_LESS			-9//仰角太小



