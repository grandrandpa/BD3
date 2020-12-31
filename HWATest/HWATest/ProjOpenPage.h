#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CProjOpenPage dialog

class CProjOpenPage : public CBCGPDialog
{
	DECLARE_DYNAMIC(CProjOpenPage)

public:
	CProjOpenPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProjOpenPage();

// Dialog Data
	enum { IDD = IDD_PROJOPENPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTreeCtrl m_treeCtrl;
	CListCtrl m_listCtrl;
	CEdit m_editTips;
	CComboBox m_cmbProjPath;
	CString m_strProjFileName;
	int m_nProjectType;
	int m_nProjectItem;
	afx_msg void OnTvnSelchangedTreeProj(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListProj(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonProjSet();
};
