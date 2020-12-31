#pragma once
#include "afxwin.h"


// CSetPOSDlg dialog

class CSetPOSDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetPOSDlg)

public:
	CSetPOSDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetPOSDlg();

// Dialog Data
	enum { IDD = IDD_SET_POS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnPosDefault();
	afx_msg void OnBnClickedBtnPosSet();
	afx_msg void OnBnClickedBtnPosCheck();
	afx_msg void OnBnClickedBtnModSet();
	afx_msg void OnBnClickedBtnModCheck();
	afx_msg void OnCbnSelchangeComboPosType();
	CComboBox m_cmbPosType;
	CEdit m_editPosAlt;
	CEdit m_editPosLat;
	CEdit m_editPosLon;
	CStatic m_tipsAlt;
	CStatic m_tipsLat;
	CStatic m_tipsLon;
	double m_dPosAlt;
	double m_dPosLat;
	double m_dPosLon;
	void GetPosition(SETPOS* data);
	void SetPosition(SETPOS data);
	int m_nPosType;
	CString m_strAltTips;
	CString m_strLatTips;
	CString m_strLonTips;
	CComboBox m_cmbPosMod;
	void GetModParameter(SETMOD* data);
public:
	void Reset();
};
