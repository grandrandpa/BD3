// ShowChaView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowChaView.h"
					//0			1		2			3				4				5					6					7					8				9
CString strACQ[] = {"������", "����", "ֱ��", "�������Ȳ���", "������������", "B3Q��ǿ�ź���������", "��Ƶͨ������", "���ݵ�Ƶ���ϲ���", "�������������", "B3AE�ź���������", 
"��Ƶͨ��BPSK-like����", "��Ƶͨ��BOC-like����", "˫�ߴ�����", "ȫ�ߴ�ֱ��", "AltBOCֱ��", "TD-AltBOCֱ��"};
	//10						//11				//12			13
CString strTrack[] = {"������", "����", "����ͨ������", "��Ƶͨ������", "���ݵ�Ƶ���ϸ���", "��Ƶͨ��BPSK-like����", "����ͨ��BPSK-like����", "����ͨ��BOC����", 
"��Ƶͨ��BOC����", "��Ƶͨ��BOC(1,1)����", "��Ƶͨ��BOC(6,1)����", "��Ƶͨ��BOC(1,1)��BOC(6,1)���ϸ���", "˫�ߴ�����", "ȫ�ߴ�����"};
int GetAcquItem(int branch, int index)
{
	int item=0;
	switch (branch)
	{
	case CH_B1I:
	case CH_B3I:
		if (index == 0)
			item = 0;
		else if (index == 1)
			item = 1;
		else if (index == 2)
			item = 3;
		break;
	case CH_B1Q:
	case CH_B3Q:
		if (index == 0)
			item = 0;
		else if (index == 1)
			item = 2;
		else if (index == 2)
			item = 4;
		else if (index == 3)
			item = 5;
		else if (index == 4)
			item = 3;
		break;
	case CH_B1C:
		if (index == 0)
			item = 0;
		else if (index == 1)
			item = 10;
		else if (index == 2)
			item = 11;
		else if (index == 3)
			item = 7;
		else if (index == 4)
			item = 3;
		break;
	case CH_B1A:
		if (index == 0)
			item = 0;
		else if (index == 1)
			item = 10;
		else if (index == 2)
			item = 11;
		else if (index == 3)
			item = 8;
		else if (index == 4)
			item = 9;
		else if (index == 5)
			item = 3;
		else if (index == 6)
			item = 7;
		break;
	case CH_B2:
		if (index == 0)
			item = 0;
		else if (index == 1)
			item = 12;
		else if (index == 2)
			item = 13;
		else if (index == 3)
			item = 3;
		break;
	case CH_B3A:
		if (index == 0)
			item = 0;
		else if (index == 1)
			item = 6;
		else if (index == 2)
			item = 7;
		else if (index == 3)
			item = 8;
		else if (index == 4)
			item = 9;
		else if (index == 5)
			item = 3;
		break;
	case CH_B2a:
	case CH_B2b:
	case CH_B3C:
	case CH_B3AE:
	case CH_Bs:
		if (index == 0)
			item = 0;
		else if (index == 1)
			item = 6;
		else if (index == 2)
			item = 7;
		else if (index == 3)
			item = 3;
		break;
	default:
		break;
	}

	return item;
}

int GetTrackItem(int branch, int index)
{
	int item = 0;
	switch (branch)
	{
	case CH_B1I:
	case CH_B1Q:
	case CH_B3I:
	case CH_B3Q:
		if (index == 0)
			item = 0;
		else if (index == 1)
			item = 1;
		break;
	case CH_B1C:
		if (index == 0)
			item = 0;
		else if (index == 1)
			item = 7;
		else if (index == 2)
			item = 9;
		else if (index == 3)
			item = 10;
		else if (index == 4)
			item = 11;
		else if (index == 5)
			item = 4;
		break;
	case CH_B1A:
		if (index == 0)
			item = 0;
		else if (index == 1)
			item = 8;
		else if (index == 2)
			item = 5;
		else if (index == 3)
			item = 7;
		else if (index == 4)
			item = 6;
		else if (index == 5)
			item = 4;
		break;
	case CH_B2a:
	case CH_B2b:
		if (index == 0)
			item = 0;
		else if (index == 1)
			item = 2;
		else if (index == 2)
			item = 3;
		else if (index == 3)
			item = 4;
		break;
	case CH_B2:
		if (index == 0)
			item = 0;
		else if (index == 1)
			item = 12;
		else if (index == 2)
			item = 13;
		break;
	case CH_B3C:
	case CH_B3A:
	case CH_B3AE:
	case CH_Bs:
		if (index == 0)
			item = 0;
		else if (index == 1)
			item = 3;
		else if (index == 2)
			item = 2;
		else if (index == 3)
			item = 4;
		break;
	default:
		break;
	}
	return item;
}
// CShowChaView
IMPLEMENT_DYNCREATE(CShowChaView, CHWATestView)

CShowChaView::CShowChaView()
{
	m_nBranch = 0;
	m_bLock = false;
	InitializeCriticalSection(&m_BufferCriticalSection);
}

CShowChaView::~CShowChaView()
{
	m_nBranch = 0;
	m_bLock = false;
	//m_listCtrl.DeleteAllItems();
}

BEGIN_MESSAGE_MAP(CShowChaView, CHWATestView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(IDR_CHA_BRANCH, OnChangeBranch)
	ON_CBN_SELENDOK(IDR_CHA_BRANCH, OnChangeBranch)
	ON_COMMAND(IDR_CHA_CLEAR, OnClearView)
	ON_UPDATE_COMMAND_UI(IDR_CHA_CLEAR, OnUpdateClearView)
	ON_COMMAND(IDR_CHA_LOCK, OnLockView)
	ON_UPDATE_COMMAND_UI(IDR_CHA_LOCK, OnUpdateLockView)
END_MESSAGE_MAP()


// CShowChaView drawing

void CShowChaView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CShowChaView diagnostics

#ifdef _DEBUG
void CShowChaView::AssertValid() const
{
	CHWATestView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowChaView::Dump(CDumpContext& dc) const
{
	CHWATestView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowChaView message handlers

int CShowChaView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CHWATestView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect (&rect);	
	// TODO:  Add your specialized creation code here
	int i = 0;
	CString str;
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create  !m_wndToolBar.LoadToolBar(IDR_DRAW_RAN_TOOLBAR)
	}
	m_wndToolBar.LoadToolBar(IDR_CHA_TOOLBAR);
	m_wndToolBar.ReplaceButton (IDR_CHA_BRANCH_LABEL, CToolbarLabel(IDR_CHA_BRANCH_LABEL, _T("�źŷ���: ")));

	CBCGPToolbarComboBoxButton comboBranch (IDR_CHA_BRANCH, CImageHash::GetImageOfCommand (IDR_CHA_BRANCH, FALSE), CBS_DROPDOWNLIST);
	for (i=0; i<MAXFREQ; i++)//
	{
		comboBranch.AddItem (strFREQ[i]);
	}
	comboBranch.SelectItem(0);
	m_wndToolBar.ReplaceButton (IDR_CHA_BRANCH, comboBranch);

	dwStyle = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL|LVS_REPORT;
	CRect chartRect(rect.left,rect.top+30,rect.Width (),rect.Height()-30);
	m_listCtrl.m_bVisualManagerStyle = true;
	if (!m_listCtrl.Create(dwStyle, chartRect, this, 1))
	{
		TRACE0("δ�ܴ����б���\n");
		return -1;      // δ�ܴ���
	}
	/*m_listCtrl.SetBkColor(RGB(227,239,255));
	m_listCtrl.SetTextBkColor(RGB(227,239,255));
	m_listCtrl.SetTextColor(RGB(0,0,255));*/
	dwStyle = m_listCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER;// | LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	m_listCtrl.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.SetExtendedStyle(dwStyle);
	InitColumn();

	return 0;
}

void CShowChaView::InitColumn()
{
	//m_listCtrl.InsertColumn(0, "���", LVCFMT_CENTER, 80, -1);
	m_listCtrl.InsertColumn(0, "ͨ�����", LVCFMT_CENTER, 80, -1);
	m_listCtrl.InsertColumn(1, "���Ǳ��", LVCFMT_LEFT, 80, -1);
	m_listCtrl.InsertColumn(2, "�źŷ���", LVCFMT_LEFT, 80, -1);
	m_listCtrl.InsertColumn(3, "�����(dBHz)",   LVCFMT_LEFT, 90, -1);
	m_listCtrl.InsertColumn(4, "���붨λ", LVCFMT_LEFT, 80, -1);
	m_listCtrl.InsertColumn(5, "��Ƶ��־", LVCFMT_LEFT, 80, -1);
	m_listCtrl.InsertColumn(6, "��Ƶǰ�˴���", LVCFMT_LEFT, 120, -1);

	m_listCtrl.InsertColumn(7, "��������", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(8, "��·����", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(9, "�뻷����", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(10, "�ز�������", LVCFMT_LEFT, 150, -1);


	m_listCtrl.InsertColumn(11, "�����״̬", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(12, "�źŴ���״̬", LVCFMT_LEFT, 120, -1);
	m_listCtrl.InsertColumn(13, "�������", LVCFMT_LEFT, 150, -1);
	m_listCtrl.InsertColumn(14, "�����㷨", LVCFMT_LEFT, 150, -1);
}
void CShowChaView::OnSize(UINT nType, int cx, int cy)
{
	CHWATestView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndToolBar.SetWindowPos (NULL, -1, -1, cx, 30, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_listCtrl.SetWindowPos(NULL, -1, 30 , cx, cy-30,SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CShowChaView::OnInitialUpdate()
{
	CHWATestView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SetWindowText("ͨ��״̬");
}

void CShowChaView::OnChangeBranch() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	CBCGPToolbarComboBoxButton* pCombobox = DYNAMIC_DOWNCAST (CBCGPToolbarComboBoxButton,
		m_wndToolBar.GetButton (m_wndToolBar.CommandToIndex (IDR_CHA_BRANCH)));
	m_listCtrl.DeleteAllItems();
	m_nBranch = pCombobox->GetCurSel();
	LeaveCriticalSection(&m_BufferCriticalSection);
	//BCGPMessageBox("����");m_nPosType
}

void CShowChaView::RefreshView(BD2_RAN* data)
{
	CString str;
	int count=0,SvId=0,temp=0;
	unsigned int state=0;
	unsigned long status1=0,status2=0;
	count = data->numuse;

	int index = BranchToitem(data->branch);
	if(index == -1 || m_nBranch != index)
		return;

	str.Empty();
	try
	{
		m_listCtrl.DeleteAllItems();
		for (int i=0; i<count; i++)
		{
			status1 = data->status1[i];
			status2 = data->status2[i];

			state = (status1 >> 3)&0x3FF;//��ȷ���Ƿ������� ʮλ1 Ӧ����0x3FF
			str.Format("%02d", state);
			m_listCtrl.InsertItem(i, str);
			str.Format("%02d", data->svId[i]);
			m_listCtrl.SetItemText(i, 1, str);


			str.Format("%s", strFREQ[index]);
			//add by cy 20180714
			if((index>=2 && index<=4 )|| index==10 || index ==11)//���B1C��B2a��B1A��B3A��B3AE�źŷ����ֱ���ʾ��ͬ��Ϣ
			{
				if(i<count/2)				
					str.Format("%s%s", strFREQ[index],"_data");				
				else
					str.Format("%s%s", strFREQ[index],"_pilot");
			}


			m_listCtrl.SetItemText(i, 2, str);






			str.Format("%.1f", data->snr[i]);
			m_listCtrl.SetItemText(i, 3, str);
			state = (status1 >> 22)&0x01;
			str.Format("%s", (state)?"��":"��");
			m_listCtrl.SetItemText(i, 4, str);
			state = (status1 >> 24)&0x03;
			str = "��";
			if(state == 1)
				str = "����ͨ��";
			else if(state == 2)
				str = "��Ƶͨ��";
			else if(state == 3)
				str = "����ͨ��";
			m_listCtrl.SetItemText(i, 5, str);
						
			//Ԥ��ش���
			//state = (status1 >> 26)&0x03;		
			//str = "��";
			//if(state == 0)
			//	str = "ȫ������";
			//else if(state == 1)
			//	str = "�������";
			//else if(state == 2)
			//	str = "2���������";
			//else if(state == 3)
			//	str = "3���������";
			//m_listCtrl.SetItemText(i, 6, str);

			//��Ƶǰ�˴���
			state = (status1 >> 26)&0x07;//add by cy 20180714 ��չ��3bit
			str = "0";
			if(state == 0)
				str = "4MHz";
			else if(state == 1)
				str = "8MHz";
			else if(state == 2)
				str = "16MHz";
			else if(state == 3)
				str = "20MHz";
			else if(state == 4)
				str = "32MHz";
			else if(state == 5)
				str = "40MHz";
			m_listCtrl.SetItemText(i, 6, str);


	
			//��������
			//unsigned short s =0;
			//byte b1 = ((status1 >> 29)&0x7)| ((status2&0x01)<<3);
			//byte b2 = (status2 >> 0)&0xFF;

			//s = (short)(s^b1);
			//s = (short)(s<<8);
			//s = (short)(s^b2);
			state =((status1 >> 29)&0x7)| ((status2&0x01)<<3);

			//state = (status1 >> 29)&0x0F;
			str.Format("%u", state);
			m_listCtrl.SetItemText(i, 7, str);





			//��·����
			//state = (status2 >> 56)&&0x03;
			state=0;
			state = (data->status2[i] >> 24)&0x03;
			str="0";
			str.Format("%u", state);
			m_listCtrl.SetItemText(i, 8, str);

			//�뻷����
			//state = (status2 >> 37)&&0x1F;
			state=0;
			state = (data->status2[i] >> 5)&0x1F;
			str="0";
			str.Format("%0.2f", state/10.0);
			m_listCtrl.SetItemText(i, 9, str);

			//�ز�������
			//state = (status2 >> 58)&&0x1F;
			state=0;
			state = (status2 >> 26)&0x1F;			
			str="0";
			str.Format("%u", state);
			TRACE0(str+"\n");
			m_listCtrl.SetItemText(i, 10, str);



			state = (status1 >> 19)&0x03;
			str = "δ֪";
			if(state == 1)
				str = "��׼�����";
			else if(state == 2)
				str = "խ���";
			else if(state == 3)
				str = "˫�����";
			m_listCtrl.SetItemText(i, 11, str);


			state = (status1 >> 0)&0x07;
			str.Empty();
			if(state == 0)
				str = "����";
			else if(state == 1)
				str = "����״̬";
			else if(state == 2)
				str = "ʵ�ֲ���";
			else if(state == 3)
				str = "pull-in";
			else if(state == 4)
				str = "ʵ�ָ���";
			else
				str.Format("����", state);
			m_listCtrl.SetItemText(i, 12, str);

			//����
			state = (status1 >> 13)&0x07;
			temp = GetAcquItem(data->branch, state);
			m_listCtrl.SetItemText(i, 13, strACQ[temp]);
			//����
			state = (status1 >> 16)&0x07;
			temp = GetTrackItem(data->branch, state);
			m_listCtrl.SetItemText(i, 14, strTrack[temp]);
		}
	}
	catch (...)
	{
	}
}

void CShowChaView::OnUpdateAllViews(CGlobalVariant* data, int type)
{
	BD2_RAN* ran = new BD2_RAN;
	memcpy(ran, data->buffer, sizeof(BD2_RAN));
	EnterCriticalSection(&m_BufferCriticalSection);
	if (!m_bLock)
	{
		RefreshView(ran);
	}
	LeaveCriticalSection(&m_BufferCriticalSection);
	delete ran;
}
void CShowChaView::Clear()
{
	OnClearView();
}
void CShowChaView::OnClearView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_listCtrl.DeleteAllItems();
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowChaView::OnUpdateClearView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CShowChaView::OnLockView() 
{
	EnterCriticalSection(&m_BufferCriticalSection);
	m_bLock = !m_bLock;
	LeaveCriticalSection(&m_BufferCriticalSection);
}

void CShowChaView::OnUpdateLockView(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bLock);
}
