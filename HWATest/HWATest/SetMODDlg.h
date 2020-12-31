#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "SetSATDlg.h"

// CSetMODDlg dialog

class CSetMODDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetMODDlg)

public:
	CSetMODDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetMODDlg();

// Dialog Data
	enum { IDD = IDD_SET_MOD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL OnInitDialog();
	CBCGPListCtrl m_wndListCtrl;
	CComboBox m_cmbPosMod;
	CBCGPEdit m_editTips;
	CButton m_CheckTRO;
	CButton m_CheckION;
	CButton m_CheckAlt;
	CButton m_CheckAll;
protected:
	void InitListNormal();
	void InitListUnion();
	afx_msg void OnNMDblclkListMod(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboMod();
	afx_msg void OnBnClickedCheckAll();
public:
	void Reset();
	void SaveConfigure();
};
