#pragma once
#include "afxwin.h"


// CSetWIDDlg dialog

class CSetWIDDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetWIDDlg)

public:
	CSetWIDDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetWIDDlg();

// Dialog Data
	enum { IDD = IDD_SET_WID_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnWidDefault();
	afx_msg void OnBnClickedBtnWidSet();
	afx_msg void OnBnClickedBtnWidCheck();
	void GetBandwidth(SETWID* data);
	void SetBandwidth(SETWID data);
	CComboBox m_cmbID;
	CComboBox m_cmbBranch;
	CComboBox m_cmbBandwidth;
	int m_nID;
	int m_nBranch;
	int m_nBandwidth;
public:
	void Reset();
	afx_msg void OnCbnSelchangeComboWidBranch();
};
