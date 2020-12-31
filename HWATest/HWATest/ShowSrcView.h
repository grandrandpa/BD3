#pragma once
#include "HWATestView.h"


// CShowSrcView view

class CShowSrcView : public CHWATestView
{
	DECLARE_DYNCREATE(CShowSrcView)

public:
	CShowSrcView();           // protected constructor used by dynamic creation
	virtual ~CShowSrcView();

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
	bool m_bHex;
	list<ComPackageData*> m_RecvList; //数据接收队列
	HANDLE m_hRecvListMtx;//数据接收事件句柄
	bool m_bRecvDataPro;//数据接收
private:
	static UINT DisposeData(LPVOID lparm);
	UINT _DisposeData();
private:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	afx_msg void OnClearView();
	afx_msg void OnUpdateClearView(CCmdUI* pCmdUI);
	afx_msg void OnClickHex();
	afx_msg void OnUpdateClickHex(CCmdUI* pCmdUI);
	afx_msg void OnLockView();
	afx_msg void OnUpdateLockView(CCmdUI* pCmdUI);
public:
	void RefreshView(char* pBuff, int len);
	virtual void OnUpdateAllViews(CGlobalVariant* data, int type);
	virtual void Clear();
	afx_msg void OnClose();
};


