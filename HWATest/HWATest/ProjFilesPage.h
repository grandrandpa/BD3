#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CProjFilesPage dialog

class CProjFilesPage : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(CProjFilesPage)

public:
	CProjFilesPage();
	virtual ~CProjFilesPage();

// Dialog Data
	enum { IDD = IDD_PROJFILESPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
public:
	afx_msg void OnBnClickedButtonProjSet();
	afx_msg void OnLvnItemchangedListProj(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTreeProj(NMHDR *pNMHDR, LRESULT *pResult);
	void WriteTableHeader(CString strPath);
	CComboBox m_cmbProjPath;
	CEdit m_editProjName;
	CEdit m_editTips;
	CListCtrl m_listCtrl;
	CTreeCtrl m_treeCtrl;
	CString m_strProjName;
	CString m_strProjPath;
	int	m_nProjectType;
};
