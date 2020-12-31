#pragma once


// CSetTcqDig dialog

class CSetTcqDig : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetTcqDig)

public:
	CSetTcqDig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetTcqDig();

// Dialog Data
	enum { IDD = IDD_SET_TCQ_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CButton m_btnSendTCQ;
    CComboBox m_cbCodeType;
    CComboBox m_cbConfirm;
    CComboBox m_cbFreq;
    int m_iCardID;
    int m_iTimes;
    CString m_strTCQData;


    afx_msg void OnClickedBtnSentTcq();
    virtual BOOL OnInitDialog();

    virtual void PostNcDestroy();
};
