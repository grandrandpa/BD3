#pragma once


//���ʱ����Ч��
bool CalEphValid(BD2_OBSTIME* time, unsigned short week,double tow);
// ��������������ʱ�䣬��������������ٶ�
HWA_POS_API bool CalculateSatPos(BD2_EPH eph, BD2_OBSTIME time, BD2_SAT_POS* pResult,double R);
bool CalculateBD1SatPos(BD2_EPH eph,double Sec, BD2_SAT_POS* pResult);
bool CalculateBD2SatPos(BD2_EPH eph,double Sec, BD2_SAT_POS* pResult);

// �����������û�����ϵ�еķ�λ�Ǻ͸߶Ƚ�
void CalculateSatAZEL(BD2_SAT_POS* sat_pos, BD2_PVT userPVT, BD2_SAT_AZEL* sat_azel);

