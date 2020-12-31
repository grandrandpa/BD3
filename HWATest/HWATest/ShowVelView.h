#pragma once
#include "HWATestView.h"


// CShowVelView view

class CShowVelView : public CHWATestView
{
	DECLARE_DYNCREATE(CShowVelView)

protected:
	CShowVelView();           // protected constructor used by dynamic creation
	virtual ~CShowVelView();

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
	bool m_bLock;
private:
	void InitColumn();
	void RefreshView(BD2_POS* data);
	afx_msg void OnClearView();
	afx_msg void OnUpdateClearView(CCmdUI* pCmdUI);
	afx_msg void OnLockView();
	afx_msg void OnUpdateLockView(CCmdUI* pCmdUI);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnUpdateAllViews(CGlobalVariant* data, int type);
	virtual void Clear();
	virtual void OnInitialUpdate();
};


