#pragma once
#include "calstruct.h"

//���ܣ�ͨ���ܼ���������������õ������ա�ʱ���룬ͬʱҲ�õ�����պ����루BD2��
HWA_POS_API void TransYMDHMS(BD2_OBSTIME* time,bool utc);
//���ܣ�������ʱת��ΪUTCʱ��
HWA_POS_API int BDTime2UTC(UTCTime* time);
//���ܣ���UTCʱת��Ϊ����ʱ��
HWA_POS_API int UTCTime2BD(UTCTime* time);
//���ܣ���UTCʱת��Ϊ����ʱ��
HWA_POS_API void UTCTimeToLocalTime(UTCTime utc, UINT8 zone, BD2_DATE_TIME* time);
//���ܣ���������ת��Ϊ������
HWA_POS_API long Calendar2JD(int yy, int mm, int dd);
//���ܣ���������ת��Ϊ������
HWA_POS_API void JD2Calendar(long jd, int* iyear, int* imonth, int* iday);

//���ܣ����ռ�����XYZ��CGS2000��ת�����������BLH
HWA_POS_API void Trans_XYZ_to_BLH(double X, double Y, double Z, double* B, double* L, double* H);
//���ܣ����������BLH��CGS2000��ת�����ռ�����XYZ
HWA_POS_API void Trans_BLH_to_XYZ(double B, double L, double H, double *X, double *Y, double *Z, char cSystem=0);
