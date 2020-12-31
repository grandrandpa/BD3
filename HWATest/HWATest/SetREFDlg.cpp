// SetREFDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetREFDlg.h"


// CSetREFDlg dialog

IMPLEMENT_DYNAMIC(CSetREFDlg, CBCGPDialog)

CSetREFDlg::CSetREFDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetREFDlg::IDD, pParent)
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE);

}

CSetREFDlg::~CSetREFDlg()
{
}

void CSetREFDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_REF, m_tabREF);
	DDX_Control(pDX, IDC_BTN_SET, m_btnSet);
}


BEGIN_MESSAGE_MAP(CSetREFDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_DEFAULT, &CSetREFDlg::OnBnClickedBtnDefault)
	ON_BN_CLICKED(IDC_BTN_SET, &CSetREFDlg::OnBnClickedBtnSet)
END_MESSAGE_MAP()


// CSetREFDlg message handlers

BOOL CSetREFDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here 
	CRect rect;
	m_tabREF.GetClientRect(rect);
	m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rect, &m_tabREF, 2);
	InitPropList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CSetREFDlg::EnableSetupControl(bool enable)
{
	m_btnSet.EnableWindow(enable);
}
void CSetREFDlg::OnBnClickedBtnDefault()
{
	// TODO: Add your control notification handler code here
}

void CSetREFDlg::OnBnClickedBtnSet()
{
	// TODO: Add your control notification handler code here
	SETREF data;
	GetPropList(&data);
	theApp.m_winLinkApp.SetupREFRequest(data);
	m_wndPropList.ResetOriginalValues(TRUE);
	BCGPMessageBox("�������óɹ�");
}

void CSetREFDlg::InitPropList(void)
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

	//delete pProp;
	//delete pGroup;
}

void CSetREFDlg::GetPropList(SETREF* data)
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

void CSetREFDlg::SetPropList(SETREF data)
{
	CString str; 
	str.Format("%f", data.ellipse.a);
	m_wndPropList.GetProperty(2)->GetSubItem(0)->SetValue(_variant_t(str));
	str.Format("%f", data.ellipse.f);
	m_wndPropList.GetProperty(2)->GetSubItem(1)->SetValue(_variant_t(str));
	str.Format("%f", data.ellipse.w);
	m_wndPropList.GetProperty(2)->GetSubItem(2)->SetValue(_variant_t(str));
	str.Format("%f", data.ellipse.gm);
	m_wndPropList.GetProperty(2)->GetSubItem(3)->SetValue(_variant_t(str));
	str.Format("%f", data.ellipse.dx);
	m_wndPropList.GetProperty(2)->GetSubItem(4)->SetValue(_variant_t(str));
	str.Format("%f", data.ellipse.dy);
	m_wndPropList.GetProperty(2)->GetSubItem(5)->SetValue(_variant_t(str));
	str.Format("%f", data.ellipse.dz);
	m_wndPropList.GetProperty(2)->GetSubItem(6)->SetValue(_variant_t(str));
	str.Format("%f", data.ellipse.alpha);
	m_wndPropList.GetProperty(2)->GetSubItem(7)->SetValue(_variant_t(str));
	str.Format("%f", data.ellipse.beta);
	m_wndPropList.GetProperty(2)->GetSubItem(8)->SetValue(_variant_t(str));
	str.Format("%f", data.ellipse.gamma);
	m_wndPropList.GetProperty(2)->GetSubItem(9)->SetValue(_variant_t(str));

	if(data.timeSys == 1)
	{
		m_wndPropList.GetProperty(0)->GetSubItem(0)->SetValue("1-BDT(����ʱ)");
	}
	else if(data.timeSys == 2)
	{
		m_wndPropList.GetProperty(0)->GetSubItem(0)->SetValue("2-MAT(����ʱ)");
	}
	else if(data.timeSys == 4)
	{
		m_wndPropList.GetProperty(0)->GetSubItem(0)->SetValue("4-GPST(GPSʱ)");
	}
	else if(data.timeSys == 5)
	{
		m_wndPropList.GetProperty(0)->GetSubItem(0)->SetValue("5-GALILEOT(٤����ʱ)");
	}
	else if(data.timeSys == 6)
	{
		m_wndPropList.GetProperty(0)->GetSubItem(0)->SetValue("6-UTC(ͨ��Э��ʱ��)");
	}
	if(data.timeFmt == 0)
	{
		m_wndPropList.GetProperty(0)->GetSubItem(1)->SetValue("0-������+ʱ����");
	}
	else
	{
		m_wndPropList.GetProperty(0)->GetSubItem(1)->SetValue("1-����+������");
	}
	if(data.posSys == 1)
	{
		m_wndPropList.GetProperty(1)->GetSubItem(0)->SetValue("1-CGS2000");
	}
	else if(data.posSys == 2)
	{
		m_wndPropList.GetProperty(1)->GetSubItem(0)->SetValue("2-BJ54(��)");
	}
	else if(data.posSys == 3)
	{
		m_wndPropList.GetProperty(1)->GetSubItem(0)->SetValue("3-WGS84");
	}
	else if(data.posSys == 4)
	{
		m_wndPropList.GetProperty(1)->GetSubItem(0)->SetValue("4-ITRF2000");
	}
	else if(data.posSys == 5)
	{
		m_wndPropList.GetProperty(1)->GetSubItem(0)->SetValue("5-�Զ���");
	}
	if(data.posFmt == 0)
	{
		m_wndPropList.GetProperty(1)->GetSubItem(1)->SetValue("0-XYZ");
	}
	else
	{
		m_wndPropList.GetProperty(1)->GetSubItem(1)->SetValue("1-BLH");
	}

	BCGPMessageBox("�����ظ��ɹ�");
}

void CSetREFDlg::SaveConfigure()
{
	SETREF data;
	CString strText;
	strText.Empty();
	ZeroMemory(&data, sizeof(SETREF));
	strText= m_wndPropList.GetProperty(0)->GetSubItem(0)->GetValue().bstrVal;
	if(strText == "1-BDT(����ʱ)")
	{
		data.timeSys = 1;
	}
	else if(strText == "2-MAT(����ʱ)")
	{
		data.timeSys = 2;
	}
	else if(strText == "4-GPST(GPSʱ)")
	{
		data.timeSys = 4;
	}
	else if(strText == "5-GALILEOT(٤����ʱ)")
	{
		data.timeSys = 5;
	}
	else if(strText == "6-UTC(ͨ��Э��ʱ��)")
	{
		data.timeSys = 6;
	}

	strText= m_wndPropList.GetProperty(0)->GetSubItem(1)->GetValue().bstrVal;
	if(strText == "0-������+ʱ����")
	{
		data.timeFmt = 0;
	}
	else
	{
		data.timeFmt = 1;
	}
	strText= m_wndPropList.GetProperty(1)->GetSubItem(0)->GetValue().bstrVal;
	if(strText == "1-CGS2000")
	{
		data.posSys = 1;
	}
	else if(strText == "2-BJ54(��)")
	{
		data.posSys = 2;
	}
	else if(strText == "3-WGS84")
	{
		data.posSys = 3;
	}
	else if(strText == "4-ITRF2000")
	{
		data.posSys = 4;
	}
	else if(strText == "5-�Զ���")
	{
		data.posSys = 5;
	}
	strText= m_wndPropList.GetProperty(1)->GetSubItem(1)->GetValue().bstrVal;
	if(strText == "0-XYZ")
	{
		data.posFmt = 0;
	}
	else
	{
		data.posFmt = 1;
	}
	strText.Format("%d", data.timeSys);
	WritePrivateProfileString("Reference", "timeSys", strText, theApp.m_strProjFile);
	strText.Format("%d", data.timeFmt);
	WritePrivateProfileString("Reference", "timeFmt", strText, theApp.m_strProjFile);
	strText.Format("%d", data.posSys);
	WritePrivateProfileString("Reference", "posSys", strText, theApp.m_strProjFile);
	strText.Format("%d", data.posFmt);
	WritePrivateProfileString("Reference", "posFmt", strText, theApp.m_strProjFile);

	strText = m_wndPropList.GetProperty(2)->GetSubItem(0)->GetValue().bstrVal;
	WritePrivateProfileString("Reference", "a", strText, theApp.m_strProjFile);

	strText = m_wndPropList.GetProperty(2)->GetSubItem(1)->GetValue().bstrVal;
	WritePrivateProfileString("Reference", "f", strText, theApp.m_strProjFile);

	strText = m_wndPropList.GetProperty(2)->GetSubItem(2)->GetValue().bstrVal;
	WritePrivateProfileString("Reference", "w", strText, theApp.m_strProjFile);

	strText = m_wndPropList.GetProperty(2)->GetSubItem(3)->GetValue().bstrVal;
	WritePrivateProfileString("Reference", "GM", strText, theApp.m_strProjFile);

	strText = m_wndPropList.GetProperty(2)->GetSubItem(4)->GetValue().bstrVal;
	WritePrivateProfileString("Reference", "dx", strText, theApp.m_strProjFile);

	strText = m_wndPropList.GetProperty(2)->GetSubItem(5)->GetValue().bstrVal;
	WritePrivateProfileString("Reference", "dy", strText, theApp.m_strProjFile);

	strText = m_wndPropList.GetProperty(2)->GetSubItem(6)->GetValue().bstrVal;
	WritePrivateProfileString("Reference", "dz", strText, theApp.m_strProjFile);

	strText = m_wndPropList.GetProperty(2)->GetSubItem(7)->GetValue().bstrVal;
	WritePrivateProfileString("Reference", "alpha", strText, theApp.m_strProjFile);

	strText = m_wndPropList.GetProperty(2)->GetSubItem(8)->GetValue().bstrVal;
	WritePrivateProfileString("Reference", "beta", strText, theApp.m_strProjFile);

	strText = m_wndPropList.GetProperty(2)->GetSubItem(9)->GetValue().bstrVal;
	WritePrivateProfileString("Reference", "gamma", strText, theApp.m_strProjFile);
}
void CSetREFDlg::Reset()
{
	m_wndPropList.ResetOriginalValues(TRUE);
}
