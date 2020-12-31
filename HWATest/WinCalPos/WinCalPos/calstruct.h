#pragma once
#ifdef HWA_POS_EXPORTS
#define HWA_POS_API __declspec(dllexport)
#else
#define HWA_POS_API __declspec(dllimport)
#endif


typedef struct tag_BD2_POS_SEL_SAT 
{
	UINT8 branch;
	UINT8 number;
	UINT8 selSat[MAXCHANNELS];
}BD2_POS_SEL_SAT;

typedef struct tag_BD2_UNION_POS_MODE
{
	UINT8 number;
	BD2_POS_SEL_SAT pos[30];
}BD2_UNION_POS_MODE;

typedef struct tag_BD2_NORMAL_POS_MODE
{
	UINT8 number;
	UINT8 posMod[30];
}BD2_NORMAL_POS_MODE;

// 北斗2UTC时结构体
typedef struct tag_BD2_UTC_DATE
{
	unsigned short vflg; 
	unsigned short dn; 
	unsigned short wnlsf;
	unsigned short Tot;
	unsigned short WNot;
	short  dtls;                              
	short  dtlsf;  
	double A0;
	double A1; 
	double A2;
}BD2_UTC_DATE;
//本地时间
typedef struct tag_BD2_DATE_TIME 
{
	unsigned short year;
	unsigned short month;
	unsigned short day;
	unsigned short hour;
	unsigned short minute;
	double second;
}BD2_DATE_TIME;
// 定位模式
typedef struct tag_BD2_POS_MODE
{
	// 模式参数
	BOOL	System;			// 定位系统
	BOOL	UseWaas;		// 是否使用差分
	BOOL    Use2D;          // 是否2D定位
	char	FreqUsed;		// 所用频点个数：1、2、3,4
	char	branch[3];		// 所使用的频点

	char	cPosMode;			// 解算模式
	char	cWeightType;		// 定权模式
} BD2_POS_MODE;
// 接收机的位置、速度、加速度、经纬度、时间偏差等，作为中间结果
// 也就是所谓的“历元”变量
typedef struct tag_BD2_PVT
{
	BD2_USER_BLH	blh;	// 经纬度和高程
	BD2_USER_XYZ	xyz;	// XYZ坐标
	BD2_USER_XYZ    speed;  // XYZ速度
	BD2_USER_XYZ	ENUV;	// 东北天速度
	BD2_DOP			Dop;	// 几何精度因子

	double			error;			// 定位计算的收敛误差
	UINT8			valid;			// 定位结果是否有效
	UINT8			velOK;			// 速度结果是否有效
	UINT8			nUsedSat;		// 定位解用到的卫星个数
	UINT8			UseSat[MAX_SatNum];//所用卫星的卫星号
} BD2_PVT;

typedef struct tag_BD2_OBSTIME
{
	unsigned short  year;		//年
	unsigned short  month;		//月
	unsigned short  day;		//日
	unsigned short  hour;		//时
	unsigned short  min;		//分
	double			second;		//秒

	int				DayOfYear;	//年积日
	unsigned short	dayofweek;	//周内天
	double			SecOfDay ;  //天秒

	unsigned int	Weeks;		//周数
	double			Tow;		//周内秒
	unsigned short  Leap;		//闰秒

	long			MJD;		//儒略日
}BD2_OBSTIME;
// 卫星在站心坐标系中的方位角和高度角结构定义
typedef struct tag_BD2_SAT_AZEL
{
	double azi;	// 方位角
	double elv;	// 高度角
} BD2_SAT_AZEL;

// 卫星位置计算结果结构
typedef struct tag_BD2_SAT_POS
{
	double x;	// 空间时间坐标
	double y;
	double z;
	double tsv;	// 卫星时间偏差，单位：米

	double	vx, vy, vz, dtsv;	// 速度分量和时间改正
	double  elv;//仰角
	double  azi;//方位角
} BD2_SAT_POS;

typedef struct tag_BD2_SAT_INFO
{
	UINT8			SatID;// 卫星编号
	UINT8			branch;
	double			Freq;		// 频点
	double			Pseudorang;	 // 伪距观测值
	double			CarrierPhase;//载波相位观测值
	double			Doppler;	 //多普勒频移
	double			Bias;
	double			Drift;
	double			SNR;	//载噪比
	BD2_SAT_POS		SatPos;	// 卫星位置
	BD2_SAT_AZEL	SatAzel;// 卫星仰角、方位角
} BD2_SAT_INFO;

typedef struct tag_BD2_EPOCH
{
	UINT8			SatNum;  //卫星数
	UINT8			NumUse; //可用卫星数
	UTCTime			utcTime;//UTC时间
	BD2_OBSTIME		obsTime; //观测时间
	BD2_POS_MODE	PosMode; //定位模式
	BD2_SAT_INFO	SatInfo[MAX_SatNum];//卫星信息
	BD2_PVT			initPVT;//初始化接收机位置信息
	BD2_PVT			calcPVT;//计算出的接收机坐标
	double			bias;	//钟差
	double			Drift;   //用户机本地振荡器偏差(钟差漂移)
	unsigned int	LockCn[21][64];// 保存故障卫星号
	unsigned int	Count[21];
}BD2_EPOCH;

typedef struct tag_BD2_LS_EPOCH
{
	double 		P[MAX_SatNum_TWO];			// 权阵
	double		A[MAX_SatNum_TWO*8];		// 设计矩阵A
	double		v[MAX_SatNum_TWO];			// 残差 v = A*x - l
	double		range_err[MAX_SatNum_TWO];	// 求解接收机坐标时平差中的伪距误差 : o - c
	double      range_errorRaim[MAX_SatNum_TWO];// 求解接收机坐标时平差中的伪距误差 : o - c
	double		del_L[MAX_SatNum_TWO];		// 求解接收机速度时平差中的 L，暂时不用！！！！！
	double		inv[64];					// N逆阵( N=AtA )
	double		U[18];						// U = At * l
	double		VtV;						// 残差平方和 VtV = v[i]*v[i]
	/***************************************************************************/
	UINT16		Dim;
	long long	RaimInd;
	UINT16		IDInd[MAX_SatNum_TWO];
	double 		Trai[MAX_SatNum_TWO];
} BD2_LS_EPOCH;

typedef struct tag_BD2_OUTPUTDATA
{
	bool			FPosOK;
	bool			FVelOK;
	unsigned int	Week;
	double			tow;
	unsigned short  PosMode; 
	unsigned short  SatNum;
	unsigned int    UseSat[MAX_SatNum];
	BD2_USER_XYZ   XYZ;
	BD2_USER_XYZ   BLH;
	BD2_USER_XYZ   Vel;
	BD2_DOP Dop;
}BD2_OUTPUTDATA;

//载波相位平滑伪距
typedef struct tag_CarrierPseudo 
{
	unsigned int smoothCount;			 //载波相位平滑次数
	double pseudoRange;			 //伪距
	double carrierPhase;		 //载波相位
	double doppler;				 //多普勒
	double smoothed_pseudoRange; //平滑后的伪距
}CarrierPseudo;	
