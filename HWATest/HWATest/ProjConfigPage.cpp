// ProjConfigPage.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ProjConfigPage.h"


// CProjConfigPage dialog

IMPLEMENT_DYNAMIC(CProjConfigPage, CBCGPPropertyPage)

CProjConfigPage::CProjConfigPage()
	: CBCGPPropertyPage(CProjConfigPage::IDD)
{
	EnableVisualManagerStyle(TRUE);
}

CProjConfigPage::~CProjConfigPage()
{
}

void CProjConfigPage::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_CONFIG, m_treeView);
	DDX_Control(pDX, IDC_TAB_CONFIG, m_tabCtrl);
}


BEGIN_MESSAGE_MAP(CProjConfigPage, CBCGPPropertyPage)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CONFIG, &CProjConfigPage::OnTvnSelchangedTreeConfig)
END_MESSAGE_MAP()


// CProjConfigPage message handlers

BOOL CProjConfigPage::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();

	CRect rect;
	m_tabCtrl.GetClientRect(&rect);
	// TODO:  Add extra initialization here
	HICON Icon[3];
	Icon[0]=AfxGetApp()->LoadIcon(IDI_ICON_USER);
	Icon[1]=AfxGetApp()->LoadIcon(IDI_ICON_SELECT);
	Icon[2]=AfxGetApp()->LoadIcon(IDI_ICON_UNSELECT);
	CImageList *ImageListTree = new CImageList;
	ImageListTree->Create(16, 16, ILC_COLOR32, 3, 3); //16,16为图标分辩率，4,4为该list最多能容纳的图标数
	ImageListTree->SetBkColor(RGB(231,241,254));
	for(int i=0;i<3;i++)
	{
		ImageListTree->Add(Icon[i]); //读入图标
	}
	m_treeView.ModifyStyle(NULL,TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS);
	m_treeView.SetImageList(ImageListTree, TVSIL_NORMAL);
	m_treeView.m_bVisualManagerStyle = true;
	HTREEITEM root;     // 树的根节点的句柄
	root = m_treeView.InsertItem("上位机多模解算设置", 0, 0, TVI_ROOT);
	m_treeView.InsertItem("定位模式", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("时空参考", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("卫星选择", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("用户位置", 2, 1, root, TVI_LAST);
	//m_treeView.InsertItem("绘图配置", 2, 1, root, TVI_LAST);
	m_treeView.Expand(root, TVE_EXPAND);
	/*root = m_treeView.InsertItem("统计分析设置", 0, 0, TVI_ROOT);
	m_treeView.InsertItem("统计项目", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("监测项目", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("门限参数", 2, 1, root, TVI_LAST);
	m_treeView.Expand(root, TVE_EXPAND);*/
	m_setMod.Create(IDD_SET_MOD_DIALOG, &m_tabCtrl);
	m_setMod.MoveWindow(rect);
	
	//上位机定位参数
	m_setREF.Create(IDD_SET_REF_DIALOG, &m_tabCtrl);
	m_setREF.MoveWindow(rect);
	m_setREF.EnableSetupControl(false);
	m_setLocal.Create(IDD_SET_LOCAL_DIALOG, &m_tabCtrl);
	m_setLocal.MoveWindow(rect);
	m_setGSV.Create(IDD_SET_GSV_DIALOG, &m_tabCtrl);
	m_setGSV.MoveWindow(rect);
	m_setStatic.Create(IDD_SET_STATIC_DIALOG, &m_tabCtrl);
	m_setStatic.MoveWindow(rect);
	m_setMonitor.Create(IDD_SET_MONITOR_DIALOG, &m_tabCtrl);
	m_setMonitor.MoveWindow(rect);
	m_setLimit.Create(IDD_SET_LIMIT_DIALOG, &m_tabCtrl);
	m_setLimit.MoveWindow(rect);
	m_setDraw.Create(IDD_SET_DRAW_DIALOG, &m_tabCtrl);
	m_setDraw.MoveWindow(rect);
	HideAllWindow();
	m_setMod.ShowWindow(SW_SHOW);

	//delete ImageListTree;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE 
}

BOOL CProjConfigPage::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	CBCGPPropertySheet* pSheet = (CBCGPPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT/*PSWIZB_FINISH*/);

	return CBCGPPropertyPage::OnSetActive();
}

LRESULT CProjConfigPage::OnWizardNext()
{
	// TODO: Add your specialized code here and/or call the base class
	//UpdateData(TRUE);
	m_setMod.SaveConfigure();
	m_setREF.SaveConfigure();
	m_setGSV.SaveConfigure();
	m_setLocal.SaveConfigure();
	m_setStatic.SaveConfigure();
	m_setMonitor.SaveConfigure();
	m_setLimit.SaveConfigure();
	m_setDraw.SaveConfigure();

	return CBCGPPropertyPage::OnWizardNext();
}

BOOL CProjConfigPage::OnWizardFinish()
{
	// TODO: Add your specialized code here and/or call the base class

	return CBCGPPropertyPage::OnWizardFinish();
}

void CProjConfigPage::OnTvnSelchangedTreeConfig(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeView.GetSelectedItem();
	CString strSelText = m_treeView.GetItemText(hItem);

	if(strSelText == "上位机多模解算设置")
	{
		hItem = m_treeView.GetChildItem(m_treeView.GetRootItem()); //获取第一个子结点
		m_treeView.SelectItem(hItem);
	}
	if (strSelText == "统计分析设置")
	{
		hItem = m_treeView.GetChildItem(hItem); //获取第一个子结点
		m_treeView.SelectItem(hItem);
	}
	if(strSelText == "绘图配置")
	{
		HideAllWindow();
		ShowThisWindow(&m_setDraw);
	}
	if(strSelText == "定位模式")
	{
		HideAllWindow();
		ShowThisWindow(&m_setMod);
	}
	if(strSelText == "时空参考")
	{
		HideAllWindow();
		ShowThisWindow(&m_setREF);
	}
	if(strSelText == "用户位置")
	{
		HideAllWindow();
		ShowThisWindow(&m_setLocal);
	}
	if (strSelText == "卫星选择")
	{
		HideAllWindow();
		ShowThisWindow(&m_setGSV);
	}
	if (strSelText == "统计项目")
	{
		HideAllWindow();
		ShowThisWindow(&m_setStatic);
	}
	if (strSelText == "监测项目")
	{
		HideAllWindow();
		ShowThisWindow(&m_setMonitor);
	}
	if (strSelText == "门限参数")
	{
		HideAllWindow();
		ShowThisWindow(&m_setLimit);
	}

	*pResult = 0;
}

void CProjConfigPage::HideAllWindow(void)
{
	m_setMod.ShowWindow(SW_HIDE);
	m_setREF.ShowWindow(SW_HIDE);
	m_setGSV.ShowWindow(SW_HIDE);
	m_setLocal.ShowWindow(SW_HIDE);
	m_setStatic.ShowWindow(SW_HIDE);
	m_setMonitor.ShowWindow(SW_HIDE);
	m_setLimit.ShowWindow(SW_HIDE);
	m_setDraw.ShowWindow(SW_HIDE);
}

void CProjConfigPage::ShowThisWindow(CBCGPDialog* pWnd)
{
	pWnd->ShowWindow(SW_SHOW);
}

void CProjConfigPage::HideThisWindow(CBCGPDialog* pWnd)
{
	pWnd->ShowWindow(SW_HIDE);
}
