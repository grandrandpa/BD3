#pragma once
#include "HWATestView.h"
#include "DrawLineWnd.h"

// CDrawPosView view

class CDrawPosView : public CHWATestView
{
	DECLARE_DYNCREATE(CDrawPosView)

public:
	CDrawPosView();           // protected constructor used by dynamic creation
	virtual ~CDrawPosView();

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
	virtual void OnUpdateAllViews(CGlobalVariant* data, int type);
	afx_msg void OnClickLock();
	afx_msg void OnUpdateLock(CCmdUI* pCmdUI);
private:
	int m_nPosType;
	CDrawLineWnd	m_wndChart[6];
public:
	virtual void Clear();
	bool m_bLock;
};


