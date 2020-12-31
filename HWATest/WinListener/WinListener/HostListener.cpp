#include "StdAfx.h"
#include "HostListener.h"

CHostListener::CHostListener(void)
{
	m_hListeners.RemoveAll();
	m_iListeners.RemoveAll();
}

CHostListener::~CHostListener(void)
{
	m_hListeners.RemoveAll();
	m_iListeners.RemoveAll();
}

LRESULT CHostListener::OnAnswerInfoCOD(WPARAM wParam, LPARAM lParam)//卫星原始导航电文
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_COD, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoCOD( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoEPH(WPARAM wParam, LPARAM lParam)//卫星星历信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_EPH, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoEPH( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoION(WPARAM wParam, LPARAM lParam)//卫星电离层参数
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_ION, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoION( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoALM(WPARAM wParam, LPARAM lParam)//卫星历书信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_ALM, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoALM( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoJAL(WPARAM wParam, LPARAM lParam)//卫星简约历书信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_JAL, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoJAL( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoCOM(WPARAM wParam, LPARAM lParam)//端口速率信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_COM, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoCOM( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoMOD(WPARAM wParam, LPARAM lParam)//定位授时模式信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_MOD, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoMOD( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoPOS(WPARAM wParam, LPARAM lParam)//定位、测速结果信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_POS, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoPOS( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoRAN(WPARAM wParam, LPARAM lParam)//伪距、载波、多普勒信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_RAN, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoRAN( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoREF(WPARAM wParam, LPARAM lParam)//时空参考信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_REF, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoREF( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoGSV(WPARAM wParam, LPARAM lParam)//卫星信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_SIV, wParam,lParam );
	}
	for ( UINT i = 0; i < count; ++i )
	{
		m_iListeners[i]->OnAnswerInfoGSV( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoPAO(WPARAM wParam, LPARAM lParam)//电文页面播发顺序和历书播发顺序
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_TEST, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoPAO( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoCHD(WPARAM wParam, LPARAM lParam)//信道译码信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_CHD, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoCHD( wParam,lParam );
	}

	return true; 
}



LRESULT CHostListener::OnAnswerInfoSTA(WPARAM wParam, LPARAM lParam)//终端工作状态信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_STA, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoSTA( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoTIM(WPARAM wParam, LPARAM lParam)//授时结果信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_TIM, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoTIM( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoXPV(WPARAM wParam, LPARAM lParam)//笛卡尔坐标定位、测速结果信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_XPV, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoXPV( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoSRC(WPARAM wParam, LPARAM lParam)//原始数据
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_SRC, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoSRC( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoSNR(WPARAM wParam, LPARAM lParam)//原始数据
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_SNR, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoSNR( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoSKY(WPARAM wParam, LPARAM lParam)//原始数据
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_SKY, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoSKY( wParam,lParam );
	}

	return true; 
}
LRESULT CHostListener::OnAnswerInfoGBS(WPARAM wParam, LPARAM lParam)//自主完好性
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_GBS, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoGBS( wParam,lParam );
	}

	return true;
}
LRESULT CHostListener::OnAnswerInfoFrame(WPARAM wParam, LPARAM lParam)//自主完好性
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_FRAME, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoGBS( wParam,lParam );
	}

	return true;
}
LRESULT CHostListener::OnAnswerInfoSIM(WPARAM wParam, LPARAM lParam)
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_SIM, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoSIM( wParam,lParam );
	}

	return true;
}
LRESULT CHostListener::OnAnswerInfoVER(WPARAM wParam, LPARAM lParam)
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_INFORMATION_VER, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnAnswerInfoVER( wParam,lParam );
	}

	return true;
}
//////////////////////////////////////////////////////////////////////////
LRESULT CHostListener::OnEmulatorSetupMOD(WPARAM wParam, LPARAM lParam)
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_EMULATOR_SETUP_MOD, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnEmulatorSetupMOD( wParam,lParam );
	}

	return true;
}
LRESULT CHostListener::OnEmulatorSetupLOG(WPARAM wParam, LPARAM lParam)
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_EMULATOR_SETUP_LOG, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnEmulatorSetupLOG( wParam,lParam );
	}

	return true;
}

LRESULT CHostListener::OnEmulatorSetupSTA(WPARAM wParam, LPARAM lParam)
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_EMULATOR_SETUP_STA, wParam,lParam );
	}
	for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	{
		m_iListeners[i]->OnEmulatorSetupSTA( wParam,lParam );
	}

	return true;
}

LRESULT CHostListener::OnShowCmdView(WPARAM wParam, LPARAM lParam)
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_SHOW_CMD_VIEW, wParam,lParam );
	}
	//for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	//{
	//	m_iListeners[i]->OnEmulatorSetupSTA( wParam,lParam );
	//}

	return true;
}

LRESULT CHostListener::OnUpdateGGAPOSView(WPARAM wParam, LPARAM lParam)
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_SHOW_GGA_POS_INFO, wParam,lParam );
	}
	//for ( UINT i = 0; i < m_iListeners.GetCount(); ++i )
	//{
	//	m_iListeners[i]->OnEmulatorSetupSTA( wParam,lParam );
	//}

	return true;
}