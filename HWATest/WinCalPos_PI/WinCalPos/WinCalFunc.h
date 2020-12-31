#pragma once

//观测量检查
int ObsCheck(double PR);
// 根据观测量和卫星位置计算权阵元素
void GetWeight(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast);
// 根据观测量和卫星位置构造A矩阵
void MakeMatrixA(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast);
// RAIM计算,返回卫星序号
UINT16 RaimWork(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast);

// 计算DOP值
int CalDOPS(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast);
// 在计算出接收机坐标后计算接收机速度
int CalReceiverVeloc(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast);
// RAIM解算出接收机坐标
int RaimLeastSquare(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast);
