

/*--------------------------------------------------------------------------------------
名称 MatrixFun.h 
功能：矩阵运算模块头文件
--------------------------------------------------------------------------------------*/

#ifndef  MATRIXFUN_H__
#define  MATRIXFUN_H__

//------------------------------矩阵运算函数-------------------------------------------------

// 功能: 二维矩阵相乘 C = A * B
void MatrixMulti(double A[], double B[], double C[], int RowA, int ColA, int ColB);

// 功能: 对称正定矩阵求逆
int MatrixInv(double A[], int n);

// 功能: 一个矩阵乘以另一矩阵的转置阵 c = A(m*n)*BT(k*n)
void MatrixABT(double A[], double B[], double ABT[], int RowA, int ColA, int RowB);

// 功能: 一个矩阵的转置乘以另一矩阵   c = AT(n*m)*B(n*k)
void MatrixATB(double A[], double B[], double ATB[], int RowA, int ColA, int ColB);

// 功能: 矩阵相乘	N = A*P*AT, 其中, A(r*n), P(n*n)
void MatrixAPAT( double A[], double P[], double APAT[], int RowA, int ColA);

// 功能: 矩阵相乘	N = AT*P*A, 其中, A(r*n), P(n*n)
void MatrixATPA( double A[], double P[], double ATPA[], int RowA, int ColA);

// 功能: 矩阵相乘	N = AT*P*A, 其中, A(n*r), P(n*1)
void MatrixAtPA( double A[], double P[], double ATPA[], int RowA, int ColA); //P[n*1]仅是对角线元素

// 功能: 计算矩阵 U = AT*P*L,  其中, A(n*r), P(n*n), L(n*1)
void MatrixATPL( double A[], double P[], double L[], double ATPL[], int RowA, int ColA);

// 功能: 计算矩阵 U = AT*P*L,  其中, A(n*r), P(n*1), L(n*1)
void MatrixAtPL( double A[], double P[], double L[], double ATPL[], int RowA, int ColA); //P[n*1]仅是对角线元素

// 功能: 二维矩阵加法 C = A + B
void MatrixPlus(double A[], double B[], double C[], int m, int n);

// 功能: 二维矩阵减法 C = A - B
void MatrixSub(double A[], double B[], double C[], int Row, int Col);

// 功能: 向量内积	N = VT*P*V, 其中, V(m*1), P(m*m)
double MatrixVTPV(double V[],double P[],int m);

// The following function was added by cdh 2007.07.02

// 功能: 向量内积	N = VT*V, 其中, V(m*1)
double MatrixVTV(double V[],int m);

// 功能: 向量乘向量的转置	N = V*VT(m*m), 其中, V(m*1)
void MatrixVVT(double V[],double N[],int m);

// 功能: 设置对角矩阵  A = [D], 其中A(m*m), D(1*m)
void MatrixSetDiag(double A[],double D[],int m);

// 功能: 插入矩阵  A = [D], 其中A(m1*n1), D(m2*n2), m1-row>m2, n1-col>n2
int MatrixInsert(double A[],double D[],int m1,int n1,int m2,int n2,int row, int col);

// 功能: 求方阵的迹  tr[A] 其中A(m*m)：方阵
double MatrixTrace(double A[],int m);

// 功能: 矩量乘以常数	A = k*A, 其中, A(m*n)
void MatrixAmplify(double A[],double k,int m, int n);

#endif
