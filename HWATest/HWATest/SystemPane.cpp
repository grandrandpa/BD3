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
	ImageListTree->Create(16, 16, ILC_COLOR32, 3, 3); //16,16Ϊͼ��ֱ��ʣ�4,4Ϊ��list��������ɵ�ͼ����
	ImageListTree->SetBkColor(RGB(231,241,254));
	for(int i=0;i<3;i++)
	{
		ImageListTree->Add(Icon[i]); //����ͼ��
	}
	m_treeView.ModifyStyle(NULL,TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS);
	m_treeView.SetImageList(ImageListTree, TVSIL_NORMAL);
	m_treeView.m_bVisualManagerStyle = true;
	HTREEITEM root;     // ���ĸ��ڵ�ľ��
	root = m_treeView.InsertItem("�ն˻�����", 0, 0, TVI_ROOT);
	m_treeView.InsertItem("��λģʽ", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("��ʱģʽ", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("����ģʽ", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("��վ�źŷ���", 2, 1, root, TVI_LAST);	
	m_treeView.InsertItem("ʱ�ղ���", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("ͨ������", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("��ʱ����", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("��������", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("���ݵ�Ƶ", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("ϵͳʱ��", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("��ش���", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("�״�����", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("����ģ��", 2, 1, root, TVI_LAST);
	m_treeView.InsertItem("�������", 2, 1, root, TVI_LAST);
	//m_treeView.InsertItem("���ƽ��", 2, 1, root, TVI_LAST);//
	m_treeView.Expand(root, TVE_EXPAND);
	root = m_treeView.InsertItem("�źŴ���Ԫ", 0, 0, TVI_ROOT);
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
	setWorkMod.Create(IDD_SET_WORK_DIALOG,	&m_tabCtrl);//����ģʽ
	setIST.Create(IDD_SET_IST_DIALOG,	&m_tabCtrl);//��վ�źŷ���

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

	if(strSelText == "�ն˻�����")
	{
		hItem = m_treeView.GetChildItem(m_treeView.GetRootItem()); //��ȡ��һ���ӽ��
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

	if(strSelText == "�״�����")
	{
		HideAllWindow();
		ShowThisWindow(&setMUT);
	}
	if(strSelText == "��������")
	{
		HideAllWindow();
		ShowThisWindow(&setEAC);
	}
	if(strSelText == "ϵͳʱ��")
	{
		HideAllWindow();
		ShowThisWindow(&setBGT);
	}
	if(strSelText == "�ź�״̬")
	{
		HideAllWindow();
		ShowThisWindow(&setSTS);
	}
	if(strSelText == "ʱ�ղ���")
	{
		HideAllWindow();
		ShowThisWindow(&setREF);
	}
	if(strSelText == "��λģʽ")
	{
		HideAllWindow();
		ShowThisWindow(&setPOS);
	}
	if(strSelText == "ͨ������")
	{
		HideAllWindow();
		ShowThisWindow(&setCHA);
	}
	if(strSelText == "��ش���")
	{
		HideAllWindow();
		ShowThisWindow(&setWID);
	}
	if(strSelText == "�������")
	{
		HideAllWindow();
		ShowThisWindow(&setLOG);
	}
	if(strSelText == "��ʱ����")
	{
		HideAllWindow();
		ShowThisWindow(&setTIM);
	}
	if(strSelText == "��ʱģʽ")//
	{
		HideAllWindow();
		ShowThisWindow(&setTimMod);
	}
	if(strSelText == "����ģʽ")//
	{
		HideAllWindow();
		ShowThisWindow(&setWorkMod);
	}	
	if(strSelText == "��վ�źŷ���")//
	{
		HideAllWindow();
		ShowThisWindow(&setIST);
	}

	

	if(strSelText == "����ģ��")//
	{
		HideAllWindow();
		ShowThisWindow(&setION);
	}
	if(strSelText == "���ݵ�Ƶ")
	{
		HideAllWindow();
		ShowThisWindow(&setPILOT);
	}
	if(strSelText == "���ƽ��")
	{
		HideAllWindow();
		ShowThisWindow(&setModual);
	}
	if(strSelText == "����Э��")
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
