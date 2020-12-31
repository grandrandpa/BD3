#pragma once
#include "afxwin.h"


// CSetMUTDlg dialog

class CSetMUTDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetMUTDlg)

public:
	CSetMUTDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetMUTDlg();

// Dialog Data
	enum { IDD = IDD_SET_MUT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSetTtf();
	afx_msg void OnBnClickedBtnSetEva();
private:
	CComboBox m_cmbTTFMod;
	CEdit m_editEVAValue;
	int m_nTTFMod;
	int m_nEVAValue;
public:
	void Reset();
};
