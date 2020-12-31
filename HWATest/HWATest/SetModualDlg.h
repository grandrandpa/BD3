#pragma once
#include "afxwin.h"


// CSetModualDlg dialog

class CSetModualDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetModualDlg)

public:
	CSetModualDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetModualDlg();

// Dialog Data
	enum { IDD = IDD_SET_MODUAL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSetModual();
	CComboBox m_cmbModual;
	CEdit m_staticTips;
	afx_msg void OnCbnSelchangeComboModual();
};
