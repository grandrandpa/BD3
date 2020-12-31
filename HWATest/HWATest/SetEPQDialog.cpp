// SetEPQDialog.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetEPQDialog.h"
#include "afxdialogex.h"
#include "OutputBar.h"


// CSetEPQDialog dialog

IMPLEMENT_DYNAMIC(CSetEPQDialog, CDialogEx)

CSetEPQDialog::CSetEPQDialog(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetEPQDialog::IDD, pParent)
    , miFreq(1)
    , miModel(1)
    , miSos(0)
    , miSpeed(1)
    , miUrgFlag(2)
    , m_iTimes(1)
{

    m_iCardID = 0;
    m_dElevValue = 0.0;

}

CSetEPQDialog::~CSetEPQDialog()
{
}

void CSetEPQDialog::DoDataExchange(CDataExchange* pDX)
{
    CBCGPDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_FREQ, m_ComboFreq);
    DDX_Control(pDX, IDC_COMBO_MODEL, m_ComboModel);
    DDX_Control(pDX, IDC_COMBO_SOS, m_ComboSos);
    DDX_Control(pDX, IDC_COMBO_SPEED, m_ComboSpeed);
    DDX_Control(pDX, IDC_COMBO_URG, m_ComboUrg);

    DDX_Text(pDX, IDC_EPQ_ELEV, m_dElevValue);
    DDX_Control(pDX, IDC_BTN_SENT_EPQ, m_btnSendEPQ);

    DDX_Text(pDX, IDC_EPQ_CARDID, m_iCardID);
    DDV_MinMaxInt(pDX, m_iCardID, 0, 9999999);
    DDX_Text(pDX, IDC_TIMES_PER_SEC, m_iTimes);
	DDV_MinMaxInt(pDX, m_iTimes, 0, 100);
}


BEGIN_MESSAGE_MAP(CSetEPQDialog, CBCGPDialog)
    ON_BN_CLICKED(IDC_BTN_SENT_EPQ, &CSetEPQDialog::OnClickedBtnSentEpq)
    ON_CBN_SELCHANGE(IDC_COMBO_MODEL, &CSetEPQDialog::OnSelchangeComboModel)
    ON_CBN_SELCHANGE(IDC_COMBO_FREQ, &CSetEPQDialog::OnSelchangeComboFreq)
    ON_CBN_SELCHANGE(IDC_COMBO_SPEED, &CSetEPQDialog::OnSelchangeComboSpeed)
    ON_CBN_SELCHANGE(IDC_COMBO_SOS, &CSetEPQDialog::OnSelchangeComboSos)
    ON_CBN_SELCHANGE(IDC_COMBO_URG, &CSetEPQDialog::OnSelchangeComboUrg)
END_MESSAGE_MAP()


// CSetEPQDialog message handlers


BOOL CSetEPQDialog::OnInitDialog()
{
    CBCGPDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    m_ComboFreq.SetCurSel(0);
    m_ComboModel.SetCurSel(0);
    m_ComboSos.SetCurSel(0);
    m_ComboSpeed.SetCurSel(0);
    m_ComboUrg.SetCurSel(1);

    if (miModel == 3 || miUrgFlag != 1)
    {
        m_ComboSos.SetCurSel(0);
        m_ComboSos.EnableWindow(0);

        if (miModel == 3 || miUrgFlag == 3)
        {
            m_dElevValue = 0.0;
        }
    }

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}


void CSetEPQDialog::OnClickedBtnSentEpq()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    //TRACE("卡号:%d,高程值：%f\n", m_iCardID, m_dElevValue);
    TRACE("speed:%d\n", m_ComboSpeed.GetCurSel()+1);
    TRACE("m_iTimes:%d\n", m_iTimes);

    SETEPQ data;
    data.CardId = m_iCardID;
	data.Model = miModel;
    data.Freq = miFreq;
    data.Speed = miSpeed;
    data.UrgFlag = miUrgFlag;
    data.ElevValue = m_dElevValue;
    data.SOSType = miSos;
    data.Times = m_iTimes;

	theApp.m_winLinkApp.SetupEPQRequest(data);
    //((CMainFrame *) (theApp.m_pMainWnd))->m_wndOutputView.ShowDataToWindow(_T("Set epq command!"));

    //CBCGPDialog::OnOK();
}


void CSetEPQDialog::OnSelchangeComboModel()
{
    // TODO: Add your control notification handler code here
    //TRACE1("model:%d\n",m_ComboModel.GetCurSel());
    miModel = m_ComboModel.GetCurSel()+1;

    if (miModel == 3) //普通模式
    {
        m_dElevValue = 0.0;
        m_ComboSos.SetCurSel(0);
        miSos = 0;
        m_ComboSos.EnableWindow(0);
        UpdateData(FALSE);
    }

    if (miUrgFlag == 1)
    {
        m_ComboSos.EnableWindow(1);
    }
}


void CSetEPQDialog::OnSelchangeComboFreq()
{
    // TODO: Add your control notification handler code here
    miFreq = m_ComboFreq.GetCurSel()+1;
}


void CSetEPQDialog::OnSelchangeComboSpeed()
{
    // TODO: Add your control notification handler code here
    miSpeed = m_ComboSpeed.GetCurSel()+1;
}


void CSetEPQDialog::OnSelchangeComboSos()
{
    // TODO: Add your control notification handler code here
    miSos = m_ComboSos.GetCurSel();
}


void CSetEPQDialog::OnSelchangeComboUrg()
{
    // TODO: Add your control notification handler code here
    miUrgFlag = m_ComboUrg.GetCurSel()+1;

    switch(miUrgFlag)
    {
    case 1:
        //m_ComboSos.EnableWindow(1);
        break;

    case 2:
        m_ComboSos.SetCurSel(0);
        miSos = 0;
        m_ComboSos.EnableWindow(0);
        UpdateData(FALSE);
        break;

    case 3:
        m_dElevValue = 0.0;
        m_ComboSos.SetCurSel(0);
        miSos = 0;
        m_ComboSos.EnableWindow(0);
        UpdateData(FALSE);
        break;

    default:
        break;
    }

    if (miModel != 3)
    {
        m_ComboSos.EnableWindow(1);
    }
}


void CSetEPQDialog::PostNcDestroy()
{
    // TODO: Add your specialized code here and/or call the base class

    CBCGPDialog::PostNcDestroy();
    delete this;
}
