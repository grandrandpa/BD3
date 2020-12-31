#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSetACQDlg dialog

class CSetACQDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetACQDlg)

public:
	CSetACQDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetACQDlg();

// Dialog Data
	enum { IDD = IDD_SET_ACQ_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	int			m_nBranch;
	CComboBox m_cmbMUT;
	CComboBox m_cmbACQ;
	CComboBox m_cmbTrack;
public:
	char GetModualation(CString strText);
	void InitComboBox(int branch);
	afx_msg void OnBnClickedBtnSetMutPath();
	afx_msg void OnBnClickedBtnSetStaTrack();
	afx_msg void OnBnClickedBtnSetStaAcq();
	afx_msg void OnBnClickedBtnSetMudual();
	CComboBox m_cmbModual;
	CEdit m_staticTips;
	afx_msg void OnCbnSelchangeComboMudual();
};
