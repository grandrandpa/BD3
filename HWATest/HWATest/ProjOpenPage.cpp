// ProjOpenPage.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ProjOpenPage.h"


// CProjOpenPage dialog

IMPLEMENT_DYNAMIC(CProjOpenPage, CBCGPDialog)

CProjOpenPage::CProjOpenPage(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CProjOpenPage::IDD, pParent)
	, m_strProjFileName(_T(""))
	, m_nProjectType(0)
{
	m_nProjectItem = 0;
	EnableVisualManagerStyle(TRUE);
}

CProjOpenPage::~CProjOpenPage()
{
}

void CProjOpenPage::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_PROJ, m_treeCtrl);
	DDX_Control(pDX, IDC_LIST_PROJ, m_listCtrl);
	DDX_Control(pDX, IDC_EDIT_PROJ_TIPS, m_editTips);
	DDX_Control(pDX, IDC_COMBO_PROJ_PATH, m_cmbProjPath);
	DDX_CBString(pDX, IDC_COMBO_PROJ_PATH, m_strProjFileName);
}


BEGIN_MESSAGE_MAP(CProjOpenPage, CBCGPDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_PROJ, &CProjOpenPage::OnTvnSelchangedTreeProj)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_PROJ, &CProjOpenPage::OnLvnItemchangedListProj)
	ON_BN_CLICKED(IDC_BUTTON_PROJ_SET, &CProjOpenPage::OnBnClickedButtonProjSet)
END_MESSAGE_MAP()


// CProjOpenPage message handlers

BOOL CProjOpenPage::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
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

	//m_nProjectType = 0;
	//m_editTips.SetWindowText("�������Ƕ�λ������Ŀ");
	//delete ImageListTab;
	//delete ImageListTree;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CProjOpenPage::OnTvnSelchangedTreeProj(NMHDR *pNMHDR, LRESULT *pResult)
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
	else if (strSelText == "��������")
	{
		m_nProjectItem = 0;
		m_listCtrl.SetItemText(0, 0, "��λ����");
		m_listCtrl.SetItemText(1, 0, "��ʱ����");
	}
	else if (strSelText == "��������")
	{
		m_nProjectItem = 1;
		m_listCtrl.SetItemText(0, 0, "��λ����");
		m_listCtrl.SetItemText(1, 0, "��ʱ����");
	}

	*pResult = 0;
}

void CProjOpenPage::OnLvnItemchangedListProj(NMHDR *pNMHDR, LRESULT *pResult)
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

void CProjOpenPage::OnBnClickedButtonProjSet()
{
	// TODO: Add your control notification handler code here
	/*if(m_nProjectType == -1)
	{
		BCGPMessageBox("��ѡ�����Ŀ������");
		return;
	}*/

	char buff[MAX_PATH];
	GetCurrentDirectory(255, buff);
	CString strfile = "PJT Files(*.xproj)|*.xproj|ALL Files(*.*)|*.*||";
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strfile);
	dlg.m_ofn.lpstrInitialDir = CString(buff);
	if(dlg.DoModal() == IDOK)
	{
		strfile = dlg.GetPathName();
		m_cmbProjPath.SetWindowText(strfile);
		WritePrivateProfileString("Product", "RecentProjName", strfile, theApp.m_strConfigPath);
		m_strProjFileName = strfile;
	}
}
