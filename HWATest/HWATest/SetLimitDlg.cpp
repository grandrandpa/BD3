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
	m_wndPropList.EnableHeaderCtrl (true,_T("����"),_T("ֵ"));
	m_wndPropList.EnableDesciptionArea ();
	m_wndPropList.SetVSDotNetLook ();
	m_wndPropList.MarkModifiedProperties ();
	m_wndPropList.EnableContextMenu();
	//1
	CBCGPProp* pGroup = new CBCGPProp(_T("�ź�ǿ��"));
	CBCGPProp* pProp = new CBCGPProp(_T("�ź�ǿ��"), NULL, TRUE);
	pProp->AddSubItem(new CBCGPProp(_T("��Сֵ"),_T("0"),_T("��Сֵ")));
	pProp->AddSubItem(new CBCGPProp(_T("��Сֵ"),_T("0"),_T("��Сֵ")));
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	pGroup = new CBCGPProp(_T("�۲���"));
	pGroup->AddSubItem(new CBCGPProp(_T("α��������Ԫ��ķ���"),_T("0.00"),_T("α��������Ԫ��ķ�������")));
	pGroup->AddSubItem(new CBCGPProp(_T("�ز���λ������Ԫ��ķ���"),_T("0.00"),_T("�ز���λ������Ԫ��ķ�������")));
	pGroup->AddSubItem(new CBCGPProp(_T("������������Ԫ��ķ���"),_T("0.00"),_T("������������Ԫ��ķ�������")));
	pGroup->AddSubItem(new CBCGPProp(_T("α��һ����"),_T("0.00"),_T("ͬһ���ǵĲ�ͬƵ���֧·α��һ�������޲��������������档")));
	pGroup->AddSubItem(new CBCGPProp(_T("����ƫ���һ����"),_T("0.00"),_T("ͬһ���ǵĲ�ͬƵ���֧·����ƫ���һ�������޲��������������档")));
	pGroup->AddSubItem(new CBCGPProp(_T("������һ����"),_T("0.00"),_T("ͬһ���ǵĲ�ͬƵ���֧·������һ�������޲��������������档")));
	m_wndPropList.AddProperty (pGroup);
	pGroup = new CBCGPProp(_T("��λ��Ϣ"));
	m_wndPropList.AddProperty (pGroup);
	pGroup = new CBCGPProp(_T("��������"));
	m_wndPropList.AddProperty (pGroup);
	pGroup = new CBCGPProp(_T("��������"));
	m_wndPropList.AddProperty (pGroup);
	pGroup = new CBCGPProp(_T("��Լ����"));
	m_wndPropList.AddProperty (pGroup);
	pGroup = new CBCGPProp(_T("�����ģ�Ͳ���"));
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