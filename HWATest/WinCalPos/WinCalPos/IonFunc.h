#pragma once

//电离层参数修正伪距的修正量
double CalculateIono(BD2_OBSTIME time, BD2_PVT* initPos, BD2_SAT_INFO* satInfo, BD2_ION* Iono,char PosMode);
double CalculateBD1Iono(BD2_OBSTIME time, BD2_USER_BLH Pos, BD2_SAT_AZEL Azel, BD2_ION* Iono);
double CalculateBD3Iono(BD2_OBSTIME time, BD2_USER_BLH Pos, BD2_SAT_AZEL Azel, BD2_ION* Iono);

double CalculateBD2Iono(BD2_OBSTIME time,double Freq, BD2_USER_XYZ UPos, BD2_SAT_POS SatPos,BD2_ION* Iono);

double CalculateTrop(double Elv, double Hgt);
void MeteorologicExt(double Hgt, double  *StationTemperature, double *StationPressure,  double *StationES );


