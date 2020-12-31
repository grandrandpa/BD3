#pragma once
#include "DrawChartBar.h"

class CBarView;
// CShowSnrGPView

class CShowSnrGPView : public CBCGPDockingControlBar
{
	DECLARE_DYNAMIC(CShowSnrGPView)

public:
	CShowSnrGPView();
	virtual ~CShowSnrGPView();
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();


protected:
    CBarView*		m_pFormView;
    CCreateContext*     m_pContext;


private:
	BD2_GSV			m_packSNR[MAXFREQ];
	CBCGPTabWnd		m_wndTabs;
	/////////////////////////////
	CDrawChartBar		m_wndSnrB1;
	CDrawChartBar		m_wndSnrB2;
	CDrawChartBar		m_wndSnrB3;
	CDrawChartBar		m_wndSnrBs;
	DWORD				m_dwRecvFlag;
	double m_nCurrentTime;

public:
    void SetContext (CCreateContext* pContext)
	{
		m_pContext = pContext;
	}

	void RefreshView(NmeaAllData* data, int branch);
	void Reset(void);
	void Clear();
	void Clean();

};


