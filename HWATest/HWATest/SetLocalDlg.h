#pragma once
#include "afxwin.h"


// CSetLocalDlg dialog

class CSetLocalDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetLocalDlg)

public:
	CSetLocalDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetLocalDlg();

// Dialog Data
	enum { IDD = IDD_SET_LOCAL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboPosType();
	CEdit m_editElv;
	CComboBox m_cmbLocalType;
	CBCGPEdit m_editAltTips;
	CBCGPEdit m_editLatTips;
	CBCGPEdit m_editLonTips;
	CBCGPEdit m_editAlt;
	CBCGPEdit m_editLat;
	CBCGPEdit m_editLon;
	CString m_strSatElv;
	CString m_strPosAlt;
	CString m_strPosLat;
	CString m_strPosLon;
public:
	void Reset();
	void SaveConfigure();
};
