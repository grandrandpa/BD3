#pragma once
#include "afxwin.h"


// CSetTimModDlg dialog

class CSetTimModDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetTimModDlg)

public:
	CSetTimModDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetTimModDlg();

// Dialog Data
	enum { IDD = IDD_SET_TIMMOD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnGetLocal();
	afx_msg void OnBnClickedBtnSet();
	afx_msg void OnBnClickedRadioSingle();
	afx_msg void OnBnClickedRadioMore();
	afx_msg void OnBnClickedCheckCurrent();
	void GetDegree(double data, double *degree, double *cent, double *sec);
	void LoadConfig();
	void GetConfig(SETTMD* data);
	BOOL m_bRadioSingle;
	CBCGPButton m_checkPos;
	CBCGPButton m_btnGetLocal;
	CComboBox m_cmbSatID;
	CEdit m_editAlt;
	CEdit m_editLatDegree;
	CEdit m_editLatCent;
	CEdit m_editLatSec;
	CEdit m_editLonDegree;
	CEdit m_editLonCent;
	CEdit m_editLonSec;
	double m_dAlt;
	int m_dLatDegree;
	int m_dLatCent;
	double m_dLatSec;
	int m_dLonDegree;
	int m_dLonCent;
	double m_dLonSec;
	CComboBox m_cmbBranch;
public:
	void Reset();
};
