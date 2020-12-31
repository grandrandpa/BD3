#pragma once


// CAnimationDlg dialog

class CAnimationDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CAnimationDlg)

public:
	CAnimationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAnimationDlg();

// Dialog Data
	enum { IDD = IDD_ANIMATION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
