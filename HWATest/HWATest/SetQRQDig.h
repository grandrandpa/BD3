#pragma once


// CSetQRQDig dialog

class CSetQRQDig : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetQRQDig)

public:
	CSetQRQDig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetQRQDig();

// Dialog Data
	enum { IDD = IDD_SET_QRQ_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnClickedBtnSentQrq();
    int m_iCardID;
    CComboBox m_cbQrqType;
    virtual BOOL OnInitDialog();
    virtual void PostNcDestroy();
};
