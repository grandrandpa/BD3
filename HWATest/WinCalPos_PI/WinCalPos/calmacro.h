#pragma once

#define CGS2000_A			(6378137.0)        // ����볤�ᣨ�ף�
#define CGS2000_F			(1/298.257222101)		// ������ʵĵ���
#define CGS2000_MIU			(3.986004418E+14)	// ����������������λ����^3/��^2
#define CGS2000_OMEGA_E		(7.2921150E-5)		// ������ת���ʣ���λ������/��

#define WGS84_A				(6378137.0)        // ����볤�ᣨ�ף�
#define WGS84_F				(1/298.257223563)		// ������ʵĵ���
#define WGS84_MIU			(3.986005E+14)		// ����������������λ����^3/��^2
#define WGS84_OMEGA_E		(7.2921151467E-5)		// ������ת���ʣ���λ������/��


//---------------------------------------------------------------------
// �궨�� 
//---------------------------------------------------------------------
// ���ش���ֵ����
#define ERROR_POS_SUCCESS		1//��λ
#define ERROR_MODE_FAIL			-1//��λģʽ����
#define ERROR_EPH_LAGGER		-2//��������
#define ERROR_EPH_HEL			-3//����������
#define ERROR_SAT_LESS			-4//����������4
#define ERROR_POS_INVALID		-5//��λ����Ч
#define ERROR_INIT_FAIL			-6//��ʼ������
#define ERROR_RAN_FAIL			-7//�������ݴ���
#define ERROR_MAT_SINGULAR		-8//A��������
#define ERROR_ELV_LESS			-9//����̫С



