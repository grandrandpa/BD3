#pragma once
#include "WinConstant.h"
#include "nmea.h"
//////////////////////////////////////////////////////////////////////////
//Function: 宏定义
//Auther: wu.xp
//Date: 2015.12.14
//////////////////////////////////////////////////////////////////////////
#define HEADER_LEN 8
typedef void (*DisposeFunc)(char* buf, int len); //回调函数
typedef struct DisposeFrame
{
	char			cFrame[HEADER_LEN];//帧头
	unsigned short	nFrame;//帧头
	DisposeFunc func;
}DisposeFrame;
typedef enum DisposeState
{
	RECV_CMD_START = 0,
	RECV_CMD_FRAME  = 1,
	RECV_CMD_DATA   = 2
}DisposeState;
//////////////////////////////////////////////////////////////////////////
typedef struct BD2_USER_BLH
{
	double lat;
	double lon;
	double alt;
	BD2_USER_BLH()
	{
		ZeroMemory(this, sizeof(BD2_USER_BLH));
	}
}BD2_USER_BLH;

typedef struct BD2_USER_XYZ 
{
	double x;
	double y;
	double z;
	BD2_USER_XYZ()
	{
		ZeroMemory(this, sizeof(BD2_USER_XYZ));
	}
}BD2_USER_XYZ;

typedef struct BD2_Ellipse
{
	double a;     //参考椭球半长轴a
	double f;     //参考椭球扁率倒数f
	double w;	  //参考椭球自转角速度w
	double gm;    //地球引力常数GM
	double dx;    //参考椭球中心坐标dx
	double dy;    //参考椭球中心坐标dy
	double dz;    //参考椭球中心坐标dz
	double alpha; //与X轴夹角Alpha
	double beta;  //与Y轴夹角Beta
	double gamma;  //与Z轴夹角Gamma
	BD2_Ellipse()
	{
		ZeroMemory(this, sizeof(BD2_Ellipse));
	}
}BD2_Ellipse;

typedef struct BD2_DOP
{
	double hdop;
	double vdop;
	double pdop;
	double tdop;
	double gdop;
	int	   valid;
	BD2_DOP()
	{
		ZeroMemory(this, sizeof(BD2_DOP));
	}
}BD2_DOP;
typedef struct tag_UTCTime //北斗授时结果信息
{
	int week;	//周计数
	double tow;	//周内秒
	int leap;	//闰秒

	int year;	//年
	int month;	//月
	int day;	//日
	int hour;	//时
	int minute;	//分
	double second;	//秒

	long MJD;	//儒略日

	bool flag;	//标识
}UTCTime;
/////////////////////////////数据解析/////////////////////////////////////////////
typedef struct BD2_SRC 
{
	int		type;
	int		length;
	char	Buffer[MSG_LENGTH];
	BD2_SRC()
	{
		ZeroMemory(this, sizeof(BD2_SRC));
	}
}BD2_SRC;
typedef struct BD2_TIME
{
	short week; //周计数
	double tow;//周内秒
	short posMod;//定位
	short timMod;//授时模式
	short num;//授时卫星数
	short year;
	short month;
	short day;
	short hour;
	short minute;
	short second;
	short Leap;//闰秒
	double   clkErr;
	char  svId[MAX_CHANNEL];//授时卫星
	bool flag;
	BD2_TIME()
	{
		ZeroMemory(this, sizeof(BD2_TIME));
	}
}BD2_TIME;
typedef struct BD2_GSV
{
    system_loc system_type;
	int		week;
	double	tow;
	int		num;
	int		branch;
	int		id[MAXCHANNELS];
	int		idErr[MAXCHANNELS];//错误卫星标记
	double	snr[MAXCHANNELS];
	double	elv[MAXCHANNELS];
	double	azi[MAXCHANNELS];
	bool	flag;
	BD2_GSV()
	{
		ZeroMemory(this, sizeof(BD2_GSV));
	}
}BD2_GSV;

typedef struct BD2_POS
{
	int				week;
	double			tow;
	int				mode;
	int				num;
	int				numuse;
	BD2_USER_BLH	blh;
	BD2_USER_XYZ	xyz;
	BD2_USER_XYZ	speed;
	double			clock;
	BD2_DOP			dop;
	UINT8			Ids[MAXCHANNELS];
	bool			flag;
	BD2_POS()
	{
		ZeroMemory(this, sizeof(BD2_POS));
	}
}BD2_POS;

typedef struct BD2_STA //终端工作状态信息 
{
	int		week;
	double	tow;
	int		number;
	int		cpu;
	int		soft;
	int		clock;
	int		pps;
	bool	flag;
	BD2_STA()
	{
		ZeroMemory(this, sizeof(BD2_STA));
	}
}BD2_STA;

typedef struct BD2_RAN
{
	int				week;
	double			tow;
	int				num;
	int				numuse;
	int				branch;
	int				svId[MAXCHANNELS];
	BD2_USER_XYZ	ran[MAXCHANNELS];
			//add by cy 20180714
	double			daltapseudos[MAXCHANNELS];//伪距历元差
	double			deltacarriers[MAXCHANNELS];//载波相位历元差
	//
	double			snr[MAXCHANNELS];

	unsigned long	status1[MAXCHANNELS];
	unsigned long	status2[MAXCHANNELS];

	bool			flag;
	int				system;

	BD2_RAN()
	{
		ZeroMemory(this, sizeof(BD2_RAN));
	}
}BD2_RAN;

typedef  struct BD2_EPH//二代二期卫星广播星历信息  --------
{
	int		week;
	double	tow;
	int		id;
	int		branch;
	int		iode;
	double	toe;
	double	deltaA; 
	double	sqrta;
	double	Adot;
	double	deltaN;
	double	Ndot;
	double	m0;
	double	e;
	double	w;
	double	omega0;
	double	i0;
	double	omegadot;
	double	idot;
	double	cis;
	double	cic;
	double	crs;
	double	crc;
	double	cus;
	double	cuc;
	int		iodc;
	double	toc;
	double	af0;
	double	af1;
	double	af2;
	double	tgd1;
	double	tgd2;
	double	tgd3;

	unsigned short	ura;
	unsigned short	health;
	char			system; 
	bool			flag;
	BD2_EPH()
	{
		ZeroMemory(this, sizeof(BD2_EPH));
	}
}BD2_EPH;

typedef struct BD2_ION //电离层模型参数信息 
{
	int    week;
	double tow;
	int    id;
	int    branch;
	double A1;
	double B;
	double alpha0;
	double alpha1;
	double alpha2;
	double alpha3;
	double beta0;
	double beta1;
	double beta2;
	double beta3;
	double gamma0;
	double gamma1;
	double gamma2;
	double gamma3;

	double af1;
	double af2;
	double af3;
	double af4;
	double af5;
	double af6;
	double af7;
	double af8;
	double af9;
	char	system; 
	bool   flag;
	BD2_ION()
	{
		ZeroMemory(this, sizeof(BD2_ION));
	}
}BD2_ION;

typedef struct BD2_ALM  //卫星历书信息 
{
	int    id;
	int    branch;
	int    week;
	int    health;
	int    toa;
	double e;
	double sigma;
	double sqrta;
	double omega0;
	double omegadot;
	double w;
	double m0;
	double af0;
	double af1;
	char	system; 
	bool   flag;
	BD2_ALM()
	{
		ZeroMemory(this, sizeof(BD2_ALM));
	}
}BD2_ALM;

typedef struct BD2_JAL 
{
	int				id;
	int				branch;
	//unsigned long	sigma; 
	long			sigma;//20180715
	double			omega;
	double			theta;
	double			health;
	char			system; 
	bool			flag;
	BD2_JAL()
	{
		ZeroMemory(this, sizeof(BD2_JAL));
	}
}BD2_JAL;

typedef struct BD2_COD
{
	int week;
	double tow;
	unsigned char	id;
	unsigned char	branch;
	unsigned char	prm;
	unsigned int	len;
	unsigned char	CodBuf[COD_LENGTH];
	char			system; 
	bool			flag;
	BD2_COD()
	{
		ZeroMemory(this, sizeof(BD2_COD));
	}
}BD2_COD;

typedef struct BD2_GBS
{
	int week;
	double tow;
	double latErr;
	double lonErr;
	double altErr;
	int    idErr;
	double checkErr;
	double evaluateErr;
	double offset;
	BD2_GBS()
	{
		ZeroMemory(this, sizeof(BD2_GBS));
	}
}BD2_GBS;
typedef struct BD2_SIM 
{
	unsigned char	branch;
	unsigned char 	prmFlag;//PRM有效期
	unsigned short  prmWeek0;//起始有效期
	unsigned short  prmWeek1;//截止有效期

	unsigned char 	mpdFlag;//MPD007密钥有效期
	unsigned short  mpdWeek0;//起始有效期
	unsigned short  mpdWeek1;//截止有效期
	BD2_SIM()
	{
		ZeroMemory(this, sizeof(BD2_SIM));
	}
}BD2_SIM;

//add by cy 20180714

typedef struct BD2_CHD 
{
	//unsigned short flag;//信息更新标志，为1时表示有更新
	unsigned short week;//周计数
	unsigned int tow;//周内秒计数
	unsigned char branch;//信号分量
	unsigned char svID;//卫星号
	unsigned char NavType;//电文类型0:B-CNAV1,1:B-CNAV2,2:B-CNAV3,3:B-ANAV,4:B-CINAV,5:B-AINAV
	unsigned char SubfameIdorMessType;//子帧号或页面类型
	unsigned char Decodeinfo;
//信道编码方式bit7~5、0:LDPC64(96,48),1:LDPC64(88,44),2:LDPC64(200,100),3:LDPC64(162,81),4:TURBO(600,300)
//译码是否通过bit4 0:不通过 1： 通过
//误码个数：bit3~0

	BD2_CHD()
	{
		ZeroMemory(this, sizeof(BD2_CHD));
	}
}BD2_CHD;

typedef struct BD2_PAORDER 
{
//	unsigned short flag;//更新标志，1有效
	//以下为显示项
	unsigned char sv;//卫星号
	unsigned char branch;//信号分量
	//标志
	//unsigned char pageupdate;//电文更新标志1：有更新
	//unsigned char almupdate;//历书更新标志1:有效
	//unsigned char briefalmupdate;//简约历书更新标志 1:有效
	//以下为显示项，在上面对应标志有效时更新相应的内容显示
	unsigned char pageid; //电文页面
	unsigned char almid;//历书卫星号
	unsigned int briefalmid;//简约历书卫星号 每8bit表示1颗星，因此显示4个简约历书卫星号

	BD2_PAORDER()
	{
		ZeroMemory(this, sizeof(BD2_PAORDER));
	}
}BD2_PAORDER;

//
typedef struct CPUVER 
{
	unsigned char  ver[4];//1.0.0.1
	unsigned short year;
	unsigned char  month;
	unsigned char  day;
	unsigned char  hour;
	unsigned char  minute;
	unsigned char  second;
}CPUVER;
typedef struct BD2_VER 
{
	unsigned char type; //0：母版 1：B1 2：B2 3：B3 4：Bs
	CPUVER			dsp;
	CPUVER			fpga;
}BD2_VER;

typedef struct BD3_GGA_POS
{
	int     hour;	//时
	int     minute;	//分
	double  second;	//秒

	int				mode;
	int				num;
	int				numuse;
	BD2_USER_BLH	blh;
	BD2_USER_XYZ	xyz;
	BD2_USER_XYZ	speed;
	BD2_DOP			dop;


	BD3_GGA_POS()
	{
		ZeroMemory(this, sizeof(BD3_GGA_POS));
	}
}BD3_GGA_POS;


typedef struct _Radar_Input
{
	double elev; //仰角
	double az;
	char systm[8];
	char prn[3];
	BOOL soln;

} Radar_Input;

typedef struct _Bar_Input
{
	char  prn[3];			//卫星PRN
	char  freq_num[12]; 	//频点号
	int cn0; 		 	   //CN0
	BOOL state;			 	   //定位状态
} Bar_Input;

/*****************************参数设置***********************************************************/
typedef struct SETSOCKET
{
	DWORD	dwIP;
	int		port;
	int     protocol;
}SETSOCKET;
typedef struct SETCOM 
{
	int  com;
	int  baud;
	int  protocol;
	SETCOM()
	{
		ZeroMemory(this, sizeof(SETCOM));
	}
}SETCOM;
typedef struct SETPOS //设置位置
{
	int			type;//坐标类型
	BD2_USER_XYZ  xyz;//坐标
	bool		bTime; //授时
	SETPOS()
	{
		type  = 0;
		bTime = false;
		ZeroMemory(&xyz, sizeof(BD2_USER_XYZ));
	}
}SETPOS;
typedef struct SETTMD 
{
	char mode;
	char svId;
	char branch;
	char flag;
	double lat;
	double lon;
	double alt;
	SETTMD()
	{
		mode = 0;
		svId = 0;
		branch = 0;
		flag = 0;
		lat = 0;
		lon = 0;
		alt = 0;
	}
}SETTMD;
typedef struct SETTIM //设置线缆时延
{
	double delay; //时延
	double zeroVal;//零值
	SETTIM()
	{
		delay   = 0;
		zeroVal = 0;
	}
}SETTIM;
typedef struct SETCHA //设置通道
{
	int id; //卫星号
	int branch;//信号分量
	int pilot; //导频标志
	int chId; //通道号
	SETCHA()
	{
		id     = 0;
		branch = 0;
		pilot  = 0;
		chId   = 0;
	}
}SETCHA;
typedef struct SETWID //设置带宽
{
	int id; //卫星号
	int branch;//信号分量
	int width; //带宽
	SETWID()
	{
		id     = 0;
		branch = 0;
		width  = 0;
	}
}SETWID;
typedef struct SETLOG //控制输出
{
	int   port;  //端口号
	int   type;  //数据类型
	char  frame[5];//数据类型
	int   freq;  //输出频率
	SETLOG()
	{
		port = 0;
		type = 0;
		freq = 0;
		ZeroMemory(frame, sizeof(frame));
	}
}SETLOG;
typedef struct SETMOD //控制输出
{
	unsigned short BD2Pos;  //试验卫星定位模式
	unsigned short BD1Pos;  //一期卫星定位模式
	unsigned char  GPSPos;	//GPS
	unsigned char  GaliPos; //Galileo
	unsigned char  ComPos;  //互操作
	unsigned short BD2Time; //试验卫星授时模式
	unsigned short BD1Time; //一期卫星授时模式
	unsigned char  GPSTime;	//GPS
	unsigned char  GaliTime; //Galileo
	SETMOD()
	{
		BD1Time = 0;
		BD1Pos  = 0;
		BD2Time = 0;
		BD2Pos  = 0;
		GPSPos = 0;
		GPSTime  = 0;
		GaliPos = 0;
		GaliTime  = 0;
		ComPos  = 0;
	}
}SETMOD;




typedef struct SETREF
{
	int timeSys;
	int timeFmt;
	int posSys;
	int posFmt;
	BD2_Ellipse  ellipse;
	SETCOM   com;
	SETREF()
	{
		timeSys = 0;
		timeFmt = 0;
		posSys  = 0;
		posFmt  = 0;
		ZeroMemory(&com, sizeof(SETCOM));
		ZeroMemory(&ellipse, sizeof(BD2_Ellipse));
	}
}SETREF;
typedef struct SETSIV
{
	int num;
	int id[MAXCHANNELS];
	int branch[MAXCHANNELS];
}SETSIV;

typedef struct SETMUT 
{
	unsigned char branch;
	unsigned char mutiPath;
}SETMUT;

typedef struct SETEAC 
{
	unsigned char id;
	unsigned char pilotId;
	unsigned char pilotBranch;
}SETEAC;

typedef struct SETBGT 
{
	unsigned char	id;
	unsigned short	wn;
	unsigned int	t0;
	double			a0;
	double			a1;
	double			a2;
}SETBGT;

typedef struct SETTTF 
{
	unsigned char mod;
}SETTTF;

typedef struct SETSTA 
{
	unsigned char mod;
}SETSTA;

typedef struct SETSTS 
{
	unsigned char b1;
	unsigned char b2;
	unsigned char b3;
}SETSTS;

typedef struct SETEVA 
{
	unsigned short elv;
}SETEVA;

typedef struct SETACQ 
{
	unsigned char branch;
	unsigned char mode;
}SETACQ;

typedef struct SETTRK 
{
	unsigned char branch;
	unsigned char mode;
}SETTRK;

typedef struct SETION 
{
	unsigned char ionFlag;//电离层修正
	unsigned char troFlag;//对流层修正
	unsigned char altFlag;//高程异常
}SETION;

typedef struct SETPILOT 
{
	unsigned short ID;//0:数据 1:导频
	unsigned char branch;
	unsigned char mode;
}SETPILOT;

typedef struct SETACK //查询
{
	unsigned short ID;//帧号
}SETACK;

typedef struct WORKMOD //工作模式
{
	unsigned char mode ; //工作模式
	unsigned char svstart ;//起始卫星号 
	unsigned char svend ;//结束卫星号

}WORKMOD;

typedef struct SETIST //入站信号发射
{
	unsigned char fp ; //频点选择	

}SETIST;


typedef struct SETEPQ
{
	int CardId;
	int Model;
	int Freq;
    int Speed;
    int UrgFlag;
    double ElevValue;
    int SOSType;
    int Times;
}SETEPQ;

typedef struct SETTCQ
{
	int CardId;
	int Freq;
    int Confirm;
    int CodeType;
    char Data[TCQ_MAX_LEN];
    int Times;

    SETTCQ()
	{
		ZeroMemory(Data, sizeof(Data));
    }
}SETTCQ;

typedef struct SETQRQ
{
	int CardId;
	int Type;
}SETQRQ;


typedef struct BD3_EPI
{
	unsigned char CardId[7];
    char FreqPoint[5];
    int Urg;
    int RepMode;
    char UTC[12];
	char Longitude[12];//		//经度
	char E_W;					//标志
    char Latitude[12];//		//纬度
	char N_S;					//
    double Elevation;           //高程
    char ElevUnit[3];
    double ElevWarn;        //高程异常
    char ElevWarnUnit[3];
    int PrecisionIndi;      //精度指示
    int MulValueSol;    //多值解
    int SoSChildType;
    int SoSIndicateType;    //sos 指示类型
    

 //   D3_EPI()
	//{
	//	ZeroMemory(this, sizeof(BD3_EPI));
	//}
}BD3_EPI;

typedef struct BD3_TCI
{
	unsigned char CardId[7];
    char FreqPoint[5];
    char UTC[12];
    int CodeType;
    char Data[TCQ_MAX_LEN];
    
	//BD3_TCI()
	//{
	//	ZeroMemory(this, sizeof(BD3_TCI));
	//}
}BD3_TCI;

typedef struct BD3_QRI
{
	unsigned char CardId[7];
    int Type;
    int ReturnNum;
    char UTC1[12];
    char UTC2[12];
    char UTC3[12];
    char UTC4[12];
    char UTC5[12];
    char UTC6[12];
    char UTC7[12];

 //   BD3_QRI()
	//{
	//	ZeroMemory(this, sizeof(BD3_QRI));
	//}
}BD3_QRI;
