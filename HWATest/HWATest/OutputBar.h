// outputbar.h : interface of the COutputBar class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList window

class COutputList : public CBCGPListBox
{
// Construction
public:
	COutputList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutputList();

	// Generated message map functions
protected:
	//{{AFX_MSG(COutputList)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnOutputGotoError();
	afx_msg void OnViewOutput();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


class COutputBar : public CBCGPDockingControlBar
{
public:
	COutputBar();
public:
	virtual ~COutputBar();
// Attributes
protected:

// Operations
public:
	COutputList	 m_wndList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputBar)
	//}}AFX_VIRTUAL

// Implementation

// Generated message map functions
protected:
	//{{AFX_MSG(COutputBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void AddString(CString strText);
    void UpdateFonts();

    void ShowDataToWindow(CString dataText);
};

/////////////////////////////////////////////////////////////////////////////
