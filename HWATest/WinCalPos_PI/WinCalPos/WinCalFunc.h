#pragma once

//�۲������
int ObsCheck(double PR);
// ���ݹ۲���������λ�ü���Ȩ��Ԫ��
void GetWeight(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast);
// ���ݹ۲���������λ�ù���A����
void MakeMatrixA(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast);
// RAIM����,�����������
UINT16 RaimWork(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast);

// ����DOPֵ
int CalDOPS(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast);
// �ڼ�������ջ�����������ջ��ٶ�
int CalReceiverVeloc(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast);
// RAIM��������ջ�����
int RaimLeastSquare(BD2_EPOCH* epoch, BD2_LS_EPOCH* epochLeast);
