#pragma once
#include "afxwin.h"


// CSetLimitDlg dialog

class CSetLimitDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetLimitDlg)

public:
	CSetLimitDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetLimitDlg();

// Dialog Data
	enum { IDD = IDD_SET_LIMIT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
protected:
	CStatic m_StaticRect;
	CBCGPPropList		m_wndPropList;
	virtual BOOL OnInitDialog();
	void InitPropList(void);
	afx_msg void OnBnClickedBtnReset();
public:
	void Reset();
	void SaveConfigure();
};
