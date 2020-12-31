#pragma once
//////////////////////////////////////////////////////////////////////////
//Function: 宏定义
//Auther: wu.xp
//Date: 2015.12.14
//////////////////////////////////////////////////////////////////////////

const int COD_LENGTH = 250;
const int MSG_LENGTH = 2050;

#define PI   (3.1415926535897932 )    //!< 180.0/PI
#define R2D   (57.295779513082320876798154814105)    //!< 180.0/PI
#define D2R   (0.017453292519943295769236907684886)  //!< PI/180.0

//////////////////////////////////////////
#define MAXMODE		22
#define MAXCHANNELS 64//卫星号
#define MAX_BUFFER 1024
#define BUFF_LEN   2048
//////////////////////////////////////////////////////

#define MAX_SVID   (64)  //卫星号
#define MAX_CH     13	//通道
#define LIGHT_SPEED    2.99792458e8
#define ENDIAN_BIG     FALSE //FALSE-表示小端字节  TRUE-表示大端字节

//////////////////////////////////////////////////////////////////////////////////////////////////
#define MAXSmoothEpoch 10 //多普勒平滑次数

#define MAX_FREQ	   13
#define MAX_CHANNEL  (36)

#define MAX_SatNum    (18)
#define MAX_SatNum_TWO  (36)

#define SNRLIMIT  (26)  //信噪比门限
#define ELVLIMIT  (0.0872664625997) //仰角门限

#define sin_5	(-0.087155742747658173558064270837474)	// sin(5度)
#define cos_5	(0.99619469809174553229501040247389)	// cos(5度)

//增加宏定义
#define MAX_WEEK	7
#define MAX_YEAR	365
#define MAX_NONLEAP_DAY	28//平月
#define MAX_LEAP_DAY	29//闰月

#define SECONDS_FOUR_YEAR 126230400
#define SECONDS_IN_YEAR 31536000
#define SECONDS_IN_WEEK 604800
#define SECONDS_HALF_WEEK 302400
#define SECONDS_IN_DAY 86400
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_MINUTE 60
////各个频点的信号中心频率
#define FREQ_B1I	1561.098
#define FREQ_B1Q	1561.098
#define FREQ_B1C	1575.420
#define FREQ_B1A	1575.420

#define FREQ_B2I	1176.450
#define FREQ_B2Q	1176.450

#define FREQ_B2a	1176.450
#define FREQ_B2b	1207.140
#define FREQ_B2		1176.450

#define FREQ_B3I	1268.520
#define FREQ_B3Q	1268.520
#define FREQ_B3C_BPSK	1278.750
#define FREQ_B3C_BOC	1268.520
#define FREQ_B3A	1268.520
#define FREQ_B3AE	1268.520

#define FREQ_Bs		2492.028


//数据解析
#define D_BUFFER            2*1024*1024		//接收数据buffer长度
#define FILE_MAX			3*1024*1024
#define	NMEA_LENGTH			220			//NMEA数据长度
#define HWA_INPUT_LEN		100000		//输入自定义数据的长度

#define HWA_RECIV_LEN		50000		//自定义接收长度
#define NMEA_LENGHT         10000		//NMEA
#define	NOVATEL_LENGTH      20480			//NOVATEL数据长度
#define RTCM_MAX_LENTH		1024

#define TCQ_MAX_LEN         2000    //最多1000个16bit汉字