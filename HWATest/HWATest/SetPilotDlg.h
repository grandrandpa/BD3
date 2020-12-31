#pragma once
#include "afxwin.h"


// CSetPilotDlg dialog

class CSetPilotDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetPilotDlg)

public:
	CSetPilotDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetPilotDlg();

// Dialog Data
	enum { IDD = IDD_SET_PILOT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSetPilotTrack();
	afx_msg void OnBnClickedBtnSetPilotAcq();
	int GetBranch(CString strText);
	CComboBox m_cmbPilot;
	CComboBox m_cmbTrack;
	CComboBox m_cmbAcqBranch;
	CComboBox m_cmbTrackBranch;
};
