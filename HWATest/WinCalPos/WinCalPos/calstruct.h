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

// ����2UTCʱ�ṹ��
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
//����ʱ��
typedef struct tag_BD2_DATE_TIME 
{
	unsigned short year;
	unsigned short month;
	unsigned short day;
	unsigned short hour;
	unsigned short minute;
	double second;
}BD2_DATE_TIME;
// ��λģʽ
typedef struct tag_BD2_POS_MODE
{
	// ģʽ����
	BOOL	System;			// ��λϵͳ
	BOOL	UseWaas;		// �Ƿ�ʹ�ò��
	BOOL    Use2D;          // �Ƿ�2D��λ
	char	FreqUsed;		// ����Ƶ�������1��2��3,4
	char	branch[3];		// ��ʹ�õ�Ƶ��

	char	cPosMode;			// ����ģʽ
	char	cWeightType;		// ��Ȩģʽ
} BD2_POS_MODE;
// ���ջ���λ�á��ٶȡ����ٶȡ���γ�ȡ�ʱ��ƫ��ȣ���Ϊ�м���
// Ҳ������ν�ġ���Ԫ������
typedef struct tag_BD2_PVT
{
	BD2_USER_BLH	blh;	// ��γ�Ⱥ͸߳�
	BD2_USER_XYZ	xyz;	// XYZ����
	BD2_USER_XYZ    speed;  // XYZ�ٶ�
	BD2_USER_XYZ	ENUV;	// �������ٶ�
	BD2_DOP			Dop;	// ���ξ�������

	double			error;			// ��λ������������
	UINT8			valid;			// ��λ����Ƿ���Ч
	UINT8			velOK;			// �ٶȽ���Ƿ���Ч
	UINT8			nUsedSat;		// ��λ���õ������Ǹ���
	UINT8			UseSat[MAX_SatNum];//�������ǵ����Ǻ�
} BD2_PVT;

typedef struct tag_BD2_OBSTIME
{
	unsigned short  year;		//��
	unsigned short  month;		//��
	unsigned short  day;		//��
	unsigned short  hour;		//ʱ
	unsigned short  min;		//��
	double			second;		//��

	int				DayOfYear;	//�����
	unsigned short	dayofweek;	//������
	double			SecOfDay ;  //����

	unsigned int	Weeks;		//����
	double			Tow;		//������
	unsigned short  Leap;		//����

	long			MJD;		//������
}BD2_OBSTIME;
// ������վ������ϵ�еķ�λ�Ǻ͸߶Ƚǽṹ����
typedef struct tag_BD2_SAT_AZEL
{
	double azi;	// ��λ��
	double elv;	// �߶Ƚ�
} BD2_SAT_AZEL;

// ����λ�ü������ṹ
typedef struct tag_BD2_SAT_POS
{
	double x;	// �ռ�ʱ������
	double y;
	double z;
	double tsv;	// ����ʱ��ƫ���λ����

	double	vx, vy, vz, dtsv;	// �ٶȷ�����ʱ�����
	double  elv;//����
	double  azi;//��λ��
} BD2_SAT_POS;

typedef struct tag_BD2_SAT_INFO
{
	UINT8			SatID;// ���Ǳ��
	UINT8			branch;
	double			Freq;		// Ƶ��
	double			Pseudorang;	 // α��۲�ֵ
	double			CarrierPhase;//�ز���λ�۲�ֵ
	double			Doppler;	 //������Ƶ��
	double			Bias;
	double			Drift;
	double			SNR;	//�����
	BD2_SAT_POS		SatPos;	// ����λ��
	BD2_SAT_AZEL	SatAzel;// �������ǡ���λ��
} BD2_SAT_INFO;

typedef struct tag_BD2_EPOCH
{
	UINT8			SatNum;  //������
	UINT8			NumUse; //����������
	UTCTime			utcTime;//UTCʱ��
	BD2_OBSTIME		obsTime; //�۲�ʱ��
	BD2_POS_MODE	PosMode; //��λģʽ
	BD2_SAT_INFO	SatInfo[MAX_SatNum];//������Ϣ
	BD2_PVT			initPVT;//��ʼ�����ջ�λ����Ϣ
	BD2_PVT			calcPVT;//������Ľ��ջ�����
	double			bias;	//�Ӳ�
	double			Drift;   //�û�����������ƫ��(�Ӳ�Ư��)
	unsigned int	LockCn[21][64];// ����������Ǻ�
	unsigned int	Count[21];
}BD2_EPOCH;

typedef struct tag_BD2_LS_EPOCH
{
	double 		P[MAX_SatNum_TWO];			// Ȩ��
	double		A[MAX_SatNum_TWO*8];		// ��ƾ���A
	double		v[MAX_SatNum_TWO];			// �в� v = A*x - l
	double		range_err[MAX_SatNum_TWO];	// �����ջ�����ʱƽ���е�α����� : o - c
	double      range_errorRaim[MAX_SatNum_TWO];// �����ջ�����ʱƽ���е�α����� : o - c
	double		del_L[MAX_SatNum_TWO];		// �����ջ��ٶ�ʱƽ���е� L����ʱ���ã���������
	double		inv[64];					// N����( N=AtA )
	double		U[18];						// U = At * l
	double		VtV;						// �в�ƽ���� VtV = v[i]*v[i]
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

//�ز���λƽ��α��
typedef struct tag_CarrierPseudo 
{
	unsigned int smoothCount;			 //�ز���λƽ������
	double pseudoRange;			 //α��
	double carrierPhase;		 //�ز���λ
	double doppler;				 //������
	double smoothed_pseudoRange; //ƽ�����α��
}CarrierPseudo;	
