#pragma once
#include "HWATestView.h"
#include "DrawLineWnd.h"


// CDrawRanView view

class CDrawRanView : public CHWATestView
{
	DECLARE_DYNCREATE(CDrawRanView)

public:
	CDrawRanView();           // protected constructor used by dynamic creation
	virtual ~CDrawRanView();

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
	afx_msg void OnChangeLineType();
	virtual void OnUpdateAllViews(CGlobalVariant* data, int type);
	afx_msg void OnClickLock();
	afx_msg void OnUpdateLock(CCmdUI* pCmdUI);
private:
	int m_nBranch;
	int m_nRanType;
	CDrawLineWnd	m_wndChart[3];
public:
	virtual void Clear();
	bool m_bLock;
};


