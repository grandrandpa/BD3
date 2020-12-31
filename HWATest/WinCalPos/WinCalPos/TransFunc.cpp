#include "StdAfx.h"
#include "TransFunc.h"

//-----------------------------------------------------------------------------
//目的：将空间坐标XYZ（CGS2000）转换至大地坐标BLH
//参数：
//[IN]	空间坐标XYZ
//[OUT]	大地坐标BLH
//返回：无
//-------------------------------------------------------------------------------
const UINT16 MONTH_TABLE[] = {0,31,59,90,120,151,181,212,243,273,304,334,365};
void Trans_XYZ_to_BLH(double X, double Y, double Z, double* B, double* L, double* H)
{
	double p,n,thet,esq,epsq,slat,clat,sth,sth3,cth,cth3,m,k;   
	double a=6378137,b=6356752.314140358;
	double a2 = 40680631590769,b2 = 40408299983328.796678596524368164;

	if ((X*X+Y*Y+Z*Z)<10)
	{
		*B = 40.111;
		*L = 116.111;
		*H = 111;
		return;
	}
	p = sqrt( X * X + Y * Y);
	thet =atan( Z * a /( p * b));
	esq = 1.0 - b2 / a2;
	epsq = a2 / b2 - 1.0;
	sth = sin( thet);
	cth =cos( thet);
	sth3 = sth * sth * sth;
	cth3 = cth * cth * cth;
	m =atan( (Z + epsq * b * sth3)/(p - esq * a * cth3));
	k = atan2( Y, X);
	clat = cos(m);
	slat = sin(m);
	n = a2 / sqrt( a2 * clat * clat + b2 * slat * slat);
	*H = p / clat - n;
	*B=m*57.295779513;
	*L=k*57.295779513;
}

//-----------------------------------------------------------------------------
//目的：将大地坐标BLH（CGS2000）转换至空间坐标XYZ
//参数：
//[IN]	大地坐标BLH
//[OUT]	空间坐标XYZ
//返回：无
//-------------------------------------------------------------------------------
void Trans_BLH_to_XYZ(double B, double L, double H, double *X, double *Y, double *Z, char cSystem)
{
	double N, a, f, e2, sinB, cosB,sinB2;

	a=CGS2000_A;
	f=CGS2000_F;

	e2 = 2*f-f*f;
	sinB = sin(B);
	cosB = cos(B);
	sinB2=sinB*sinB;
	N = a/(sqrt(1-e2*sinB2));

	*X = (N + H)*cosB*cos(L);
	*Y = (N + H)*cosB*sin(L);
	*Z = (N*(1-e2) + H)*sinB;
}

//------------------------------------------------------------------------------
//功能：将年月日转换为儒略日
//参数：
//[IN] 年 yy
//[IN] 月 mm
//[IN] 日 dd
//返回：儒略日
//-------------------------------------------------------------------------------
long Calendar2JD(int yy, int mm, int dd)
{
	long jd;
	double y, m;

	if(yy == 0)
		--yy;         // there is no year 0

	if(yy < 0) 
		++yy;

	y = (double)(yy);
	m = (double)(mm);//, d = double(dd);

	// In the conversion from the Julian Calendar to the Gregorian
	// Calendar the day after October 4, 1582 was October 15, 1582.
	//
	// if the date is before October 15, 1582
	if(yy < 1582 || (yy == 1582 && (mm < 10 || (mm == 10 && dd < 15))))
	{
		jd = 1729777 + dd + 367 * yy 
			- (long)(7 * ( y + 5001 + (long)((m - 9) / 7)) / 4) 
			+ (long)(275 * m / 9);
	}
	else   // after Oct 4, 1582
	{     
		jd = 1721029 + dd + 367 * yy
			- (long)(7 * (y + (long)((m + 9) / 12)) / 4)
			- (long)(3 * ((long)((y + (m - 9) / 7) / 100) + 1) / 4) 
			+ (long)(275 * m / 9);

		// catch century/non-400 non-leap years
		if( (! (yy % 100) && 
			(yy % 400) && 
			mm > 2 && 
			mm < 9)      ||
			(!((yy - 1) % 100) &&
			((yy - 1) % 400) &&
			mm == 1)) 
		{
			--jd;
		}
	}
	return jd;
}

//------------------------------------------------------------------------------
//功能：将儒略日转换为年月日
//参数：
//[IN] 年 yy
//[OUT] 年 iyear
//[OUT] 月 imonth
//[OUT] 日 iday
//返回：无
//-------------------------------------------------------------------------------
void JD2Calendar(long jd, int* iyear, int* imonth, int* iday)
{
	long L, M, N, P, Q;
	if(jd > 2299160)    // after Oct 4, 1582
	{
		L = jd + 68569;
		M = (4 * L) / 146097;
		L = L - ((146097 * M + 3) / 4);
		N = (4000 * (L + 1)) / 1461001;
		L = L - ((1461 * N) / 4) + 31;
		P = (80 * L) / 2447;
		*iday = (int)(L - (2447 * P) / 80);
		L = P / 11;
		*imonth = (int)(P + 2 - 12 * L);
		*iyear = (int)(100 * (M - 49) + N + L);
	}
	else 
	{
		P = jd + 1402;
		Q = (P - 1) / 1461;
		L = P - 1461 * Q;
		M = (L - 1) / 365 - L / 1461;
		N = L - 365 * M + 30;
		P = (80 * N) / 2447;
		*iday = (int)(N - (2447 * P) / 80);
		N = P / 11;
		*imonth = (int)(P + 2 - 12 * N);
		*iyear = (int)(4 * Q + M + N - 4716);
		if((*iyear) <= 0) 
		{
			--(*iyear);
		}
	}
	// catch century/non-400 non-leap years
	if(*iyear > 1599 &&
		!(*iyear % 100) &&
		(*iyear % 400) &&
		*imonth == 2 &&
		*iday == 29)
	{
		*imonth = 3;
		*iday = 1;
	}
}

//-------------------------------------------------------------------------------
//功能：通过周计数和周内秒计数得到年月日、时分秒，同时也得到年积日和天秒（BD2）
//参数：
//[IN] 时间结构体指针 ObsTime*
//返回：无
//-------------------------------------------------------------------------------
void TransYMDHMS(BD2_OBSTIME* time,bool utc)
{
	unsigned int total_sec;
	int four_year, one_year;
	int four_year_sec, year_sec, year_day;
	int day_sec, delta;
	unsigned short month;
	bool leap = false;

	if(utc)
	{
		if(time->Weeks>100)
			time->Tow=time->Tow;
		if(time->Tow<0)
		{
			time->Tow+=604800;
			time->Weeks--;
		}
	}
	total_sec = time->Weeks*604800 + (unsigned int)time->Tow;// + time->Leap;//BDT -> UTC
	total_sec += 31536000;	

	four_year = total_sec/126230400;
	four_year_sec = total_sec%126230400;
	one_year = four_year_sec/31536000;
	year_sec = four_year_sec%31536000;

	if(one_year>3)
		one_year = 3;

	time->year = 2005 + four_year*4 + one_year;
	if(time->year%400==0 || (time->year%4==0 && time->year%100!=0))
	{
		leap = true;
	}

	year_day = year_sec/86400 + 1;
	for(month=1; month<13; month++)
	{
		if(month == 2 && leap)
		{
			year_day--;	
			delta = 1;
		}
		else
			delta = 0;

		if(year_day > (MONTH_TABLE[month-1]-delta) && year_day <= MONTH_TABLE[month])
			break;
	}
	time->month = month;
	if(month == 2 && leap)
		year_day++;
	time->day = year_day - MONTH_TABLE[month-1];
	time->DayOfYear = year_day;

	day_sec = ((int)time->Tow)%86400;
	time->SecOfDay = day_sec + (time->Tow - (int)time->Tow);

	time->hour = day_sec/3600;
	time->min = (day_sec%3600)/60;
	time->second = day_sec - (time->hour*3600 + time->min*60) + (time->Tow - (int)time->Tow);
	time->dayofweek=(unsigned short)(time->Tow/(3600*24));
	time->MJD=53736+time->dayofweek+time->Weeks*7;//儒略日
}

//-------------------------------------------------------------------------------
// 将北斗时转换为UTC时间
//参数：
//[IN/OUT] 时间参数指针 time
//返回：
//-------------------------------------------------------------------------------
int BDTime2UTC(UTCTime* time)
{
	unsigned int total_sec=0;
	int four_year=0, one_year=0;
	int four_year_sec=0, year_sec=0, year_day=0;
	int day_sec=0, delta=0;
	unsigned short month=0;
	bool leap = false;

	if(time->tow<0)
	{
		time->tow+=SECONDS_IN_WEEK;
		time->week--;
	}
	total_sec = time->week*SECONDS_IN_WEEK + (unsigned int)time->tow + time->leap;//BDT -> UTC
	total_sec += SECONDS_IN_YEAR;	

	four_year = total_sec/SECONDS_FOUR_YEAR;
	four_year_sec = total_sec%SECONDS_FOUR_YEAR;
	one_year = four_year_sec/SECONDS_IN_YEAR;
	year_sec = four_year_sec%SECONDS_IN_YEAR;//年内秒

	if(one_year>3)
		one_year = 3;
	// 于是得到了年
	time->year = 2005 + four_year*4 + one_year;
	// 判断是否是闰年
	if(time->year%400==0 || (time->year%4==0 && time->year%100!=0))
		leap = true;
	// 得到年内天数
	year_day = year_sec/SECONDS_IN_DAY + 1;
	// 根据天数得到月份和数
	for(month=1; month<13; month++)
	{
		if(month == 2 && leap)
		{
			year_day--;	// 闰年月要特殊处理
			delta = 1;
		}
		else
			delta = 0;

		if(year_day > (MONTH_TABLE[month-1]-delta) && year_day <= MONTH_TABLE[month])
			break;
	}
	//得到月份
	time->month = month;
	if(month == 2 && leap)
		year_day++;
	//得到日
	time->day = year_day - MONTH_TABLE[month-1];
	// 得到天内秒数
	day_sec = ((INT32)time->tow)%SECONDS_IN_DAY;
	// 即可得到时、分、秒
	time->hour = day_sec/3600;
	time->minute = (day_sec%3600)/60;
	time->second = day_sec - (time->hour*3600 + time->minute*60) + (time->tow - (INT32)time->tow);

	return 1;
}

//-------------------------------------------------------------------------------
//功能：将UTC时转换为北斗时间
//参数：
//[IN/OUT] 时间参数指针 time
//返回：
//-------------------------------------------------------------------------------
int UTCTime2BD(UTCTime* time)
{
	unsigned int total_sec=0, week_sec=0;
	int four_year=0, one_year=0, year_day=0;
	int four_year_sec=0,one_year_sec=0, year_sec=0;
	double day_sec=0;
	bool leap = false;

	if(time->year < 2005)
		return 0;
	four_year = (time->year - 2005)/4;
	one_year = (time->year - 2005)%4;

	four_year_sec = four_year*SECONDS_FOUR_YEAR;
	one_year_sec = one_year*SECONDS_IN_YEAR;
	// 判断是否是闰年
	if(time->year%400==0 || (time->year%4==0 && time->year%100!=0))
		leap = TRUE;
	//得到年内天
	year_day = MONTH_TABLE[time->month];
	if (time->month > 2 && leap)
		year_day++;
	year_sec = (year_day - 1)*SECONDS_IN_DAY;

	//得到天内秒
	day_sec = time->hour*SECONDS_IN_HOUR + time->minute*SECONDS_IN_MINUTE + time->second;
	//总计整天数秒数
	total_sec = four_year_sec + one_year_sec + year_sec;
	week_sec = total_sec % SECONDS_IN_WEEK;

	//得到周计数、周内秒
	time->week = total_sec / SECONDS_IN_WEEK;
	time->tow = week_sec + day_sec - time->leap;

	return 1;
}

//-------------------------------------------------------------------------------
//功能：将UTC时转换为本地时间
//参数：
//[IN] 时间参数 utc
//[IN] 时区参数 zone
//[OUT] 时间参数指针 time
//返回：
//-------------------------------------------------------------------------------
void UTCTimeToLocalTime(UTCTime utc, UINT8 zone, BD2_DATE_TIME* time)
{
	unsigned long MJD=0;
	int year=0,month=0,day=0,hour=0;

	MJD = Calendar2JD(utc.year, utc.month, utc.day);
	hour = utc.hour + zone;
	if (hour > 23)
	{
		hour = hour%24;
		MJD++;
	}
	JD2Calendar(MJD, &year, &month, &day);

	time->year = year;
	time->month = month;
	time->day = day;
	time->hour = hour;
	time->minute = utc.minute;
	time->second = utc.second;
}
