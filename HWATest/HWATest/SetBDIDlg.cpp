// SetBDIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetBDIDlg.h"


// CSetBDIDlg dialog

IMPLEMENT_DYNAMIC(CSetBDIDlg, CBCGPDialog)

CSetBDIDlg::CSetBDIDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetBDIDlg::IDD, pParent)
{

	CBCGPDialog::EnableVisualManagerStyle(TRUE, TRUE);
}

CSetBDIDlg::~CSetBDIDlg()
{
}

void CSetBDIDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_BDI, m_tabBDI);
}


BEGIN_MESSAGE_MAP(CSetBDIDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_DEFAULT, &CSetBDIDlg::OnBnClickedBtnDefault)
	ON_BN_CLICKED(IDC_BTN_SET, &CSetBDIDlg::OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CSetBDIDlg message handlers

BOOL CSetBDIDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rect;
	m_tabBDI.GetClientRect(rect);
	m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rect, &m_tabBDI, 2);
	InitPropList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetBDIDlg::InitPropList(void)
{
	m_wndPropList.EnableToolBar(FALSE);
	m_wndPropList.EnableSearchBox(FALSE);
	m_wndPropList.EnableHeaderCtrl (true,_T("������"),_T("����ֵ"));
	m_wndPropList.EnableDesciptionArea ();
	m_wndPropList.SetVSDotNetLook ();
	m_wndPropList.MarkModifiedProperties ();
	m_wndPropList.EnableContextMenu();
	//1
	CBCGPProp* pGroup = new CBCGPProp(_T("ʱ��ο�ϵ"));
	CBCGPProp* pProp = new CBCGPProp(_T("ʱ��ο�ϵ"), _T("1-BDT(����ʱ)"), _T("1-BDT(����ʱ)��2-MAT(����ʱ)��4-GPST(GPSʱ)��5-GALILEOT(٤����ʱ)��6-UTC(ͨ��Э��ʱ��)"));
	pProp->AddOption(_T("1-BDT(����ʱ)"));
	pProp->AddOption(_T("2-MAT(����ʱ)"));
	pProp->AddOption(_T("4-GPST(GPSʱ)"));
	pProp->AddOption(_T("5-GALILEOT(٤����ʱ)"));
	pProp->AddOption(_T("6-UTC(ͨ��Э��ʱ��)"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	pProp = new CBCGPProp(_T("ʱ���ʽ"), _T("1-����+������"), _T("0-������+ʱ���롢1-����+������"));
	pProp->AddOption(_T("0-������+ʱ����"));
	pProp->AddOption(_T("1-����+������"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	//2
	pGroup = new CBCGPProp(_T("����ο�ϵ"));
	pProp = new CBCGPProp(_T("����ο�ϵ"), _T("1-CGS2000"), _T("1-CGS2000��2-BJ54(��)��3-WGS84��4-ITRF2000��5-�Զ���"));
	pProp->AddOption(_T("1-CGS2000"));
	pProp->AddOption(_T("2-BJ54(��)"));
	pProp->AddOption(_T("3-WGS84"));
	pProp->AddOption(_T("4-ITRF2000"));
	pProp->AddOption(_T("5-�Զ���"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	pProp = new CBCGPProp(_T("�����ʽ"), _T("1-BLH"), _T("0-XYZ��1-BLH"));
	pProp->AddOption(_T("0-XYZ"));
	pProp->AddOption(_T("1-BLH"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	//3
	pGroup = new CBCGPProp(_T("����ο�ϵ"));
	pGroup->AddSubItem(new CBCGPProp(_T("a"),_T("6378137.0"),_T("�볤��a")));
	pGroup->AddSubItem(new CBCGPProp(_T("f"),_T("0.0033528106811823"),_T("ƫ���ʵ���f")));
	pGroup->AddSubItem(new CBCGPProp(_T("��"),_T("7.292115e-5"),_T("��ת���ٶȦ�")));
	pGroup->AddSubItem(new CBCGPProp(_T("gm"),_T("398600.4418e+9"),_T("������������GM")));
	pGroup->AddSubItem(new CBCGPProp(_T("dx"),_T("0"),_T("�ο�������������dx(���CGS2000����)")));
	pGroup->AddSubItem(new CBCGPProp(_T("dy"),_T("0"),_T("�ο�������������dy(���CGS2000����)")));
	pGroup->AddSubItem(new CBCGPProp(_T("dz"),_T("0"),_T("�ο�������������dz(���CGS2000����)")));
	pGroup->AddSubItem(new CBCGPProp(_T("��"),_T("0"),_T("��X��нǦ�(���CGS2000����ϵ)")));
	pGroup->AddSubItem(new CBCGPProp(_T("��"),_T("0"),_T("��Y��нǦ�(���CGS2000����ϵ)")));
	pGroup->AddSubItem(new CBCGPProp(_T("��"),_T("0"),_T("��Z��нǦ�(���CGS2000����ϵ)")));
	m_wndPropList.AddProperty (pGroup);
	//4
	pGroup = new CBCGPProp(_T("�˿�����"));
	pGroup->AddSubItem(new CBCGPProp(_T("�˿�����"),_T("1"),_T("���ں�")));
	pGroup->AddSubItem(new CBCGPProp(_T("������"),_T("3"),_T("������")));
	m_wndPropList.AddProperty (pGroup);

	//delete pProp;
	//delete pGroup;
}

void CSetBDIDlg::GetPropList(SETREF* data)
{
	CString str;
	str = m_wndPropList.GetProperty(2)->GetSubItem(0)->GetValue().bstrVal;
	data->ellipse.a = strtod(str, NULL);
	str = m_wndPropList.GetProperty(2)->GetSubItem(1)->GetValue().bstrVal;
	data->ellipse.f = strtod(str, NULL);
	str = m_wndPropList.GetProperty(2)->GetSubItem(2)->GetValue().bstrVal;
	data->ellipse.w = strtod(str, NULL);
	str = m_wndPropList.GetProperty(2)->GetSubItem(3)->GetValue().bstrVal;
	data->ellipse.gm = strtod(str, NULL);
	str = m_wndPropList.GetProperty(2)->GetSubItem(4)->GetValue().bstrVal;
	data->ellipse.dx = strtod(str, NULL);
	str = m_wndPropList.GetProperty(2)->GetSubItem(5)->GetValue().bstrVal;
	data->ellipse.dy = strtod(str, NULL);
	str = m_wndPropList.GetProperty(2)->GetSubItem(6)->GetValue().bstrVal;
	data->ellipse.dz = strtod(str, NULL);
	str = m_wndPropList.GetProperty(2)->GetSubItem(7)->GetValue().bstrVal;
	data->ellipse.alpha = strtod(str, NULL);
	str = m_wndPropList.GetProperty(2)->GetSubItem(8)->GetValue().bstrVal;
	data->ellipse.beta = strtod(str, NULL);
	str = m_wndPropList.GetProperty(2)->GetSubItem(9)->GetValue().bstrVal;
	data->ellipse.gamma = strtod(str, NULL);

	str= m_wndPropList.GetProperty(3)->GetSubItem(0)->GetValue().bstrVal;
	data->com.com = atoi(str);
	str= m_wndPropList.GetProperty(3)->GetSubItem(1)->GetValue().bstrVal;
	data->com.baud = atoi(str);

	str= m_wndPropList.GetProperty(0)->GetSubItem(0)->GetValue().bstrVal;
	if(str == "1-BDT(����ʱ)")
	{
		data->timeSys = 1;
	}
	else if(str == "2-MAT(����ʱ)")
	{
		data->timeSys = 2;
	}
	else if(str == "4-GPST(GPSʱ)")
	{
		data->timeSys = 4;
	}
	else if(str == "5-GALILEOT(٤����ʱ)")
	{
		data->timeSys = 5;
	}
	else if(str == "6-UTC(ͨ��Э��ʱ��)")
	{
		data->timeSys = 6;
	}

	str= m_wndPropList.GetProperty(0)->GetSubItem(1)->GetValue().bstrVal;
	if(str == "0-������+ʱ����")
	{
		data->timeFmt = 0;
	}
	else
	{
		data->timeFmt = 1;
	}
	str= m_wndPropList.GetProperty(1)->GetSubItem(0)->GetValue().bstrVal;
	if(str == "1-CGS2000")
	{
		data->posSys = 1;
	}
	else if(str == "2-BJ54(��)")
	{
		data->posSys = 2;
	}
	else if(str == "3-WGS84")
	{
		data->posSys = 3;
	}
	else if(str == "4-ITRF2000")
	{
		data->posSys = 4;
	}
	else if(str == "5-�Զ���")
	{
		data->posSys = 5;
	}
	str= m_wndPropList.GetProperty(1)->GetSubItem(1)->GetValue().bstrVal;
	if(str == "0-XYZ")
	{
		data->posFmt = 0;
	}
	else
	{
		data->posFmt = 1;
	}
}

void CSetBDIDlg::OnBnClickedBtnDefault()
{
	// TODO: Add your control notification handler code here
	m_wndPropList.ResetOriginalValues(TRUE);
}

void CSetBDIDlg::OnBnClickedBtnSet()
{
	// TODO: Add your control notification handler code here
	SETREF data;
	GetPropList(&data);
	theApp.m_winLinkApp.SetupBDIRequest(data);
	m_wndPropList.ResetOriginalValues(TRUE);
	BCGPMessageBox("�������óɹ�");
}
void CSetBDIDlg::Reset()
{
	m_wndPropList.ResetOriginalValues(TRUE);
}