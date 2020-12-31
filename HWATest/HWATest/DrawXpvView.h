#pragma once
#include "HWATestView.h"
#include "DrawLineWnd.h"


// CDrawXpvView view

class CDrawXpvView : public CHWATestView
{
	DECLARE_DYNCREATE(CDrawXpvView)

protected:
	CDrawXpvView();           // protected constructor used by dynamic creation
	virtual ~CDrawXpvView();

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	afx_msg void OnClickLock();
	afx_msg void OnUpdateLock(CCmdUI* pCmdUI);
	void Clear(void);
private:
	bool m_bLock;
	CDrawLineWnd	m_wndChart[6];
public:
	virtual void OnUpdateAllViews(CGlobalVariant* data, int type);
};


