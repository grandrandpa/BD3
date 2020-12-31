#pragma once
#include "afxwin.h"


// CSetMonitorDlg dialog

class CSetMonitorDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetMonitorDlg)

public:
	CSetMonitorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetMonitorDlg();

// Dialog Data
	enum { IDD = IDD_SET_MONITOR_DIALOG };

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
