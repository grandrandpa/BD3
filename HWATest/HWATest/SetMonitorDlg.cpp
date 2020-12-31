// SetMonitorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetMonitorDlg.h"


// CSetMonitorDlg dialog

IMPLEMENT_DYNAMIC(CSetMonitorDlg, CBCGPDialog)

CSetMonitorDlg::CSetMonitorDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetMonitorDlg::IDD, pParent)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CSetMonitorDlg::~CSetMonitorDlg()
{
}

void CSetMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_COLOR, m_StaticRect);
}


BEGIN_MESSAGE_MAP(CSetMonitorDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_RESET, &CSetMonitorDlg::OnBnClickedBtnReset)
END_MESSAGE_MAP()


// CSetMonitorDlg message handlers

BOOL CSetMonitorDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rect;
	m_StaticRect.GetClientRect(rect);
	m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rect, &m_StaticRect, 2);
	InitPropList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetMonitorDlg::InitPropList(void)
{
	CString strText;
	m_wndPropList.EnableToolBar(FALSE);
	m_wndPropList.EnableSearchBox(FALSE);
	m_wndPropList.EnableHeaderCtrl (true,_T("参数"),_T("值"));
	m_wndPropList.EnableDesciptionArea ();
	m_wndPropList.SetVSDotNetLook ();
	m_wndPropList.MarkModifiedProperties ();
	m_wndPropList.EnableContextMenu();
	//1
	CBCGPProp* pGroup = new CBCGPProp(_T("门限类别"));
	CBCGPProp* pProp = new CBCGPProp(_T("观测量"), _T("监测"), _T("不监测"));
	pProp->AddOption(_T("监测"));
	pProp->AddOption(_T("不监测"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	pProp = new CBCGPProp(_T("定位信息"), _T("监测"), _T("不监测"));
	pProp->AddOption(_T("监测"));
	pProp->AddOption(_T("不监测"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	pProp = new CBCGPProp(_T("信号强度"), _T("监测"), _T("不监测"));
	pProp->AddOption(_T("监测"));
	pProp->AddOption(_T("不监测"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	pProp = new CBCGPProp(_T("导航电文-卫星星历"), _T("监测"), _T("不监测"));
	pProp->AddOption(_T("监测"));
	pProp->AddOption(_T("不监测"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	pProp = new CBCGPProp(_T("导航电文-卫星历书"), _T("监测"), _T("不监测"));
	pProp->AddOption(_T("监测"));
	pProp->AddOption(_T("不监测"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	pProp = new CBCGPProp(_T("导航电文-简约历书"), _T("监测"), _T("不监测"));
	pProp->AddOption(_T("监测"));
	pProp->AddOption(_T("不监测"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	pProp = new CBCGPProp(_T("导航电文-电离层模型参数"), _T("监测"), _T("不监测"));
	pProp->AddOption(_T("监测"));
	pProp->AddOption(_T("不监测"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);

	//delete pProp;
	//delete pGroup;
}

void CSetMonitorDlg::OnBnClickedBtnReset()
{
	// TODO: Add your control notification handler code here
}

void CSetMonitorDlg::SaveConfigure()
{
}
void CSetMonitorDlg::Reset()
{
	m_wndPropList.ResetOriginalValues(TRUE);
}
