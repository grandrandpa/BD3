#pragma once
#include "HWATestView.h"


// CShowAlmView view
#define MAXALM	12

class CShowAlmView : public CHWATestView
{
	DECLARE_DYNCREATE(CShowAlmView)

public:
	CShowAlmView();           // protected constructor used by dynamic creation
	virtual ~CShowAlmView();

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
	int					m_nSvId;
	//afx_msg void OnChangeBranch();
	afx_msg void OnChangeSvID();
	afx_msg void OnClearView();
	afx_msg void OnUpdateClearView(CCmdUI* pCmdUI);
	void RefreshView(BD2_ALM* data);
	void InitColumn();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	virtual void OnUpdateAllViews(CGlobalVariant* data, int type);
	virtual void Clear();

	bool m_bLock;
	afx_msg void OnLockView();
	afx_msg void OnUpdateLockView(CCmdUI* pCmdUI);
};


