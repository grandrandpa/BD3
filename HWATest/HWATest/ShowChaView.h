#pragma once

int GetTrackItem(int branch, int index);
// CShowChaView view
class CShowChaView : public CHWATestView
{
	DECLARE_DYNCREATE(CShowChaView)

protected:
	CShowChaView();           // protected constructor used by dynamic creation
	virtual ~CShowChaView();

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
private:
	bool m_bLock;
	int m_nBranch;
private:
	void InitColumn();
	void RefreshView(BD2_RAN* data);
	afx_msg void OnChangeBranch();
	afx_msg void OnClearView();
	afx_msg void OnUpdateClearView(CCmdUI* pCmdUI);
	afx_msg void OnLockView();
	afx_msg void OnUpdateLockView(CCmdUI* pCmdUI);
public:
	virtual void OnUpdateAllViews(CGlobalVariant* data, int type);
	virtual void Clear();
};


