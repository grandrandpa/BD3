#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CSetPortDlg dialog

class CSetPortDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetPortDlg)

public:
	CSetPortDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetPortDlg();

// Dialog Data
	enum { IDD = IDD_SET_PORT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_cmbBaud;
	CComboBox m_cmbPort;
	CEdit m_editPort;
	CIPAddressCtrl m_editIP;
	int m_nBaud;
	CString m_strComPort;
	int m_nSocketPort;
	DWORD m_dwIP;
	afx_msg void OnBnClickedRadioCom();
	afx_msg void OnBnClickedRadioSocket();
	int GetSerialPorts(UINT nID);
	afx_msg void OnBnClickedOk();
	BOOL m_bConnectType;
	CComboBox m_cmbProtocol;
};
