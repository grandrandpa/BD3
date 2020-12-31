// SetMODDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetMODDlg.h"


// CSetMODDlg dialog

IMPLEMENT_DYNAMIC(CSetMODDlg, CBCGPDialog)

CSetMODDlg::CSetMODDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetMODDlg::IDD, pParent)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CSetMODDlg::~CSetMODDlg()
{
}

void CSetMODDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MOD, m_wndListCtrl);
	DDX_Control(pDX, IDC_COMBO_MOD, m_cmbPosMod);
	DDX_Control(pDX, IDC_EDIT_TIPS, m_editTips);
	DDX_Control(pDX, IDC_CHECK_TRO, m_CheckTRO);
	DDX_Control(pDX, IDC_CHECK_ION, m_CheckION);
	DDX_Control(pDX, IDC_CHECK_ALT, m_CheckAlt);
	DDX_Control(pDX, IDC_CHECK_ALL, m_CheckAll);
}


BEGIN_MESSAGE_MAP(CSetMODDlg, CBCGPDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MOD, &CSetMODDlg::OnNMDblclkListMod)
	ON_CBN_SELCHANGE(IDC_COMBO_MOD, &CSetMODDlg::OnCbnSelchangeComboMod)
	ON_BN_CLICKED(IDC_CHECK_ALL, &CSetMODDlg::OnBnClickedCheckAll)
END_MESSAGE_MAP()


// CSetMODDlg message handlers

BOOL CSetMODDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int i=0,flag=0,index=0;
	CString strText;
	char buf[MAX_PATH];
	DWORD dwStyle = m_wndListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_wndListCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wndListCtrl.SetExtendedStyle(dwStyle);
	//为列表框增加列
	InitListNormal();
	m_cmbPosMod.AddString("普通模式");
	m_cmbPosMod.AddString("联合模式");
	m_cmbPosMod.SetCurSel(0);

	if(theApp.m_strProjFile.IsEmpty())
		return 0;
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	GetPrivateProfileString("POSMOD", "ALTError", "0", buf, MAX_PATH,theApp.m_strProjFile);
	flag = atoi(buf);
	m_CheckAlt.SetCheck(flag);
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	GetPrivateProfileString("POSMOD", "IONCheck", "0", buf, MAX_PATH, theApp.m_strProjFile);
	flag = atoi(buf);
	m_CheckION.SetCheck(flag);
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	GetPrivateProfileString("POSMOD", "TROCheck", "0", buf, MAX_PATH, theApp.m_strProjFile);
	flag = atoi(buf);
	m_CheckTRO.SetCheck(flag);
	ZeroMemory(buf, sizeof(char)*MAX_PATH);
	GetPrivateProfileString("POSMOD", "ModType", "0", buf, MAX_PATH, theApp.m_strProjFile);
	index = atoi(buf);
	m_cmbPosMod.SetCurSel(index);
	if (index == 1)//联合模式
	{
		for (i=0; i<13; i++)
		{
			flag = GetPrivateProfileInt("POSMOD", "Union"+strMODE[i], 0, theApp.m_strProjFile);
			m_wndListCtrl.SetCheck(i, flag);
			ZeroMemory(buf, sizeof(char)*MAX_PATH);
			GetPrivateProfileString("POSMOD", "Union"+strMODE[i]+"Sel", "0", buf, MAX_PATH, theApp.m_strProjFile);
			strText = CString(buf);
			m_wndListCtrl.SetItemText(i, 2, strText);
		}
	} 
	else if (index == 0)//普通模式
	{
		for (i=0; i<MAXMODE-1; i++)
		{
			flag = GetPrivateProfileInt("POSMOD", "Normal"+strMODE[i], 0, theApp.m_strProjFile);
			m_wndListCtrl.SetCheck(i, flag);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetMODDlg::InitListNormal()
{
	int mod=0,i=0,count=0;
	CString strText;
	count = m_wndListCtrl.GetHeaderCtrl().GetItemCount();
	for (i=0; i<count; i++)
	{
		m_wndListCtrl.DeleteColumn(0);
	}
	m_wndListCtrl.DeleteAllItems();
	m_wndListCtrl.InsertColumn(0, "序号", LVCFMT_LEFT, 60);
	m_wndListCtrl.InsertColumn(1, "编码", LVCFMT_LEFT, 80);
	m_wndListCtrl.InsertColumn(2, "解算模式", LVCFMT_RIGHT, 100);
	m_wndListCtrl.InsertColumn(3, "描述", LVCFMT_RIGHT, 100);
	for(i=0; i<MAXMODE-1; i++)
	{
		mod = pow(2.0, i);
		strText.Format("%02d", i+1);
		m_wndListCtrl.InsertItem(i, strText);
		strText.Format("%d", mod);
		m_wndListCtrl.SetItemText(i, 1, strText);
		m_wndListCtrl.SetItemText(i, 2, strMODE[i]);
		if (i<13)
		{
			m_wndListCtrl.SetItemText(i, 3, "单频");
		} 
		else if(i<19)
		{
			m_wndListCtrl.SetItemText(i, 3, "双频");
		}
		else
		{
			m_wndListCtrl.SetItemText(i, 3, "三频");
		}
	}
}
void CSetMODDlg::InitListUnion()
{
	int mod=0,i=0,count=0;
	CString strText;
	count = m_wndListCtrl.GetHeaderCtrl().GetItemCount();
	for (i=0; i<count; i++)
	{
		m_wndListCtrl.DeleteColumn(0);
	}
	m_wndListCtrl.DeleteAllItems();
	m_wndListCtrl.InsertColumn(0, "序号", LVCFMT_LEFT, 60);
	m_wndListCtrl.InsertColumn(1, "信号分量", LVCFMT_LEFT, 80);
	m_wndListCtrl.InsertColumn(2, "卫星号", LVCFMT_LEFT, 200);
	for(i=0; i<13; i++)
	{
		strText.Format("%02d", i+1);
		m_wndListCtrl.InsertItem(i, strText);
		m_wndListCtrl.SetItemText(i, 1, strMODE[i]);
	}
}
void CSetMODDlg::OnNMDblclkListMod(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	int item=0;
	CString strText;
	char buf[MAX_PATH];
	CSetSATDlg dlg;
	int index = m_cmbPosMod.GetCurSel();
	item = pNMItemActivate->iItem;
	m_wndListCtrl.GetItemText(item, 1, buf, MAX_PATH);
	strText = CString(buf);
	strText.ReleaseBuffer();
	if (index == 1)
	{
		dlg.SetTips("信号分量："+ strText);
		if (dlg.DoModal() == IDOK)
		{
			m_wndListCtrl.SetItemText(item, 2, dlg.m_strSelectedSVID);
		}
	}
	*pResult = 0;
}

void CSetMODDlg::OnCbnSelchangeComboMod()
{
	// TODO: Add your control notification handler code here
	int index = m_cmbPosMod.GetCurSel();
	if (index == 1)
	{
		InitListUnion();
		m_editTips.SetWindowText("双击所选模式，设置卫星参数。");
	} 
	else
	{
		InitListNormal();
		m_editTips.SetWindowText("");
	}
}

void CSetMODDlg::OnBnClickedCheckAll()
{
	// TODO: Add your control notification handler code here
	int bcheck = m_CheckAll.GetCheck();
	int count = m_wndListCtrl.GetItemCount();
	for (int i=0; i<count; i++)
	{
		m_wndListCtrl.SetCheck(i, bcheck);
	}
}

void CSetMODDlg::SaveConfigure()
{
	CString strText;
	int bCheck = 0, i=0;
	int index = m_cmbPosMod.GetCurSel();
	if(theApp.m_strProjFile.IsEmpty())
		return;
	bCheck = m_CheckAlt.GetCheck();
	WritePrivateProfileString("POSMOD", "ALTError", bCheck?"1":"0", theApp.m_strProjFile);
	bCheck = m_CheckION.GetCheck();
	WritePrivateProfileString("POSMOD", "IONCheck", bCheck?"1":"0", theApp.m_strProjFile);
	bCheck = m_CheckTRO.GetCheck();
	WritePrivateProfileString("POSMOD", "TROCheck", bCheck?"1":"0", theApp.m_strProjFile);
	WritePrivateProfileString("POSMOD", "ModType", index?"1":"0", theApp.m_strProjFile);
	if (index == 1)//联合模式
	{
		for (i=0; i<13; i++)
		{
			bCheck = m_wndListCtrl.GetCheck(i);
			WritePrivateProfileString("POSMOD", "Union"+strMODE[i], bCheck?"1":"0", theApp.m_strProjFile);
			strText = m_wndListCtrl.GetItemText(i, 2);
			WritePrivateProfileString("POSMOD", "Union"+strMODE[i]+"Sel", strText, theApp.m_strProjFile);
		}
	} 
	else if (index == 0)//普通模式
	{
		for (i=0; i<MAXMODE-1; i++)
		{
			bCheck = m_wndListCtrl.GetCheck(i);
			WritePrivateProfileString("POSMOD", "Normal"+strMODE[i], bCheck?"1":"0", theApp.m_strProjFile);
		}
	}
}

void CSetMODDlg::Reset()
{
	int i=0;
	m_CheckAlt.SetCheck(FALSE);
	m_CheckION.SetCheck(FALSE);
	m_CheckTRO.SetCheck(FALSE);
	m_cmbPosMod.SetCurSel(0);
	for (i=0; i<MAXMODE-1; i++)
	{
		m_wndListCtrl.SetCheck(i);
	}
}