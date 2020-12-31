#pragma once
#include "afxwin.h"


// CSetTIMDlg dialog

class CSetTIMDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetTIMDlg)

public:
	CSetTIMDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetTIMDlg();

// Dialog Data
	enum { IDD = IDD_SET_TIM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnTimDefault();
	afx_msg void OnBnClickedBtnTimSet();
	afx_msg void OnBnClickedBtnTimCheck();
	CEdit m_editDelay;
	CEdit m_editZero;
	int m_nDelay;
	void GetCableDelay(SETTIM* data);
	void SetCableDelay(SETTIM data);
	int m_nZero;
public:
	void Reset();
};
