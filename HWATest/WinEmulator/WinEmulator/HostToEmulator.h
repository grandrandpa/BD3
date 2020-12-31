#pragma once
#include "WinStruct.h"
#include "WinListener.h"
#include "SerialPort.h"
#include "EmulatorListener.h"

class CHostToEmulator : public CSerialPort
{
public:
	CHostToEmulator(void);
	~CHostToEmulator(void);
private:
	int m_nProtocol;
	bool m_bLinkStatus;
	CEmulatorListener m_Listener;
protected:
	virtual void CompleteRecData(char* buf, int len);
	virtual void Reset();
public:
	CEmulatorListener*	GetListener(){return &m_Listener; }
	bool Open(int Port, DWORD dwRate, int protocol);//×¢²áÊµÀý
	void Close();
	bool GetStatus();
};
