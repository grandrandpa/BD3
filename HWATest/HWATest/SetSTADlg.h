#pragma once
#include "afxwin.h"


// CSetSTADlg dialog

class CSetSTADlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetSTADlg)

public:
	CSetSTADlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetSTADlg();

// Dialog Data
	enum { IDD = IDD_SET_STA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_cmbSta;
	int m_nSta;
	afx_msg void OnCbnSelchangeComboSta();
};
