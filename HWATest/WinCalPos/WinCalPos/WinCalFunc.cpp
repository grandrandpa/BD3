#include "StdAfx.h"
#include "WinCalFunc.h"


//观测量检查
int ObsCheck(double PR)
{
	if((PR<18000000)||(PR>50000000))
		return 0;
	return 1;
}
/*--------------------------------------------------------------------------------------
// 功能:根据观测量和卫星位置计算权阵元素
// 参数: 
// [IN/OUT] epoch		当前历元
// [IN/OUT] ls_epoch	LS方法的历元
// 返回: 无
--------------------------------------------------------------------------------------*/
void  GetWeight(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast)
{
	int i=0,satID=0;
	double elv = 0.0;

	//权阵P对角线元素清0
	for(i=0; i<MAX_CHANNEL; i++) 
		epochLeast->P[i] = 1.0;

	//根据有效卫星的信息来定权阵对角线元素
	for( i=0; i<epoch->SatNum; i++)
	{
		satID=epoch->SatInfo[i].SatID;
		// 根据高度角来定权
		elv = epoch->SatInfo[i].SatAzel.elv;
		epochLeast->P[i] = sin(elv+0.25)*sin(elv+0.25);
	}
}

/*--------------------------------------------------------------------------------------\
// 功能:根据观测量和卫星位置构造A矩阵
// 参数: 
// [IN/OUT] epoch		当前历元
// [IN/OUT] ls_epoch	LS方法的历元
// 返回: 无
\--------------------------------------------------------------------------------------*/
void MakeMatrixA(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast)
{
	short  i=0,j=0,nUsableSat=0,satID;// 可视卫星个数
	double angle=0,dx=0,dy=0,dz=0,range=0;
	
	memset(&epochLeast->A,0,sizeof(epochLeast->A));
	memset(&epochLeast->range_err,0,sizeof(epochLeast->range_err));
	memset(&epochLeast->v,0,sizeof(epochLeast->v));
	memset(epochLeast->IDInd,0,sizeof(epochLeast->IDInd));
	memset(epochLeast->P,0,sizeof(epochLeast->P));
	memset(epoch->initPVT.UseSat,0,sizeof(epoch->initPVT.UseSat));
	nUsableSat = epoch->SatNum;
	for (i=0; i<nUsableSat; i++)
	{
		satID = epoch->SatInfo[i].SatID;
		if((epochLeast->RaimInd>>(satID-1))&0x01)
		  		continue;
		angle=0.08 * 7.2921151467e-5;
		dx = epoch->initPVT.xyz.x- (epoch->SatInfo[i].SatPos.x*cos(angle)+epoch->SatInfo[i].SatPos.y*sin(angle));
		dy = epoch->initPVT.xyz.y- (epoch->SatInfo[i].SatPos.y*cos(angle)-epoch->SatInfo[i].SatPos.x*sin(angle));
        dz = epoch->initPVT.xyz.z - epoch->SatInfo[i].SatPos.z;
		range = sqrt(dx*dx+dy*dy+dz*dz);
		angle=range*2.432387791e-13;
		dx = epoch->initPVT.xyz.x- (epoch->SatInfo[i].SatPos.x*cos(angle)+epoch->SatInfo[i].SatPos.y*sin(angle));
		dy = epoch->initPVT.xyz.y- (epoch->SatInfo[i].SatPos.y*cos(angle)-epoch->SatInfo[i].SatPos.x*sin(angle));
        dz = epoch->initPVT.xyz.z - epoch->SatInfo[i].SatPos.z;
		range = sqrt(dx*dx+dy*dy+dz*dz);
		// 构造设计矩阵
		epochLeast->A[j*4+0] = dx/range;
		epochLeast->A[j*4+1] = dy/range;
		epochLeast->A[j*4+2] = dz/range;
		epochLeast->A[j*4+3] = 1;
		epochLeast->IDInd[j]=i;
        epochLeast->range_err[j]=epoch->SatInfo[i].Pseudorang - range+epoch->SatInfo[i].SatPos.tsv*299792458- epoch->bias;
		epochLeast->P[j] = 1;//sin(epoch->SatInfo[i].SatAzel.elv+0.1)*sin(epoch->SatInfo[i].SatAzel.elv+0.1);
		epoch->initPVT.UseSat[j] = epoch->SatInfo[i].SatID;
		if(epoch->initPVT.valid)
		{
			if(fabs(epochLeast->range_err[j])>3000)
			{
				epochLeast->RaimInd|=(1<<(satID-1));
				continue;
			}
		}
		j++;
	}
	epochLeast->Dim=j;
}

/*--------------------------------------------------------------------------------------
// 功能:RAIM计算
// 参数: 
// [IN/OUT] ls_epoch	LS方法的历元
// [IN/OUT] satNum		卫星个数
// 返回: 故障卫星的通道编号，MAX_CHANNEL表示没有发现故障卫星
// 说明:
--------------------------------------------------------------------------------------*/
UINT16 RaimWork(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast)
{
	unsigned short i,j,Num = epochLeast->Dim;
	unsigned short  found=0,Index = 1000;
	double  ATA[16]={0},Trai[18*18]={0},Max =0,Err=0;
	int flag=0;

	epochLeast->VtV=0;
	for(i=0;i<Num;i++)
	{
		epochLeast->VtV+=epochLeast->range_err[i]*epochLeast->range_err[i];
		if(fabs(epochLeast->range_err[i])>14.0)
		{
			found=1;
			break;
		}
	}
	if(found==1)
	{
		MatrixATB(epochLeast->A, epochLeast->A, ATA, Num, 4, 4);
    	flag = MatrixInv(ATA,4);
		if(!flag)
		{
			return  1000;
		}
		MatrixAPAT(epochLeast->A,ATA,Trai,Num,4);
		for(j=0;j<Num;j++)
		{
			epochLeast->Trai[j]=Trai[j*Num+j];
			Err =fabs( epochLeast->range_err[j]/sqrt(1-epochLeast->Trai[j]) );
			if( Err>Max )
			{
				Max = Err;
				Index = j;
			}
		}
		if(Index<Num)
		{
			return (epoch->SatInfo[epochLeast->IDInd[Index]].SatID);
		}
	}
	return 1000;
}
/***********************************************************************************************************************************/
/*--------------------------------------------------------------------------------------
// 功能:计算DOP值
// 参数: 
// [IN/OUT] epoch			卫星位置
// [IN]		epochLeast		接收机PVT
// 返回:	0失败，1则成功
--------------------------------------------------------------------------------------*/
int CalDOPS(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast)
{
	int i=0,j=0;
	double x=0,y=0,z=0,r=0,rxy=0;		
	double Rt[9],Rxyz[64],G[64];
	double H[MAX_SatNum_TWO*8],Hx[MAX_SatNum_TWO*8];
	unsigned short CurN=4, nSatUsed=epoch->SatNum;
	int det=0;

	//将地球作为球体的近似，减少计算量
	x   = epoch->initPVT.xyz.x;
	y   = epoch->initPVT.xyz.y;
	z   = epoch->initPVT.xyz.z;
	rxy = sqrt(x*x + y*y);
	r= sqrt(x*x + y*y + z*z);
	for(i=0; i<64; i++)
		Rxyz[i]=0;
	for(i=0; i<CurN; i++)
		Rxyz[i*CurN+i]=1;
	
	Rt[0] = -x/rxy * z/r;  //north.x
	Rt[3] = -y/rxy * z/r;  //north.y
	Rt[6] =  rxy / r;      //north.z
	Rt[1] = -y / rxy;      //east.x
	Rt[4] =  x / rxy;      //east.y
	Rt[7] =  0.0;          //east.z
	Rt[2] =  x / r;        // up.x
	Rt[5] =  y / r;        // up.y
	Rt[8] =  z / r;        // up.z
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
			Rxyz[i*CurN+j]=Rt[i*3+j];
	}
	if( rxy < 1e-8 )
	{
		epoch->initPVT.Dop.hdop = 0;
		epoch->initPVT.Dop.vdop = 0;
		epoch->initPVT.Dop.tdop = 0;
		epoch->initPVT.Dop.pdop = 0;
		epoch->initPVT.Dop.gdop = 0;
		return 0;
	}
	for( i=0; i<MAX_CHANNEL*8; i++)
	{
		H[i]=epochLeast->A[i];	
	}
	MatrixMulti(H,Rxyz,Hx,nSatUsed,CurN,CurN);
	for( i=0; i<MAX_CHANNEL*8; i++)
	{
		H[i]=Hx[i];	
	}
	//计算G=HTH
	MatrixATB(H, Hx, G, nSatUsed, CurN, CurN);

	//计算inverse(N) = (HTH)^-1
	det = MatrixInv( G, CurN);
	if( det <= 1.0e-12 )              //矩阵奇异
	{
		return 0;
	}
	epoch->initPVT.Dop.hdop = sqrt(fabs(G[0]+G[5]));
	epoch->initPVT.Dop.vdop = sqrt(fabs(G[10]));
	epoch->initPVT.Dop.tdop = sqrt(fabs(G[15]));
	epoch->initPVT.Dop.pdop = sqrt(fabs(G[0]+G[5]+G[10]));
	epoch->initPVT.Dop.gdop = sqrt(fabs(G[0]+G[5]+G[10]+G[15]));

	return 1;
}
/*--------------------------------------------------------------------------------------
// 功能:在计算出接收机坐标后计算接收机速度
// 参数: 
// [IN/OUT] epoch			卫星位置
// [IN]		epochLeast		接收机PVT
// 返回:	0失败，1则成功
--------------------------------------------------------------------------------------*/
int CalReceiverVeloc(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast)
{
	unsigned short i,j,k,H,ID,Ind,HInd,Num=epochLeast->Dim,Times=0;
	double posErr=1000,deltaX[5]={0},Trai[18*18]={0},Max=0;
    double dx,dy,dz,dr,temp,dEx,dEy,dEz,Err,B,L;
 	int flag=0,found=0;
	double A[18*4];
	unsigned short IDInd[18];
	memset(&A,0,sizeof(A));
	memset(&IDInd,0,sizeof(IDInd));
	memset(&epochLeast->inv,0,sizeof(epochLeast->inv));
	for(k=0;k<10;k++)
	{
		epoch->Drift=0;
		memset(&epoch->initPVT.speed,0,sizeof(epoch->initPVT.speed));
		do
		{
			j=0;
			for(i=0;i<Num;i++)
			{
				Ind=epochLeast->IDInd[i];
				ID=epoch->SatInfo[Ind].SatID;
				if((epochLeast->RaimInd>>(ID-1))&0x01)
					continue;
				dx=(epoch->initPVT.speed.x-epoch->SatInfo[Ind].SatPos.vx)*epochLeast->A[i*4];
				dy=(epoch->initPVT.speed.y-epoch->SatInfo[Ind].SatPos.vy)*epochLeast->A[i*4+1];
				dz=(epoch->initPVT.speed.z-epoch->SatInfo[Ind].SatPos.vz)*epochLeast->A[i*4+2];
				dr=dx+dy+dz-epoch->SatInfo[Ind].SatPos.dtsv*299792458;
				epochLeast->del_L[j]=epoch->SatInfo[Ind].Doppler-dr-epoch->Drift;
				A[j*4]=epochLeast->A[i*4];
				A[j*4+1]=epochLeast->A[i*4+1];
				A[j*4+2]=epochLeast->A[i*4+2];
				A[j*4+3]=1;
				IDInd[j]=ID;
				j++;
			}
			MatrixATB(A,A,epochLeast->inv,j,4,4);
			flag = MatrixInv(epochLeast->inv,4);
	 	    if(!flag)
	 	    {
	 	       return 0;
	 	    }
			MatrixATB(A,epochLeast->del_L,epochLeast->U,j,4,1);
			MatrixMulti(epochLeast->inv,epochLeast->U,deltaX,4,4,1);

			epoch->initPVT.speed.x += deltaX[0];
			epoch->initPVT.speed.y += deltaX[1];
			epoch->initPVT.speed.z += deltaX[2];
			epoch->Drift += deltaX[3]; 

			posErr = deltaX[0]*deltaX[0]+deltaX[1]*deltaX[1]+deltaX[2]*deltaX[2];
			Times++;
		}while((Times<10)&&(posErr>0.0001));

		for(i=0;i<j;i++)
		{
			if(epochLeast->del_L[i]>5)
			{
				found=1;
				break;
			}
		}
		if((found)&&(j>4))
		{
			found=0;
			MatrixAPAT(A,epochLeast->inv,Trai,j,4);
			for(H=0;H<j;H++)
			{
				Err =fabs( epochLeast->del_L[H]/sqrt(1-Trai[H*j+H]) );
				if( Err>Max )
				{
					Max = Err;
					HInd = H;
				}
			}
			if(HInd<j)
			{
				Times=0;
				epoch->Drift=0;
				epoch->initPVT.speed.x=0;
				epoch->initPVT.speed.y=0;
				epoch->initPVT.speed.z=0;
				epochLeast->RaimInd|=(1<<(epochLeast->IDInd[HInd]-1));
			}
		}
		else
			break;
	}
	if((posErr>0.1)||(Times==10))
	{
		return 0;
	}
	B=epoch->initPVT.blh.lat/57.295779513;
	L=epoch->initPVT.blh.lon/57.295779513;
	dEx = -epoch->initPVT.speed.x*sin(B)*cos(L);
	dEx +=(-epoch->initPVT.speed.y*sin(B)*sin(L));
	dEx +=(epoch->initPVT.speed.z*cos(B));

	dEy = -epoch->initPVT.speed.x*sin(L);
	dEy +=(epoch->initPVT.speed.y*cos(L));
	epoch->initPVT.ENUV.x = sqrt(dEx*dEx+dEy*dEy);

	dEz = epoch->initPVT.speed.x*cos(B)*cos(L);
	dEz +=(epoch->initPVT.speed.y*cos(B)*sin(L));
	dEz +=(epoch->initPVT.speed.z*sin(B));
	epoch->initPVT.ENUV.y = dEz;

	temp=0;
	for(i=0;i<Num;i++)
	{
		temp+=epochLeast->del_L[i]*epochLeast->del_L[i];
	}
	if(sqrt(temp/(j-4))<0.1)
		epoch->initPVT.velOK=1;
	else
		epoch->initPVT.velOK=0;
	return 1;
}
/*--------------------------------------------------------------------------------------
// 功能:在计算出接收机坐标后计算接收机速度
// 参数: 
// [IN/OUT] epoch			卫星位置
// [IN]		epochLeast		接收机PVT
// 返回:	0失败，1则成功
--------------------------------------------------------------------------------------*/
int RaimLeastSquare(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast)
{
	unsigned short  i,j,k,Times=0,FaultSat=1000;
	double deltaX[5]={0},posErr=1000,Rms=0;
	unsigned short Num = epoch->SatNum;
	double Sigma0=0;
	int flag=0;

	epoch->bias=0;
	for(k=0;k<10;k++)
	{
		do 
		{
			MakeMatrixA(epoch, epochLeast);
			MatrixAtPA(epochLeast->A, epochLeast->P, epochLeast->inv,epochLeast->Dim, 4);
			flag = MatrixInv(epochLeast->inv, 4);
			if(!flag)
			{
				return ERROR_MAT_SINGULAR;
			}
			MatrixAtPL(epochLeast->A,epochLeast->P,epochLeast->range_err,epochLeast->U,epochLeast->Dim,4);
			MatrixMulti(epochLeast->inv,epochLeast->U,deltaX,4,4,1);

			epoch->initPVT.xyz.x  += deltaX[0];
			epoch->initPVT.xyz.y  += deltaX[1];
			epoch->initPVT.xyz.z  += deltaX[2];
			epoch->bias += deltaX[3];

			posErr = deltaX[0]*deltaX[0]+deltaX[1]*deltaX[1]+deltaX[2]*deltaX[2];
			Times++;
		}while((Times<10)&&(posErr>0.0001));
		//RAIM计算
		for(i=0;i<epochLeast->Dim;i++)
		{
			for(j=0;j<4;j++)
				epochLeast->v[i]+=epochLeast->A[i*4+j]*deltaX[j];
			epochLeast->range_err[i]-=epochLeast->v[i];
		}
		FaultSat = RaimWork(epoch,epochLeast);
		if((FaultSat<64)&&(epochLeast->Dim>4))
		{
			Times = 0;
		    epoch->bias = 0;
			memset(&epoch->initPVT,0,sizeof(BD2_PVT));
			epochLeast->RaimInd|=(1<<(FaultSat-1));
		}
		else
			break;

	}

	if((posErr>2)||(Times==10))
	{
		return ERROR_POS_INVALID;
	}
	epoch->NumUse = epochLeast->Dim;
	epoch->initPVT.nUsedSat = epochLeast->Dim;
	
	if(epochLeast->Dim>4)
	{
		Sigma0=sqrt(epochLeast->VtV/(epochLeast->Dim-4));
		if(Sigma0< 26)
	 	{
			epoch->initPVT.error = Sigma0;
			Trans_XYZ_to_BLH(epoch->initPVT.xyz.x,epoch->initPVT.xyz.y,epoch->initPVT.xyz.z,&epoch->initPVT.blh.lat,&epoch->initPVT.blh.lon,&epoch->initPVT.blh.alt);
	 		epoch->initPVT.valid=1;
			
			if(!CalReceiverVeloc(epoch, epochLeast))
				epoch->initPVT.velOK = 0;
		}
		else
		{
			epoch->initPVT.valid=0;
			return 0;
		}
	}
	else
	{
		epoch->initPVT.valid = 0;
		return ERROR_SAT_LESS;
	}
	//计算DOP值
	if(CalDOPS(epoch, epochLeast) == 1)
		epoch->initPVT.Dop.valid = 1;
	// 保留计算结果
	if(epoch->initPVT.Dop.pdop > 20)// PDOP值过大
		epoch->initPVT.valid = 0;

	if(epoch->initPVT.valid)
		memcpy(&epoch->calcPVT, &epoch->initPVT, sizeof(BD2_PVT));
		
	return 1;
}

