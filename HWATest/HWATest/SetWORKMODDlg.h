#pragma once
#include "afxwin.h"


// CSetWORKMODDlg dialog

class CSetWORKMODDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetWORKMODDlg)

public:
	CSetWORKMODDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetWORKMODDlg();

// Dialog Data
	enum { IDD = IDD_SET_WORK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void GetWorkData(WORKMOD* data);
	CComboBox m_cmbMode;
	int m_nMode;
	CComboBox m_cmbsvstart;
	int m_nsvstart;
	CComboBox m_cmbsvend;
	int m_nsvend;
	afx_msg void OnBnClickedBtnWorkSet();
};
