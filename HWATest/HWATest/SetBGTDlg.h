#pragma once
#include "afxwin.h"


// CSetBGTDlg dialog

class CSetBGTDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetBGTDlg)

public:
	CSetBGTDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetBGTDlg();

// Dialog Data
	enum { IDD = IDD_SET_BGT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSetBgt();
	CEdit m_editGnssID;
	CEdit m_editGnssWn;
	CEdit m_editGnssT0;
	CEdit m_editGnssA0;
	CEdit m_editGnssA1;
	CEdit m_editGnssA2;
	int m_nGnssID;
	int m_nGnssWn;
	long m_nGnssT0;
	double m_dbGnssA0;
	double m_dbGnssA1;
	double m_dbGnssA2;
public:
	void Reset();
};
