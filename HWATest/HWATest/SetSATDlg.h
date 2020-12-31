#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSetSATDlg dialog

class CSetSATDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetSATDlg)

public:
	CSetSATDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetSATDlg();

// Dialog Data
	enum { IDD = IDD_SET_SAT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL OnInitDialog();
	CBCGPListCtrl m_wndListCtrl;
	afx_msg void OnBnClickedCheckAll();
	CString m_strTips;
	CButton m_CheckAll;
	afx_msg void OnBnClickedOk();
public:
	void Reset();
public:
	CString m_strSelectedSVID;
	void SetTips(CString strTips);
	void SaveConfigure();
};
