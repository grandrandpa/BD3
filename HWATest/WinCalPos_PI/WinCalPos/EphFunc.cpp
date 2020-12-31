#include "StdAfx.h"
#include "EphFunc.h"

//检查时间有效性
bool CalEphValid(BD2_OBSTIME* time, unsigned short week,double tow)
{
	double TimeLength;

	TimeLength = (time->Weeks - week)*604800;
	TimeLength +=(time->Tow  - tow);
	if(TimeLength>302400)
	{
		TimeLength -=604800;
	}
	else if(TimeLength<-302400)
	{
		TimeLength -=604800;
	}
	if(fabs(TimeLength)>7200)
	{
		return false;
	}
	return true;
}
bool CalculateSatPos(BD2_EPH eph, BD2_OBSTIME time, BD2_SAT_POS* pResult,double R)
{
	bool flag=false;
	double Sec=0;
	
	if(!CalEphValid(&time, eph.week, eph.toe))
		return false;
	if (eph.system == SYSTEM_BD1)//BD1
	{
		Sec=time.Tow-R/299792458;
		flag = CalculateBD1SatPos(eph,Sec, pResult);
	} 
	else if(eph.system == SYSTEM_BD2)//BD2
	{
		Sec=time.Tow-R/299792458;
		flag = CalculateBD2SatPos(eph,Sec, pResult);
	}

	return flag;
}
bool CalculateBD1SatPos(BD2_EPH eph,double Sec, BD2_SAT_POS* pResult)
{
	unsigned short k=0;
	double SE=0,CE=0,A=0,n0=0,deltaToc=0,deltaTsv=0,deltaToe=0,Mdot=0,M=0,E=0,Ek=0;
	double delta_tr=0,sqrt1me2=0,EI=0,EO=0,Edot=0,Phi=0,Pdot=0,S2P=0,C2P=0,U=0,SU=0,CU=0,Udot=0,SUdot=0,CUdot=0;
	double R=0,Rdot=0,I=0,Idot=0,SI=0,CI=0,Xpos=0,Ypos=0,Xdot=0,Ydot=0,L=0,Ldot=0,SL=0,CL=0,BDx=0,BDy=0,BDz=0,BDvx=0;
	double BDvy=0,BDvz=0,arg=0,SARG=0,CARG=0;
	double dx=0,dy=0,dz=0,north=0,east=0,up=0,rho=0,sinB=0,sinL=0,cosB=0,cosL=0;
	double cos5 = 0.996194698091745532295,sin5 = -0.087155742747658173558;
	SE =0;
	CE =0;
	
	if(!eph.flag)
	{
		memset(&pResult,0,sizeof(BD2_SAT_POS));
		return 0;
	}
	deltaToc = Sec - eph.toc;
	if(deltaToc>302400)
		deltaToc -=604800;
	else if(deltaToc<-302400)
		deltaToc +=604800;
	deltaTsv = eph.af0 + deltaToc*eph.af1*+deltaToc*deltaToc*eph.af2;
	if(eph.branch < 10)
		deltaToc = Sec-deltaTsv+eph.tgd1;
	else if(eph.branch < 20)
		deltaToc = Sec-deltaTsv+eph.tgd2;
	else
		deltaToc = Sec-deltaTsv;
	deltaToc -=eph.toc;
	if(deltaToc>302400)
		deltaToc -=604800;
	else if(deltaToc<-302400)
		deltaToc +=604800;
	deltaTsv = eph.af0 + deltaToc*eph.af1*+deltaToc*deltaToc*eph.af2;
	if(eph.branch < 10)
		deltaToe = Sec-deltaTsv+eph.tgd1;
	else if(eph.branch < 20)
		deltaToe = Sec-deltaTsv+eph.tgd2;
	else
		deltaToe = Sec-deltaTsv;
	deltaToe -=eph.toe;
	if(deltaToe>302400)
		deltaToe -=604800;
	else if(deltaToe<-302400)
		deltaToe +=604800;
	A = eph.sqrta * eph.sqrta;
	n0 = sqrt(3.986004418E14/(A*A*A));
	Mdot = n0+eph.deltaN;
	M = eph.m0+Mdot*deltaToe;
	E = eph.e;
	sqrt1me2 = sqrt(1.0-E*E);
	EI = M;
	for(k=0;k<20;k++)
	{
		EO =M+E*sin(EI);
		if(fabs(EO-EI)<=1.0E-20)
			break;
		EI = EO;
	}
	Ek = EO;
	SE = sin(Ek);
	CE = cos(Ek);
	delta_tr = (-4.442807309E-10)*E*eph.sqrta*SE;
	pResult->tsv = deltaTsv +delta_tr;
	pResult->dtsv = eph.af1*+2*deltaToc*eph.af2;
	Edot = Mdot/(1.0-E*CE);
	Phi =atan2(sqrt1me2*SE,CE-E)+eph.w;
	Pdot = sqrt1me2*Edot/(1.0-E*CE);
	S2P = sin(2.0*Phi);
	C2P =cos(2.0*Phi);
	U = Phi+(eph.cus*S2P + eph.cuc*C2P);
	SU = sin(U);
	CU = cos(U);
	Udot = Pdot *(1.0+2.0*eph.cus*C2P-2.0*eph.cuc*S2P);
	SUdot = CU*Udot;
	CUdot = -SU*Udot;
	R = A*(1.0-E*CE)+(eph.crs*S2P+eph.crc*C2P);
	Rdot = A*E*SE*Edot+2.0*Pdot*(eph.crs*C2P-eph.crc*S2P);
	I = eph.i0+eph.idot*deltaToe+(eph.cis*S2P+eph.cic*C2P);
	SI = sin(I);
	CI = cos(I);
	Idot = eph.idot +2.0*Pdot*(eph.cis*C2P - eph.cic*S2P);
	Xpos = R*CU;
	Ypos = R*SU;
	Xdot = Rdot*CU+R*CUdot;
	Ydot = Rdot*SU+R*SUdot;
	if(eph.id > 5)
	{
		L =eph.omega0+deltaToe*(eph.omegadot-7.292115E-5)-eph.toe*7.292115E-5;
		Ldot = eph.omegadot-7.292115E-5; 
		SL =sin(L);
		CL =cos(L);
		pResult->x =Xpos*CL-Ypos*CI*SL;
		pResult->y =Xpos*SL+Ypos*CI*CL;
		pResult->z = Ypos*SI;
		// ********** 还需计算卫星速度 **********//
		// 算法依据hhb程序以及禛PS原理及应用》P48原理。将卫星在轨道平面直角坐标系中的表达式微分，
		// 即可得到在轨道平面中的速度，然后再坐标转换的CGS2000坐标系。
		// 也可参考《GPS导航与精密定位》P87公式	
		pResult->vx = -Ldot*pResult->y+Xdot*CL-Ydot*CI*SL+Ypos*SI*Idot*SL;
		pResult->vy = Ldot*pResult->x+Xdot*SL+Ydot*CI*CL-Ypos*SI*Idot*CL;
		pResult->vz = Ypos*CI*Idot+Ydot*SI;
	}
	else
	{
		L =eph.omega0+deltaToe*eph.omegadot-eph.toe*7.292115E-5;
		Ldot = eph.omegadot; 
		SL =sin(L);
		CL =cos(L);
		BDx = Xpos*CL-Ypos*CI*SL;
		BDy = Xpos*SL+Ypos*CI*CL;
		BDz = Ypos*SI;
		BDvx = Xdot*CL-Ydot*SL*CI+BDz*SL*Idot-Ldot*BDy;
		BDvy = Xdot*SL+Ydot*CL*CI-BDz*CL*Idot+Ldot*BDx;
		BDvz = Ydot*SI+Ypos*CI*Idot;
		arg = deltaToe*7.292115E-5;
		SARG = sin(arg);
		CARG = cos(arg);
		pResult->x = BDx*CARG + SARG*(BDy*cos5+BDz*sin5);
		pResult->y = -BDx*SARG + CARG*(BDy*cos5+BDz*sin5);
		pResult->z = -BDy*sin5+BDz*cos5;
		// ********** 还需计算卫星速度 **********//
		// 算法依据hhb程序以及禛PS原理及应用》P48原理。将卫星在轨道平面直角坐标系中的表达式微分，
		// 即可得到在轨道平面中的速度，然后再坐标转换的CGS2000坐标系。
		// 也可参考《GPS导航与精密定位》P87公式	
		pResult->vx = pResult->y*7.292115E-5+SARG*(BDvy * cos5 + BDvz * sin5)+ BDvx * CARG;
		pResult->vy = - pResult->x*7.292115E-5-BDvx*SARG+CARG* (BDvy*cos5 + BDvz*sin5);
		pResult->vz = -BDvy*sin5 + BDvz*cos5;
	}

	return true;
}
bool CalculateBD2SatPos(BD2_EPH eph,double Sec, BD2_SAT_POS* pResult)
{
	unsigned short k=0;
	double SE=0,CE=0,A=0,A0=0,n0=0,deltaToc=0,deltaTsv=0,deltaToe=0,deltaNA=0,NA=0,M=0,E=0,Ek=0;
	double delta_tr=0,sqrt1me2=0,EI=0,EO=0,Edot=0,Phi=0,Pdot=0,S2P=0,C2P=0,U=0,SU=0,CU=0,Udot=0,SUdot=0,CUdot=0;
	double R=0,Rdot=0,I=0,Idot=0,SI=0,CI=0,Xpos=0,Ypos=0,Xdot=0,Ydot=0,L=0,Ldot=0,SL=0,CL=0,BDx=0,BDy=0,BDz=0,BDvx=0,BDvy=0,BDvz=0,arg=0,SARG=0,CARG=0;
	double dx=0,dy=0,dz=0,north=0,east=0,up=0,rho=0,sinB=0,sinL=0,cosB=0,cosL=0,OmegaDot=0;
	double cos5 = 0.996194698091745532295,sin5 = -0.087155742747658173558;
	SE =0;
	CE =0;

	if(!eph.flag)
	{
		memset(&pResult,0,sizeof(BD2_SAT_POS));
		return 0;
	}
	// 考虑跨周影响
	deltaToc = Sec - eph.toc;
	if(deltaToc>302400)
		deltaToc -=604800;
	else if(deltaToc<-302400)
		deltaToc +=604800;
	deltaTsv = eph.af0 + deltaToc*eph.af1 + deltaToc*deltaToc*eph.af2;
	deltaToc = Sec-deltaTsv;
	deltaToc -=eph.toc;
	if(deltaToc>302400)
		deltaToc -=604800;
	else if(deltaToc<-302400)
		deltaToc +=604800;
	deltaTsv = eph.af0 + deltaToc*eph.af1 + deltaToc*deltaToc*eph.af2;
	deltaToe = Sec-deltaTsv;
	deltaToe -=eph.toe;
	if(deltaToe>302400)
		deltaToe -=604800;
	else if(deltaToe<-302400)
		deltaToe +=604800;

	if((eph.id<12)||(eph.id==32))
		A0 = 42162200 + eph.deltaA;
	else
		A0 = 27906100+eph.deltaA;
	A = A0 + eph.Adot * deltaToe;// 轨道半长轴开方
	// ********** 开始迭代计算开普勒方程 **********//
	n0 = sqrt(3.986004418e14/(A*A*A));// 先计算轨道平均角速度
	deltaNA = eph.deltaN + (eph.Ndot * deltaToe)/2;
	NA = n0 + deltaNA;
	M = eph.m0 + NA*deltaToe;
	E = eph.e;// 轨道偏心率
	sqrt1me2 = sqrt(1-E*E);
	EI = M;
	for(k=0;k<15;k++)
	{
		EO =M + E * sin(EI);
		if(fabs(EO-EI)<=1e-20)
			break;
		EI = EO;
	}
	// ********** 迭代计算完成 **********//
	Ek = EO;
	SE = sin(Ek);
	CE = cos(Ek);
	delta_tr = (-4.442807633e-10) * E * sqrt(A) * SE;
	pResult->tsv = deltaTsv +delta_tr;
	pResult->dtsv = eph.af1 + 2*deltaToc*eph.af2;
	Edot = NA/(1-E*CE);
	Phi =atan2(sqrt1me2*SE,CE-E) + eph.w;
	Pdot = sqrt1me2*Edot/(1-E*CE);
	S2P = sin(2*Phi);
	C2P =cos(2*Phi);
	U = Phi+(eph.cus * S2P + eph.cuc * C2P);
	SU = sin(U);
	CU = cos(U);
	Udot = Pdot *(1+2*(eph.cus * C2P - eph.cuc * S2P));
	SUdot = CU*Udot;
	CUdot = -SU*Udot;
	R = A*(1-E*CE) + (eph.crs * S2P + eph.crc * C2P);
	Rdot = A*E*SE*Edot + 2*Pdot*(eph.crs * C2P - eph.crc * S2P);
	I = eph.i0 + eph.idot * deltaToe + (eph.cis * S2P + eph.cic * C2P);
	SI = sin(I);
	CI = cos(I);
	Idot = eph.idot + 2*Pdot*(eph.cis * C2P - eph.cic * S2P);
	Xpos = R*CU;
	Ypos = R*SU;
	Xdot = Rdot*CU+R*CUdot;
	Ydot = Rdot*SU+R*SUdot;
	OmegaDot = eph.omegadot - 8.16814089933346242e-9;
	// 计算卫星坐标和速度
	if(eph.id > 5)
	{
		L =eph.omega0+deltaToe*(OmegaDot-7.292115e-5)-eph.toe*7.292115e-5;
		Ldot = OmegaDot-7.292115e-5; 
		SL =sin(L);
		CL =cos(L);
		pResult->x =Xpos*CL - Ypos*CI*SL;
		pResult->y =Xpos*SL + Ypos*CI*CL;
		pResult->z = Ypos*SI;
		pResult->vx = -Ldot*pResult->y+Xdot*CL-Ydot*CI*SL+Ypos*SI*Idot*SL;
		pResult->vy = Ldot*pResult->x+Xdot*SL+Ydot*CI*CL-Ypos*SI*Idot*CL;
		pResult->vz = Ypos*CI*Idot+Ydot*SI;
	}
	else
	{
		L =eph.omega0+deltaToe*OmegaDot-eph.toe*7.292115e-5;
		Ldot = OmegaDot; 
		SL =sin(L);
		CL =cos(L);
		BDx = Xpos*CL-Ypos*CI*SL;
		BDy = Xpos*SL+Ypos*CI*CL;
		BDz = Ypos*SI;
		BDvx = Xdot*CL-Ydot*SL*CI+BDz*SL*Idot-Ldot*BDy;
		BDvy = Xdot*SL+Ydot*CL*CI-BDz*CL*Idot+Ldot*BDx;
		BDvz = Ydot*SI+Ypos*CI*Idot;
		arg = deltaToe*7.292115e-5;
		SARG = sin(arg);
		CARG = cos(arg);
		pResult->x = BDx*CARG + SARG*(BDy*cos5+BDz*sin5);
		pResult->y = -BDx*SARG + CARG*(BDy*cos5+BDz*sin5);
		pResult->z = -BDy*sin5+BDz*cos5;
		pResult->vx = pResult->y*(7.292115e-5)+SARG*(BDvy * cos5 + BDvz * sin5)+ BDvx * CARG;
		pResult->vy = - pResult->x*(7.292115e-5)-BDvx*SARG+CARG* (BDvy*cos5 + BDvz*sin5);
		pResult->vz = -BDvy*sin5 + BDvz*cos5; 

	}

	return true;
}

// 计算卫星在用户坐标系中的方位角和高度角
void CalculateSatAZEL(BD2_SAT_POS* sat_pos, BD2_PVT userPVT, BD2_SAT_AZEL* sat_azel)
{
	DOUBLE xls, yls, zls;	
	DOUBLE xaz, yaz, zaz;	
	DOUBLE az, el;			
	DOUBLE	north_x,north_y,north_z,
		east_x, east_y,
		up_x,   up_y,   up_z ;	
	DOUBLE x,y,z,r,rxy;

	if( fabs(userPVT.xyz.x)< 1.0E-8 &&
		fabs(userPVT.xyz.y)< 1.0E-8 &&
		fabs(userPVT.xyz.z)< 1.0E-8 )
	{
		sat_azel->elv = 0.0;
		sat_azel->azi = 0.0;
		return;
	}

	x = userPVT.xyz.x;
	y = userPVT.xyz.y;
	z = userPVT.xyz.z;
	r = sqrt(x*x + y*y + z*z);	
	rxy = sqrt(x*x + y*y);	

	sat_azel->elv = 0.0;               
	sat_azel->azi = 0.0;

	if ( rxy > 1.0E-8 )
	{
		north_x = -x/rxy * z/r;
		north_y = -y/rxy * z/r;
		north_z =  rxy / r;
		east_x  = -y / rxy;
		east_y  =  x / rxy;
		up_x    =  x / r;
		up_y    =  y / r;
		up_z    =  z / r;

		xls = sat_pos->x - x;
		yls = sat_pos->y - y;
		zls = sat_pos->z - z;

		zaz = (up_x * xls + up_y * yls + up_z * zls) / sqrt( xls * xls + yls * yls + zls * zls);

		if ( zaz >= 1.0 )
			el = PI/2;
		else if ( zaz <= -1.0 )
			el = - PI/2;
		else
			el = asin(zaz);

		xaz = north_x * xls + north_y * yls + north_z * zls;
		yaz = east_x * xls + east_y * yls;

		if (xaz != 0.0 || yaz != 0.0)
		{
			az = atan2(yaz, xaz);
			if( az < 0) az += 2*PI;
		}
		else
			az = 0.0;

		sat_azel->elv = el;
		sat_azel->azi =az;

		xls = sat_pos->x - x + sat_pos->vx*20;
		yls = sat_pos->y - y + sat_pos->vy*20;
		zls = sat_pos->z - z + sat_pos->vz*20;

		zaz = (up_x * xls + up_y * yls + up_z * zls) / sqrt( xls * xls + yls * yls + zls * zls);
		if ( zaz >= 1.0 )
			el = PI/2;
		else if ( zaz <= -1.0 )
			el = - PI/2;
		else
			el = asin(zaz);
		sat_azel->elv = el;
	}
	return;
}
