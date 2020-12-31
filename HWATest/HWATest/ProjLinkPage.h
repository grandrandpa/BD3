#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CProjLinkPage dialog

class CProjLinkPage : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(CProjLinkPage)

public:
	CProjLinkPage();
	virtual ~CProjLinkPage();

// Dialog Data
	enum { IDD = IDD_PROJLINKPAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int GetSerialPorts(UINT nID);
	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	afx_msg void OnBnClickedRadioCom();
	afx_msg void OnBnClickedRadioSocket();
	BOOL m_bConnectType;
	CComboBox m_cmbBaud;
	CComboBox m_cmbPort;
	CEdit m_editPort;
	int m_nBaud;
	int m_nSocketPort;
	DWORD m_dwIP;
	CString m_strComPort;
	CIPAddressCtrl m_editIP;
	CComboBox m_cmbProtocol;
};
