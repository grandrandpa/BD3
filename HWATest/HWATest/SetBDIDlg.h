#pragma once
#include "afxcmn.h"


// CSetBDIDlg dialog

class CSetBDIDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetBDIDlg)

public:
	CSetBDIDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetBDIDlg();

// Dialog Data
	enum { IDD = IDD_SET_BDI_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL OnInitDialog();
	void InitPropList(void);
	void GetPropList(SETREF* data);
	afx_msg void OnBnClickedBtnDefault();
	afx_msg void OnBnClickedBtnSet();
private:
	CTabCtrl m_tabBDI;
	CBCGPPropList	m_wndPropList;
public:
	void Reset();
};
