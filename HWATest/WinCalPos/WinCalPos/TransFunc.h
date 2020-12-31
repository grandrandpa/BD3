#pragma once
#include "calstruct.h"

//功能：通过周计数和周内秒计数得到年月日、时分秒，同时也得到年积日和天秒（BD2）
HWA_POS_API void TransYMDHMS(BD2_OBSTIME* time,bool utc);
//功能：将北斗时转换为UTC时间
HWA_POS_API int BDTime2UTC(UTCTime* time);
//功能：将UTC时转换为北斗时间
HWA_POS_API int UTCTime2BD(UTCTime* time);
//功能：将UTC时转换为本地时间
HWA_POS_API void UTCTimeToLocalTime(UTCTime utc, UINT8 zone, BD2_DATE_TIME* time);
//功能：将年月日转换为儒略日
HWA_POS_API long Calendar2JD(int yy, int mm, int dd);
//功能：将儒略日转换为年月日
HWA_POS_API void JD2Calendar(long jd, int* iyear, int* imonth, int* iday);

//功能：将空间坐标XYZ（CGS2000）转换至大地坐标BLH
HWA_POS_API void Trans_XYZ_to_BLH(double X, double Y, double Z, double* B, double* L, double* H);
//功能：将大地坐标BLH（CGS2000）转换至空间坐标XYZ
HWA_POS_API void Trans_BLH_to_XYZ(double B, double L, double H, double *X, double *Y, double *Z, char cSystem=0);
