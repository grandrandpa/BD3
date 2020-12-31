#pragma once


// CSetEPQDialog dialog

class CSetEPQDialog : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetEPQDialog)

public:
	CSetEPQDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetEPQDialog();

// Dialog Data
	enum { IDD = IDD_SET_EPQ_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
    virtual BOOL OnInitDialog();
    afx_msg void OnClickedBtnSentEpq();

public:
    CComboBox m_ComboFreq;
    CComboBox m_ComboModel;
    CComboBox m_ComboSos;
    CComboBox m_ComboSpeed;
    CComboBox m_ComboUrg;
    int m_iCardID;
    double m_dElevValue;
    CButton m_btnSendEPQ;
    int m_iTimes;
    
    afx_msg void OnSelchangeComboModel();
    afx_msg void OnSelchangeComboFreq();
    afx_msg void OnSelchangeComboSpeed();
    afx_msg void OnSelchangeComboSos();
    afx_msg void OnSelchangeComboUrg();


private:
    int miFreq;
    int miModel;
    int miSos;
    int miSpeed;
    int miUrgFlag;
    
    virtual void PostNcDestroy();
};
