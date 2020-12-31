// SetLOGDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetLOGDlg.h"


const SLOGTips m_LOGTips[] = 
{
	{OUT_GNREF, "GNREF：时空参考信息"}, 
	{OUT_GNMOD, "GNMOD：定位授时模式信息"}, 
	{OUT_GNCOM, "GNCOM：端口速率信息"}, 
	{OUT_BDRAN, "BDRAN：伪距、载波、多普勒信息"}, 
	{OUT_BDEPH, "BDEPH：一期卫星星历信息"}, 
	{OUT_BSEPH, "BSEPH：试验卫星星历信息"}, 
	{OUT_BDALM, "BDALM：一期卫星历书信息"}, 
	{OUT_BSALM, "BSALM：试验卫星历书信息"}, 
	{OUT_BSJAL, "BSJAL：试验卫星简约历书信息"}, 
	{OUT_BDION, "BDION：一期卫星电离层参数"}, 
	{OUT_BSION, "BSION：试验卫星电离层参数"}, 
	{OUT_GNCOD, "GNCOD：卫星原始导航电文"},
	{OUT_GNPOS, "GNPOS：定位、测速结果信息"}, 
	{OUT_GNGBS, "BDGBS：自主完好性信息"}, 
	{OUT_BDGSV, "BDGSV：可视卫星信息"},
	{OUT_GNTIM, "GNTIM：授时结果信息"}, 
	{OUT_GNSTA, "GNSTA：终端工作状态信息"},
	{OUT_BDCHD, "BDCHD：信道译码信息"}, //add by cy 20180715
	{OUT_BDPAO, "BDPAO：电文页面播发顺序和历书播发顺序"}
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
	CString strchPort[] = {"0: USB", "1: COM1", "2: COM2", "3: COM3", "4: COM4", "5: COM5", "6: COM6", "7: COM7", "扩展" };
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

	m_cmbFreq.InsertString(0, "-3：清除终端当前工作模式");
	m_cmbFreq.InsertString(1, "-2：按2Hz更新频率输出");
	m_cmbFreq.InsertString(2, "-1：只输出一次指定信息");
	m_cmbFreq.InsertString(3, "00：关闭指定信息类型输出");
	for(i=0; i<10; i++)
	{
		str.Format("%02d：%02d秒输出一次指定信息", i+1, i+1);
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
	BCGPMessageBox("参数设置成功");
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