// SetPosDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetPosDlg.h"


// CSetPOSDlg dialog

IMPLEMENT_DYNAMIC(CSetPOSDlg, CBCGPDialog)

CSetPOSDlg::CSetPOSDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetPOSDlg::IDD, pParent)
	, m_dPosAlt(50.0)
	, m_dPosLat(40.0)
	, m_dPosLon(116.0)
	, m_nPosType(0)
	, m_strAltTips(_T(""))
	, m_strLatTips(_T(""))
	, m_strLonTips(_T(""))
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE);

}

CSetPOSDlg::~CSetPOSDlg()
{
}

void CSetPOSDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_POS_TYPE, m_cmbPosType);
	DDX_Control(pDX, IDC_EDIT_POS_ALT, m_editPosAlt);
	DDX_Control(pDX, IDC_EDIT_POS_LAT, m_editPosLat);
	DDX_Control(pDX, IDC_EDIT_POS_LON, m_editPosLon);
	DDX_Control(pDX, IDC_STATIC_TIPS_ALT, m_tipsAlt);
	DDX_Control(pDX, IDC_STATIC_TIPS_LAT, m_tipsLat);
	DDX_Control(pDX, IDC_STATIC_TIPS_LON, m_tipsLon);
	DDX_Text(pDX, IDC_EDIT_POS_ALT, m_dPosAlt);
	DDX_Text(pDX, IDC_EDIT_POS_LAT, m_dPosLat);
	DDX_Text(pDX, IDC_EDIT_POS_LON, m_dPosLon);
	DDX_CBIndex(pDX, IDC_COMBO_POS_TYPE, m_nPosType);
	DDX_Text(pDX, IDC_STATIC_TIPS_ALT, m_strAltTips);
	DDX_Text(pDX, IDC_STATIC_TIPS_LAT, m_strLatTips);
	DDX_Text(pDX, IDC_STATIC_TIPS_LON, m_strLonTips);
	DDX_Control(pDX, IDC_COMBO_MOD, m_cmbPosMod);
}


BEGIN_MESSAGE_MAP(CSetPOSDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_POS_DEFAULT, &CSetPOSDlg::OnBnClickedBtnPosDefault)
	ON_BN_CLICKED(IDC_BTN_POS_SET, &CSetPOSDlg::OnBnClickedBtnPosSet)
	ON_BN_CLICKED(IDC_BTN_POS_CHECK, &CSetPOSDlg::OnBnClickedBtnPosCheck)
	ON_CBN_SELCHANGE(IDC_COMBO_POS_TYPE, &CSetPOSDlg::OnCbnSelchangeComboPosType)
	ON_BN_CLICKED(IDC_BTN_MOD_SET, &CSetPOSDlg::OnBnClickedBtnModSet)
	ON_BN_CLICKED(IDC_BTN_MOD_CHECK, &CSetPOSDlg::OnBnClickedBtnModCheck)
END_MESSAGE_MAP()


// CSetPOSDlg message handlers

BOOL CSetPOSDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int i = 0;
	//下位机定位模式
	for(i=0; i<MAXMODE-1; i++)
	{
		m_cmbPosMod.InsertString(i, strMODE[i]);
	}
	m_cmbPosMod.SetCurSel(0);

	m_cmbPosType.InsertString(0, "BLH形式(度)");
	m_cmbPosType.InsertString(1, "XYZ形式(米)");
	m_cmbPosType.SetCurSel(0);
	m_strLatTips = _T("纬度(度)：");
	m_strLonTips = _T("经度(度)：");
	m_strAltTips = _T("高程(米)：");
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetPOSDlg::OnBnClickedBtnPosDefault()
{
	// TODO: Add your control notification handler code here
	m_cmbPosType.SetCurSel(0);
	m_editPosAlt.SetWindowText("50.00");
	m_editPosLat.SetWindowText("40.00");
	m_editPosLon.SetWindowText("116.00");
}

void CSetPOSDlg::OnBnClickedBtnPosSet()
{
	// TODO: Add your control notification handler code here
	SETPOS data;
	GetPosition(&data);
	theApp.m_winLinkApp.SetupPOSRequest(data);

	BCGPMessageBox("参数设置成功");
}

void CSetPOSDlg::OnBnClickedBtnPosCheck()
{
	// TODO: Add your control notification handler code here
	CString str;
	str.Format("%f", theApp.m_CurPosition.lat);
	m_editPosLat.SetWindowText(str);
	str.Format("%f", theApp.m_CurPosition.lon);
	m_editPosLon.SetWindowText(str);
	str.Format("%f", theApp.m_CurPosition.alt);
	m_editPosAlt.SetWindowText(str);
}

void CSetPOSDlg::GetPosition(SETPOS* data)
{
	CString str;
	UpdateData(TRUE);
	data->type = m_nPosType;
	data->xyz.x = m_dPosLat;
	data->xyz.y = m_dPosLon;
	data->xyz.z = m_dPosAlt;
	str.Format("%d", m_nPosType);
	WritePrivateProfileString("LocalPos", "Type", str, theApp.m_strConfigPath);
	str.Format("%f", m_dPosLat);
	WritePrivateProfileString("LocalPos", "Lat", str, theApp.m_strConfigPath);
	str.Format("%f", m_dPosLon);
	WritePrivateProfileString("LocalPos", "Lon", str, theApp.m_strConfigPath);
	str.Format("%f", m_dPosAlt);
	WritePrivateProfileString("LocalPos", "Alt", str, theApp.m_strConfigPath);
}

void CSetPOSDlg::SetPosition(SETPOS data)
{
	m_nPosType = data.type;
	m_dPosLat = data.xyz.x;
	m_dPosLon = data.xyz.y;
	m_dPosAlt = data.xyz.z;
	UpdateData(FALSE);

	BCGPMessageBox("参数查询成功");
}

void CSetPOSDlg::OnCbnSelchangeComboPosType()
{
	// TODO: Add your control notification handler code here
	int index = m_cmbPosType.GetCurSel();
	switch (index)
	{
	case 0:
		m_strLatTips = _T("纬度(度)：");
		m_strLonTips = _T("经度(度)：");
		m_strAltTips = _T("高程(米)：");
		break;
	case 1:
		m_strLatTips = _T("X（米）：");
		m_strLonTips = _T("Y（米）：");
		m_strAltTips = _T("Z（米）：");
		break;
	default:
		break;
	}
	UpdateData(FALSE);
}

void CSetPOSDlg::OnBnClickedBtnModSet()
{
	// TODO: Add your control notification handler code here
	SETMOD data;
	ZeroMemory(&data, sizeof(SETMOD));
	GetModParameter(&data);
	theApp.m_winLinkApp.SetupMODRequest(data);
	BCGPMessageBox("参数设置成功");
}
void CSetPOSDlg::OnBnClickedBtnModCheck()
{
	SETACK data;
	int mode = 0, index=0;
	data.ID = OUT_GNMOD;
	theApp.m_winLinkApp.SetupACKRequest(data);
	/*Sleep(500);
	mode = GetPrivateProfileInt("GNMOD", "mode", 1, theApp.m_strConfigPath);
	index = ModeToItem(mode);
	if(index < 21)
		m_cmbPosMod.SetCurSel(index);
	BCGPMessageBox("查询参数成功");*/
}
void CSetPOSDlg::GetModParameter(SETMOD* data)
{
	CString strText;
	int mode = m_cmbPosMod.GetCurSel();
	m_cmbPosMod.GetWindowText(strText);
	if("B1I" == strText)
	{
		data->BD1Pos = (1 << 0) & 0xFFFF;
		data->BD1Time = (1 << 0) & 0xFFFF;
		data->BD2Pos = (1 << 0) & 0xFFFF;
		data->BD2Time = (1 << 0) & 0xFFFF;
	}
	else if("B1Q" == strText)
	{
		data->BD1Pos = (1 << 1) & 0xFFFF;
		data->BD1Time = (1 << 1) & 0xFFFF;
		data->BD2Pos = (1 << 1) & 0xFFFF;
		data->BD2Time = (1 << 1) & 0xFFFF;
	}
	else if("B1C" == strText)
	{
		data->BD2Pos = (1 << 2) & 0xFFFF;
		data->BD2Time = (1 << 2) & 0xFFFF;
	}
	else if("B1A" == strText)
	{
		data->BD2Pos = (1 << 3) & 0xFFFF;
		data->BD2Time = (1 << 3) & 0xFFFF;
	}
	else if("B2a" == strText)
	{
		data->BD2Pos = (1 << 4) & 0xFFFF;
		data->BD2Time = (1 << 4) & 0xFFFF;
	}
	else if("B2b_I" == strText)
	{
		data->BD2Pos = (1 << 5) & 0xFFFF;
		data->BD2Time = (1 << 5) & 0xFFFF;
	}
	else if("B2b_Q" == strText)
	{
		data->BD2Pos = (1 << 6) & 0xFFFF;
		data->BD2Time = (1 << 6) & 0xFFFF;
	}
	else if("B3I" == strText)
	{
		data->BD1Pos = (1 << 8) & 0xFFFF;
		data->BD1Time = (1 << 8) & 0xFFFF;
		data->BD2Pos = (1 << 8) & 0xFFFF;
		data->BD2Time = (1 << 8) & 0xFFFF;
	}
	else if("B3Q" == strText)
	{
		data->BD1Pos = (1 << 9) & 0xFFFF;
		data->BD1Time = (1 << 9) & 0xFFFF;
		data->BD2Pos = (1 << 9) & 0xFFFF;
		data->BD2Time = (1 << 9) & 0xFFFF;
	}
	else if("B3C" == strText)
	{
		data->BD2Pos = (1 << 10) & 0xFFFF;
		data->BD2Time = (1 << 10) & 0xFFFF;
	}
	else if("B3A" == strText)
	{
		data->BD2Pos = (1 << 11) & 0xFFFF;
		data->BD2Time = (1 << 11) & 0xFFFF;
	}
	else if("B3AE" == strText)
	{
		data->BD2Pos = (1 << 13) & 0xFFFF;
		data->BD2Time = (1 << 13) & 0xFFFF;
	}
	else if("Bs" == strText)
	{
		data->BD2Pos = (1 << 12) & 0xFFFF;
		data->BD2Time = (1 << 12) & 0xFFFF;
	}
	else if ("B1CB3C" == strText)
	{
		data->BD2Pos = (1 << 2) & 0xFFFF;
		data->BD2Time = (1 << 2) & 0xFFFF;

		data->BD2Pos |= (1 << 10) & 0xFFFF;
		data->BD2Time |= (1 << 10) & 0xFFFF;
	}
	else if ("B1QB3Q" == strText)
	{
		data->BD1Pos = (1 << 1) & 0xFFFF;
		data->BD1Time = (1 << 1) & 0xFFFF;
		data->BD2Pos = (1 << 1) & 0xFFFF;
		data->BD2Time = (1 << 1) & 0xFFFF;

		data->BD1Pos |= (1 << 9) & 0xFFFF;
		data->BD1Time |= (1 << 9) & 0xFFFF;
		data->BD2Pos |= (1 << 9) & 0xFFFF;
		data->BD2Time |= (1 << 9) & 0xFFFF;
	}
	else if ("B1AB3A" == strText)
	{
		data->BD2Pos = (1 << 3) & 0xFFFF;
		data->BD2Time = (1 << 3) & 0xFFFF;

		data->BD2Pos |= (1 << 11) & 0xFFFF;
		data->BD2Time |= (1 << 11) & 0xFFFF;
	}
	else if ("B1AB3AE" == strText)
	{
		data->BD2Pos = (1 << 3) & 0xFFFF;
		data->BD2Time = (1 << 3) & 0xFFFF;

		data->BD2Pos |= (1 << 13) & 0xFFFF;
		data->BD2Time |= (1 << 13) & 0xFFFF;
	}
	else if ("BsB3A" == strText)
	{
		data->BD2Pos = (1 << 12) & 0xFFFF;
		data->BD2Time = (1 << 12) & 0xFFFF;

		data->BD2Pos |= (1 << 11) & 0xFFFF;
		data->BD2Time |= (1 << 11) & 0xFFFF;
	}
	else if ("B1CB2a" == strText)
	{
		data->BD2Pos = (1 << 2) & 0xFFFF;
		data->BD2Time = (1 << 2) & 0xFFFF;

		data->BD2Pos |= (1 << 4) & 0xFFFF;
		data->BD2Time |= (1 << 4) & 0xFFFF;
	}
	else if ("B1CB2B3C" == strText)
	{
		data->BD2Pos = (1 << 2) & 0xFFFF;
		data->BD2Time = (1 << 2) & 0xFFFF;

		data->BD2Pos |= (1 << 6) & 0xFFFF;
		data->BD2Time |= (1 << 6) & 0xFFFF;

		data->BD2Pos |= (1 << 10) & 0xFFFF;
		data->BD2Time |= (1 << 10) & 0xFFFF;
	}
}
void CSetPOSDlg::Reset()
{
	m_nPosType = 0;
	m_dPosLat = 0;
	m_dPosLon = 0;
	m_dPosAlt = 0;
	UpdateData(FALSE);
}