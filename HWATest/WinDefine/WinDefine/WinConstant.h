#pragma once
//////////////////////////////////////////////////////////////////////////
//Function: �궨��
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
#define MAXCHANNELS 64//���Ǻ�
#define MAX_BUFFER 1024
#define BUFF_LEN   2048
//////////////////////////////////////////////////////

#define MAX_SVID   (64)  //���Ǻ�
#define MAX_CH     13	//ͨ��
#define LIGHT_SPEED    2.99792458e8
#define ENDIAN_BIG     FALSE //FALSE-��ʾС���ֽ�  TRUE-��ʾ����ֽ�

//////////////////////////////////////////////////////////////////////////////////////////////////
#define MAXSmoothEpoch 10 //������ƽ������

#define MAX_FREQ	   13
#define MAX_CHANNEL  (36)

#define MAX_SatNum    (18)
#define MAX_SatNum_TWO  (36)

#define SNRLIMIT  (26)  //���������
#define ELVLIMIT  (0.0872664625997) //��������

#define sin_5	(-0.087155742747658173558064270837474)	// sin(5��)
#define cos_5	(0.99619469809174553229501040247389)	// cos(5��)

//���Ӻ궨��
#define MAX_WEEK	7
#define MAX_YEAR	365
#define MAX_NONLEAP_DAY	28//ƽ��
#define MAX_LEAP_DAY	29//����

#define SECONDS_FOUR_YEAR 126230400
#define SECONDS_IN_YEAR 31536000
#define SECONDS_IN_WEEK 604800
#define SECONDS_HALF_WEEK 302400
#define SECONDS_IN_DAY 86400
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_MINUTE 60
////����Ƶ����ź�����Ƶ��
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


//���ݽ���
#define D_BUFFER            2*1024*1024		//��������buffer����
#define FILE_MAX			3*1024*1024
#define	NMEA_LENGTH			220			//NMEA���ݳ���
#define HWA_INPUT_LEN		100000		//�����Զ������ݵĳ���

#define HWA_RECIV_LEN		50000		//�Զ�����ճ���
#define NMEA_LENGHT         10000		//NMEA
#define	NOVATEL_LENGTH      20480			//NOVATEL���ݳ���
#define RTCM_MAX_LENTH		1024

#define TCQ_MAX_LEN         2000    //���1000��16bit����