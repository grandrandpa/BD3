#pragma once
#include "afxwin.h"


// CTestDlg dialog

class CTestDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTestDlg();

// Dialog Data
	enum { IDD = IDD_TEST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL OnInitDialog();
	int GetSerialPorts(UINT nID);
	CButton m_btnCheck;
	CComboBox m_cmbBaud;
	CComboBox m_cmbPort;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheckLink();
	CString m_strPort;
	CString m_strBaud;
public:
	int m_nPort;
	DWORD m_nBaud;
};
