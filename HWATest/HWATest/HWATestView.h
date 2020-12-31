// HWATestView.h : interface of the CHWATestView class
//


#pragma once
#include "HWATestDoc.h"
#include "WinTools.h"

#define MAXSVNUM     64
#define MAXBAUD     10
#define MAXFREQ     13
#define MAXFREQS     31
#define ELV_LIMIT	5.0

#define IDD_USER_VIEW_TREECTRL	(WM_USER+3100)
//消息，控制状态栏
#define MSG_MAIN_STATUSBAR_TIM	(WM_USER+3101)
#define MSG_MAIN_FORM_CLOSE		(WM_USER+3102)

//背景色和字体
extern COLORREF clrBkFace;
extern COLORREF clrBarFace;
extern COLORREF clrTextFace;
extern CPen		m_GnsspenLine;
extern CPen		m_GnssDotpenLine;
extern CFont	m_GnssfontBold;
extern CFont	m_GnssfontNormal;
extern CFont	m_GnssfontNormal25;
//////////////////////////////////////////////////////////////////////////
extern int bauds[MAXBAUD];
extern CString strFREQ[MAXFREQ];
extern CString strMODE[MAXMODE];
extern CString strFrameID[16];
///////////////////////////////////////////////////
#define MAX_LINE 120
class CToolbarLabel : public CBCGPToolbarButton  
{
	DECLARE_SERIAL(CToolbarLabel)

public:
	CToolbarLabel (UINT nID = 0, LPCTSTR lpszText = NULL);

	virtual void OnDraw (CDC* pDC, const CRect& rect, CBCGPToolBarImages* pImages, 
		BOOL bHorz = TRUE, BOOL bCustomizeMode = FALSE,						
		BOOL bHighlight = FALSE,						
		BOOL bDrawBorder = TRUE, 
		BOOL bGrayDisabledButtons = TRUE);
};

class CHWATestView : public CView
{
public: // create from serialization only
	CHWATestView();
	DECLARE_DYNCREATE(CHWATestView)

// Attributes
public:
	CHWATestDoc* GetDocument() const;

// Operations
public:
// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CHWATestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg LRESULT OnPrintClient(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
public:
	CBCGPTabWnd		m_wndTabs;
	CBCGPToolBar	m_wndToolBar;
	CBCGPListCtrl	m_listCtrl;
	CRITICAL_SECTION m_BufferCriticalSection;//临界区
public:
	virtual void OnUpdateAllViews(CGlobalVariant* data, int type);
	virtual void Clear();
};

#ifndef _DEBUG  // debug version in HWATestView.cpp
inline CHWATestDoc* CHWATestView::GetDocument() const
   { return reinterpret_cast<CHWATestDoc*>(m_pDocument); }
#endif

//////////////////////////////////////////////////////////

//绘图工具函数
void DrawWindowsRect(CWnd *pwnd);
void DrawText(CDC& dc, int x, int y, CString s,COLORREF color, int align);
void DrawFontText(CDC* pDC, int x, int y,CFont *oldFont, CString s,COLORREF color, int align);

//////////////////////////////////////////////////