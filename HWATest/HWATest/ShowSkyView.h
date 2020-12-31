#pragma once
#include "DrawSkyWnd.h"

// CShowSkyView

class RadarPointView;

class CShowSkyView : public CBCGPDockingControlBar
{
	DECLARE_DYNAMIC(CShowSkyView)

public:
	CShowSkyView();
	virtual ~CShowSkyView();
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void RefreshView(NmeaAllData* data);
	void Reset(void);
	void Clear();
	afx_msg void OnPaint();

    void SetContext (CCreateContext* pContext)
	{
		m_pContext = pContext;
	}

    //void DealData(NmeaAllData* data);

protected:
	//CDrawSkyWnd*		m_pDawSky;
    RadarPointView*		m_pFormView;
    CCreateContext*     m_pContext;

    CStatic m_StaticText;
};


