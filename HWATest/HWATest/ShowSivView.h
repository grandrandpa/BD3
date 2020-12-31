#pragma once
#include "HWATestView.h"


// CShowSivView view

class CShowSivView : public CHWATestView
{
	DECLARE_DYNCREATE(CShowSivView)

public:
	CShowSivView();           // protected constructor used by dynamic creation
	virtual ~CShowSivView();

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
	afx_msg void OnChangeBranch();
	afx_msg void OnClearView();
	afx_msg void OnUpdateClearView(CCmdUI* pCmdUI);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	virtual void OnUpdateAllViews(CGlobalVariant* data, int type);
	virtual void Clear();
	int m_nBranch;
	void RefreshView(BD2_GSV* data);

	bool m_bLock;
	afx_msg void OnLockView();
	afx_msg void OnUpdateLockView(CCmdUI* pCmdUI);
};


