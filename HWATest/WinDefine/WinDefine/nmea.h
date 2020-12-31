

#pragma once

#define SATALLITE_NUM	12

enum nmea_type
{
	nmea_GPS,
	nmea_BD,
	nmea_GLONASS,
	nmea_GNSS,
};


/*typedef */struct nmea_GSA
{
	enum nmea_type system_type;

	char mode;				//手动|自动定位
	char location_tpye;		//no_fix|2D|3D
	char PRN[12][3];
	char PDOP[4];
	char HDOP[4];
	char VDOP[4];

	int PRN_count;
};//nmea_GSA;
extern struct nmea_GSA save_GSA;
//nmea_GSA *save_GSA;


struct nmea_GGA
{
	enum nmea_type system_type;

	char UTC[12];//				//1
	char Latitude[15];//		//2
	char N_S;					//3
	char Lontitude[15];//		//4
	char E_W;					//5
	char state;					//6
	char satellite_use[3];		//7
	char HDOP[4];				//8
	char Altitude[12];			//9天线大地高
    char AntennaHeightUnit;     //10天线大地高单位 M
    char AltitudeAbnormal[12];	//11高程异常
    char AltitudeAbnormalUnit;  //12高程异常单位 M
	char del_fentime[12];//		//13可为空
	char del_ID[4];				//14可为空
    char VDOP[4];               //15
};
extern struct nmea_GGA save_GGA;


struct satellite_in_view
{
	char PRN[4];				//4
	char yang_cour[3];		//5
	char fangwei_cour[4];	//6
	char CN0[3];					//7
};

struct nmea_GSV
{
	enum nmea_type system_type;

	char GSV_count;		//1
	char GSV_numb;		//2
	char satellite_view[3];	//3
	struct satellite_in_view satellite_info[20][4];		//4、5、6、7
};
extern struct nmea_GSV save_GSV;


struct nmea_GLL
{
	enum nmea_type system_type;

	char Latitude[12];//		//1
	char N_S;					//2
	char Lontitude[12];//		//3
	char E_W;					//4
	char UTC[12];//				//5
	char locat_state;			//6
	char mode_state;			//7
};
extern struct nmea_GLL save_GLL;


struct nmea_RMC
{
	enum nmea_type system_type;

	char UTC[12];				//1 hhmmss
	char locat_state;			//2
	char Latitude[12];//		//3
	char N_S;					//4
	char Lontitude[12];//		//5
	char E_W;					//6
	char speed[12];//			//7
	char direction[12];//		//8	//地面航向
	char UTC_date[7];			//9	ddmmyy
	char mag_cour[12];			//10
	char mag_direct;			//11	E|W
	char mode_state;			//12

};
extern struct nmea_RMC save_RMC;


enum system_loc
{
	NONE_LOC,
	GP,
	BD,
	GL,
	GN,
	HWACHIP,
    GA,
};

enum nmea_cmd
{
	NONE_CMD,
	GSA,
	GGA,
	GSV,
	GLL,
	RMC,
};

struct satellite_view_save
{	
	//system GSV
	int ID;		//01~32
	int CN0;	//00~99dB

	//satellite distribution	GSV
	int Y_cour;	//仰角y_cour
	int D_cour;	//方位角dire_cour
};

typedef struct{  
	int year;    
	int month;   
	int day;  
	int hour;  
	int minute;  
	float second;
}date_time;


struct _nmea_cmd
{
	struct nmea_GSA _save_GSA;
	struct nmea_GGA _save_GGA;
	struct nmea_GSV _save_GSV;
	struct nmea_GLL _save_GLL;
	struct nmea_RMC _save_RMC;
};


typedef struct nmea_char_data_save
{
	enum system_loc sys;
	enum nmea_cmd cmd;

	bool gn_gga;
	bool bd_gga;
	bool gl_gga;
    bool ga_gga;

	bool gn_gsv;
	bool gp_gga;
	bool gn_gsv1;
	bool gp_gga1;

	int gp_n;			//使用卫星数
	int bd_n;
	int gl_n;
    int ga_n;

	//GSV  data
    int				week;
	double			tow;
	char GP_view_count[3];		//GSV	00~12
	char GL_view_count[3];
	char BD_view_count[3];
    char GA_view_count[3];

	int GP_view_C;		//GSV	00~12
	int GL_view_C;
	int BD_view_C;
    int GA_view_C;

	char GSV_in_use[3];

	struct satellite_in_view GP_view[32];//12];
	struct satellite_in_view GL_view[32];//12];
	struct satellite_in_view BD_view[32];//12];
    struct satellite_in_view GA_view[32];//12];
	/********************************************/
	int GP_use;		//GGA	00~12
	int GL_use;
	int BD_use;
    int GA_use;
	int GN_use;

	char GP_in_use[3];		//GGA	00~12
	char GL_in_use[3];
    char GA_in_use[3];
	char BD_in_use[3];
	char GN_in_use[3];

	char Latitude[12];			//纬度	//保留到小数点后7位
	char Longitude[12];		//经度
	char Altitude[12];			//高度
    char N_S;
    char E_W;

	date_time UTC;			//时间 
	char utc_date[7];
	char utc_clk[10];

	char sat_num[3];       //使用卫星数
	//	int UTC;
	/********************************************/
	//GSA
	char PDOP[4];//12];		//暂时保留小数点后两位 
	char HDOP[4];//12];
	char VDOP[4];//12];

	char GP_PRN[12][3];
	char BD_PRN[12][3];
	char GL_PRN[12][3];
    char GA_PRN[12][3];
	/********************************************/

	//speed	RMC
	char fix_mode;	//有效定位|无定位
	char speed[12];	//速度
	//direction	RMC
	double direction;	//方位 000.0~359.9度
	/********************************************/
	//卫星参与定位的情况
	int GP_have[SATALLITE_NUM];//有
	int BD_have[SATALLITE_NUM];
	int GL_have[SATALLITE_NUM];
    int GA_have[SATALLITE_NUM];

	int GP_no[SATALLITE_NUM];//无
	int BD_no[SATALLITE_NUM];
	int GL_no[SATALLITE_NUM];
    int GA_no[SATALLITE_NUM];

	bool GP_SEQ[SATALLITE_NUM];//顺序排序
	bool BD_SEQ[SATALLITE_NUM];
	bool GL_SEQ[SATALLITE_NUM];
    bool GA_SEQ[SATALLITE_NUM];
}NmeaAllData;
extern struct nmea_char_data_save nmea_char_save;

