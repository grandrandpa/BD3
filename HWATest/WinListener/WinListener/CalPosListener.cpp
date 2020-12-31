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
LRESULT CCalPosListener::OnAnswerCalPositionPOS(WPARAM wParam, LPARAM lParam)//�ѿ������궨λ�����ٽ����Ϣ
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
LRESULT CCalPosListener::OnAnswerCalPositionEPH(WPARAM wParam, LPARAM lParam)//����������Ϣ
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
LRESULT CCalPosListener::OnAnswerCalPositionION(WPARAM wParam, LPARAM lParam)//���ǵ�������
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
LRESULT CCalPosListener::OnAnswerCalPositionALM(WPARAM wParam, LPARAM lParam)//����������Ϣ
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
LRESULT CCalPosListener::OnAnswerCalPositionJAL(WPARAM wParam, LPARAM lParam)//���Ǽ�Լ������Ϣ
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
LRESULT CCalPosListener::OnAnswerCalPositionRAN(WPARAM wParam, LPARAM lParam)//α�ࡢ�ز�����������Ϣ
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