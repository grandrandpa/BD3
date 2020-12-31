#pragma once
#include "afxcmn.h"
#include "SetCHADlg.h"
#include "SetLOGDlg.h"
#include "SetPosDlg.h"
#include "SetREFDlg.h"
#include "SetTIMDlg.h"
#include "SetWIDDlg.h"
#include "SetMUTDlg.h"
#include "SetEACDlg.h"
#include "SetBGTDlg.h"
#include "SetSTSDlg.h"
#include "SetACQDlg.h"
#include "SetIONDlg.h"
#include "SetTimModDlg.h"
#include "SetPilotDlg.h"
#include "SetModualDlg.h"
#include "SetWORKMODDlg.h"
#include "SetISTDlg.h"
// CSystemPane dialog
class CSystemPane : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSystemPane)

public:
	CSystemPane(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSystemPane();

// Dialog Data
	enum { IDD = IDD_PANE_DIALOG }; //IDD_PROPERTY_DIALOG

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CSetCHADlg	setCHA;
	CSetLOGDlg	setLOG;
	CSetPOSDlg	setPOS;
	CSetREFDlg	setREF;
	CSetTIMDlg	setTIM;
	CSetWIDDlg	setWID;
	CSetMUTDlg	setMUT;
	CSetEACDlg	setEAC;
	CSetBGTDlg	setBGT;
	CSetSTSDlg	setSTS;
	CSetACQDlg	setACQ;
	CSetIONDlg	setION;
	CSetPilotDlg setPILOT;
	CSetTimModDlg setTimMod;
	CSetModualDlg setModual;
	CSetWORKMODDlg setWorkMod;
	CSetISTDlg setIST;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTvnSelchangedTreePropertySet(NMHDR *pNMHDR, LRESULT *pResult);
	CBCGPTreeCtrl m_treeView;
	CBCGPTabWnd m_tabCtrl;
	void HideAllWindow(void);
	void ShowThisWindow(CBCGPDialog* pWnd);
	void HideThisWindow(CBCGPDialog* pWnd);
	void InitRectPane(CRect rect);
};
