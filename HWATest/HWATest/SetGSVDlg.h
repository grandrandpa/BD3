#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSetGSVDlg dialog

class CSetGSVDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetGSVDlg)

public:
	CSetGSVDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetGSVDlg();

// Dialog Data
	enum { IDD = IDD_SET_GSV_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
protected:
	CListCtrl m_wndListCtrl;
	CButton m_CheckAll;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckAll();
public:
	void Reset();
	void SaveConfigure();
};
