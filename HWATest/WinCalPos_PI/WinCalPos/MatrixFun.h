

/*--------------------------------------------------------------------------------------
���� MatrixFun.h 
���ܣ���������ģ��ͷ�ļ�
--------------------------------------------------------------------------------------*/

#ifndef  MATRIXFUN_H__
#define  MATRIXFUN_H__

//------------------------------�������㺯��-------------------------------------------------

// ����: ��ά������� C = A * B
void MatrixMulti(double A[], double B[], double C[], int RowA, int ColA, int ColB);

// ����: �Գ�������������
int MatrixInv(double A[], int n);

// ����: һ�����������һ�����ת���� c = A(m*n)*BT(k*n)
void MatrixABT(double A[], double B[], double ABT[], int RowA, int ColA, int RowB);

// ����: һ�������ת�ó�����һ����   c = AT(n*m)*B(n*k)
void MatrixATB(double A[], double B[], double ATB[], int RowA, int ColA, int ColB);

// ����: �������	N = A*P*AT, ����, A(r*n), P(n*n)
void MatrixAPAT( double A[], double P[], double APAT[], int RowA, int ColA);

// ����: �������	N = AT*P*A, ����, A(r*n), P(n*n)
void MatrixATPA( double A[], double P[], double ATPA[], int RowA, int ColA);

// ����: �������	N = AT*P*A, ����, A(n*r), P(n*1)
void MatrixAtPA( double A[], double P[], double ATPA[], int RowA, int ColA); //P[n*1]���ǶԽ���Ԫ��

// ����: ������� U = AT*P*L,  ����, A(n*r), P(n*n), L(n*1)
void MatrixATPL( double A[], double P[], double L[], double ATPL[], int RowA, int ColA);

// ����: ������� U = AT*P*L,  ����, A(n*r), P(n*1), L(n*1)
void MatrixAtPL( double A[], double P[], double L[], double ATPL[], int RowA, int ColA); //P[n*1]���ǶԽ���Ԫ��

// ����: ��ά����ӷ� C = A + B
void MatrixPlus(double A[], double B[], double C[], int m, int n);

// ����: ��ά������� C = A - B
void MatrixSub(double A[], double B[], double C[], int Row, int Col);

// ����: �����ڻ�	N = VT*P*V, ����, V(m*1), P(m*m)
double MatrixVTPV(double V[],double P[],int m);

// The following function was added by cdh 2007.07.02

// ����: �����ڻ�	N = VT*V, ����, V(m*1)
double MatrixVTV(double V[],int m);

// ����: ������������ת��	N = V*VT(m*m), ����, V(m*1)
void MatrixVVT(double V[],double N[],int m);

// ����: ���öԽǾ���  A = [D], ����A(m*m), D(1*m)
void MatrixSetDiag(double A[],double D[],int m);

// ����: �������  A = [D], ����A(m1*n1), D(m2*n2), m1-row>m2, n1-col>n2
int MatrixInsert(double A[],double D[],int m1,int n1,int m2,int n2,int row, int col);

// ����: ����ļ�  tr[A] ����A(m*m)������
double MatrixTrace(double A[],int m);

// ����: �������Գ���	A = k*A, ����, A(m*n)
void MatrixAmplify(double A[],double k,int m, int n);

#endif
