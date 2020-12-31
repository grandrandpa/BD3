#pragma once
#include "afxwin.h"


// CSetSTSDlg dialog

class CSetSTSDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetSTSDlg)

public:
	CSetSTSDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetSTSDlg();

// Dialog Data
	enum { IDD = IDD_SET_STS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_cmbB1;
	CComboBox m_cmbB2;
	CComboBox m_cmbB3;
	int m_nB1;
	int m_nB2;
	int m_nB3;
	afx_msg void OnCbnSelchangeComboB1();
	afx_msg void OnCbnSelchangeComboB2();
	afx_msg void OnCbnSelchangeComboB3();
	afx_msg void OnBnClickedBtnSet();
public:
	void Reset();
};
