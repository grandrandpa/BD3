#pragma once


// CSetTTFDlg dialog

class CSetTTFDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetTTFDlg)

public:
	CSetTTFDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetTTFDlg();

// Dialog Data
	enum { IDD = IDD_SET_TTF_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
