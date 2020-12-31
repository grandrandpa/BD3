#pragma once
#include "BasicListener.hpp"
#include "CompListener.hpp"
#pragma warning(disable:4251)

#ifdef HWA_EMULATOR_EXPORTS
#define HWA_EMULATOR_API __declspec(dllexport)
#else
#define HWA_EMULATOR_API __declspec(dllimport)
#endif


class HWA_EMULATOR_API CEmulatorListener : public CompListener<CBasicListener>
{
public:
	CEmulatorListener(void);
	~CEmulatorListener(void);
public:
	virtual LRESULT OnEmulatorSetupMOD(WPARAM wParam, LPARAM lParam);
};
