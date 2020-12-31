// SystemPane.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SystemPane.h"


// CSystemPane dialog

IMPLEMENT_DYNAMIC(CSystemPane, CBCGPDialog)

CSystemPane::CSystemPane(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSystemPane::IDD, pParent)
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE, TRUE);
}

CSystemPane::~CSystemPane()
{
}

void CSystemPane::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_PROPERTY_SET, m_treeView);
	DDX_Control(pDX, IDC_TAB_PROPERTY_SET, m_tabCtrl);
}


BEGIN_MESSAGE_MAP(CSystemPane, CBCGPDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_PROPERTY_SET, &CSystemPane::OnTvnSelchangedTreePropertySet)
END_MESSAGE_MAP()


// CSystemPane message handlers

BOOL CSystemPane::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

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
	root = m_treeView.InsertItem("终端机设置", 0, 0, TVI_ROOT);
	m_treeView.InsertItem("定位模式", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("授时模式", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("工作模式", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("入站信号发射", 2, 1, root, TVI_LAST);	
	m_treeView.InsertItem("时空参数", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("通道配置", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("定时配置", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("引导捕获", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("数据导频", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("系统时差", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("相关带宽", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("首次启动", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("格网模型", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("输出控制", 2, 1, root, TVI_LAST);
	//m_treeView.InsertItem("调制解调", 2, 1, root, TVI_LAST);//
	m_treeView.Expand(root, TVE_EXPAND);
	root = m_treeView.InsertItem("信号处理单元", 0, 0, TVI_ROOT);
	m_treeView.InsertItem("B1I", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("B1Q", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("B1C", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("B1A", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("B2a", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("B2b", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("B2", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("B3I", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("B3Q", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("B3C", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("B3A", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("B3AE", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("Bs", 2, 1, root, TVI_LAST);
	//m_treeView.Expand(root, TVE_EXPAND);
	//////////////////////////////////////////////////////////////////////////
	setPOS.Create(IDD_SET_POS_DIALOG,	&m_tabCtrl);
	setREF.Create(IDD_SET_REF_DIALOG,	&m_tabCtrl);
	setCHA.Create(IDD_SET_CHA_DIALOG,	&m_tabCtrl);
	setWID.Create(IDD_SET_WID_DIALOG,	&m_tabCtrl);
	setLOG.Create(IDD_SET_LOG_DIALOG,	&m_tabCtrl);
	setTIM.Create(IDD_SET_TIM_DIALOG,	&m_tabCtrl);
	setMUT.Create(IDD_SET_MUT_DIALOG,	&m_tabCtrl);
	setEAC.Create(IDD_SET_EAC_DIALOG,	&m_tabCtrl);
	setBGT.Create(IDD_SET_BGT_DIALOG,	&m_tabCtrl);
	setSTS.Create(IDD_SET_STS_DIALOG,	&m_tabCtrl);//
	setACQ.Create(IDD_SET_ACQ_DIALOG,	&m_tabCtrl);
	setION.Create(IDD_SET_ION_DIALOG,	&m_tabCtrl);
	setPILOT.Create(IDD_SET_PILOT_DIALOG,	&m_tabCtrl);//setModual
	setTimMod.Create(IDD_SET_TIMMOD_DIALOG,	&m_tabCtrl);
	setModual.Create(IDD_SET_MODUAL_DIALOG,	&m_tabCtrl);
	setWorkMod.Create(IDD_SET_WORK_DIALOG,	&m_tabCtrl);//工作模式
	setIST.Create(IDD_SET_IST_DIALOG,	&m_tabCtrl);//入站信号发射

	CRect m_rect;
	m_tabCtrl.GetClientRect(&m_rect);
	InitRectPane(m_rect);//

	//delete ImageListTree;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSystemPane::OnTvnSelchangedTreePropertySet(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = m_treeView.GetSelectedItem();
	CString strSelText = m_treeView.GetItemText(hItem);

	if(strSelText == "终端机设置")
	{
		hItem = m_treeView.GetChildItem(m_treeView.GetRootItem()); //获取第一个子结点
		m_treeView.SelectItem(hItem);
	}
	//////////////////////////////////////////
	if(strSelText == "B1I")
	{
		HideAllWindow();
		ShowThisWindow(&setACQ);
		setACQ.InitComboBox(CH_B1I);
	}
	if(strSelText == "B1Q")
	{
		HideAllWindow();
		ShowThisWindow(&setACQ);
		setACQ.InitComboBox(CH_B1Q);
	}
	if(strSelText == "B1C")
	{
		HideAllWindow();
		ShowThisWindow(&setACQ);
		setACQ.InitComboBox(CH_B1C);
	}
	if(strSelText == "B1A")
	{
		HideAllWindow();
		ShowThisWindow(&setACQ);
		setACQ.InitComboBox(CH_B1A);
	}
	//////////////////////////////////////////
	if(strSelText == "B2a")
	{
		HideAllWindow();
		ShowThisWindow(&setACQ);
		setACQ.InitComboBox(CH_B2a);
	}
	if(strSelText == "B2b")
	{
		HideAllWindow();
		ShowThisWindow(&setACQ);
		setACQ.InitComboBox(CH_B2b);
	}
	if(strSelText == "B2")
	{
		HideAllWindow();
		ShowThisWindow(&setACQ);
		setACQ.InitComboBox(CH_B2);
	}
	//////////////////////////////////////////
	if(strSelText == "B3I")
	{
		HideAllWindow();
		ShowThisWindow(&setACQ);
		setACQ.InitComboBox(CH_B3I);
	}
	if(strSelText == "B3Q")
	{
		HideAllWindow();
		ShowThisWindow(&setACQ);
		setACQ.InitComboBox(CH_B3Q);
	}
	if(strSelText == "B3C")
	{
		HideAllWindow();
		ShowThisWindow(&setACQ);
		setACQ.InitComboBox(CH_B3C);
	}
	if(strSelText == "B3A")
	{
		HideAllWindow();
		ShowThisWindow(&setACQ);
		setACQ.InitComboBox(CH_B3A);
	}
	if(strSelText == "B3AE")
	{
		HideAllWindow();
		ShowThisWindow(&setACQ);
		setACQ.InitComboBox(CH_B3AE);
	}
	////////////////////////////////////
	if(strSelText == "Bs")
	{
		HideAllWindow();
		ShowThisWindow(&setACQ);
		setACQ.InitComboBox(CH_Bs);
	}
	////////////////////////////////////

	if(strSelText == "首次启动")
	{
		HideAllWindow();
		ShowThisWindow(&setMUT);
	}
	if(strSelText == "引导捕获")
	{
		HideAllWindow();
		ShowThisWindow(&setEAC);
	}
	if(strSelText == "系统时差")
	{
		HideAllWindow();
		ShowThisWindow(&setBGT);
	}
	if(strSelText == "信号状态")
	{
		HideAllWindow();
		ShowThisWindow(&setSTS);
	}
	if(strSelText == "时空参数")
	{
		HideAllWindow();
		ShowThisWindow(&setREF);
	}
	if(strSelText == "定位模式")
	{
		HideAllWindow();
		ShowThisWindow(&setPOS);
	}
	if(strSelText == "通道配置")
	{
		HideAllWindow();
		ShowThisWindow(&setCHA);
	}
	if(strSelText == "相关带宽")
	{
		HideAllWindow();
		ShowThisWindow(&setWID);
	}
	if(strSelText == "输出控制")
	{
		HideAllWindow();
		ShowThisWindow(&setLOG);
	}
	if(strSelText == "定时配置")
	{
		HideAllWindow();
		ShowThisWindow(&setTIM);
	}
	if(strSelText == "授时模式")//
	{
		HideAllWindow();
		ShowThisWindow(&setTimMod);
	}
	if(strSelText == "工作模式")//
	{
		HideAllWindow();
		ShowThisWindow(&setWorkMod);
	}	
	if(strSelText == "入站信号发射")//
	{
		HideAllWindow();
		ShowThisWindow(&setIST);
	}

	

	if(strSelText == "格网模型")//
	{
		HideAllWindow();
		ShowThisWindow(&setION);
	}
	if(strSelText == "数据导频")
	{
		HideAllWindow();
		ShowThisWindow(&setPILOT);
	}
	if(strSelText == "调制解调")
	{
		HideAllWindow();
		ShowThisWindow(&setModual);
	}
	if(strSelText == "传输协议")
	{
	}


	*pResult = 0;
}

void CSystemPane::HideAllWindow(void)
{
	setMUT.ShowWindow(SW_HIDE);
	setEAC.ShowWindow(SW_HIDE);
	setBGT.ShowWindow(SW_HIDE);
	setSTS.ShowWindow(SW_HIDE);
	setREF.ShowWindow(SW_HIDE);
	setPOS.ShowWindow(SW_HIDE);
	setCHA.ShowWindow(SW_HIDE);
	setWID.ShowWindow(SW_HIDE);
	setLOG.ShowWindow(SW_HIDE);//setModual
	setTIM.ShowWindow(SW_HIDE);
	setACQ.ShowWindow(SW_HIDE);
	setION.ShowWindow(SW_HIDE);
	setPILOT.ShowWindow(SW_HIDE);
	setTimMod.ShowWindow(SW_HIDE);
	setModual.ShowWindow(SW_HIDE);
	setWorkMod.ShowWindow(SW_HIDE);
	setIST.ShowWindow(SW_HIDE);
}

void CSystemPane::ShowThisWindow(CBCGPDialog* pWnd)
{
	pWnd->ShowWindow(SW_SHOW);
}

void CSystemPane::HideThisWindow(CBCGPDialog* pWnd)
{
	pWnd->ShowWindow(SW_HIDE);
}

void CSystemPane::InitRectPane(CRect rect)
{
	setREF.MoveWindow(rect);
	HideThisWindow(&setREF);

	setPOS.MoveWindow(rect);
	ShowThisWindow(&setPOS);

	setCHA.MoveWindow(rect);
	HideThisWindow(&setCHA);

	setWID.MoveWindow(rect);
	HideThisWindow(&setWID);

	setLOG.MoveWindow(rect);
	HideThisWindow(&setLOG);

	setTIM.MoveWindow(rect);
	HideThisWindow(&setTIM);

	setMUT.MoveWindow(rect);
	HideThisWindow(&setMUT);

	setEAC.MoveWindow(rect);
	HideThisWindow(&setEAC);

	setBGT.MoveWindow(rect);
	HideThisWindow(&setBGT);

	setSTS.MoveWindow(rect);
	HideThisWindow(&setSTS);

	setTimMod.MoveWindow(rect);
	HideThisWindow(&setTimMod);

	setACQ.MoveWindow(rect);
	HideThisWindow(&setACQ);

	setION.MoveWindow(rect);
	HideThisWindow(&setION);

	setPILOT.MoveWindow(rect);
	HideThisWindow(&setPILOT);

	setModual.MoveWindow(rect);
	HideThisWindow(&setModual);

	setWorkMod.MoveWindow(rect);
	HideThisWindow(&setWorkMod);

	setIST.MoveWindow(rect);
	HideThisWindow(&setIST);	
	
}//
