#pragma once
#include "afxwin.h"


// CSetStaticDlg dialog

class CSetStaticDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetStaticDlg)

public:
	CSetStaticDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetStaticDlg();

// Dialog Data
	enum { IDD = IDD_SET_STATIC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL OnInitDialog();
	CButton m_checkPos;
	CButton m_checkRan;
	CButton m_checkSnr;
	CButton m_checkStart;
	BOOL m_bCheckStatic;
public:
	void Reset();
public:
	void SaveConfigure();
};
