#pragma once
#include "afxwin.h"


// CSetDrawDlg dialog

class CSetDrawDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetDrawDlg)

public:
	CSetDrawDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetDrawDlg();

// Dialog Data
	enum { IDD = IDD_SET_DRAW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton m_CheckZoom;
	int m_nPointCount;
public:
	void Reset();
	void SaveConfigure();
};
