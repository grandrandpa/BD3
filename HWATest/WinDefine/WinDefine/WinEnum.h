#pragma once
//////////////////////////////////////////////////////////////////////////
//Function: 枚举类型
//Auther: wu.xp
//Date: 2015.12.14
//////////////////////////////////////////////////////////////////////////

// 参考椭球参数类型
enum ENUM_ELLIPSE
{
	Ellipse_a,		// 参考椭球长半轴
	Ellipse_f,		// 参考椭球扁率倒数
	Ellipse_w,		// 参考椭球自转角速度
	Ellipse_gm		// 地球引力常数
}ENUM_ELLIPSE;


// BD2/GPS
enum BD2GpsSystem
{
	SYSTEM_BD1			= 0,
	SYSTEM_BD2			= 1,
	SYSTEM_GPS			= 2,
	SYSTEM_GLN			= 3,
	SYSTEM_BD2_GPS		= 4,
	SYSTEM_BD2_GLN	    = 5,
	SYSTEM_GPS_GLN		= 6,
	SYSTEM_BD2_GPS_GLN	= 7
};

typedef enum CONNECT_TYPE
{
	CONNECT_TYPE_NONE		= 0,
	CONNECT_TYPE_COM		= 1,
	CONNECT_TYPE_SOCKET		= 2,
	CONNECT_TYPE_COM_SOCKET = 4,
}CONNECT_TYPE;

typedef enum PROTOCOL_TYPE
{
	PROTOCOL_NONE	= 0,
	PROTOCOL_NMEA	= 1,
	PROTOCOL_BINARY = 2,
    PROTOCOL_BD3    = 3,
}PROTOCOL_TYPE;

typedef enum ENUM_FRAME
{
    SET_BDI = 2001,
	SET_REF = 2002,
	SET_MOD = 2003,
	SET_COM = 2004,
	SET_LOG = 2005,
	SET_TIM = 2006,
	SET_POS = 2007,
	SET_CHA = 2008,
	SET_WID = 2009,
	SET_MUT = 2010,
	SET_EAC = 2011,
	SET_BGT = 2012,
	SET_TTF = 2013,
	SET_STA = 2014,
	SET_STS = 2015,
	SET_EVA = 2016,
	SET_PRT = 2017,
	SET_TMD = 2018,
	SET_ACQ = 2019,
	SET_TRK = 2020,
	SET_ION = 2021,
	SET_ACQ_PILOT = 2022,
	SET_TRK_PILOT = 2023,
	SET_WORK = 2024,//add by cy 201580714
	SET_IST = 2025,//add by cy 201580715

	OUT_GNREF = 3401,
	OUT_GNMOD = 3402,
	OUT_GNCOM = 3403,
	OUT_GNRAN = 3404,
	OUT_GNPOS = 3415,
	OUT_GNXPV = 3416,
	OUT_GNTIM = 3417,
	OUT_GNSTA = 3418,
	OUT_GNGBS = 3419,

	OUT_BDEPH = 3005,
	OUT_BSEPH = 3006,
	OUT_BSALM = 3009,
	OUT_BSJAL = 3010,
	OUT_BDION = 3011,
	OUT_BSION = 3012,
	OUT_BDRAN = 3001,

	OUT_BDCHD = 3021,//add by 20180715
	OUT_BDPAO = 3022,
    OUT_BDGSA = 3030,
	OUT_BDGSV = 3031,
    OUT_BDGGA = 3032,
    OUT_BDGLL = 3034,
    OUT_BDRMC = 3035,

    //GSA,GGA,GSV,GLL,RMC,
    OUT_GPGSA = 3123,
    OUT_GPGGA = 3124,
    OUT_GPGSV = 3125,
    OUT_GPGLL = 3126,
    OUT_GPRMC = 3127,

    OUT_GLGSA = 3201,
    OUT_GLGGA = 3202,
    OUT_GLGSV = 3203,
    OUT_GLGLL = 3204,
    OUT_GLRMC = 3205,

    OUT_GAGSA = 3301,
    OUT_GAGGA = 3302,
    OUT_GAGSV = 3303,
    OUT_GAGLL = 3304,
    OUT_GARMC = 3305,

	OUT_BDALM = 3103,
	OUT_BDJAL = 3111,
	OUT_GNCOD = 3110,

    //response set
    RES_BDEPI = 4001,
    RES_BDTCI = 4002,
    RES_BDQRI = 4003,

	OUT_BDSIM = 8002,
	OUT_BDVER = 8003,

	SET_ACK	= 9001,


}ENUM_FRAME;

typedef enum ENUM_POSMOD
{
	MOD_NONE		= 0, //无
	MOD_B1I			= 1, //单频
	MOD_B1Q			= 2,  //单频
	MOD_B1C			= 3,  //单频
	MOD_B1A			= 4,  //单频
	MOD_B2a			= 5,  //单频
	MOD_B2b			= 6,  //单频
	MOD_B2			= 7,   //单频
	MOD_B3I			= 8,  //单频
	MOD_B3Q			= 9,  //单频
	MOD_B3C			= 10, //单频
	MOD_B3A			= 11, //单频
	MOD_Bs			= 12,  //单频
	MOD_B3AE		= 13,  //单频
	MOD_B1CB3C		= 21, //双频：B1C/B3C
	MOD_B1QB3Q		= 22, //双频：B1Q/B3Q
	MOD_B1AB3A		= 23, //双频：B1A/B3A
	MOD_BsB3A		= 24,  //双频：Bs/B3A
	MOD_B1CB2B3C	= 25,  //三频：B1C/B2/B3C
	MOD_B1CB2a		= 26, //双频：B1C/B2a
	MOD_B1AB3AE		= 27, //双频：B1AB3AE
	MOD_BsB3AE		= 28, //双频：Bs/B3AE
	MOD_USER		= 99  //用户自定义定位模式
}ENUM_POSMOD; //解算模式
typedef enum ENUM_USERPOS
{
	POS_LAT		= 0,
	POS_LON		= 1,
	POS_ALT		= 2,
	POS_X		= 3,
	POS_Y		= 4,
	POS_Z		= 5,
	POS_VX		= 6,
	POS_VY		= 7,
	POS_VZ		= 8,
	POS_PDOP	= 9,
}ENUM_USERPOS;
typedef enum ENUM_BRANCH
{
	CH_NONE			= 0,
	CH_B1I			= 1,
	CH_B1Q			= 2,
	CH_B1C			= 3,
	CH_B1A			= 4,
	CH_B1C_data		= 5,
	CH_B1C_pilot	= 6,
	CH_B1A_data		= 7,
	CH_B1A_pilot	= 8,
	CH_B2I			= 11,
	CH_B2Q			= 12,
	CH_B2a			= 13, //5
	CH_B2b			= 14, //6
	CH_B2			= 15,  //7
	CH_B2a_data		= 16,
	CH_B2a_pilot	= 17,
	CH_B2b_data		= 18,
	CH_B2b_pilot	= 19,
	CH_B3I			= 21, //8
	CH_B3Q			= 22, //9
	CH_B3C			= 23, //10
	CH_B3A			= 24, //11
	CH_B3AE			= 25,
	CH_B3C_data		= 26,
	CH_B3C_pilot	= 27,
	CH_B3A_data		= 28,
	CH_B3A_pilot	= 29,
	CH_Bs			= 31,   //12
	CH_Bs_data		= 32,
	CH_Bs_pilot		= 33,
	CH_B3AE_data	= 34,
	CH_B3AE_pilot	= 35,
	CH_L1C		= 41,
	CH_L5		= 42,
	CH_E5a		= 51,
	CH_E5b		= 52,
	CH_E5		= 53
}ENUM_BRANCH; //信号分量

typedef enum MODULATE_Type
{
	MODULATE_B3C_BPSK		= 0,
	MODULATE_B3C_BOC		= 1,
	MODULATE_B2a_TDAltBOC	= 2,
	MODULATE_B2a_AltBOC		= 3,
	MODULATE_B2b_TDAltBOC	= 4,
	MODULATE_B2b_AltBOC		= 5,
	MODULATE_B2_TDAltBOC	= 6,
	MODULATE_B2_AltBOC		= 7,
	MODULATE_B1A_TDDM		= 8,
	MODULATE_B1A_BOC		= 9,
	MODULATE_B3A_BPSK		= 10,
	MODULATE_B3AE_BPSK		= 11,
	MODULATE_Bs_BPSK		= 12,
	MODULATE_B1I_BPSK		= 13,
	MODULATE_B1Q_BPSK		= 14,
	MODULATE_B1C_TMBOC		= 15,
	MODULATE_B1C_BOC		= 16,
	MODULATE_B3I_BPSK		= 17,
	MODULATE_B3Q_BPSK		= 18,
}MODULATE_Type;

typedef enum TRACK_Type 
{
	TRACK_NONE		= 0,//
	TRACK_BPSK		= 1,//
	TRACK_BOC		= 2,//
	TRACK_BPSK_LIKE = 3,//
	TRACK_TMBOC_BOC = 4,//
	TRACK_TMBOC		= 5,//
	TRACK_ALTBOC	= 6,//
	TRACK_TD_ALTBOC = 7//
}TRACK_Type;

typedef enum ACQU_Type
{
	ACQU_NONE			= 0,//
	ACQU_BOC			= 1,//BOC捕获
	ACQU_BPSK			= 2,//BPSK捕获
	ACQU_BPSK_LIKE		= 3,//BPSK-Like捕获
	ACQU_NORMAL			= 4,//直接捕获
	ACQU_PILOT			= 5,//公开码引导捕获
	ACQU_POWER_PILOT	= 6,//功率增强引导捕获
}ACQU_Type;


//协议类型
enum cmd_type{
	none_cmd,
	nmea_cmd,
	hwa_cmd,
	novatel_cmd,
	rtcm_cmd,
};