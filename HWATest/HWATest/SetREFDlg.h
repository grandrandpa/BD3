#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSetREFDlg dialog

class CSetREFDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetREFDlg)

public:
	CSetREFDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetREFDlg();

// Dialog Data
	enum { IDD = IDD_SET_REF_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CBCGPPropList		m_wndPropList;
private:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnDefault();
	afx_msg void OnBnClickedBtnSet();
	CTabCtrl m_tabREF;
	void InitPropList(void);
	void GetPropList(SETREF* data);
	void SetPropList(SETREF data);
	CButton m_btnSet;
public:
	void Reset();
public:
	void SaveConfigure();
	void EnableSetupControl(bool enable);
};
