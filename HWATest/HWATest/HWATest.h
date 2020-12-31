// HWATest.h : main header file for the HWATest application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "WinStruct.h"
#include "WinEnum.h"
#include "calMacro.h"
#include "calstruct.h"
#include "CalPosListener.h"
#include "WinTools.h"
#include "WinLink.h"
#include "WinConfig.h"
#include "WinPlayer.h"
#include "WinStore.h"
#include "WinGlobal.h"
#include "WinPrint.h"
#include "WinCalPos.h"

#include "HWATestDoc.h"
#include "MainFrm.h"
#include "LoginDlg.h"

#include "ShowSrcView.h"
#include "ShowAlmView.h"
#include "ShowEphView.h"
#include "ShowIonView.h"
#include "ShowJalView.h"
#include "ShowPosView.h"
#include "ShowRanView.h"
#include "ShowTimView.h"
#include "ShowSkyView.h"
#include "ShowSnrView.h"
#include "ShowSivView.h"
#include "ShowGbsView.h"
#include "ShowXpvView.h"
#include "ShowVelView.h"
#include "ShowChaView.h"
#include "DrawPosView.h"
#include "DrawRanView.h"
#include "DrawTestView.h"
#include "ChDecodeView.h"
#include "ShowGgaPosView.h"

// CHWATestApp:
// See HWATest.cpp for the implementation of this class
//

inline double Rand (double dblStart, double dblFinish)
{
	double minVal = min(dblStart, dblFinish);
	double maxVal = max(dblStart, dblFinish);

	return (maxVal - minVal) * (double)rand() / (RAND_MAX + 1) + minVal;
}

class CHWATestApp : public CBCGPWinApp
{
public:
	CHWATestApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	virtual BOOL SaveAllModified();
	virtual void UpdateChartColorTheme(int nTheme);

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
protected:
	CBCGPChartTheme m_CustomColorTheme;
	CBCGPChartTheme m_CustomTexturedTheme;
private:
	void Reset();
	BOOL CreateDocTemplate();
public:
	void Clear();
	const CBCGPChartTheme& GetCustomTheme(int nTheme)
	{
		return nTheme == -2 ? m_CustomColorTheme : m_CustomTexturedTheme;
	}
public:
	CMultiDocTemplate* m_pSrcTemplate;
	CMultiDocTemplate* m_pAlmTemplate;
	CMultiDocTemplate* m_pEphTemplate;
	CMultiDocTemplate* m_pIonTemplate;
	CMultiDocTemplate* m_pJalTemplate;
	CMultiDocTemplate* m_pPosTemplate;
	CMultiDocTemplate* m_pRanTemplate;
	CMultiDocTemplate* m_pTimTemplate;
	CMultiDocTemplate* m_pSivTemplate;
	CMultiDocTemplate* m_pGbsTemplate;
	CMultiDocTemplate* m_pXpvTemplate;
	CMultiDocTemplate* m_pVelTemplate;
	CMultiDocTemplate* m_pChaTemplate;
	CMultiDocTemplate* m_pDrawPosTemplate;
	CMultiDocTemplate* m_pDrawRanTemplate;
	CMultiDocTemplate* m_pPAOrderTemplate;
	CMultiDocTemplate* m_pChDecodeTemplate;

    CMultiDocTemplate* m_pGgaPosTemplate;
public:
	int m_nProjectType;
	CString m_strProjPath;
	CString m_strProjName;
	CString m_strProjFile;
	CString m_strDatabase;
	CString	m_strSaveData;
	CString m_strOriginData;
	CString m_strPictures;
	CString m_strConfigPath;
	int m_nProtocol;
	bool m_bConnectFlag;
	int m_nConnectType;
	CString m_strSatPath;
public:
	BD2_USER_BLH m_CurPosition;
	bool m_bStaticMeasure;
	CWinLinkApp		m_winLinkApp;
	CWinLinkApp		m_LinkTestApp;
	CWinPlayerApp	m_winPlayerApp;
	//CWinStoreApp	m_winStoreApp;
	CWinPrintApp	m_winPrintApp;
	CWinCalPosApp	m_winCalPosApp;
};

extern CHWATestApp theApp;
void InitSeriesColors(BCGPSeriesColors& sc, const CBCGPColor& color, UINT nTextureResID = 0);

