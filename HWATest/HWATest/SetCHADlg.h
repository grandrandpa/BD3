#pragma once
#include "afxwin.h"


// CSetCHADlg dialog

class CSetCHADlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetCHADlg)

public:
	CSetCHADlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetCHADlg();

// Dialog Data
	enum { IDD = IDD_SET_CHA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnChaDefault();
	afx_msg void OnBnClickedBtnChaSet();
	afx_msg void OnBnClickedBtnChaCheck();
	void GetChannel(SETCHA* data);
	void SetChannel(SETCHA data);
private:
	CComboBox m_cmbID;
	CComboBox m_cmbBranch;
	CComboBox m_cmbPilot;
	CComboBox m_cmbCHID;
	int m_nID;
	int m_nBranch;
	int m_nPilot;
	int m_nCHID;
public:
	void Reset();
};
