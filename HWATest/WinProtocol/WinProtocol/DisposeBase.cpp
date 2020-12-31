#include "StdAfx.h"
#include "DisposeBase.h"


CDisposeBase::CDisposeBase()
{
	Reset();
	m_nlines = 0;
	ZeroMemory(&m_SvIdErr, sizeof(m_SvIdErr));
	ZeroMemory(&m_packSKY, sizeof(m_packSKY));
	ZeroMemory(&m_packGSV, sizeof(m_packGSV));
}

CDisposeBase::~CDisposeBase()
{
	Reset();
	m_nlines = 0;
	ZeroMemory(&m_SvIdErr, sizeof(m_SvIdErr));
	ZeroMemory(&m_packSKY, sizeof(m_packSKY));
	ZeroMemory(&m_packGSV, sizeof(m_packGSV));
}

void CDisposeBase::Reset()
{
	m_chLen = 0;
	m_nFrame = 0;
	m_CmdState = RECV_CMD_START;
	ZeroMemory(&m_chBuffer, sizeof(m_chBuffer));
}
