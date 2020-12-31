#pragma once


// CSendCmdDig dialog

class CSendCmdDig : public CDialogEx
{
	DECLARE_DYNAMIC(CSendCmdDig)

public:
	CSendCmdDig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSendCmdDig();

// Dialog Data
	enum { IDD = IDD_SEND_CMD };
    #define ID_SEND_TIMER	10   //timer id

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CButton m_btnStart;
    CButton m_btnStop;
    BOOL m_ckCheckout;
    BOOL m_bAddCR;
    BOOL m_ckLoopSend;
    CString m_strCmd;

    UINT_PTR m_TimerID;
    std::string m_strLoopCmd;

public:
    afx_msg void OnClickedStart();
    afx_msg void OnClickedStop();

    void StringToHex(char *str, char *strhex);
    CString CalXorValue(CString str);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};
