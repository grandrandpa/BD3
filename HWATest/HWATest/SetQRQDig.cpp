// SetQRQDig.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetQRQDig.h"
#include "afxdialogex.h"


// CSetQRQDig dialog

IMPLEMENT_DYNAMIC(CSetQRQDig, CBCGPDialog)

CSetQRQDig::CSetQRQDig(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetQRQDig::IDD, pParent)
{

    m_iCardID = 0;
}

CSetQRQDig::~CSetQRQDig()
{
}

void CSetQRQDig::DoDataExchange(CDataExchange* pDX)
{
    CBCGPDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_QRQ_CARDID, m_iCardID);
    DDV_MinMaxInt(pDX, m_iCardID, 0, 9999999);
    DDX_Control(pDX, IDC_COMBO_QRQ_TYPE, m_cbQrqType);
}


BEGIN_MESSAGE_MAP(CSetQRQDig, CBCGPDialog)
    ON_BN_CLICKED(IDC_BTN_SENT_QRQ, &CSetQRQDig::OnClickedBtnSentQrq)
END_MESSAGE_MAP()


// CSetQRQDig message handlers
BOOL CSetQRQDig::OnInitDialog()
{
    CBCGPDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    m_cbQrqType.SetCurSel(0);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetQRQDig::OnClickedBtnSentQrq()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);

    SETQRQ data;
    data.CardId = m_iCardID;
    data.Type = m_cbQrqType.GetCurSel()+1;


    theApp.m_winLinkApp.SetupQRQRequest(data);

    //CBCGPDialog::OnOK();
}





void CSetQRQDig::PostNcDestroy()
{
    // TODO: Add your specialized code here and/or call the base class

    CBCGPDialog::PostNcDestroy();
    delete this;
}
