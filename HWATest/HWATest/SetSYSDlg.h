#pragma once
#include "SystemPane.h"
#include "afxcmn.h"


// CSetSYSDlg dialog

class CSetSYSDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetSYSDlg)

public:
	CSetSYSDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetSYSDlg();

// Dialog Data
	enum { IDD = IDD_SET_SYSTEM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CTabCtrl m_tabCtrl;
	CSystemPane m_wndPane;
public:
	virtual BOOL OnInitDialog();
public:
	void Reset();
};
