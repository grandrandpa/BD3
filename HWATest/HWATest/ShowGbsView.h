#pragma once
#include "HWATestView.h"


// CShowGbsView view

class CShowGbsView : public CHWATestView
{
	DECLARE_DYNCREATE(CShowGbsView)

protected:
	CShowGbsView();           // protected constructor used by dynamic creation
	virtual ~CShowGbsView();

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
private:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	afx_msg void OnClear();
	afx_msg void OnUpdateClear(CCmdUI* pCmdUI);
	void RefreshView(BD2_GBS* gbs);
public:
	virtual void OnUpdateAllViews(CGlobalVariant* data, int type);
	virtual void Clear();

	bool m_bLock;
	afx_msg void OnLockView();
	afx_msg void OnUpdateLockView(CCmdUI* pCmdUI);
};


