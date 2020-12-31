// SetTcqDig.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetTcqDig.h"
#include "afxdialogex.h"


// CSetTcqDig dialog

IMPLEMENT_DYNAMIC(CSetTcqDig, CBCGPDialog)

CSetTcqDig::CSetTcqDig(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetTcqDig::IDD, pParent)
{
    m_iCardID = 0;
    m_iTimes = 1;
    m_strTCQData = _T("");
}

CSetTcqDig::~CSetTcqDig()
{
}

void CSetTcqDig::DoDataExchange(CDataExchange* pDX)
{
    CBCGPDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BTN_SENT_TCQ, m_btnSendTCQ);
    DDX_Control(pDX, IDC_COMBO_CODE_TYPE, m_cbCodeType);
    DDX_Control(pDX, IDC_COMBO_CONFIRM, m_cbConfirm);
    DDX_Control(pDX, IDC_COMBO_FREQ, m_cbFreq);
    DDX_Text(pDX, IDC_EPQ_CARDID, m_iCardID);
    DDV_MinMaxInt(pDX, m_iCardID, 0, 9999999);
    DDX_Text(pDX, IDC_TIMES_PER_SEC, m_iTimes);
    DDV_MinMaxInt(pDX, m_iTimes, 1, 99);
    DDX_Text(pDX, IDC_TCQ_DATA, m_strTCQData);

}


BEGIN_MESSAGE_MAP(CSetTcqDig, CDialog)
    ON_BN_CLICKED(IDC_BTN_SENT_TCQ, &CSetTcqDig::OnClickedBtnSentTcq)
END_MESSAGE_MAP()


// CSetTcqDig message handlers
BOOL CSetTcqDig::OnInitDialog()
{
    CBCGPDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    m_cbCodeType.SetCurSel(0);
    m_cbConfirm.SetCurSel(0);
    m_cbFreq.SetCurSel(0);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetTcqDig::OnClickedBtnSentTcq()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    //test utf-16
    TRACE("string length:%d\n", strlen(m_strTCQData));
    //end test

    SETTCQ data;
    memset(&data, 0, sizeof(data));
    data.CardId = m_iCardID;
    data.Freq = m_cbFreq.GetCurSel()+1;
    data.CodeType = m_cbCodeType.GetCurSel()+1;
    data.Confirm = m_cbConfirm.GetCurSel()+1;
    data.Times = m_iTimes;

    //strcpy(data.Data, (LPSTR)(LPCTSTR)m_strTCQData);
    //m_strTCQData.GetAt(2);
    int len = 0;
    len = strlen(m_strTCQData)<1000 ? strlen(m_strTCQData) : 1000;
    if (data.CodeType == 1 || data.CodeType == 3)
    {

        char buf[2048] = {0};
        strncpy(buf, m_strTCQData, len);
        for(int i=0; i<len; ++i)
        {
             sprintf(data.Data+i*2, "%02X", (unsigned char)buf[i]);
        }

        TRACE("data hex:%s\n", data.Data);
    }
    else
    {
        strncpy(data.Data, m_strTCQData, len);    //ASCII
    }

    //char s[6];
    //char hs[9];
    //strcpy(s, buf);
    //int i=0;
    //while (1) 
    //{
    //    if (0==s[i]) 
    //        break;
    //    sprintf(hs+i*2,"%02X",(unsigned char)s[i]);
    //    i++;
    //}
    //TRACE("string length:%s\n", hs);


	theApp.m_winLinkApp.SetupTCQRequest(data);

    //CBCGPDialog::OnOK();
    
}


void CSetTcqDig::PostNcDestroy()
{
    // TODO: Add your specialized code here and/or call the base class

    CBCGPDialog::PostNcDestroy();
    delete this;
}
