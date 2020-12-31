// SendCmdDig.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SendCmdDig.h"
#include "afxdialogex.h"


// CSendCmdDig dialog

IMPLEMENT_DYNAMIC(CSendCmdDig, CDialogEx)

CSendCmdDig::CSendCmdDig(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSendCmdDig::IDD, pParent)
{
    m_ckCheckout = TRUE;
    m_bAddCR = TRUE;
    m_ckLoopSend = FALSE;
    m_strCmd = _T("");

    m_TimerID = -1;
    m_strLoopCmd.clear();
}

CSendCmdDig::~CSendCmdDig()
{
}

void CSendCmdDig::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, ID_START, m_btnStart);
    DDX_Control(pDX, ID_STOP, m_btnStop);
    DDX_Check(pDX, IDC_CHECK_CHECKOUT, m_ckCheckout);
    DDX_Check(pDX, IDC_CHECK_ENTER, m_bAddCR);
    DDX_Check(pDX, IDC_CHECK_LOOP_SEND, m_ckLoopSend);
    DDX_Text(pDX, IDC_EDIT_CMD, m_strCmd);
}


BEGIN_MESSAGE_MAP(CSendCmdDig, CDialogEx)
    ON_BN_CLICKED(ID_START, &CSendCmdDig::OnClickedStart)
    ON_BN_CLICKED(ID_STOP, &CSendCmdDig::OnClickedStop)
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CSendCmdDig message handlers


void CSendCmdDig::OnClickedStart()
{
    // TODO: Add your control notification handler code here
    UpdateData (TRUE);
    
    //CString strDur;
    //pBoxOne = (CEdit*) GetDlgItem(IDC_EDIT_SEND_DUR);
    //pBoxOne->GetWindowText(strDur);
    //int iDur = atoi(strDur);//_ttoi(strDur);
    int iDur = 1000;

    CEdit* pBoxOne;
    CString cmd;
    pBoxOne = (CEdit*) GetDlgItem(IDC_EDIT_CMD);
    pBoxOne->GetWindowText(cmd);

    if(m_ckCheckout)
    {
        cmd.Append(CalXorValue(cmd));
    }

    if (m_bAddCR)
    {
        cmd.Append("\r\n");
    }

    std::string data((LPCTSTR)cmd);
    theApp.m_winLinkApp.SendCmdRequest(data);

    //m_strCmd = _T("");
    //UpdateData (FALSE);


    if (m_ckLoopSend)
    {
        m_strLoopCmd = data;
        m_btnStart.EnableWindow(FALSE);
        m_TimerID = SetTimer(ID_SEND_TIMER, iDur, NULL); //Send comand
    }
    else
    {
        m_strLoopCmd.clear();
    }
}


void CSendCmdDig::OnClickedStop()
{
    // TODO: Add your control notification handler code here
    UpdateData (FALSE);

    if (m_TimerID != -1)
    {
        KillTimer(ID_SEND_TIMER);
        m_TimerID = -1;
    }

    if (m_ckLoopSend)
    {
        m_btnStart.EnableWindow(TRUE);
    }
}

void CSendCmdDig::StringToHex(char *str, char *strhex)
{
    int i, cnt=0;
    char *p = str;
    int len = strlen(str);

    while(*p != '\0')
    {
        for(i = 0; i< len; ++i)
        {
            if ((*p>='0') && (*p<='9'))
            {
                strhex[cnt] = *p - '0' + 0x30;
            }

            if ((*p>='A') && (*p<='Z'))
            {
                strhex[cnt] = *p - 'A' + 0x41;
            }

            if ((*p>='a') && (*p<='z'))
            {
                strhex[cnt] = *p - 'a' + 0x61;
            }

            if( *p == ',')
            {
                strhex[cnt] = 0x2C;
            }

            if( *p == '^')
            {
                strhex[cnt] = 0x5E;
            }

            p++;
            cnt++;
        }
        strhex[cnt] = '\0';
    }
}

CString CSendCmdDig::CalXorValue(CString cstr)
{
    char *cmdChar = (LPSTR)(LPCTSTR)cstr;
    int len = strlen(cmdChar);
    int check_result = *(cmdChar+1);
    cmdChar += 2;

    for (int i=0; i<len-1; ++i)
    {
        check_result ^= *cmdChar;
        cmdChar++;
    }

    CString tmp;
    tmp.Format(_T("*%X"), check_result);

    return tmp;
}

void CSendCmdDig::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    if (nIDEvent == ID_SEND_TIMER && !m_strLoopCmd.empty())
    {
       theApp.m_winLinkApp.SendCmdRequest(m_strLoopCmd);
    }

    CDialogEx::OnTimer(nIDEvent);
}
