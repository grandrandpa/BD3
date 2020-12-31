#pragma once
#include "afxwin.h"


// CSetIONDlg dialog

class CSetIONDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetIONDlg)

public:
	CSetIONDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetIONDlg();

// Dialog Data
	enum { IDD = IDD_SET_ION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnCheckIon();
	afx_msg void OnBnClickedBtnSetIon();
	CComboBox m_cmbIon;
	CComboBox m_cmbTro;
	CComboBox m_cmbAlt;
};
