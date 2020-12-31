// SetACQDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetACQDlg.h"


// CSetACQDlg dialog

IMPLEMENT_DYNAMIC(CSetACQDlg, CBCGPDialog)

CSetACQDlg::CSetACQDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetACQDlg::IDD, pParent)
{
	m_nBranch = 0;
	CBCGPDialog::EnableVisualManagerStyle(TRUE, TRUE);
}

CSetACQDlg::~CSetACQDlg()
{
}

void CSetACQDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MUT, m_cmbMUT);
	DDX_Control(pDX, IDC_COMBO_STA_ACQ, m_cmbACQ);
	DDX_Control(pDX, IDC_COMBO_STA_TRACK, m_cmbTrack);
	DDX_Control(pDX, IDC_COMBO_MUDUAL, m_cmbModual);
	DDX_Control(pDX, IDC_EDIT_TIPS, m_staticTips);
}


BEGIN_MESSAGE_MAP(CSetACQDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_SET_MUT_PATH, &CSetACQDlg::OnBnClickedBtnSetMutPath)
	ON_BN_CLICKED(IDC_BTN_SET_STA_TRACK, &CSetACQDlg::OnBnClickedBtnSetStaTrack)
	ON_BN_CLICKED(IDC_BTN_SET_STA_ACQ, &CSetACQDlg::OnBnClickedBtnSetStaAcq)
	ON_BN_CLICKED(IDC_BTN_SET_MUDUAL, &CSetACQDlg::OnBnClickedBtnSetMudual)
	ON_CBN_SELCHANGE(IDC_COMBO_MUDUAL, &CSetACQDlg::OnCbnSelchangeComboMudual)
END_MESSAGE_MAP()


// CSetACQDlg message handlers

BOOL CSetACQDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_cmbMUT.AddString("0���޶ྶ�����㷨");
	m_cmbMUT.AddString("1��խ���");
	m_cmbMUT.AddString("2��˫�����");
	m_cmbMUT.AddString("3������");
	m_cmbMUT.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetACQDlg::InitComboBox(int branch)
{
	m_nBranch = branch;
	m_cmbACQ.ResetContent();
	m_cmbTrack.ResetContent();
	m_cmbModual.ResetContent();
	switch (m_nBranch)
	{
	case CH_B1I:
		m_cmbModual.AddString("Ĭ��");
		m_cmbACQ.AddString("BPSK����");
		m_staticTips.SetWindowText("��Ƶ�ʣ�2.046Mchip/s\r\n�ز�Ƶ�ʣ�1561.098MHz");

		m_cmbTrack.AddString("BPSK����");
		break;
	case CH_B1Q:
		m_cmbModual.AddString("Ĭ��");
		m_cmbACQ.AddString("ֱ�Ӳ���");
		m_cmbACQ.AddString("��������������");
		m_staticTips.SetWindowText("��Ƶ�ʣ�2.046Mchip/s\r\n�ز�Ƶ�ʣ�1561.098MHz");

		m_cmbTrack.AddString("BPSK����");
		break;
	case CH_B1C:
		m_cmbModual.AddString("Ĭ��");
		m_staticTips.SetWindowText("��Ƶ�ʣ�1.023Mchip/s\r\n�ز�Ƶ�ʣ�1575.420MHz");

		m_cmbACQ.AddString("BOC����");
		m_cmbACQ.AddString("BPSK-Like����");

		m_cmbTrack.AddString("BOC����");
		m_cmbTrack.AddString("BPSK-Like ����");
		m_cmbTrack.AddString("TMBOC(1��1)-BOC����");
		m_cmbTrack.AddString("TMBOCȫ����");
		break;
	case CH_B1A:
		m_cmbModual.AddString("B1A_TDDM");
		m_cmbModual.AddString("B1A_BOC(14,2)");
		m_staticTips.SetWindowText("��Ƶ�ʣ�2.046Mchip/s\r\n�ز�Ƶ�ʣ�1575.42MHz");

		m_cmbACQ.AddString("ֱ�Ӳ���");
		m_cmbACQ.AddString("��������������");
		m_cmbACQ.AddString("������ǿ��������");

		m_cmbTrack.AddString("BOC����");
		m_cmbTrack.AddString("BPSK-Like ����");
		break;
	case CH_B2a:
		m_cmbModual.AddString("B2a_AltBOC");
		m_cmbModual.AddString("B2a_TD-AltBOC");
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1176.45MHz");

		m_cmbACQ.AddString("BPSK����");

		m_cmbTrack.AddString("BPSK����");
		break;
	case CH_B2b:
		m_cmbModual.AddString("B2b_AltBOC");
		m_cmbModual.AddString("B2b_TD-AltBOC");
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1207.14MHz");

		m_cmbACQ.AddString("BPSK����");

		m_cmbTrack.AddString("BPSK����");
		break;
	case CH_B2:
		m_cmbModual.AddString("B2_AltBOC");
		m_cmbModual.AddString("B2_TD-AltBOC");
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1207.14MHz");

		m_cmbACQ.AddString("BPSK-Like����");

		m_cmbTrack.AddString("AltBOC����");
		m_cmbTrack.AddString("TD-AltBOC����");
		break;
	case CH_B3I:
		m_cmbModual.AddString("Ĭ��");
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1268.520MHz");
		m_cmbACQ.AddString("BPSK����");

		m_cmbTrack.AddString("BPSK����");
		break;
	case CH_B3Q:
		m_cmbModual.AddString("Ĭ��");
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1268.520MHz");
		m_cmbACQ.AddString("ֱ�Ӳ���");
		m_cmbACQ.AddString("��������������");

		m_cmbTrack.AddString("BPSK����");
		break;
	case CH_B3C:
		m_cmbModual.AddString("B3C_BPSK(5)");
		m_cmbModual.AddString("B3C_BOC(15,2.5)");
		m_staticTips.SetWindowText("��Ƶ�ʣ�5.115Mchip/s\r\n�ز�Ƶ�ʣ�1278.75MHz");

		m_cmbACQ.AddString("BOC����");
		m_cmbACQ.AddString("BPSK-Like����");

		m_cmbTrack.AddString("BOC����");
		m_cmbTrack.AddString("BPSK-Like ����");
		m_cmbTrack.AddString("BPSK����");
		break;
	case CH_B3A:
		m_cmbModual.AddString("B3A_BPSK(10)");
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1268.52MHz");

		m_cmbACQ.AddString("ֱ�Ӳ���");
		m_cmbACQ.AddString("��������������");

		m_cmbTrack.AddString("BPSK����");
		break;
	case CH_B3AE:
		m_cmbModual.AddString("B3AE_BPSK(10)");
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1268.52MHz");

		m_cmbACQ.AddString("ֱ�Ӳ���");
		m_cmbACQ.AddString("��������������");

		m_cmbTrack.AddString("BPSK����");
		break;
	case CH_Bs:
		m_cmbModual.AddString("Ĭ��");
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�2492.028MHz");

		m_cmbACQ.AddString("ֱ�Ӳ���");
		m_cmbACQ.AddString("��������������");
		m_cmbACQ.AddString("������ǿ��������");

		m_cmbTrack.AddString("BPSK����");
		break;
	default:
		break;
	}
	m_cmbACQ.SetCurSel(0);
	m_cmbTrack.SetCurSel(0);
	m_cmbModual.SetCurSel(0);
}

void CSetACQDlg::OnBnClickedBtnSetMutPath()
{
	// TODO: Add your control notification handler code here
	SETMUT data;
	data.branch = m_nBranch;
	data.mutiPath = m_cmbMUT.GetCurSel();
	theApp.m_winLinkApp.SetupMUTRequest(data);
	BCGPMessageBox("�������óɹ�");
}

void CSetACQDlg::OnBnClickedBtnSetStaTrack()
{
	// TODO: Add your control notification handler code here
	SETTRK data;
	CString strText;
	m_cmbTrack.GetWindowText(strText);
	if (strText == "BPSK����")
	{
		data.mode = TRACK_BPSK;
	} 
	else if (strText == "BOC����")
	{
		data.mode = TRACK_BOC;
	}
	else if (strText == "BPSK-Like����")
	{
		data.mode = TRACK_BPSK_LIKE;
	}
	else if (strText == "TMBOC-BOC(1,1)����")
	{
		data.mode = TRACK_TMBOC_BOC;
	}
	else if (strText == "TMBOCȫ����")
	{
		data.mode = TRACK_TMBOC;
	}
	else if (strText == "AltBOC����")
	{
		data.mode = TRACK_ALTBOC;
	}
	else if (strText == "TD-AltBOC����")
	{
		data.mode = TRACK_TD_ALTBOC;
	}
	data.branch = m_nBranch;
	theApp.m_winLinkApp.SetupTRKRequest(data);
	BCGPMessageBox("�������óɹ�");
}

void CSetACQDlg::OnBnClickedBtnSetStaAcq()
{
	// TODO: Add your control notification handler code here
	SETACQ data;
	CString strText;
	m_cmbACQ.GetWindowText(strText);
	if (strText == "BOC����")
	{
		data.mode = ACQU_BOC;
	} 
	else if (strText == "BPSK����")
	{
		data.mode = ACQU_BPSK;
	}
	else if (strText == "BPSK-Like����")
	{
		data.mode = ACQU_BPSK_LIKE;
	}
	else if (strText == "ֱ�Ӳ���")
	{
		data.mode = ACQU_NORMAL;
	}
	else if (strText == "��������������")
	{
		data.mode = ACQU_PILOT;
	}
	else if (strText == "������ǿ��������")
	{
		data.mode = ACQU_POWER_PILOT;
	}
	data.branch = m_nBranch;
	theApp.m_winLinkApp.SetupACQRequest(data);
	BCGPMessageBox("�������óɹ�");
}
char CSetACQDlg::GetModualation(CString strText)
{
	char mode = 0;
	if (strText == "B3C_BPSK(5)")
	{
		mode = 0;
	} 
	else if (strText == "B3C_BOC(15,2.5)")
	{
		mode = 1;
	}
	else if (strText == "B2a_TD-AltBOC")
	{
		mode = 2;
	}
	else if (strText == "B2a_AltBOC")
	{
		mode = 3;
	}
	else if (strText == "B2b_TD-AltBOC")
	{
		mode = 4;
	}
	else if (strText == "B2b_AltBOC")
	{
		mode = 5;
	}
	else if (strText == "B2_TD-AltBOC")
	{
		mode = 6;
	}
	else if (strText == "B2_AltBOC")
	{
		mode = 7;
	}
	else if (strText == "B1A_TDDM")
	{
		mode = 8;
	}
	else if (strText == "B1A_BOC(14,2)")
	{
		mode = 9;
	}
	else if (strText == "B3A_BPSK(10)")
	{
		mode = 10;
	}
	else if (strText == "B3AE_BPSK(10)")
	{
		mode = 11;
	}
	else
	{
		mode = 12;
	}
	return mode;
}
void CSetACQDlg::OnBnClickedBtnSetMudual()
{
	// TODO: Add your control notification handler code here
	SETSTA data;
	CString strText;
	m_cmbModual.GetWindowText(strText);
	data.mod = GetModualation(strText);
	theApp.m_winLinkApp.SetupSTARequest(data);
	BCGPMessageBox("�������óɹ�");
}

void CSetACQDlg::OnCbnSelchangeComboMudual()
{
	// TODO: Add your control notification handler code here
	int index = m_cmbModual.GetCurSel();
	CString strText;
	m_cmbModual.GetWindowText(strText);
	if (strText == "B3C_BPSK(5)")
		m_staticTips.SetWindowText("��Ƶ�ʣ�5.115Mchip/s\r\n�ز�Ƶ�ʣ�1278.75MHz");
	else if (strText == "B3C_BOC(15,2.5)")
		m_staticTips.SetWindowText("��Ƶ�ʣ�2.575Mchip/s\r\n�ز�Ƶ�ʣ�1268.52MHz");
	else if (strText == "B2a_TD-AltBOC")
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1176.45MHz");
	else if (strText == "B2a_AltBOC")
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1176.45MHz");
	else if (strText == "B2b_TD-AltBOC")
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1207.14MHz");
	else if (strText == "B2b_AltBOC")
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1207.14MHz");
	else if (strText == "B2_TD-AltBOC")
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1207.14MHz");
	else if (strText == "B2_AltBOC")
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1207.14MHz");
	else if (strText == "B1A_TDDM")
		m_staticTips.SetWindowText("��Ƶ�ʣ�2.046Mchip/s\r\n�ز�Ƶ�ʣ�1575.42MHz");
	else if (strText == "B1A_BCO(14,2)")
		m_staticTips.SetWindowText("��Ƶ�ʣ�2.046Mchip/s\r\n�ز�Ƶ�ʣ�1575.42MHz");
	else if (strText == "B3A_BPSK(10)")
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1268.52MHz");
	else if (strText == "B3AE_BPSK(10)")
		m_staticTips.SetWindowText("��Ƶ�ʣ�10.23Mchip/s\r\n�ز�Ƶ�ʣ�1268.52MHz");
}
