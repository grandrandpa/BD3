#pragma once


// CSetEVADlg dialog

class CSetEVADlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetEVADlg)

public:
	CSetEVADlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetEVADlg();

// Dialog Data
	enum { IDD = IDD_SET_EVA_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
