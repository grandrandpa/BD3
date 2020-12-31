#pragma once
#include "afxwin.h"


// CSetFileDlg dialog

class CSetFileDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetFileDlg)

public:
	CSetFileDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSetFileDlg();

// Dialog Data
	enum { IDD = IDD_SET_FILE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CButton m_checkAlm;
	CButton m_checkCod;
	CButton m_checkEph;
	CButton m_checkIon;
	CButton m_checkJal;
	CButton m_checkMod;
	CButton m_checkPos;
	CButton m_checkRaim;
	CButton m_checkRan;
	CButton m_checkREF;
	CButton m_checkSIV;
	CButton m_checkSTA;
	CButton m_checkTIM;
	CButton m_checkAll;
	//CButton m_btnStart;
	//CButton m_btnStop;
	CEdit m_editPath;
	CButton m_btnSave;
	CString m_strFilePath;
	CTime	m_startTime;
private:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckRan();
	afx_msg void OnBnClickedCheckJal();
	afx_msg void OnBnClickedCheckTim();
	afx_msg void OnBnClickedCheckEph();
	afx_msg void OnBnClickedCheckAlm();
	afx_msg void OnBnClickedCheckPos();
	afx_msg void OnBnClickedCheckMod();
	afx_msg void OnBnClickedCheckSiv();
	afx_msg void OnBnClickedCheckCod();
	afx_msg void OnBnClickedCheckIon();
	afx_msg void OnBnClickedCheckSta();
	afx_msg void OnBnClickedCheckRef();
	afx_msg void OnBnClickedCheckRaim();
	afx_msg void OnBnClickedCheckAll();
	afx_msg void OnBnClickedBtnSave();
private:
	void ResetCounter();
public:
	void Reset();
	void SetProjectPath(CString strPath);
	afx_msg void OnBnClickedCheckXpv();
	CButton m_checkXPV;
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	CButton m_btnStart;
	CButton m_btnStop;
	bool m_bStart;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CBCGPEdit m_staticALM;
	CBCGPEdit m_staticCOD;
	CBCGPEdit m_staticEPH;
	CBCGPEdit m_staticGBS;
	CBCGPEdit m_staticGSV;
	CBCGPEdit m_staticION;
	CBCGPEdit m_staticJAL;
	CBCGPEdit m_staticMOD;
	CBCGPEdit m_staticPOS;
	CBCGPEdit m_staticRAN;
	CBCGPEdit m_staticREF;
	CBCGPEdit m_staticSTA;
	CBCGPEdit m_staticTIM;
	CBCGPEdit m_staticXPV;
	CBCGPEdit m_editRecordTime;
};
