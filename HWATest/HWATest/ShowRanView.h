#pragma once
#include "HWATestView.h"


// CShowRanView view

class CShowRanView : public CHWATestView
{
	DECLARE_DYNCREATE(CShowRanView)

public:
	CShowRanView();           // protected constructor used by dynamic creation
	virtual ~CShowRanView();

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
	afx_msg void OnChangeBranch();
	void RefreshView(BD2_RAN* data);
	void InitColumn();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	virtual void OnUpdateAllViews(CGlobalVariant* data, int type);
	virtual void Clear();
	int m_nBranch;
	afx_msg void OnClearView();
	afx_msg void OnUpdateClearView(CCmdUI* pCmdUI);

	bool m_bLock;
	afx_msg void OnLockView();
	afx_msg void OnUpdateLockView(CCmdUI* pCmdUI);
};


