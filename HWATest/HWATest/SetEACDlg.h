#pragma once
#include "afxwin.h"


// CSetEACDlg dialog

class CSetEACDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetEACDlg)

public:
	CSetEACDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetEACDlg();

// Dialog Data
	enum { IDD = IDD_SET_EAC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSet();
	CComboBox m_cmbID;
	CComboBox m_cmbPilotID;
	CComboBox m_cmbPilotBranch;
	int m_nID;
	int m_nPilotID;
	int m_nPilotBranch;
public:
	void Reset();
};
