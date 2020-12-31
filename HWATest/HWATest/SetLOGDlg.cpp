// SetLOGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetLOGDlg.h"


const SLOGTips m_LOGTips[] = 
{
	{OUT_GNREF, "GNREF��ʱ�ղο���Ϣ"}, 
	{OUT_GNMOD, "GNMOD����λ��ʱģʽ��Ϣ"}, 
	{OUT_GNCOM, "GNCOM���˿�������Ϣ"}, 
	{OUT_BDRAN, "BDRAN��α�ࡢ�ز�����������Ϣ"}, 
	{OUT_BDEPH, "BDEPH��һ������������Ϣ"}, 
	{OUT_BSEPH, "BSEPH����������������Ϣ"}, 
	{OUT_BDALM, "BDALM��һ������������Ϣ"}, 
	{OUT_BSALM, "BSALM����������������Ϣ"}, 
	{OUT_BSJAL, "BSJAL���������Ǽ�Լ������Ϣ"}, 
	{OUT_BDION, "BDION��һ�����ǵ�������"}, 
	{OUT_BSION, "BSION���������ǵ�������"}, 
	{OUT_GNCOD, "GNCOD������ԭʼ��������"},
	{OUT_GNPOS, "GNPOS����λ�����ٽ����Ϣ"}, 
	{OUT_GNGBS, "BDGBS�������������Ϣ"}, 
	{OUT_BDGSV, "BDGSV������������Ϣ"},
	{OUT_GNTIM, "GNTIM����ʱ�����Ϣ"}, 
	{OUT_GNSTA, "GNSTA���ն˹���״̬��Ϣ"},
	{OUT_BDCHD, "BDCHD���ŵ�������Ϣ"}, //add by cy 20180715
	{OUT_BDPAO, "BDPAO������ҳ�沥��˳������鲥��˳��"}
};

// CSetLOGDlg dialog

IMPLEMENT_DYNAMIC(CSetLOGDlg, CBCGPDialog)

CSetLOGDlg::CSetLOGDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetLOGDlg::IDD, pParent)
	, m_nPort(0)
	, m_nType(0)
	, m_nFrequency(0)
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE);

}

CSetLOGDlg::~CSetLOGDlg()
{
}

void CSetLOGDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LOG_PORT, m_cmbPort);
	DDX_Control(pDX, IDC_COMBO_LOG_TYPE, m_cmbType);
	DDX_Control(pDX, IDC_COMBO_LOG_FREQ, m_cmbFreq);
	DDX_CBIndex(pDX, IDC_COMBO_LOG_PORT, m_nPort);
	DDX_CBIndex(pDX, IDC_COMBO_LOG_TYPE, m_nType);
	DDX_CBIndex(pDX, IDC_COMBO_LOG_FREQ, m_nFrequency);
}


BEGIN_MESSAGE_MAP(CSetLOGDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTN_LOG_SET, &CSetLOGDlg::OnBnClickedBtnLogSet)
	ON_BN_CLICKED(IDC_BTN_LOG_CHECK, &CSetLOGDlg::OnBnClickedBtnLogCheck)
END_MESSAGE_MAP()


// CSetLOGDlg message handlers

BOOL CSetLOGDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int i = 0;
	CString str;
	CString strchPort[] = {"0: USB", "1: COM1", "2: COM2", "3: COM3", "4: COM4", "5: COM5", "6: COM6", "7: COM7", "��չ" };
	for(i=0; i<9; i++)
	{
		m_cmbPort.InsertString(i, strchPort[i]);
	}
	m_cmbPort.SetCurSel(0);

	for(i=0; i<17; i++)
	{
		m_cmbType.InsertString(i, m_LOGTips[i].strTips);
	}
	m_cmbType.SetCurSel(0);

	m_cmbFreq.InsertString(0, "-3������ն˵�ǰ����ģʽ");
	m_cmbFreq.InsertString(1, "-2����2Hz����Ƶ�����");
	m_cmbFreq.InsertString(2, "-1��ֻ���һ��ָ����Ϣ");
	m_cmbFreq.InsertString(3, "00���ر�ָ����Ϣ�������");
	for(i=0; i<10; i++)
	{
		str.Format("%02d��%02d�����һ��ָ����Ϣ", i+1, i+1);
		m_cmbFreq.InsertString(i+4, str);
	}
	m_cmbFreq.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSetLOGDlg::OnBnClickedBtnLogSet()
{
	// TODO: Add your control notification handler code here
	SETLOG data;
	GetOutput(&data);
	theApp.m_winLinkApp.SetupLOGRequest(data);
	BCGPMessageBox("�������óɹ�");
}

void CSetLOGDlg::OnBnClickedBtnLogCheck()
{
	// TODO: Add your control notification handler code here
}

void CSetLOGDlg::GetOutput(SETLOG* data)
{
	UpdateData(TRUE);
	CString strText = m_LOGTips[m_nType].strTips;
	data->port = m_nPort;
	data->type = m_LOGTips[m_nType].type;
	memcpy(data->frame, strText.GetBuffer(), 5);
	data->freq = m_nFrequency - 3;
}

void CSetLOGDlg::SetOutput(SETLOG data)
{
	m_nPort = data.port % 9;
	m_nType = data.type % 16;
	if(data.freq == -2)
	{
		m_nFrequency = 0;
	}
	else if(data.freq == -1)
	{
		m_nFrequency = 1;
	}
	else 
	{
		m_nFrequency = (data.freq+2);
	}
}
void CSetLOGDlg::Reset()
{

}