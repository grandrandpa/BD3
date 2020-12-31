/*--------------------------------------------------------------------------------------
���� MatrixFun.c 
���ܣ���������ģ��ʵ���ļ�
--------------------------------------------------------------------------------------*/
#include "stdafx.h"
#include <math.h>
#include "MatrixFun.h"

//--------------------------------------------------------------------------------------
// ����: ��ά������� C = A * B
// ����: 
// [IN] A, B		�������ָ��
// [IN] RowA, ColA	A���������������
// [IN]	ColB		B���������
// [OUT]C			�������ָ��
// ����: ��
void MatrixMulti(double A[],double B[],double C[], int RowA, int ColA, int ColB)
{
	// CDH��ȥ�������CC
	int	i, j, k;

	//double* CC;
	//CC = (double *)malloc( sizeof(double) * RowA * ColB );

	for( i=0; i<RowA; i++ )
	{
		for( j=0; j<ColB; j++ )
		{
			C[i * ColB + j] = 0.0;
			for( k=0; k<ColA; k++ )  C[i * ColB + j] += A[i * ColA + k] * B[k * ColB + j];
		}
	}

	//for( i=0; i<RowA; i++ )
	//	for( j=0; j<ColB; j++ )
	//		C[i * ColB + j] = CC[i * ColB + j];

	//free(CC);
}


//--------------------------------------------------------------------------------------
// ����: �Գ�������������
// ����: 
// [IN] A		�������ָ��
// [IN] n		����ά��
// [OUT]A		����󣬻Ὣԭ������󸲸�
// ����: ��
int MatrixInv( double A[], int n )
{
	int i,j;
	int m_nRow;
	int iRow;			
	int k = 0;
	int loop,loop1,loop2;
	double 	dBuf;
	double adInvValue[8][8]; 
	double m_adValue[8][8];	

	// ����ֵ
	m_nRow=n;
	// ��������	
	for(loop=0;loop<n;loop++)
	{
		for(loop1=0;loop1<n;loop1++)
		{
			m_adValue[loop][loop1] = A[k];
			k++;
		}
	}
	for(loop=0;loop<m_nRow;loop++)
		for(loop1=0;loop1<m_nRow;loop1++)
			adInvValue[loop][loop1]=0.0;

	for(loop=0;loop<m_nRow;loop++)
		adInvValue[loop][loop]=1.0;

	for(loop=0;loop<m_nRow;loop++){
		iRow=loop;
		dBuf=fabs(m_adValue[loop][loop]);
		for(loop1=loop+1;loop1<m_nRow;loop1++){
			if(dBuf<fabs(m_adValue[loop1][loop])){
				dBuf=fabs(m_adValue[loop1][loop]);
				iRow=loop1;
			}
		}
		if(dBuf==0.0)
		{	
			return 0;   //�������
		}

		for(loop1=loop;loop1<m_nRow;loop1++){
			dBuf=m_adValue[loop][loop1];
			m_adValue[loop][loop1]=m_adValue[iRow][loop1];
			m_adValue[iRow][loop1]=dBuf;
		}
		for(loop1=0;loop1<m_nRow;loop1++){
			dBuf=adInvValue[loop][loop1];
			adInvValue[loop][loop1]=adInvValue[iRow][loop1];
			adInvValue[iRow][loop1]=dBuf;
		}
		for(loop1=loop+1;loop1<m_nRow;loop1++){
			m_adValue[loop][loop1]/=m_adValue[loop][loop];
		}
		for(loop1=0;loop1<m_nRow;loop1++){
			adInvValue[loop][loop1]/=m_adValue[loop][loop];
		}

		for(loop1=loop+1;loop1<m_nRow;loop1++){
			for(loop2=loop+1;loop2<m_nRow;loop2++)
				m_adValue[loop1][loop2]-=m_adValue[loop1][loop]*m_adValue[loop][loop2];
			for(loop2=0;loop2<m_nRow;loop2++)
				adInvValue[loop1][loop2]-=m_adValue[loop1][loop]*adInvValue[loop][loop2];
		}
	}

	for(loop=m_nRow-1;loop>=0;loop--){
		for(loop1=loop-1;loop1>=0;loop1--){
			for(loop2=0;loop2<m_nRow;loop2++)
				adInvValue[loop1][loop2]-=m_adValue[loop1][loop]*adInvValue[loop][loop2];
		}
	}

	for(loop=0;loop<m_nRow;loop++)
		for(loop1=0;loop1<m_nRow;loop1++)
			m_adValue[loop][loop1]=adInvValue[loop][loop1];

	// ����ָ�
	k = 0;
	for(i=0;i<m_nRow;i++)
	{
		for(j=0;j<m_nRow;j++)
		{
			A[k] = m_adValue[i][j];
			k++;
		}
	}	
	return 1; // ����
}



//--------------------------------------------------------------------------------------
// ����: һ�����������һ�����ת���� c = A(m*n)*BT(k*n)
// ����: 
// [IN] A, B		�������ָ��
// [IN] RowA, ColA	A���������������
// [IN]	ColB		B���������
// [OUT]ABT			�������ָ��
// ����: ��
void MatrixABT(double A[], double B[], double ABT[], int RowA, int ColA, int RowB)
{
	// CDH��ȥ�������Temp
	int	i, j, l;
	double  ab;
	//, *Temp;
	//Temp = (double *)malloc(sizeof(double) * RowA * RowB);

	for (i=0; i<RowA; i++)
	{
		for (j=0; j<RowB; j++)
		{
			ab = 0.;
			for (l=0; l<ColA; l++)
				ab += A[i * ColA + l] * B[j * ColA + l];
			ABT[i * RowB + j] = ab;
		}
	}

	/*for (i=0; i<RowA; i++)
		for (j=0; j<RowB; j++)
			ABT[i * RowB + j] = Temp[i * RowB + j];

	free( Temp );*/
}


//--------------------------------------------------------------------------------------
// ����: һ�������ת�ó�����һ����   c = AT(n*m)*B(n*k)
// ����: 
// [IN] A, B		�������ָ��
// [IN] RowA, ColA	A���������������
// [IN]	ColB		B���������
// [OUT]ATB			�������ָ��
// ����: ��
void MatrixATB(double A[], double B[], double ATB[], int RowA, int ColA, int ColB)
{
	// CDH��ȥ�������Temp
	int	i, j, l;
	double  ab;
	//, *Temp;
	// Temp = (double *)malloc(sizeof(double) * ColA * ColB);

	for (i=0; i<ColA; i++)
	{
		for (j=0; j<ColB; j++)
		{
			ab = 0.;
			for (l=0; l<RowA; l++)
				ab += A[l * ColA + i] * B[l * ColB + j];
			ATB[i * ColB + j] = ab;
		}
	}

	/*for (i=0; i<ColA; i++)
		for (j=0; j<ColB; j++)
			ATB[i * ColB + j] = Temp[i * ColB + j];

	free( Temp );*/
}


//--------------------------------------------------------------------------------------
// ����: �������	N = A*P*AT, ����, A(r*n), P(n*n)
// ����: 
// [IN] A, P		�������ָ��
// [IN] RowA, ColA	A���������������
// [OUT]APAT			�������ָ��
// ����: ��
void MatrixAPAT( double A[], double P[], double APAT[], int RowA, int ColA)
{
	// CDH��ȥ�������Temp
	int	i, j, k, l;
	double  paa;
	//, *Temp = NULL;
	// Temp = (double *)malloc(sizeof(double) * RowA * RowA);

	for (i=0; i<RowA; i++)
	{
		for (j=0; j<i+1; j++)
		{
			paa = 0.;
			for (k=0; k<ColA; k++)
				for (l=0; l<ColA; l++)
					paa += A[i * ColA + k] * P[k * ColA + l] * A[j * ColA + l];

			APAT[i * RowA + j] = paa;
		}
	}

	//����ȷ�������ǶԳƵ�
	for (i=0; i<RowA-1; i++)
		for (j=i+1; j<RowA; j++)
			APAT[i * RowA + j] = APAT[j * RowA + i];

	/*for (i=0; i<RowA; i++)
		for (j=0; j<RowA; j++)
			APAT[i * RowA + j] = Temp[i * RowA + j];

	free(Temp);*/

}


//--------------------------------------------------------------------------------------
// ����: �������	N = AT*P*A, ����, A(r*n), P(n*n)
// ����: 
// [IN] A, P		�������ָ��
// [IN] RowA, ColA	A���������������
// [OUT]ATPA			�������ָ��
// ����: ��
void MatrixATPA( double A[], double P[], double ATPA[], int RowA, int ColA)
{
	// ȥ�������Temp
	int	i, j, k, l;
	double  paa;
	//, *Temp = NULL;
	//Temp = (double *)malloc(sizeof(double) * ColA * ColA);

	for (i=0; i<ColA; i++)
	{
		for (j=0; j<i+1; j++)
		{
			paa = 0.;
			for (k=0; k<RowA; k++)
				for (l=0; l<RowA; l++)
					paa += A[k * ColA + i] * P[k * RowA + l] * A[l * ColA +j];

			ATPA[i * ColA + j] = paa;
		}
	}

	//����ȷ�������ǶԳƵ�
	for (i=0; i<ColA-1; i++)
		for (j=i+1; j<ColA; j++)
			ATPA[i * ColA + j] = ATPA[j * ColA + i];

	/*for (i=0; i<ColA; i++)
		for (j=0; j<ColA; j++)
			ATPA[i * ColA + j] = Temp[i * ColA + j];

	free(Temp);*/
}


//--------------------------------------------------------------------------------------
// ����: �������	N = AT*P*A, ����, A(n*r), P(n*1)
// ����: 
// [IN] A, P		�������ָ�룬P�ǶԽ�Ԫ�ؾ���
// [IN] RowA, ColA	A���������������
// [OUT]ATPA			�������ָ��
// ����: ��
void MatrixAtPA( double A[], double P[], double ATPA[], int RowA, int ColA)
{
	int	i, j, k;

	for (i=0; i<ColA; i++)
	{
		for (j=0; j<ColA; j++)
		{
			ATPA[i * ColA + j] = 0.;
			for (k=0; k<RowA; k++)
				ATPA[i * ColA + j] += A[k * ColA + i] * P[k] * A[k * ColA +j];
		}
	}
}


//--------------------------------------------------------------------------------------
// ����: ������� U = AT*P*L,  ����, A(n*r), P(n*n), L(n*1)
// ����: 
// [IN] A, P, L		�������ָ��
// [IN] RowA, ColA	A���������������
// [OUT]ATPL			�������ָ��
// ����: ��
void MatrixATPL( double A[], double P[], double L[], double ATPL[], int RowA, int ColA)
{
	int	i, j, l;
	double  ab;

	for (i=0; i<ColA; i++)
	{
		ATPL[i] = 0.0;//
		for (j=0; j<RowA; j++)
		{
			ab = 0.;
			for (l=0; l<RowA; l++)
				ab += A[j * ColA + i] * P[l * RowA + j];

			ATPL[i] += ab * L[j];//
		}
	}
}


//--------------------------------------------------------------------------------------
// ����: ������� U = AT*P*L,  ����, A(n*r), P(n*1), L(n*1)
// ����: 
// [IN] A, P, L		�������ָ�룬P�ǶԽ�Ԫ�ؾ���
// [IN] RowA, ColA	A���������������
// [OUT]ATPL			�������ָ��
// ����: ��
void MatrixAtPL( double A[], double P[], double L[], double ATPL[], int RowA, int ColA)
{
	int	i, j;

	for (i=0; i<ColA; i++)
	{
		ATPL[i] = 0.0;//
		for (j=0; j<RowA; j++)
			ATPL[i] += A[j * ColA + i] * P[j] * L[j];
	}
}




//--------------------------------------------------------------------------------------
// ����: ��ά����ӷ� C = A + B
// ����: 
// [IN] A, B		�������ָ��
// [IN] m, n		AB���������������
// [OUT]C			�������ָ��
// ����: ��
void MatrixPlus(double A[], double B[], double C[], int m, int n)
{
	int	i, j;
	for (i = 0; i < m; i ++)
		for (j = 0; j < n; j ++)
			C[i * n + j] = A[i * n + j] + B[i * n + j];
}


//--------------------------------------------------------------------------------------
// ����: ��ά������� C = A - B
// ����: 
// [IN] A, B		�������ָ��
// [IN] Row, Col	AB���������������
// [OUT]C			�������ָ��
// ����: ��
void MatrixSub(double A[], double B[], double C[], int Row, int Col)
{
	int i, j;
	for (i=0; i<Row; i++)
		for (j=0; j<Col; j++)
			C[i * Col + j] = A[i * Col + j] - B[i * Col + j];
}

//--------------------------------------------------------------------------------------
// ����: �����ڻ�	N = VT*P*V, ����, V(m*1), P(m*m)
// ����: 
// [IN] V, P	���������;���ָ��
// [IN] m		������ά��
// ����: ��
double MatrixVTPV(double V[],double P[],int m)
{
	int i, j;
	double pvv = 0;

	for (i=0; i<m; i++)
		pvv += V[i] * V[i] * P[i * m + i]; 

	for (i=0; i<m; i++)
		for (j=0; j<m; j++)
			pvv += 2 * V[i] * V[j] * P[i * m + j];

	return pvv;
}
//-------------------------------------------------------------------------------
