#pragma once
#include "afxwin.h"


typedef struct SLOGTips 
{
	unsigned short type;
	CString strTips;
}SLOGTips;

// CSetLOGDlg dialog
class CSetLOGDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetLOGDlg)

public:
	CSetLOGDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetLOGDlg();

// Dialog Data
	enum { IDD = IDD_SET_LOG_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnLogSet();
	afx_msg void OnBnClickedBtnLogCheck();
	void GetOutput(SETLOG* data);
	void SetOutput(SETLOG data);
private:
	CComboBox m_cmbPort;
	CComboBox m_cmbType;
	CComboBox m_cmbFreq;
	int m_nPort;
	int m_nType;
	int m_nFrequency;
public:
	void Reset();
};
