#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CCheckDevDlg dialog

class CCheckDevDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CCheckDevDlg)

public:
	CCheckDevDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCheckDevDlg();

// Dialog Data
	enum { IDD = IDD_ABOUT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CTabCtrl m_tabCtrl;
	CBCGPPropList	m_wndPropList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckVersion();
	afx_msg void OnBnClickedCheckPrm();
private:
	void ResetSIM();
	void ResetVER();
public:
	void InitPropListSIM();
	void InitPropListPRM();
};
