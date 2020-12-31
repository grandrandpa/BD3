// ProjPropertyPage.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ProjPropertyPage.h"


// CProjPropertyPage dialog

IMPLEMENT_DYNAMIC(CProjPropertyPage, CBCGPDialog)

CProjPropertyPage::CProjPropertyPage(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CProjPropertyPage::IDD, pParent)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

CProjPropertyPage::~CProjPropertyPage()
{
}

void CProjPropertyPage::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROPERTY, m_tabCtrl);
	DDX_Control(pDX, IDC_TREE_PROPERTY, m_treeView);
}


BEGIN_MESSAGE_MAP(CProjPropertyPage, CBCGPDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_PROPERTY, &CProjPropertyPage::OnTvnSelchangedTreeProperty)
	ON_BN_CLICKED(IDC_BTN_COMPLETE, &CProjPropertyPage::OnBnClickedBtnComplete)
END_MESSAGE_MAP()


// CProjPropertyPage message handlers

BOOL CProjPropertyPage::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

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
	m_wndMOD.Create(IDD_SET_MOD_DIALOG, &m_tabCtrl);
	m_wndMOD.MoveWindow(rect);
	
	//上位机定位参数
	m_wndREF.Create(IDD_SET_REF_DIALOG, &m_tabCtrl);
	m_wndREF.MoveWindow(rect);
	m_wndREF.EnableSetupControl(false);
	m_wndLocal.Create(IDD_SET_LOCAL_DIALOG, &m_tabCtrl);
	m_wndLocal.MoveWindow(rect);
	m_wndGSV.Create(IDD_SET_GSV_DIALOG, &m_tabCtrl);
	m_wndGSV.MoveWindow(rect);
	m_wndStatic.Create(IDD_SET_STATIC_DIALOG, &m_tabCtrl);
	m_wndStatic.MoveWindow(rect);
	m_wndMonitor.Create(IDD_SET_MONITOR_DIALOG, &m_tabCtrl);
	m_wndMonitor.MoveWindow(rect);
	m_wndLimit.Create(IDD_SET_LIMIT_DIALOG, &m_tabCtrl);
	m_wndLimit.MoveWindow(rect);
	/*m_wndDraw.Create(IDD_SET_DRAW_DIALOG, &m_tabCtrl);
	m_wndDraw.MoveWindow(rect);*/
	HideAllWindow();
	m_wndMOD.ShowWindow(SW_SHOW);

	//delete ImageListTree;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CProjPropertyPage::OnTvnSelchangedTreeProperty(NMHDR *pNMHDR, LRESULT *pResult)
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
	/*if(strSelText == "绘图配置")
	{
		HideAllWindow();
		ShowThisWindow(&m_wndDraw);
	}*/
	if(strSelText == "定位模式")
	{
		HideAllWindow();
		ShowThisWindow(&m_wndMOD);
	}
	if(strSelText == "时空参考")
	{
		HideAllWindow();
		ShowThisWindow(&m_wndREF);
	}
	if(strSelText == "用户位置")
	{
		HideAllWindow();
		ShowThisWindow(&m_wndLocal);
	}
	if (strSelText == "卫星选择")
	{
		HideAllWindow();
		ShowThisWindow(&m_wndGSV);
	}
	if (strSelText == "统计项目")
	{
		HideAllWindow();
		ShowThisWindow(&m_wndStatic);
	}
	if (strSelText == "监测项目")
	{
		HideAllWindow();
		ShowThisWindow(&m_wndMonitor);
	}
	if (strSelText == "门限参数")
	{
		HideAllWindow();
		ShowThisWindow(&m_wndLimit);
	}

	*pResult = 0;
}

void CProjPropertyPage::HideAllWindow(void)
{
	m_wndMOD.ShowWindow(SW_HIDE);
	m_wndREF.ShowWindow(SW_HIDE);
	m_wndGSV.ShowWindow(SW_HIDE);
	m_wndLocal.ShowWindow(SW_HIDE);
	m_wndStatic.ShowWindow(SW_HIDE);
	m_wndMonitor.ShowWindow(SW_HIDE);
	m_wndLimit.ShowWindow(SW_HIDE);
	//m_wndDraw.ShowWindow(SW_HIDE);
}

void CProjPropertyPage::ShowThisWindow(CBCGPDialog* pWnd)
{
	pWnd->ShowWindow(SW_SHOW);
}

void CProjPropertyPage::HideThisWindow(CBCGPDialog* pWnd)
{
	pWnd->ShowWindow(SW_HIDE);
}

void CProjPropertyPage::OnBnClickedBtnComplete()
{
	// TODO: Add your control notification handler code here
	m_wndMOD.SaveConfigure();
	m_wndREF.SaveConfigure();
	m_wndGSV.SaveConfigure();
	m_wndLocal.SaveConfigure();
	m_wndStatic.SaveConfigure();
	m_wndMonitor.SaveConfigure();
	m_wndLimit.SaveConfigure();
	//m_wndDraw.SaveConfigure();

	CBCGPDialog::OnOK();
}
void CProjPropertyPage::Reset()
{
	m_wndMOD.Reset();
	m_wndREF.Reset();
	m_wndGSV.Reset();
	m_wndLocal.Reset();
	m_wndStatic.Reset();
	m_wndMonitor.Reset();
	m_wndLimit.Reset();
	//m_wndDraw.Reset();
}