// CheckDevDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "CheckDevDlg.h"


// CCheckDevDlg dialog

IMPLEMENT_DYNAMIC(CCheckDevDlg, CBCGPDialog)

CCheckDevDlg::CCheckDevDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CCheckDevDlg::IDD, pParent)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CCheckDevDlg::~CCheckDevDlg()
{
}

void CCheckDevDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SIM, m_tabCtrl);
}


BEGIN_MESSAGE_MAP(CCheckDevDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_CHECK_VERSION, &CCheckDevDlg::OnBnClickedCheckVersion)
	ON_BN_CLICKED(IDC_CHECK_PRM, &CCheckDevDlg::OnBnClickedCheckPrm)
END_MESSAGE_MAP()


// CCheckDevDlg message handlers

BOOL CCheckDevDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rect;
	m_tabCtrl.GetClientRect(rect);
	m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rect, &m_tabCtrl, 2);
	m_wndPropList.EnableToolBar(FALSE);
	m_wndPropList.EnableSearchBox(FALSE);
	m_wndPropList.EnableHeaderCtrl (true,_T("����"),_T("ֵ"));
	m_wndPropList.EnableDesciptionArea ();
	m_wndPropList.SetVSDotNetLook ();
	m_wndPropList.MarkModifiedProperties ();
	m_wndPropList.EnableContextMenu(FALSE);
	m_wndPropList.EndEditItem(FALSE);

	/*SETACK data;
	data.ID = OUT_BDSIM;
	theApp.m_winLinkApp.SetupACKRequest(data);
	Sleep(1000);
	InitPropListSIM();*/

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CCheckDevDlg::InitPropListSIM()
{
	_variant_t val=0;
	CString strAppName;
	char buffer[MAX_PATH];
	CBCGPProp* pGroup=NULL; 
	CBCGPProp* pProp=NULL;
	m_wndPropList.RemoveAll();

	//////////////////////////////////////////////////////////////////////////
	strAppName = "VERSION";
	pGroup = new CBCGPProp(_T("ĸ��-�汾��Ϣ"));
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "DSPVer", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pGroup->AddSubItem(new CBCGPProp(_T("�汾��Ϣ"), val, _T("����汾��Ϣ")));
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "DSPTime", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pGroup->AddSubItem(new CBCGPProp(_T("����ʱ��"), val, _T("��һ�γ������ʱ��")));
	m_wndPropList.AddProperty (pGroup);
	//////////////////////////////////////////////////////////////////////////
	pGroup = new CBCGPProp(_T("B1-�汾��Ϣ"));
	pProp = new CBCGPProp(_T("DSP��Ϣ"), NULL, TRUE);
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "DSPB1Ver", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("�汾��Ϣ"), val, _T("�汾��Ϣ")));
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "DSPB1Time", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("����ʱ��"), val, _T("��һ�γ������ʱ��")));
	pGroup->AddSubItem(pProp);

	pProp = new CBCGPProp(_T("FPGA��Ϣ"), NULL, TRUE);
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "FPGAB1Ver", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("�汾��Ϣ"), val, _T("�汾��Ϣ")));
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "FPGAB1Time", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("����ʱ��"), val, _T("��һ�γ������ʱ��")));
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	//////////////////////////////////////////////////////////////////////////
	pGroup = new CBCGPProp(_T("B2-�汾��Ϣ"));
	pProp = new CBCGPProp(_T("DSP��Ϣ"), NULL, TRUE);
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "DSPB2Ver", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("�汾��Ϣ"), val, _T("�汾��Ϣ")));
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "DSPB2Time", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("����ʱ��"), val, _T("��һ�γ������ʱ��")));
	pGroup->AddSubItem(pProp);

	pProp = new CBCGPProp(_T("FPGA��Ϣ"), NULL, TRUE);
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "FPGAB2Ver", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("�汾��Ϣ"), val, _T("�汾��Ϣ")));
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "FPGAB2Time", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("����ʱ��"), val, _T("��һ�γ������ʱ��")));
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	//////////////////////////////////////////////////////////////////////////
	pGroup = new CBCGPProp(_T("B3-�汾��Ϣ"));
	pProp = new CBCGPProp(_T("DSP��Ϣ"), NULL, TRUE);
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "DSPB3Ver", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("�汾��Ϣ"), val, _T("�汾��Ϣ")));
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "DSPB3Time", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("����ʱ��"), val, _T("��һ�γ������ʱ��")));
	pGroup->AddSubItem(pProp);

	pProp = new CBCGPProp(_T("FPGA��Ϣ"), NULL, TRUE);
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "FPGAB3Ver", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("�汾��Ϣ"), val, _T("�汾��Ϣ")));
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "FPGAB3Time", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("����ʱ��"), val, _T("��һ�γ������ʱ��")));
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	//////////////////////////////////////////////////////////////////////////
	pGroup = new CBCGPProp(_T("Bs/B3AE-�汾��Ϣ"));
	pProp = new CBCGPProp(_T("DSP��Ϣ"), NULL, TRUE);
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "DSPBsVer", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("�汾��Ϣ"), val, _T("�汾��Ϣ")));
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "DSPBsTime", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("����ʱ��"), val, _T("��һ�γ������ʱ��")));
	pGroup->AddSubItem(pProp);

	pProp = new CBCGPProp(_T("FPGA��Ϣ"), NULL, TRUE);
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "FPGABsVer", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("�汾��Ϣ"), val, _T("�汾��Ϣ")));
	ZeroMemory(buffer, sizeof(char)*MAX_PATH);
	GetPrivateProfileString(strAppName, "FPGABsTime", "-", buffer, MAX_PATH, theApp.m_strProjFile);
	val.SetString(buffer);
	pProp->AddSubItem(new CBCGPProp(_T("����ʱ��"), val, _T("��һ�γ������ʱ��")));
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
//////////////////////////////////////////////////////////////////////////
	ResetVER();

	/*delete pProp;
	delete pGroup;*/
}
void CCheckDevDlg::InitPropListPRM()
{
	int temp = 0;
	_variant_t val=0;
	CString strAppName,strText;
	CBCGPProp* pGroup=NULL; 
	CBCGPProp* pProp=NULL;
	m_wndPropList.RemoveAll();
	//////////////////////////////////////////////////////////////////////////
	strAppName = "PRM_B1Q";
	pGroup = new CBCGPProp(_T("B1Q-�źŴ���Ԫ"));
	pProp = new CBCGPProp(_T("PRM��Ч��"), NULL, TRUE);
	temp = GetPrivateProfileInt(strAppName, "prmStartTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ʼʱ��"),val,_T("��ʼʱ��(��λ����)")));
	temp = GetPrivateProfileInt(strAppName, "prmDeadTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ֹʱ��"),val,_T("��ֹʱ��(��λ����)")));
	pGroup->AddSubItem(pProp);

	pProp = new CBCGPProp(_T("MPD007��Ч��"), NULL, TRUE);
	temp = GetPrivateProfileInt(strAppName, "simStartTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ʼʱ��"),val,_T("��ʼʱ��(��λ����)")));
	temp = GetPrivateProfileInt(strAppName, "simDeadTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ֹʱ��"),val,_T("��ֹʱ��(��λ����)")));
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	//////////////////////////////////////////////////////////////////////////
	strAppName = "PRM_B1A";
	pGroup = new CBCGPProp(_T("B1A-�źŴ���Ԫ"));
	pProp = new CBCGPProp(_T("PRM��Ч��"), NULL, TRUE);
	temp = GetPrivateProfileInt(strAppName, "prmStartTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ʼʱ��"),val,_T("��ʼʱ��(��λ����)")));
	temp = GetPrivateProfileInt(strAppName, "prmDeadTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ֹʱ��"),val,_T("��ֹʱ��(��λ����)")));
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	//////////////////////////////////////////////////////////////////////////
	strAppName = "PRM_B3Q";
	pGroup = new CBCGPProp(_T("B3Q-�źŴ���Ԫ"));
	pProp = new CBCGPProp(_T("PRM��Ч��"), NULL, TRUE);
	temp = GetPrivateProfileInt(strAppName, "prmStartTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ʼʱ��"),val,_T("��ʼʱ��(��λ����)")));
	temp = GetPrivateProfileInt(strAppName, "prmDeadTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ֹʱ��"),val,_T("��ֹʱ��(��λ����)")));
	pGroup->AddSubItem(pProp);

	pProp = new CBCGPProp(_T("MPD007��Ч��"), NULL, TRUE);
	temp = GetPrivateProfileInt(strAppName, "simStartTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ʼʱ��"),val,_T("��ʼʱ��(��λ����)")));
	temp = GetPrivateProfileInt(strAppName, "simDeadTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ֹʱ��"),val,_T("��ֹʱ��(��λ����)")));
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	//////////////////////////////////////////////////////////////////////////
	strAppName = "PRM_B3A";
	pGroup = new CBCGPProp(_T("B3A-�źŴ���Ԫ"));
	pProp = new CBCGPProp(_T("PRM��Ч��"), NULL, TRUE);
	temp = GetPrivateProfileInt(strAppName, "prmStartTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ʼʱ��"),val,_T("��ʼʱ��(��λ����)")));
	temp = GetPrivateProfileInt(strAppName, "prmDeadTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ֹʱ��"),val,_T("��ֹʱ��(��λ����)")));
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	//////////////////////////////////////////////////////////////////////////
	strAppName = "PRM_B3AE";
	pGroup = new CBCGPProp(_T("B3AE-�źŴ���Ԫ"));
	pProp = new CBCGPProp(_T("PRM��Ч��"), NULL, TRUE);
	temp = GetPrivateProfileInt(strAppName, "prmStartTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ʼʱ��"),val,_T("��ʼʱ��(��λ����)")));
	temp = GetPrivateProfileInt(strAppName, "prmDeadTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ֹʱ��"),val,_T("��ֹʱ��(��λ����)")));
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	//////////////////////////////////////////////////////////////////////////
	strAppName = "PRM_Bs";
	pGroup = new CBCGPProp(_T("Bs-�źŴ���Ԫ"));
	pProp = new CBCGPProp(_T("PRM��Ч��"), NULL, TRUE);
	temp = GetPrivateProfileInt(strAppName, "prmStartTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ʼʱ��"),val,_T("��ʼʱ��(��λ����)")));
	temp = GetPrivateProfileInt(strAppName, "prmDeadTime", 0, theApp.m_strProjFile);
	strText.Format("%u", temp);
	val.Clear();
	val.SetString((temp==0)?"-":strText);
	pProp->AddSubItem(new CBCGPProp(_T("��ֹʱ��"),val,_T("��ֹʱ��(��λ����)")));
	pGroup->AddSubItem(pProp);
	m_wndPropList.AddProperty (pGroup);
	//////////////////////////////////////////////////////////////////////////
	ResetSIM();
}

void CCheckDevDlg::ResetSIM()
{
	CString strAppName;
	//////////////////////////////////////////////////////////////////////////
	strAppName = "PRM_B1Q";
	WritePrivateProfileString(strAppName, "Flag", "1", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmFlag", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmStartTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmDeadTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simFlag", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simStartTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simDeadTime", "0", theApp.m_strProjFile);
	//////////////////////////////////////////////////////////////////////////
	strAppName = "PRM_B1A";
	WritePrivateProfileString(strAppName, "Flag", "1", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmFlag", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmStartTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmDeadTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simFlag", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simStartTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simDeadTime", "0", theApp.m_strProjFile);
	//////////////////////////////////////////////////////////////////////////
	strAppName = "PRM_B3Q";
	WritePrivateProfileString(strAppName, "Flag", "1", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmFlag", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmStartTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmDeadTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simFlag", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simStartTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simDeadTime", "0", theApp.m_strProjFile);
	//////////////////////////////////////////////////////////////////////////
	strAppName = "PRM_B3A";
	WritePrivateProfileString(strAppName, "Flag", "1", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmFlag", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmStartTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmDeadTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simFlag", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simStartTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simDeadTime", "0", theApp.m_strProjFile);
	//////////////////////////////////////////////////////////////////////////
	strAppName = "PRM_B3AE";
	WritePrivateProfileString(strAppName, "Flag", "1", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmFlag", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmStartTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmDeadTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simFlag", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simStartTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simDeadTime", "0", theApp.m_strProjFile);
	//////////////////////////////////////////////////////////////////////////
	strAppName = "PRM_Bs";
	WritePrivateProfileString(strAppName, "Flag", "1", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmFlag", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmStartTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "prmDeadTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simFlag", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simStartTime", "0", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "simDeadTime", "0", theApp.m_strProjFile);
	//////////////////////////////////////////////////////////////////////////
}
void CCheckDevDlg::ResetVER()
{
	CString strAppName;
	strAppName = "VERSION";
	//////////////////////////////////////////////////////////////////////////
	WritePrivateProfileString(strAppName, "DSPVer", "-", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "DSPTime", "-", theApp.m_strProjFile);
	//////////////////////////////////////////////////////////////////////////
	WritePrivateProfileString(strAppName, "DSPB1Ver", "-", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "DSPB1Time", "-", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "FPGAB1Ver", "-", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "FPGAB1Time", "-", theApp.m_strProjFile);
	//////////////////////////////////////////////////////////////////////////
	WritePrivateProfileString(strAppName, "DSPB2Ver", "-", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "DSPB2Time", "-", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "FPGAB2Ver", "-", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "FPGAB2Time", "-", theApp.m_strProjFile);
	//////////////////////////////////////////////////////////////////////////
	WritePrivateProfileString(strAppName, "DSPB3Ver", "-", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "DSPB3Time", "-", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "FPGAB3Ver", "-", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "FPGAB3Time", "-", theApp.m_strProjFile);
	//////////////////////////////////////////////////////////////////////////
	WritePrivateProfileString(strAppName, "DSPB4Ver", "-", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "DSPB4Time", "-", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "FPGAB4Ver", "-", theApp.m_strProjFile);
	WritePrivateProfileString(strAppName, "FPGAB4Time", "-", theApp.m_strProjFile);
	//////////////////////////////////////////////////////////////////////////

}
void CCheckDevDlg::OnBnClickedCheckVersion()
{
	// TODO: Add your control notification handler code here
	SETACK data;
	data.ID = OUT_BDVER;
	theApp.m_winLinkApp.SetupACKRequest(data);
	Sleep(1000);
	InitPropListSIM();
}

void CCheckDevDlg::OnBnClickedCheckPrm()
{
	// TODO: Add your control notification handler code here
	SETACK data;
	data.ID = OUT_BDSIM;
	theApp.m_winLinkApp.SetupACKRequest(data);
	Sleep(1000);
	InitPropListPRM();
}
