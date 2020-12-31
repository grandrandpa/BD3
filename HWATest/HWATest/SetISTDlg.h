#pragma once
#include "afxwin.h"

// CSetISTDlg dialog

class CSetISTDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetISTDlg)

public:
	CSetISTDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetISTDlg();

// Dialog Data
	enum { IDD = IDD_SET_IST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnIstSet();
	virtual BOOL OnInitDialog();
	CComboBox m_fp;
	int m_nfp;
};
