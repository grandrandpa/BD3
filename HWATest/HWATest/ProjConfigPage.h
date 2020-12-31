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


// CProjConfigPage dialog

class CProjConfigPage : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(CProjConfigPage)

public:
	CProjConfigPage();
	virtual ~CProjConfigPage();

// Dialog Data
	enum { IDD = IDD_PROJCONFIGPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnSelchangedTreeConfig(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
private:
	CSetMODDlg m_setMod;
	CSetREFDlg m_setREF;
	CSetLocalDlg m_setLocal;
	CSetGSVDlg	m_setGSV;
	CSetStaticDlg m_setStatic;
	CSetMonitorDlg m_setMonitor;
	CSetLimitDlg m_setLimit;
	CSetDrawDlg	m_setDraw;
	CBCGPTreeCtrl m_treeView;
	CBCGPTabWnd m_tabCtrl;
public:
	void HideAllWindow(void);
	void ShowThisWindow(CBCGPDialog* pWnd);
	void HideThisWindow(CBCGPDialog* pWnd);
};
