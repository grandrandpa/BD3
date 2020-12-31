#include "StdAfx.h"
#include "CalPosListener.h"

CCalPosListener::CCalPosListener(void)
{
	m_hListeners.RemoveAll();
	m_iListeners.RemoveAll();
}

CCalPosListener::~CCalPosListener(void)
{
	m_hListeners.RemoveAll();
	m_iListeners.RemoveAll();
}
LRESULT CCalPosListener::OnAnswerCalPositionMOD(WPARAM wParam, LPARAM lParam)
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_POSITION_MOD, wParam,lParam );
	}
	count = m_iListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		m_iListeners[i]->OnAnswerCalPositionMOD( wParam,lParam );
	}

	return true; 
}
LRESULT CCalPosListener::OnAnswerCalPositionPOS(WPARAM wParam, LPARAM lParam)//笛卡尔坐标定位、测速结果信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_POSITION_POS, wParam,lParam );
	}
	count = m_iListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		m_iListeners[i]->OnAnswerCalPositionPOS( wParam,lParam );
	}

	return true; 
}
LRESULT CCalPosListener::OnAnswerCalPositionEPH(WPARAM wParam, LPARAM lParam)//卫星星历信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_POSITION_EPH, wParam,lParam );
	}
	count = m_iListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		m_iListeners[i]->OnAnswerCalPositionEPH( wParam,lParam );
	}

	return true; 
}
LRESULT CCalPosListener::OnAnswerCalPositionION(WPARAM wParam, LPARAM lParam)//卫星电离层参数
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_POSITION_ION, wParam,lParam );
	}
	count = m_iListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		m_iListeners[i]->OnAnswerCalPositionION( wParam,lParam );
	}

	return true; 
}
LRESULT CCalPosListener::OnAnswerCalPositionALM(WPARAM wParam, LPARAM lParam)//卫星历书信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_POSITION_ALM, wParam,lParam );
	}
	count = m_iListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		m_iListeners[i]->OnAnswerCalPositionALM( wParam,lParam );
	}

	return true; 
}
LRESULT CCalPosListener::OnAnswerCalPositionJAL(WPARAM wParam, LPARAM lParam)//卫星简约历书信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_POSITION_JAL, wParam,lParam );
	}
	count = m_iListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		m_iListeners[i]->OnAnswerCalPositionJAL( wParam,lParam );
	}

	return true; 
}
LRESULT CCalPosListener::OnAnswerCalPositionRAN(WPARAM wParam, LPARAM lParam)//伪距、载波、多普勒信息
{
	int count = m_hListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		::SendMessage( m_hListeners[i], MSG_ANSWER_POSITION_RAN, wParam,lParam );
	}
	count = m_iListeners.GetCount();
	for ( int i = 0; i < count; ++i )
	{
		m_iListeners[i]->OnAnswerCalPositionRAN( wParam,lParam );
	}

	return true; 
}