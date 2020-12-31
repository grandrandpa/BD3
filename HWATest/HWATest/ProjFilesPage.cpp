// ProjFilesPage.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ProjFilesPage.h"


// CProjFilesPage dialog

IMPLEMENT_DYNAMIC(CProjFilesPage, CBCGPPropertyPage)

CProjFilesPage::CProjFilesPage()
	: CBCGPPropertyPage(CProjFilesPage::IDD)
	, m_strProjName(_T(""))
	, m_strProjPath(_T(""))
{
	EnableVisualManagerStyle();
	m_nProjectType = -1;
}

CProjFilesPage::~CProjFilesPage()
{
}

void CProjFilesPage::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PROJ_PATH, m_cmbProjPath);
	DDX_Control(pDX, IDC_EDIT_PROJ_NAME, m_editProjName);
	DDX_Control(pDX, IDC_EDIT_PROJ_TIPS, m_editTips);
	DDX_Control(pDX, IDC_LIST_PROJ, m_listCtrl);
	DDX_Control(pDX, IDC_TREE_PROJ, m_treeCtrl);
	DDX_Text(pDX, IDC_EDIT_PROJ_NAME, m_strProjName);
	DDX_CBString(pDX, IDC_COMBO_PROJ_PATH, m_strProjPath);
}


BEGIN_MESSAGE_MAP(CProjFilesPage, CBCGPPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_PROJ_SET, &CProjFilesPage::OnBnClickedButtonProjSet)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PROJ, &CProjFilesPage::OnLvnItemchangedListProj)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_PROJ, &CProjFilesPage::OnTvnSelchangedTreeProj)
END_MESSAGE_MAP()


// CProjFilesPage message handlers

BOOL CProjFilesPage::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();

	// TODO:  Add extra initialization here
	char buff[MAX_PATH];
	CString str;
	SHGetSpecialFolderPath(NULL, buff, CSIDL_DESKTOP, FALSE);
	str = CString(buff);
	m_cmbProjPath.InsertString(0, str);
	GetPrivateProfileString("Product", "WorkSpace", "", buff, MAX_PATH, "config.ini");
	str = CString(buff);
	if (str.IsEmpty())
	{
		GetCurrentDirectory(255, buff);
		str = CString(buff);
		m_cmbProjPath.InsertString(1, str+"\\Projects");
	}
	else
		m_cmbProjPath.InsertString(1, str);
	m_cmbProjPath.SetCurSel(1);
	//////////////////////////////////////////////////////////////////////////
	CTime tt = CTime::GetCurrentTime();
	str.Format("%04d%02d%02d-%02d%02d%02d", tt.GetYear(), tt.GetMonth(), tt.GetDay(), tt.GetHour(), tt.GetMinute(), tt.GetSecond());
	m_editProjName.SetWindowText(str);
	//////////////////////////////////////////////////////////////////////////
	HICON Icon[5];
	Icon[0]=AfxGetApp()->LoadIcon(IDI_ICON_USER);
	Icon[1]=AfxGetApp()->LoadIcon(IDI_ICON_SELECT);
	Icon[2]=AfxGetApp()->LoadIcon(IDI_ICON_UNSELECT);
	Icon[3]=AfxGetApp()->LoadIcon(IDI_ICON_TEST);
	Icon[4]=AfxGetApp()->LoadIcon(IDI_ICON_DEBUG);
	CImageList *ImageListTree = new CImageList;
	ImageListTree->Create(16, 16, ILC_COLOR32, 3, 3); //16,16Ϊͼ��ֱ��ʣ�4,4Ϊ��list��������ɵ�ͼ����
	ImageListTree->SetBkColor(RGB(231,241,254));
	for(int i=0;i<3;i++)
	{
		ImageListTree->Add(Icon[i]); //����ͼ��
	}
	//////////////////////////////////////////////////////////////////////////
	m_treeCtrl.ModifyStyle(NULL,TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS);
	m_treeCtrl.SetImageList(ImageListTree, TVSIL_NORMAL);
	HTREEITEM hRoot = m_treeCtrl.InsertItem("������Ŀ", 0, 0, TVI_ROOT);
	m_treeCtrl.InsertItem("��������", 2, 1, hRoot, TVI_LAST);
	m_treeCtrl.InsertItem("��������", 2, 1, hRoot, TVI_LAST);
	m_treeCtrl.Expand(hRoot, TVE_EXPAND);
	//////////////////////////////////////////////////////////////////////////
	CImageList *ImageListTab = new CImageList;
	ImageListTab->Create(32, 32, ILC_COLOR32, 3, 3); //16,16Ϊͼ��ֱ��ʣ�4,4Ϊ��list��������ɵ�ͼ����
	ImageListTab->Add(Icon[3]);
	ImageListTab->Add(Icon[4]);
	m_listCtrl.SetImageList(ImageListTab, TVSIL_NORMAL);
	m_listCtrl.InsertItem(0, "���Ƕ�λ", 0);
	m_listCtrl.InsertItem(1, "������ʱ", 1);

	m_nProjectType = 0;
	m_editTips.SetWindowText("�������Ƕ�λ������Ŀ");

	//delete ImageListTab;
	//delete ImageListTree;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CProjFilesPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	CBCGPPropertySheet* pSheet = (CBCGPPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_NEXT);

	return CBCGPPropertyPage::OnSetActive();
}

LRESULT CProjFilesPage::OnWizardNext()
{
	// TODO: Add your specialized code here and/or call the base class
	CString str;
	if(m_nProjectType == -1)
	{
		BCGPMessageBox("��ѡ��Ҫ��������Ŀ����");
		return -1;
	}
	theApp.m_nProjectType = m_nProjectType;
	theApp.m_strSaveData.Empty();
	//////////////////////////////////////////////////////////////////////////
	UpdateData(TRUE);
	theApp.m_strProjPath = m_strProjPath + "\\" + m_strProjName;
	theApp.m_strProjName = m_strProjName;
	theApp.m_strProjFile = theApp.m_strProjPath + "\\" + theApp.m_strProjName + ".xproj";
	theApp.m_strDatabase = theApp.m_strProjPath + "\\Database\\";
	//str.Format("\\OriginData\\%s.ori", m_strProjName);
	theApp.m_strOriginData = theApp.m_strProjPath + "\\OriginData\\";//·��
	theApp.m_strPictures = theApp.m_strProjPath + "\\images\\";
	theApp.m_strSatPath = theApp.m_strProjPath + "\\Database\\SAT\\";

	//�ȴ��������ļ���·��
	CreateDirectory(theApp.m_strProjPath, NULL);
	CreateDirectory(theApp.m_strProjPath+"\\Database", NULL);
	CreateDirectory(theApp.m_strProjPath+"\\OriginData", NULL);
	CreateDirectory(theApp.m_strProjPath+"\\SaveData", NULL);
	CreateDirectory(theApp.m_strProjPath+"\\Database\\SAT", NULL);
	//��Ŀ�ļ�
	WritePrivateProfileString("Product", "WorkSpace", m_strProjPath, "config.ini");
	str.Format("%d", m_nProjectType);
	WritePrivateProfileString("Product", "ProjType", str, theApp.m_strProjFile);
	WritePrivateProfileString("Product", "Protocol", "0", theApp.m_strProjFile);
	WritePrivateProfileString("Product", "ProjName", theApp.m_strProjName, theApp.m_strProjFile);
	WritePrivateProfileString("Product", "ProjPath", theApp.m_strProjPath, theApp.m_strProjFile);
	WritePrivateProfileString("Product", "ProjFile", theApp.m_strProjFile, theApp.m_strProjFile);
	WritePrivateProfileString("Product", "ProjOrigin", theApp.m_strOriginData, theApp.m_strProjFile);
	WritePrivateProfileString("Product", "SaveData", "", theApp.m_strProjFile);
	WritePrivateProfileString("Product", "ProjData", theApp.m_strDatabase, theApp.m_strProjFile);
	WritePrivateProfileString("Product", "ProjImage", theApp.m_strPictures, theApp.m_strProjFile);
	WritePrivateProfileString("Product", "ProjSat", theApp.m_strSatPath, theApp.m_strProjFile);
	//�������ݴ洢�ļ�
	WritePrivateProfileString("FILE", "codFile", "COD.table", theApp.m_strProjFile);
	WritePrivateProfileString("FILE", "ephFile", "EPH.table", theApp.m_strProjFile);
	WritePrivateProfileString("FILE", "ionFile", "ION.table", theApp.m_strProjFile);
	WritePrivateProfileString("FILE", "almFile", "ALM.table", theApp.m_strProjFile);
	WritePrivateProfileString("FILE", "jalFile", "JAL.table", theApp.m_strProjFile);
	WritePrivateProfileString("FILE", "modFile", "MOD.table", theApp.m_strProjFile);
	WritePrivateProfileString("FILE", "posFile", "POS.table", theApp.m_strProjFile);
	WritePrivateProfileString("FILE", "xpvFile", "POS.table", theApp.m_strProjFile);
	WritePrivateProfileString("FILE", "ranFile", "RAN.table", theApp.m_strProjFile);
	WritePrivateProfileString("FILE", "refFile", "REF.table", theApp.m_strProjFile);
	WritePrivateProfileString("FILE", "gsvFile", "GSV.table", theApp.m_strProjFile);
	WritePrivateProfileString("FILE", "staFile", "STA.table", theApp.m_strProjFile);
	WritePrivateProfileString("FILE", "timFile", "TIM.table", theApp.m_strProjFile);
	WritePrivateProfileString("FILE", "gbsFile", "GBS.table", theApp.m_strProjFile);
	WriteTableHeader(theApp.m_strDatabase);

	return CBCGPPropertyPage::OnWizardNext();
}
void CProjFilesPage::WriteTableHeader(CString strPath)
{
	int len=0;
	char buf[MAX_BUFFER];
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"BD:���Ǳ��-�źŷ���-PRM��ʶ-����\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"COD.table");
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"BD1:�ܼ���-������-���Ǳ��-�źŷ���-iode-toe-sqrta-m0-e-��-omega0-i0-omegadot-idot-cis-cic-crs-crc-cus-cuc-iodc-toc-a0-a1-a2-Tgd1-Tgd2\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"EPH.table");
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"BD2:�ܼ���-������-���Ǳ��-�źŷ���-iode-toe-deltaA-adot-deltaN-ndot-e-w-omega0-i0-omegadot-idot-cis-cic-crs-crc-cus-cuc-iodc-toc-a0-a1-a2-Tgd1-Tgd2-Tgd3\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"EPH.table");
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"BD1:�ܼ���-������-���Ǳ��-�źŷ���-A1-B-alpha0-alpha1-alpha2-alpha3-beta0-beta1-beta2-beta3-gamma0-gamma1-gamma2-gamma3\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"ION.table");
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"BD2:�ܼ���-������-���Ǳ��-�źŷ���-a1-a2-a3-a4-a5-a6-a7-a8-a9\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"ION.table");
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"BD:���Ǳ��-�źŷ���-WNa-SatH-toa-e-��i-sqrta-omega0-omegadot-��-m0-af0-af1\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"ALM.table");
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"BD:���Ǳ��-�źŷ���-��A-omega0-��0-health\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"JAL.table");
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"�����Ƕ�λģʽ-һ���Ƕ�λģʽ-GPS��λģʽ-Gal��λģʽ-������ģʽ-��������ʱģʽ-һ������ʱģʽ-GPS��ʱģʽ-Gal��ʱģʽ\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"MOD.table");
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"�ܼ���-������-��������-����������-����ʹ��������-γ��-����-�߳�-ˮƽ�ٶ�-��ֱ�ٶ�-�����Ӳ�-HDOP-VDOP-PDOP-TDOP-GDOP-������ʹ�õ����Ǳ��\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"POS.table");
	RecordFile(buf,len, strPath+"XPV.table");
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"�ܼ���-������-�۲�������-���Ǳ��-�źŷ���-α�����ֵ-�ز���λ����ֵ-�����ղ���ֵ-�����-ͨ������״̬\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"RAN.table");
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"ʱ��ο�ϵ-ʱ���ʽ-����ο�ϵ-�����ʽ-a-f-w-GM-dx-dy-dz-alpha-beta-gamma\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"REF.table");
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"�ɼ�������-���Ǳ��-����-��λ��-�����\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"GSV.table");
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"�ܼ���-������-�ն�ϵ�к�-������״̬-���״̬-ʱ��״̬-1PPS״̬\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"STA.table");
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"�ܼ���-������-����ģʽ-��ʱģʽ-���ñ�׼ʱ��-����-�����Ӳ�-����ʹ�����Ǳ��\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"TIM.table");
	ZeroMemory(buf, sizeof(char)*MAX_BUFFER);
	sprintf(buf,"�ܼ���-������-γ��Ԥ�����-����Ԥ�����-�߳�Ԥ�����-�������Ǳ��-��������©�����-�������ǹ���ƫ��-ƫ�ù���ı�׼ƫ��\r\n");
	len = strlen(buf);
	RecordFile(buf,len, strPath+"GBS.table");
}
void CProjFilesPage::OnBnClickedButtonProjSet()
{
	// TODO: Add your control notification handler code here
	CString strfilePath;
	HWND hwnd = GetSafeHwnd();
	LPMALLOC pMalloc;
	if(::SHGetMalloc(&pMalloc) == NOERROR)
	{
		BROWSEINFO bi;
		TCHAR      pszBuffer[MAX_PATH];
		LPITEMIDLIST pidl;
		ZeroMemory(&bi, sizeof(BROWSEINFO));
		bi.hwndOwner       = GetSafeHwnd();
		bi.pidlRoot        = NULL;
		bi.pszDisplayName  = pszBuffer;
		bi.lpszTitle	   = _T("��ѡ����Ŀ����·��");

		bi.ulFlags = BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn    = NULL;
		bi.lParam  = 0;
		bi.iImage  = 0;

		if((pidl = SHBrowseForFolder(&bi)) != NULL)
		{
			if(SHGetPathFromIDList(pidl, pszBuffer))
			{
				strfilePath = pszBuffer;
				strfilePath.ReleaseBuffer();
				//((CComboBox *)GetDlgItem(IDC_COMBO_PROJ_PATH))->SetWindowText(strfilePath);
				//SetDlgItemText(IDC_COMBO_PROJ_PATH, strfilePath);
				m_cmbProjPath.SetWindowText(strfilePath);
			}
			pMalloc->Free(pidl);
		}
		pMalloc->Release();
	}
}

void CProjFilesPage::OnLvnItemchangedListProj(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(pNMLV->uNewState & LVIS_SELECTED)
	{
		if(pNMLV->iItem == 0)
		{
			m_nProjectType = 0;
			m_editTips.SetWindowText("�������Ƕ�λ������Ŀ");
		}
		else if(pNMLV->iItem == 1)
		{
			m_nProjectType = 1;
			m_editTips.SetWindowText("����������ʱ������Ŀ");
		}
		//str.Format("ѡ�У�%02d", pNMLV->iItem);
	}
	else
	{
		//if(pNMLV->iItem == -1)
		{
			m_nProjectType = -1;
			m_editTips.SetWindowText("��ѡ�񴴽���Ŀ������");
		}
	}
	*pResult = 0;
}

void CProjFilesPage::OnTvnSelchangedTreeProj(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeCtrl.GetSelectedItem();
	CString strSelText = m_treeCtrl.GetItemText(hItem);

	if(strSelText == "������Ŀ")
	{
		hItem = m_treeCtrl.GetChildItem(m_treeCtrl.GetRootItem()); //��ȡ��һ���ӽ��
		m_treeCtrl.SelectItem(hItem);
	}
	*pResult = 0;
}
