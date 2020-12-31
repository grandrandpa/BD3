#include "StdAfx.h"
#include "EmulatorListener.h"

CEmulatorListener::CEmulatorListener(void)
{
}

CEmulatorListener::~CEmulatorListener(void)
{
}

LRESULT CEmulatorListener::OnEmulatorSetupMOD(WPARAM wParam, LPARAM lParam)
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