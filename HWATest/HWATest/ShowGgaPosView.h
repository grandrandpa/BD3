#pragma once
#include "HWATestView.h"


// CShowGgaPosView view

class CShowGgaPosView : public CHWATestView
{
	DECLARE_DYNCREATE(CShowGgaPosView)

public:
	CShowGgaPosView();           // protected constructor used by dynamic creation
	virtual ~CShowGgaPosView();

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
	void RefreshView(NmeaAllData* data);
	void InitColumn();
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	virtual void OnUpdateAllViews(CGlobalVariant* data, int type);
	virtual void Clear();
	int m_nPosType;
	afx_msg void OnClearView();
	afx_msg void OnUpdateClearView(CCmdUI* pCmdUI);

	bool m_bLock;
	afx_msg void OnLockView();
	afx_msg void OnUpdateLockView(CCmdUI* pCmdUI);
};


