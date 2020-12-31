#pragma once
#include "afxcmn.h"
#include "SetMODDlg.h"
#include "SetREFDlg.h"
#include "SetLocalDlg.h"
#include "SetGSVDlg.h"
#include "SetStaticDlg.h"
#include "SetMonitorDlg.h"
#include "SetLimitDlg.h"
#include "SetDrawDlg.h"


// CProjPropertyPage dialog

class CProjPropertyPage : public CBCGPDialog
{
	DECLARE_DYNAMIC(CProjPropertyPage)

public:
	CProjPropertyPage(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProjPropertyPage();

// Dialog Data
	enum { IDD = IDD_PROJPROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL OnInitDialog();
	void HideAllWindow(void);
	void ShowThisWindow(CBCGPDialog* pWnd);
	void HideThisWindow(CBCGPDialog* pWnd);
	afx_msg void OnTvnSelchangedTreeProperty(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnComplete();
private:
	CSetMODDlg m_wndMOD;
	CSetREFDlg m_wndREF;
	CSetGSVDlg	m_wndGSV;
	CSetLocalDlg m_wndLocal;
	CSetStaticDlg m_wndStatic;
	CSetMonitorDlg m_wndMonitor;
	CSetLimitDlg m_wndLimit;
	CSetDrawDlg	m_wndDraw;
	CBCGPTabWnd m_tabCtrl;
	CBCGPTreeCtrl m_treeView;
public:
	void Reset();
};
