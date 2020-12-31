// SetLimitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetLimitDlg.h"


// CSetLimitDlg dialog

IMPLEMENT_DYNAMIC(CSetLimitDlg, CBCGPDialog)

CSetLimitDlg::CSetLimitDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetLimitDlg::IDD, pParent)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CSetLimitDlg::~CSetLimitDlg()
{
}

void CSetLimitDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_RECT, m_StaticRect);
}


BEGIN_MESSAGE_MAP(CSetLimitDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_RESET, &CSetLimitDlg::OnBnClickedBtnReset)
END_MESSAGE_MAP()


// CSetLimitDlg message handlers

BOOL CSetLimitDlg::OnInitDialog()
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
void CSetLimitDlg::InitPropList(void)
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
	CBCGPProp* pGroup = new CBCGPProp(_T("信号强度"));
	CBCGPProp* pProp = new CBCGPProp(_T("信号强度"), NULL, TRUE);
	pProp->AddSubItem(new CBCGPProp(_T("最小值"),_T("0"),_T("最小值")));
	pProp->AddSubItem(new CBCGPProp(_T("最小值"),_T("0"),_T("最小值")));
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	pGroup = new CBCGPProp(_T("观测量"));
	pGroup->AddSubItem(new CBCGPProp(_T("伪距相邻历元差的方差"),_T("0.00"),_T("伪距相邻历元差的方差门限")));
	pGroup->AddSubItem(new CBCGPProp(_T("载波相位相邻历元差的方差"),_T("0.00"),_T("载波相位相邻历元差的方差门限")));
	pGroup->AddSubItem(new CBCGPProp(_T("多普勒相邻历元差的方差"),_T("0.00"),_T("多普勒相邻历元差的方差门限")));
	pGroup->AddSubItem(new CBCGPProp(_T("伪距一致性"),_T("0.00"),_T("同一卫星的不同频点和支路伪距一致性门限参数，超出即警告。")));
	pGroup->AddSubItem(new CBCGPProp(_T("码载偏离度一致性"),_T("0.00"),_T("同一卫星的不同频点和支路码载偏离度一致性门限参数，超出即警告。")));
	pGroup->AddSubItem(new CBCGPProp(_T("多普勒一致性"),_T("0.00"),_T("同一卫星的不同频点和支路多普勒一致性门限参数，超出即警告。")));
	m_wndPropList.AddProperty (pGroup);
	pGroup = new CBCGPProp(_T("定位信息"));
	m_wndPropList.AddProperty (pGroup);
	pGroup = new CBCGPProp(_T("卫星星历"));
	m_wndPropList.AddProperty (pGroup);
	pGroup = new CBCGPProp(_T("卫星历书"));
	m_wndPropList.AddProperty (pGroup);
	pGroup = new CBCGPProp(_T("简约历书"));
	m_wndPropList.AddProperty (pGroup);
	pGroup = new CBCGPProp(_T("电离层模型参数"));
	m_wndPropList.AddProperty (pGroup);

	//delete pProp;
	//delete pGroup;
}

void CSetLimitDlg::OnBnClickedBtnReset()
{
	// TODO: Add your control notification handler code here
	m_wndPropList.ResetOriginalValues(TRUE);
}

void CSetLimitDlg::SaveConfigure()
{

}

void CSetLimitDlg::Reset()
{
	m_wndPropList.ResetOriginalValues(TRUE);
}