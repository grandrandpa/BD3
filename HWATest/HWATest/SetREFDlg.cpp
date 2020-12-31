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
	BCGPMessageBox("参数设置成功");
}

void CSetREFDlg::InitPropList(void)
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
	CBCGPProp* pGroup = new CBCGPProp(_T("时间参考系"));
	CBCGPProp* pProp = new CBCGPProp(_T("时间参考系"), _T("1-BDT(北斗时)"), _T("1-BDT(北斗时)、2-MAT(军用时)、4-GPST(GPS时)、5-GALILEOT(伽利略时)、6-UTC(通用协调时间)"));
	pProp->AddOption(_T("1-BDT(北斗时)"));
	pProp->AddOption(_T("2-MAT(军用时)"));
	pProp->AddOption(_T("4-GPST(GPS时)"));
	pProp->AddOption(_T("5-GALILEOT(伽利略时)"));
	pProp->AddOption(_T("6-UTC(通用协调时间)"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	pProp = new CBCGPProp(_T("时间格式"), _T("1-周数+周内秒"), _T("0-年月日+时分秒、1-周数+周内秒"));
	pProp->AddOption(_T("0-年月日+时分秒"));
	pProp->AddOption(_T("1-周数+周内秒"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	//2
	pGroup = new CBCGPProp(_T("坐标参考系"));
	pProp = new CBCGPProp(_T("坐标参考系"), _T("1-CGS2000"), _T("1-CGS2000、2-BJ54(新)、3-WGS84、4-ITRF2000、5-自定义"));
	pProp->AddOption(_T("1-CGS2000"));
	pProp->AddOption(_T("2-BJ54(新)"));
	pProp->AddOption(_T("3-WGS84"));
	pProp->AddOption(_T("4-ITRF2000"));
	pProp->AddOption(_T("5-自定义"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	pProp = new CBCGPProp(_T("坐标格式"), _T("1-BLH"), _T("0-XYZ、1-BLH"));
	pProp->AddOption(_T("0-XYZ"));
	pProp->AddOption(_T("1-BLH"));
	pProp->AllowEdit (FALSE);
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	//3
	pGroup = new CBCGPProp(_T("椭球参考系"));
	pGroup->AddSubItem(new CBCGPProp(_T("a"),_T("6378137.0"),_T("半长轴a")));
	pGroup->AddSubItem(new CBCGPProp(_T("f"),_T("0.0033528106811823"),_T("偏心率倒数f")));
	pGroup->AddSubItem(new CBCGPProp(_T("ω"),_T("7.292115e-5"),_T("自转角速度ω")));
	pGroup->AddSubItem(new CBCGPProp(_T("gm"),_T("398600.4418e+9"),_T("地球引力常数GM")));
	pGroup->AddSubItem(new CBCGPProp(_T("dx"),_T("0"),_T("参考椭球中心坐标dx(相对CGS2000质心)")));
	pGroup->AddSubItem(new CBCGPProp(_T("dy"),_T("0"),_T("参考椭球中心坐标dy(相对CGS2000质心)")));
	pGroup->AddSubItem(new CBCGPProp(_T("dz"),_T("0"),_T("参考椭球中心坐标dz(相对CGS2000质心)")));
	pGroup->AddSubItem(new CBCGPProp(_T("α"),_T("0"),_T("与X轴夹角α(相对CGS2000坐标系)")));
	pGroup->AddSubItem(new CBCGPProp(_T("β"),_T("0"),_T("与Y轴夹角β(相对CGS2000坐标系)")));
	pGroup->AddSubItem(new CBCGPProp(_T("γ"),_T("0"),_T("与Z轴夹角γ(相对CGS2000坐标系)")));
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
	if(str == "1-BDT(北斗时)")
	{
		data->timeSys = 1;
	}
	else if(str == "2-MAT(军用时)")
	{
		data->timeSys = 2;
	}
	else if(str == "4-GPST(GPS时)")
	{
		data->timeSys = 4;
	}
	else if(str == "5-GALILEOT(伽利略时)")
	{
		data->timeSys = 5;
	}
	else if(str == "6-UTC(通用协调时间)")
	{
		data->timeSys = 6;
	}

	str= m_wndPropList.GetProperty(0)->GetSubItem(1)->GetValue().bstrVal;
	if(str == "0-年月日+时分秒")
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
	else if(str == "2-BJ54(新)")
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
	else if(str == "5-自定义")
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
		m_wndPropList.GetProperty(0)->GetSubItem(0)->SetValue("1-BDT(北斗时)");
	}
	else if(data.timeSys == 2)
	{
		m_wndPropList.GetProperty(0)->GetSubItem(0)->SetValue("2-MAT(军用时)");
	}
	else if(data.timeSys == 4)
	{
		m_wndPropList.GetProperty(0)->GetSubItem(0)->SetValue("4-GPST(GPS时)");
	}
	else if(data.timeSys == 5)
	{
		m_wndPropList.GetProperty(0)->GetSubItem(0)->SetValue("5-GALILEOT(伽利略时)");
	}
	else if(data.timeSys == 6)
	{
		m_wndPropList.GetProperty(0)->GetSubItem(0)->SetValue("6-UTC(通用协调时间)");
	}
	if(data.timeFmt == 0)
	{
		m_wndPropList.GetProperty(0)->GetSubItem(1)->SetValue("0-年月日+时分秒");
	}
	else
	{
		m_wndPropList.GetProperty(0)->GetSubItem(1)->SetValue("1-周数+周内秒");
	}
	if(data.posSys == 1)
	{
		m_wndPropList.GetProperty(1)->GetSubItem(0)->SetValue("1-CGS2000");
	}
	else if(data.posSys == 2)
	{
		m_wndPropList.GetProperty(1)->GetSubItem(0)->SetValue("2-BJ54(新)");
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
		m_wndPropList.GetProperty(1)->GetSubItem(0)->SetValue("5-自定义");
	}
	if(data.posFmt == 0)
	{
		m_wndPropList.GetProperty(1)->GetSubItem(1)->SetValue("0-XYZ");
	}
	else
	{
		m_wndPropList.GetProperty(1)->GetSubItem(1)->SetValue("1-BLH");
	}

	BCGPMessageBox("参数回复成功");
}

void CSetREFDlg::SaveConfigure()
{
	SETREF data;
	CString strText;
	strText.Empty();
	ZeroMemory(&data, sizeof(SETREF));
	strText= m_wndPropList.GetProperty(0)->GetSubItem(0)->GetValue().bstrVal;
	if(strText == "1-BDT(北斗时)")
	{
		data.timeSys = 1;
	}
	else if(strText == "2-MAT(军用时)")
	{
		data.timeSys = 2;
	}
	else if(strText == "4-GPST(GPS时)")
	{
		data.timeSys = 4;
	}
	else if(strText == "5-GALILEOT(伽利略时)")
	{
		data.timeSys = 5;
	}
	else if(strText == "6-UTC(通用协调时间)")
	{
		data.timeSys = 6;
	}

	strText= m_wndPropList.GetProperty(0)->GetSubItem(1)->GetValue().bstrVal;
	if(strText == "0-年月日+时分秒")
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
	else if(strText == "2-BJ54(新)")
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
	else if(strText == "5-自定义")
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
