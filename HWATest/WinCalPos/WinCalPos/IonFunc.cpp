#include "StdAfx.h"
#include "IonFunc.h"

double CalculateIono(BD2_OBSTIME time, BD2_PVT* initPos, BD2_SAT_INFO* satInfo, BD2_ION* Iono,char PosMode)
{
	double delay = 0,Freq=0;
	if(Iono->flag!=1)
		return delay;
	if(PosMode<20)
	{
		if (Iono->system == SYSTEM_BD1)
		{
			if((Iono->gamma0<1.0e-6)&&(Iono->gamma0>-1.0e-6))
				delay = CalculateBD3Iono(time, initPos->blh, satInfo->SatAzel, Iono);
			else
			delay = CalculateBD1Iono(time, initPos->blh, satInfo->SatAzel, Iono);
			if(PosMode>7)
				delay *=1.514487513;
		}
		else if(Iono->system == SYSTEM_BD2)
		{
			if((PosMode==1)||(PosMode==2))
				Freq=15.61098;
			else if((PosMode==3)||(PosMode==4))
				Freq=15.7542;
			else if(PosMode==5)
				Freq=11.7645;
			else if(PosMode==6)
				Freq=12.0714;
			else if(PosMode==7)
				Freq=11.91795;
			else if((PosMode==8)||(PosMode==9)||(PosMode==10)||(PosMode==11)||(PosMode==12))
				Freq=12.6852;
			else if(PosMode==13)
				Freq=24.92028;
			else
				return 0;
			delay = CalculateBD2Iono(time, Freq, initPos->xyz, satInfo->SatPos, Iono);
		}
	}
	return delay;
}
double CalculateBD1Iono(BD2_OBSTIME time, BD2_USER_BLH Pos, BD2_SAT_AZEL Azel, BD2_ION* Iono)
{
	double lat=0,lon = 0,elv=0,azi=0;
	double psi,phi,lambdai,phim,F,t,Z,tmp;
	double A2, A3, A4,diono=0.0;

	if((Iono->flag==0)||(Azel.elv<=0.0))
		return 0;
	lat = Pos.lat;
	lon = Pos.lon;
	elv = Azel.elv;
	azi = Azel.azi;
	Z	= asin( 6378.0E3* cos( elv ) / ( 6378.0E3 + 375.0E3 ) );
	psi = 0.5*PI-elv-Z;
	phi	= asin( sin( lat ) * cos( psi ) + cos( lat ) * sin( psi ) * cos( azi ) );
	lambdai	= lon + asin( sin( psi ) * sin( azi ) / cos( phi ) );	
	phim=phi/PI;
	phim=fabs(phim);
	lambdai=lambdai/PI;
	t=43200.0*lambdai+ time.Tow -floor((43200.0*lambdai + time.Tow )/86400.)*86400.;
	if (t>=86400.0) 
		t -= 86400.0;
	if (t<0.0)
		t += 86400.0;
	tmp=0.53-elv/PI;
	F=1.0+16.0*tmp*tmp*tmp;

	A2 =Iono->alpha0 +
		Iono->alpha1 * phim +
		Iono->alpha2 * phim*phim + 
		Iono->alpha3 * phim*phim*phim;
	if(A2 < 0)
		A2 = 0;

	A3 = 50400 + 
		Iono->gamma0 +
		Iono->gamma1 * phim +
		Iono->gamma2 * phim*phim + 
		Iono->gamma3 * phim*phim*phim;
	if(A3 < 43200)
		A3 = 43200;
	else if(A3 > 55800)
		A3 = 55800;

	A4 =Iono->beta0 +
		Iono->beta1 * phim +
		Iono->beta2 * phim*phim + 
		Iono->beta3 * phim*phim*phim;
	if(A4 < 72000)
		A4 = 72000;
	else if(A4 > 172800)
		A4 = 172800;

	diono = Iono->A1 - Iono->B*phim;	
	if (fabs(t-A3) <  (A4/4.0 )  )
	{
		diono += A2*cos(2*PI*(t - A3)/A4);
	}
	diono*=F*299792458;

	return diono;
}
double CalculateBD3Iono(BD2_OBSTIME time, BD2_USER_BLH Pos, BD2_SAT_AZEL Azel, BD2_ION* Iono)
{
		double  es, a, phu, lmu, temp, f, psi, phi, lmi, phm, phm2, phm3,suma, sumb, sumc,xtemp,  tlocal, ic,A4ofFour;
	   const double re=6378.0,hion=375.0;
	   double cosa,cose,rp,sinap,tanap,tanu;
	   ic=0.0;
	   if((Iono->flag==0)||(Azel.elv<=0.0))
		return 0;
	   es = Azel.elv;                       
	   a = Azel.azi;  
	   phu = Pos.lat; 
	   lmu = Pos.lon; 
	   cosa=cos(a); 
	   cose=cos(es);
	   rp=re/(re+hion)*cose;
	   psi=PI*0.5-es-asin(rp);
	   sinap=sin(psi);
	   tanap=tan(psi);
	   tanu =tan(PI*0.5-phu);   
	   phi=asin(sin(phu)*cos(psi)+cos(phu)*sinap*cosa);    
	   if ((phi> (70.0*D2R)&& tanap*cosa>tanu)||
		   (phi<(-70.0*D2R)&&-tanap*cosa>tan(PI*0.5+phu)))
		   lmi=lmu+PI-asin(sinap*sin(a)/cos(phi));
	   else
		   lmi=lmu+asin(sinap*sin(a)/cos(phi));
	   lmi=lmi/PI;
	   tlocal = time.second + SECONDS_IN_DAY*0.5*lmi;
	   tlocal-=floor(tlocal/86400.0)*86400.0;	
	   temp = 0.53 - es/PI;
	   f = 1.0 + 16.0*temp*temp*temp;
	   phm = phi/PI;
	   phm2 = phm*phm;
	   phm3 = phm2*phm;
	   //A2
	   suma = Iono->alpha0+ Iono->alpha1*phm + Iono->alpha2*phm2 + Iono->alpha3*phm3;
	   if(suma<0.0)
		   suma=0.0;
	   //A4
	   sumb = Iono->beta0+ Iono->beta1*phm + Iono->beta2*phm2 + Iono->beta3*phm3;
	   if(sumb>=172800)
	   	   sumb = 172800;
	   if(sumb<72000.0 )
		   sumb = 72000.0;	
	   sumc=tlocal-50400.0;
	   xtemp = 2.0*PI*(tlocal-50400.0)/sumb;		
	   A4ofFour= sumb*0.25;	
	   if(fabs(sumc)<A4ofFour)
	   {
		   xtemp = 2.0*PI*sumc/sumb;	
		   ic = f*(5.0e-9+suma*cos(xtemp))*299792458 ;
	   }
	   else
		   ic = f*(5.0e-9)*299792458 ;

	   return ic;	
}

double W[13]={0,2*PI,4*PI,2*PI/0.33,2*PI/14.6,2*PI/27,2*PI/121.6,2*PI/182.51,2*PI/365.25,2*PI/4028.71,2*PI/2014.35,2*PI/1007.18,2*PI/503.59};
double AK[221]={-0.61,-1.31,-2.00,-0.03, 0.15,-0.48,-0.40, 2.28,-0.16,-0.21,-0.10,-0.13, 0.21, 0.68, 1.06,    0,-0.12,
-0.51,-0.43, 0.34,-0.01, 0.17, 0.02,-0.06, 0.30, 0.44,-0.28,-0.31,-0.17, 0.04, 0.39,-0.12, 0.12,    0,
-0.06,-0.05, 0.06, 0.17, 0.15,    0, 0.11,-0.05,-0.16, 0.02, 0.11, 0.04, 0.12, 0.07, 0.02,-0.14,-0.14,
0.01,-0.03, 0.01,    0, 0.05,-0.03, 0.05,-0.03,-0.01,    0,-0.08,-0.04,    0,-0.02,-0.03,    0,-0.03,
-0.01,    0, 0.01,    0, 0.01,    0,-0.01,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
0,-0.03,-0.02, 0.01, 0.02,-0.01, 0.01,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
-0.19,-0.02, 0.12, 0.52, 0.06,-0.08,-0.02,-0.08,-0.02,-0.01, 0.01, 0.03, 0.15, 0.06,-0.05,-0.03,-0.10,
-0.18, 0.06,-0.55, 0.05, 0.09,    0,    0, 0.86,-0.18,-0.05,-0.07, 0.04, 0.14,-0.03, 0.37,-0.11,-0.12,
-0.80,-0.14,-0.21, 0.05, 0.27,-0.29,-0.11, 0.17, 0.23, 0.35,-0.05, 0.02,-0.60, 0.02, 0.01, 0.27, 0.32,
-0.35,-0.09,-1.22, 0.03, 0.15,-0.11,-0.17, 1.58,-0.06,-0.15,    0, 0.13, 0.28,-0.08, 0.62,-0.01,-0.04,
-0.13, 0.07,-0.37, 0.04, 0.06,-0.05,-0.07, 0.46,    0,-0.04, 0.01, 0.07, 0.09,-0.05, 0.15,-0.01, 0.01,
-0.06, 0.13,-0.07,    0, 0.02,-0.02,-0.05,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
-0.03, 0.08,-0.01,    0, 0.01,    0,-0.02,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,};
double BK[221]={    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
0.23,-0.20,-0.31, 0.16,-0.03, 0.02, 0.04, 0.18, 0.34, 0.45, 0.19,-0.25,-0.12, 0.18, 0.40,-0.09, 0.21,
0.02,-0.08,-0.06,-0.11, 0.15,-0.14, 0.01, 0.01, 0.04,-0.14,-0.05, 0.08, 0.08,-0.01, 0.01, 0.11,-0.12,
0,-0.02,-0.03,-0.05,-0.01,-0.07,-0.03,-0.01, 0.02,-0.01, 0.03,-0.10, 0.01, 0.05,-0.01, 0.04,    0,
0,-0.02, 0.01,    0,-0.01, 0.01,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
0.01, 0.04, 0.03,-0.01,    0, 0.01,-0.01,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0, 
-0.09, 0.07, 0.03, 0.36, 0.09,-0.03, 0.02,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
0.15,-0.31, 0.13, 0.01,-0.09, 0.04, 0.06,-0.36, 0.08, 0.05, 0.06,-0.02,-0.05, 0.06,-0.20, 0.04, 0.07,
-0.87,-0.12,-0.38, 0.02, 0.14,-0.03,    0, 0.25, 0.17, 0.27,-0.03,-0.03,-0.32,-0.10, 0.20, 0.10, 0.30,
0,-0.10,-0.22,-0.01, 0.02, 0.03,-0.01, 0.49,-0.03,-0.02, 0.01, 0.02, 0.04,-0.04, 0.16,-0.02,-0.01,
0.05, 0.03, 0.07,    0,-0.01, 0.02, 0.02,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
0.03,-0.02, 0.04,    0,-0.03,    0, 0.01,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
0.04,-0.02,-0.04,    0,-0.01,    0, 0.01,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
double CalculateBD2Iono(BD2_OBSTIME time, double Freq, BD2_USER_XYZ UPos, BD2_SAT_POS SatPos,BD2_ION* Iono)
{
	unsigned short i=0, j=0, temp=0;
	double Ux=UPos.x,Uy=UPos.y,Uz=UPos.z,Sx=SatPos.x,Sy=SatPos.y,Sz=SatPos.z,UTC=0;
	double A1,A2,A3,A4,A5,A6,A7,A8,A9,lat,lon,Nclk,TN;
	double Ru,Rs,Rus,Ri,alpha1,alpha2,Map,VTE;//15.61098   12.0714   12.6852 	40.28
	double A0=0,Re=6771000,B=1.3936454077,L=-1.254542666,diono=0,BI[17]={0},K=0;
	double Xig,Yig,Zig,Xim,Yim,Zim,phim,lamm,phig,lamg;
	double sinL,cosL,sinB,cosB,sin2B,cos2B,sin3B,cos3B,sinL2,cosL2,sinL3,sinL4,sinL5;
	static double belta[17],SavSec=0;
	static short Flag = 0;

	if((Iono->af1==0)&&(Iono->af2==0)&&(Iono->af3==0))
		return 0;
	memset(belta,0,sizeof(belta));
	Ru = sqrt(Ux*Ux+Uy*Uy+Uz*Uz);
	Rs = sqrt(Sx*Sx+Sy*Sy+Sz*Sz);
	Rus = sqrt((Ux-Sx)*(Ux-Sx)+(Uy-Sy)*(Uy-Sy)+(Uz-Sz)*(Uz-Sz));
	alpha1 = PI-acos((Ru*Ru+Rus*Rus-Rs*Rs)/(2*Ru*Rus));
	alpha2 = asin(Ru*sin(alpha1)/Re);
	Ri = sqrt(Ru*Ru+Re*Re-2*Ru*Re*cos(alpha1-alpha2));
	Map = sqrt(1/(1-0.8853389732*sin(alpha1)*sin(alpha1)));

	Xig=Ux*(Rus-Ri)/Rus + Sx*Ri/Rus;
	Yig=Uy*(Rus-Ri)/Rus + Sy*Ri/Rus;
	Zig=Uz*(Rus-Ri)/Rus + Sz*Ri/Rus;
	phig=atan(Zig/sqrt(Xig*Xig+Yig*Yig));
	lamg=atan(Yig/Xig);
	Xim = Xig*sin(B)*cos(L)+Yig*sin(B)*sin(L)-Zig*cos(B);
	Yim = -Xig*sin(L)+Yig*cos(L);
	Zim = Xig*cos(B)*cos(L)+Yig*cos(B)*sin(L)+Zig*sin(B);
	phim = atan(Zim/sqrt(Xim*Xim+Yim*Yim));
	lamm = atan(Yim/Xim);
	Nclk = time.Tow + 43200*lamg;
	Nclk-=floor(Nclk/86400.0)*86400.0;
	lat = phim;   
	lon = lamm-PI+(Nclk/43200)*PI;   
	sinL = sin(lat);
	sinL2 = sin(lat)*sin(lat);
	cosL2 = 1-sinL2;
	cosL = sqrt(cosL2);
	sinL3 = sinL2*sin(lat);
	sinL4 = sinL3*sin(lat);
	sinL5 = sinL4*sin(lat);
	sinB = sin(lon);
	cosB = cos(lon);
	sin2B = sin(2*lon);
	cos2B = cos(2*lon);
	sin3B = sin(3*lon);
	cos3B = cos(3*lon);
	
	if((int)(SavSec/86400)!=(int)(time.Tow/86400))
	{
		Flag=0;
	}
	if(Flag==0)
	{
		for( i=0;i<17;i++ )
		{
			for( j=0;j<13;j++ )
			{
				temp=17*j+i;
				TN = W[j] * time.MJD;
				belta[i] +=( AK[temp]*cos(TN) + BK[temp]*sin(TN));
			}
		}
		SavSec=time.Tow;
		Flag=1;
	}

	BI[0] = sqrt(7.0)*(5*sinL3-3*sinL)/2;   
	BI[1] =  sqrt(42.0)*cosL*(5*sinL2-1)*cosB/4;
	BI[2] = -sqrt(42.0)*cosL*(5*sinL2-1)*sinB/4;
	BI[3] = sqrt(105.0)*sinL*cosL2*cos2B/2;
	BI[4] = sqrt(105.0)*sinL*cosL2*sin2B/2;
	BI[5] =  sqrt(70.0)*cosL*cosL2*cos3B/4;
	BI[6] = -sqrt(70.0)*cosL*cosL2*sin3B/4;
	BI[7] = 0.375*(35*sinL4-30*sinL2+3);  
	BI[8] =  0.75*sqrt(10.0)*cosL*(7*sinL3-3*sinL)*cosB;
	BI[9] = -0.75*sqrt(10.0)*cosL*(7*sinL3-3*sinL)*sinB;
	BI[10]= 0.75*sqrt(5.0)*cosL2*(7*sinL2-1)*cos2B;
	BI[11]= 0.75*sqrt(5.0)*cosL2*(7*sinL2-1)*sin2B;
	BI[12]= sqrt(11.0)*(63*sinL5-70*sinL3+15*sinL)/8;  
	BI[13]=  sqrt(165.0)*cosL*(21*sinL4-14*sinL2+1)*cosB/8;
	BI[14]= -sqrt(165.0)*cosL*(21*sinL4-14*sinL2+1)*sinB/8;
	BI[15]= sqrt(1155.0)*cosL2*(3*sinL3-sinL)*cos2B/4;
	BI[16]= sqrt(1155.0)*cosL2*(3*sinL3-sinL)*sin2B/4;
	for(i=0;i<17;i++)
	{
		A0 += belta[i]*BI[i];
	}

	A1 =  1;
	A2 = sqrt(3.0)*sinL;
	A3 =  sqrt(3.0)*cosL*cosB;
	A4 = -sqrt(3.0)*cosL*sinB;
	A5 = sqrt(5.0)*(3*sinL2-1)/2;
	A6 =  sqrt(15.0)*sinL*cosL*cosB;
	A7 = -sqrt(15.0)*sinL*cosL*sinB;
	A8 = sqrt(15.0)*cosL2*cos2B/2;
	A9 = sqrt(15.0)*cosL2*sin2B/2;
	VTE = A0+A1*Iono->af1+A2*Iono->af2+A3*Iono->af3+A4*Iono->af4+A5*Iono->af5+A6*Iono->af6+A7*Iono->af7+A8*Iono->af8+A9*Iono->af9;

	diono=VTE*Map*40.28/Freq/Freq;

	return diono;
}
void MeteorologicExt(   double Hgt, double  *StationTemperature, double *StationPressure,  double *StationES )
{
	*StationTemperature=18-(Hgt)*0.0065;	
	*StationPressure=18*pow((1.0-(2.26E-5)*Hgt),5.25);	//!@# 93
	*StationES=50*exp(-(6.396E-4)*Hgt);		
	*StationES = ((*StationES)*0.01)*exp(-37.2465+0.213166*(*StationTemperature+273.15)-0.000256908*(*StationTemperature+273.15)*(*StationTemperature+273.15));
	if( (*StationES)>100.0 )
		*StationES = 100.0;	
}
double CalculateTrop(double Elv, double Hgt)
{
	double theta,ae,sinth,costh,alpha[9], r, a, b, E,TropError,h[2], n[2],Temperature,Pressure,ES;
	int k,i;
	TropError=0.0;
	Temperature=0.0;
	Pressure=0.0;
	ES=0.0;
	k=0;	
	if(Hgt > 44247.787)
		return 0.0;
	MeteorologicExt( Hgt, &Temperature, &Pressure,&ES );	
	Temperature += 273.15;	

	n[0]  = 0.776E-4*Pressure/Temperature;               //Ndry
	n[1]  = 0.373*ES/(Temperature*Temperature);          //Nwet	
	h[0]  = 40.136+0.14872*(Temperature-273.15);         //Hdry
	h[1]  = 11.0;//Hwet		
	theta = Elv;
	ae    = 6378.137 + Hgt*0.001;
	sinth = sin(theta);
	costh = cos(theta);	
	for(  i = 0 ; i < 2 ; i++)
	{
		r = sqrt(pow((ae+h[i]),2) - pow((ae*costh),2)) - ae*sinth;
		a = -sinth/h[i];
		b = -costh*costh/(2.*h[i]*ae);
		alpha[0] = 1.;
		alpha[1] = 4.*a;
		alpha[2] = 6.*a*a+4.*b;
		alpha[3] = 4.*a*(a*a+3.*b);
		alpha[4] = a*a*a*a+12.*a*a*b+6.*b*b;
		alpha[5] = 4.*a*b*(a*a+3.*b);
		alpha[6] = b*b*(6.*a*a+4.*b);
		alpha[7] = 4.*a*b*b*b;
		alpha[8] = b*b*b*b;		
		E = 0.0;					
		for(k=0 ; k<9 ; k++)
			E = E + alpha[k]/(k+1)*pow(r,k+1);
		TropError = TropError + 1.0e3 * E * n[i];
	}
	return TropError;
}
