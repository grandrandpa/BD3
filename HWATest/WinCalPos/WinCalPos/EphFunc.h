#pragma once


//检查时间有效性
bool CalEphValid(BD2_OBSTIME* time, unsigned short week,double tow);
// 根据卫星星历和时间，计算卫星坐标和速度
HWA_POS_API bool CalculateSatPos(BD2_EPH eph, BD2_OBSTIME time, BD2_SAT_POS* pResult,double R);
bool CalculateBD1SatPos(BD2_EPH eph,double Sec, BD2_SAT_POS* pResult);
bool CalculateBD2SatPos(BD2_EPH eph,double Sec, BD2_SAT_POS* pResult);

// 计算卫星在用户坐标系中的方位角和高度角
void CalculateSatAZEL(BD2_SAT_POS* sat_pos, BD2_PVT userPVT, BD2_SAT_AZEL* sat_azel);

