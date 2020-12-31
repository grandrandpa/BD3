// SetFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "SetFileDlg.h"


// CSetFileDlg dialog
IMPLEMENT_DYNAMIC(CSetFileDlg, CBCGPDialog)

CSetFileDlg::CSetFileDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetFileDlg::IDD, pParent)
	, m_strFilePath(_T(""))
	, m_bStart(false)
{
	CBCGPDialog::EnableVisualManagerStyle(TRUE, TRUE);
}

CSetFileDlg::~CSetFileDlg()
{
	KillTimer(1);
	theApp.m_winPrintApp.Stop();
}
void CSetFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ALM, m_checkAlm);
	DDX_Control(pDX, IDC_CHECK_COD, m_checkCod);
	DDX_Control(pDX, IDC_CHECK_EPH, m_checkEph);
	DDX_Control(pDX, IDC_CHECK_ION, m_checkIon);
	DDX_Control(pDX, IDC_CHECK_JAL, m_checkJal);
	DDX_Control(pDX, IDC_CHECK_MOD, m_checkMod);
	DDX_Control(pDX, IDC_CHECK_POS, m_checkPos);
	DDX_Control(pDX, IDC_CHECK_RAIM, m_checkRaim);
	DDX_Control(pDX, IDC_CHECK_RAN, m_checkRan);
	DDX_Control(pDX, IDC_CHECK_REF, m_checkREF);
	DDX_Control(pDX, IDC_CHECK_SIV, m_checkSIV);
	DDX_Control(pDX, IDC_CHECK_STA, m_checkSTA);
	DDX_Control(pDX, IDC_CHECK_TIM, m_checkTIM);
	DDX_Control(pDX, IDC_CHECK_ALL, m_checkAll);
	DDX_Control(pDX, IDC_EDIT_PATH, m_editPath);
	DDX_Control(pDX, IDC_BTN_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_CHECK_XPV, m_checkXPV);
	DDX_Control(pDX, IDC_BTN_START, m_btnStart);
	DDX_Control(pDX, IDC_BTN_STOP, m_btnStop);
	DDX_Control(pDX, IDC_EDIT_ALM, m_staticALM);
	DDX_Control(pDX, IDC_EDIT_COD, m_staticCOD);
	DDX_Control(pDX, IDC_EDIT_EPH, m_staticEPH);
	DDX_Control(pDX, IDC_EDIT_GBS, m_staticGBS);
	DDX_Control(pDX, IDC_EDIT_GSV, m_staticGSV);
	DDX_Control(pDX, IDC_EDIT_ION, m_staticION);
	DDX_Control(pDX, IDC_EDIT_JAL, m_staticJAL);
	DDX_Control(pDX, IDC_EDIT_MOD, m_staticMOD);
	DDX_Control(pDX, IDC_EDIT_POS, m_staticPOS);
	DDX_Control(pDX, IDC_EDIT_RAN, m_staticRAN);
	DDX_Control(pDX, IDC_EDIT_REF, m_staticREF);
	DDX_Control(pDX, IDC_EDIT_STA, m_staticSTA);
	DDX_Control(pDX, IDC_EDIT_TIM, m_staticTIM);
	DDX_Control(pDX, IDC_EDIT_XPV, m_staticXPV);
	DDX_Control(pDX, IDC_EDIT_RECORD_TIME, m_editRecordTime);
}


BEGIN_MESSAGE_MAP(CSetFileDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_CHECK_RAN, &CSetFileDlg::OnBnClickedCheckRan)
	ON_BN_CLICKED(IDC_CHECK_JAL, &CSetFileDlg::OnBnClickedCheckJal)
	ON_BN_CLICKED(IDC_CHECK_TIM, &CSetFileDlg::OnBnClickedCheckTim)
	ON_BN_CLICKED(IDC_CHECK_EPH, &CSetFileDlg::OnBnClickedCheckEph)
	ON_BN_CLICKED(IDC_CHECK_ALM, &CSetFileDlg::OnBnClickedCheckAlm)
	ON_BN_CLICKED(IDC_CHECK_POS, &CSetFileDlg::OnBnClickedCheckPos)
	ON_BN_CLICKED(IDC_CHECK_MOD, &CSetFileDlg::OnBnClickedCheckMod)
	ON_BN_CLICKED(IDC_CHECK_SIV, &CSetFileDlg::OnBnClickedCheckSiv)
	ON_BN_CLICKED(IDC_CHECK_COD, &CSetFileDlg::OnBnClickedCheckCod)
	ON_BN_CLICKED(IDC_CHECK_ION, &CSetFileDlg::OnBnClickedCheckIon)
	ON_BN_CLICKED(IDC_CHECK_STA, &CSetFileDlg::OnBnClickedCheckSta)
	ON_BN_CLICKED(IDC_CHECK_REF, &CSetFileDlg::OnBnClickedCheckRef)
	ON_BN_CLICKED(IDC_CHECK_RAIM, &CSetFileDlg::OnBnClickedCheckRaim)
	ON_BN_CLICKED(IDC_CHECK_ALL, &CSetFileDlg::OnBnClickedCheckAll)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CSetFileDlg::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_CHECK_XPV, &CSetFileDlg::OnBnClickedCheckXpv)
	ON_BN_CLICKED(IDC_BTN_START, &CSetFileDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CSetFileDlg::OnBnClickedBtnStop)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSetFileDlg message handlers

BOOL CSetFileDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	CString strText;
	char buf[MAX_PATH];
	GetPrivateProfileString("Product", "ProjPath", "", buf, MAX_PATH, theApp.m_strProjFile);
	strText = CString(buf);
	m_editPath.SetWindowText(strText);
	m_btnStart.EnableWindow(TRUE);
	m_btnStop.EnableWindow(FALSE);
	ResetCounter();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
void CSetFileDlg::SetProjectPath(CString strPath)
{
	m_editPath.SetWindowText(strPath);
}
void CSetFileDlg::OnBnClickedCheckRan()
{
	// TODO: Add your control notification handler code here
	CString str;
	int flag = m_checkRan.GetCheck();
	WritePrivateProfileString("FILE", "ran", flag?"1":"0", theApp.m_strProjFile);
}

void CSetFileDlg::OnBnClickedCheckJal()
{
	// TODO: Add your control notification handler code here
	CString str;
	int flag = m_checkJal.GetCheck();
	WritePrivateProfileString("FILE", "jal", flag?"1":"0", theApp.m_strProjFile);
}

void CSetFileDlg::OnBnClickedCheckTim()
{
	// TODO: Add your control notification handler code here
	CString str;
	int flag = m_checkTIM.GetCheck();
	WritePrivateProfileString("FILE", "tim", flag?"1":"0", theApp.m_strProjFile);
}

void CSetFileDlg::OnBnClickedCheckEph()
{
	// TODO: Add your control notification handler code here
	CString str;
	int flag = m_checkEph.GetCheck();
	WritePrivateProfileString("FILE", "eph", flag?"1":"0", theApp.m_strProjFile);
}

void CSetFileDlg::OnBnClickedCheckAlm()
{
	// TODO: Add your control notification handler code here
	CString str;
	int flag = m_checkAlm.GetCheck();
	WritePrivateProfileString("FILE", "alm", flag?"1":"0", theApp.m_strProjFile);
}

void CSetFileDlg::OnBnClickedCheckPos()
{
	// TODO: Add your control notification handler code here
	CString str;
	int flag = m_checkPos.GetCheck();
	WritePrivateProfileString("FILE", "pos", flag?"1":"0", theApp.m_strProjFile);
}

void CSetFileDlg::OnBnClickedCheckMod()
{
	// TODO: Add your control notification handler code here
	CString str;
	int flag = m_checkMod.GetCheck();
	WritePrivateProfileString("FILE", "mod", flag?"1":"0", theApp.m_strProjFile);
}

void CSetFileDlg::OnBnClickedCheckSiv()
{
	// TODO: Add your control notification handler code here
	CString str;
	int flag = m_checkSIV.GetCheck();
	WritePrivateProfileString("FILE", "gsv", flag?"1":"0", theApp.m_strProjFile);
}

void CSetFileDlg::OnBnClickedCheckCod()
{
	// TODO: Add your control notification handler code here
	CString str;
	int flag = m_checkCod.GetCheck();
	WritePrivateProfileString("FILE", "cod", flag?"1":"0", theApp.m_strProjFile);
}

void CSetFileDlg::OnBnClickedCheckIon()
{
	// TODO: Add your control notification handler code here
	CString str;
	int flag = m_checkIon.GetCheck();
	WritePrivateProfileString("FILE", "ion", flag?"1":"0", theApp.m_strProjFile);
}

void CSetFileDlg::OnBnClickedCheckSta()
{
	// TODO: Add your control notification handler code here
	CString str;
	int flag = m_checkSTA.GetCheck();
	WritePrivateProfileString("FILE", "sta", flag?"1":"0", theApp.m_strProjFile);
}

void CSetFileDlg::OnBnClickedCheckRef()
{
	// TODO: Add your control notification handler code here
	CString str;
	int flag = m_checkREF.GetCheck();
	WritePrivateProfileString("FILE", "ref", flag?"1":"0", theApp.m_strProjFile);
}

void CSetFileDlg::OnBnClickedCheckRaim()
{
	// TODO: Add your control notification handler code here
	CString str;
	int flag = m_checkRaim.GetCheck();
	WritePrivateProfileString("FILE", "gbs", flag?"1":"0", theApp.m_strProjFile);
}

void CSetFileDlg::OnBnClickedCheckXpv()
{
	// TODO: Add your control notification handler code here
	int flag = m_checkXPV.GetCheck();
	WritePrivateProfileString("FILE", "xpv", flag?"1":"0", theApp.m_strProjFile);
}

void CSetFileDlg::ResetCounter()
{
	m_staticALM.SetWindowText("0");
	m_staticCOD.SetWindowText("0");
	m_staticEPH.SetWindowText("0");
	m_staticGBS.SetWindowText("0");
	m_staticGSV.SetWindowText("0");
	m_staticION.SetWindowText("0");
	m_staticJAL.SetWindowText("0");
	m_staticMOD.SetWindowText("0");
	m_staticPOS.SetWindowText("0");
	m_staticRAN.SetWindowText("0");
	m_staticREF.SetWindowText("0");
	m_staticSTA.SetWindowText("0");
	m_staticTIM.SetWindowText("0");
	m_staticXPV.SetWindowText("0");
}
void CSetFileDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CString strName;
	CStdioFile hFile;
	ULONGLONG length = 0;
	if (nIDEvent == 1)
	{
		strName.Empty();
		CTime tt = CTime::GetCurrentTime();
		CTimeSpan span = tt - m_startTime;
		strName = span.Format("记录时间：%D天%H时%M分%S秒");
		m_editRecordTime.SetWindowText(strName);
		//m_startTime
		//////////////////////////////////////////////////////////////////////////
		strName.Empty();
		strName = theApp.m_strDatabase + "COD.table";
		if(hFile.Open(strName, CFile::modeReadWrite))
		{
			length = hFile.GetLength();
			strName.Empty();
			if (length>=1024 && length <1024*1024)
			{
				strName.Format("%dKB", length/1024);
			} 
			else if(length >= 1024*1024)
			{
				strName.Format("%dMB", length/1024/1024);
			}
			else
			{
				strName.Format("%dB", length);
			}
			m_staticCOD.SetWindowText(strName);
			hFile.Close();
		}
		//////////////////////////////////////////////////////////////////////////
		strName.Empty();
		strName = theApp.m_strDatabase + "EPH.table";
		if(hFile.Open(strName, CFile::modeReadWrite))
		{
			length = hFile.GetLength();
			strName.Empty();
			if (length>=1024 && length <1024*1024)
			{
				strName.Format("%dKB", length/1024);
			} 
			else if(length >= 1024*1024)
			{
				strName.Format("%dMB", length/1024/1024);
			}
			else
			{
				strName.Format("%dB", length);
			}
			m_staticEPH.SetWindowText(strName);
			hFile.Close();
		}
		//////////////////////////////////////////////////////////////////////////
		strName.Empty();
		strName = theApp.m_strDatabase + "ION.table";
		if(hFile.Open(strName, CFile::modeReadWrite))
		{
			length = hFile.GetLength();
			strName.Empty();
			if (length>=1024 && length <1024*1024)
			{
				strName.Format("%dKB", length/1024);
			} 
			else if(length >= 1024*1024)
			{
				strName.Format("%dMB", length/1024/1024);
			}
			else
			{
				strName.Format("%dB", length);
			}
			m_staticION.SetWindowText(strName);
			hFile.Close();
		}
		//////////////////////////////////////////////////////////////////////////
		strName.Empty();
		strName = theApp.m_strDatabase + "ALM.table";
		if(hFile.Open(strName, CFile::modeReadWrite))
		{
			length = hFile.GetLength();
			strName.Empty();
			if (length>=1024 && length <1024*1024)
			{
				strName.Format("%dKB", length/1024);
			} 
			else if(length >= 1024*1024)
			{
				strName.Format("%dMB", length/1024/1024);
			}
			else
			{
				strName.Format("%dB", length);
			}
			m_staticALM.SetWindowText(strName);
			hFile.Close();
		}
		//////////////////////////////////////////////////////////////////////////
		strName.Empty();
		strName = theApp.m_strDatabase + "JAL.table";
		if(hFile.Open(strName, CFile::modeReadWrite))
		{
			length = hFile.GetLength();
			strName.Empty();
			if (length>=1024 && length <1024*1024)
			{
				strName.Format("%dKB", length/1024);
			} 
			else if(length >= 1024*1024)
			{
				strName.Format("%dMB", length/1024/1024);
			}
			else
			{
				strName.Format("%dB", length);
			}
			m_staticJAL.SetWindowText(strName);
			hFile.Close();
		}
		//////////////////////////////////////////////////////////////////////////
		strName.Empty();
		strName = theApp.m_strDatabase + "MOD.table";
		if(hFile.Open(strName, CFile::modeReadWrite))
		{
			length = hFile.GetLength();
			strName.Empty();
			if (length>=1024 && length <1024*1024)
			{
				strName.Format("%dKB", length/1024);
			} 
			else if(length >= 1024*1024)
			{
				strName.Format("%dMB", length/1024/1024);
			}
			else
			{
				strName.Format("%dB", length);
			}
			m_staticMOD.SetWindowText(strName);
			hFile.Close();
		}
		//////////////////////////////////////////////////////////////////////////
		strName.Empty();
		strName = theApp.m_strDatabase + "POS.table";
		if(hFile.Open(strName, CFile::modeReadWrite))
		{
			length = hFile.GetLength();
			strName.Empty();
			if (length>=1024 && length <1024*1024)
			{
				strName.Format("%dKB", length/1024);
			} 
			else if(length >= 1024*1024)
			{
				strName.Format("%dMB", length/1024/1024);
			}
			else
			{
				strName.Format("%dB", length);
			}
			m_staticPOS.SetWindowText(strName);
			hFile.Close();
		}
		//////////////////////////////////////////////////////////////////////////
		strName.Empty();
		strName = theApp.m_strDatabase + "XPV.table";
		if(hFile.Open(strName, CFile::modeReadWrite))
		{
			length = hFile.GetLength();
			strName.Empty();
			if (length>=1024 && length <1024*1024)
			{
				strName.Format("%dKB", length/1024);
			} 
			else if(length >= 1024*1024)
			{
				strName.Format("%dMB", length/1024/1024);
			}
			else
			{
				strName.Format("%dB", length);
			}
			m_staticXPV.SetWindowText(strName);
			hFile.Close();
		}
		//////////////////////////////////////////////////////////////////////////
		strName.Empty();
		strName = theApp.m_strDatabase + "RAN.table";
		if(hFile.Open(strName, CFile::modeReadWrite))
		{
			length = hFile.GetLength();
			strName.Empty();
			if (length>=1024 && length <1024*1024)
			{
				strName.Format("%dKB", length/1024);
			} 
			else if(length >= 1024*1024)
			{
				strName.Format("%dMB", length/1024/1024);
			}
			else
			{
				strName.Format("%dB", length);
			}
			m_staticRAN.SetWindowText(strName);
			hFile.Close();
		}
		//////////////////////////////////////////////////////////////////////////
		strName.Empty();
		strName = theApp.m_strDatabase + "REF.table";
		if(hFile.Open(strName, CFile::modeReadWrite))
		{
			length = hFile.GetLength();
			strName.Empty();
			if (length>=1024 && length <1024*1024)
			{
				strName.Format("%dKB", length/1024);
			} 
			else if(length >= 1024*1024)
			{
				strName.Format("%dMB", length/1024/1024);
			}
			else
			{
				strName.Format("%dB", length);
			}
			m_staticREF.SetWindowText(strName);
			hFile.Close();
		}
		//////////////////////////////////////////////////////////////////////////
		strName.Empty();
		strName = theApp.m_strDatabase + "GSV.table";
		if(hFile.Open(strName, CFile::modeReadWrite))
		{
			length = hFile.GetLength();
			strName.Empty();
			if (length>=1024 && length <1024*1024)
			{
				strName.Format("%dKB", length/1024);
			} 
			else if(length >= 1024*1024)
			{
				strName.Format("%dMB", length/1024/1024);
			}
			else
			{
				strName.Format("%dB", length);
			}
			m_staticGSV.SetWindowText(strName);
			hFile.Close();
		}
		//////////////////////////////////////////////////////////////////////////
		strName.Empty();
		strName = theApp.m_strDatabase + "STA.table";
		if(hFile.Open(strName, CFile::modeReadWrite))
		{
			length = hFile.GetLength();
			strName.Empty();
			if (length>=1024 && length <1024*1024)
			{
				strName.Format("%dKB", length/1024);
			} 
			else if(length >= 1024*1024)
			{
				strName.Format("%dMB", length/1024/1024);
			}
			else
			{
				strName.Format("%dB", length);
			}
			m_staticSTA.SetWindowText(strName);
			hFile.Close();
		}
		//////////////////////////////////////////////////////////////////////////
		strName.Empty();
		strName = theApp.m_strDatabase + "TIM.table";
		if(hFile.Open(strName, CFile::modeReadWrite))
		{
			length = hFile.GetLength();
			strName.Empty();
			if (length>=1024 && length <1024*1024)
			{
				strName.Format("%dKB", length/1024);
			} 
			else if(length >= 1024*1024)
			{
				strName.Format("%dMB", length/1024/1024);
			}
			else
			{
				strName.Format("%dB", length);
			}
			m_staticTIM.SetWindowText(strName);
			hFile.Close();
		}
		//////////////////////////////////////////////////////////////////////////
		strName.Empty();
		strName = theApp.m_strDatabase + "GBS.table";
		if(hFile.Open(strName, CFile::modeReadWrite))
		{
			length = hFile.GetLength();
			strName.Empty();
			if (length>=1024 && length <1024*1024)
			{
				strName.Format("%dKB", length/1024);
			} 
			else if(length >= 1024*1024)
			{
				strName.Format("%dMB", length/1024/1024);
			}
			else
			{
				strName.Format("%dB", length);
			}
			m_staticGBS.SetWindowText(strName);
			hFile.Close();
		}
		//////////////////////////////////////////////////////////////////////////
	}
	//UpdateData(FALSE);

	CBCGPDialog::OnTimer(nIDEvent);
}

void CSetFileDlg::OnBnClickedCheckAll()
{
	// TODO: Add your control notification handler code here
	int flag = m_checkAll.GetCheck();
	m_checkREF.SetCheck(flag);
	OnBnClickedCheckRef();
	m_checkMod.SetCheck(flag);
	OnBnClickedCheckMod();
	m_checkRan.SetCheck(flag);
	OnBnClickedCheckRan();
	m_checkEph.SetCheck(flag);
	OnBnClickedCheckEph();
	m_checkAlm.SetCheck(flag);
	OnBnClickedCheckAlm();
	m_checkJal.SetCheck(flag);
	OnBnClickedCheckJal();
	m_checkIon.SetCheck(flag);
	OnBnClickedCheckIon();
	m_checkCod.SetCheck(flag);
	OnBnClickedCheckCod();
	m_checkPos.SetCheck(flag);
	OnBnClickedCheckPos();
	m_checkTIM.SetCheck(flag);
	OnBnClickedCheckTim();
	m_checkSTA.SetCheck(flag);
	OnBnClickedCheckSta();
	m_checkSIV.SetCheck(flag);
	OnBnClickedCheckSiv();
	m_checkRaim.SetCheck(flag);
	OnBnClickedCheckRaim();
	m_checkXPV.SetCheck(flag);
	OnBnClickedCheckXpv();
}
void CSetFileDlg::Reset()
{
	bool flag = FALSE;
	m_checkAll.SetCheck(flag);
	m_checkREF.SetCheck(flag);
	OnBnClickedCheckRef();
	m_checkMod.SetCheck(flag);
	OnBnClickedCheckMod();
	m_checkRan.SetCheck(flag);
	OnBnClickedCheckRan();
	m_checkEph.SetCheck(flag);
	OnBnClickedCheckEph();
	m_checkAlm.SetCheck(flag);
	OnBnClickedCheckAlm();
	m_checkJal.SetCheck(flag);
	OnBnClickedCheckJal();
	m_checkIon.SetCheck(flag);
	OnBnClickedCheckIon();
	m_checkCod.SetCheck(flag);
	OnBnClickedCheckCod();
	m_checkPos.SetCheck(flag);
	OnBnClickedCheckPos();
	m_checkTIM.SetCheck(flag);
	OnBnClickedCheckTim();
	m_checkSTA.SetCheck(flag);
	OnBnClickedCheckSta();
	m_checkSIV.SetCheck(flag);
	OnBnClickedCheckSiv();
	m_checkRaim.SetCheck(flag);
	OnBnClickedCheckRaim();
	m_checkXPV.SetCheck(flag);
	OnBnClickedCheckXpv();
}
void CSetFileDlg::OnBnClickedBtnSave()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_strProjPath.IsEmpty())
		return;

	ShellExecute(NULL, "open",  theApp.m_strProjPath, NULL, NULL, SW_SHOWNORMAL);
}

void CSetFileDlg::OnBnClickedBtnStart()
{
	// TODO: Add your control notification handler code here
	int i=0, len=0;
	CString strText,strTemp,strPath;
	CTime tt = CTime::GetCurrentTime();
	ResetCounter();
	strText.Format("%04d%02d%02d%02d%02d%02d", tt.GetYear(),tt.GetMonth(),tt.GetDay(),tt.GetHour(),tt.GetMinute(),tt.GetSecond());
	strTemp = theApp.m_strProjPath+"\\SaveData" + "\\"+strText;
	CreateDirectory(strTemp, NULL);
	CreateDirectory(strTemp+"\\COD", NULL);
	CreateDirectory(strTemp+"\\EPH", NULL);
	CreateDirectory(strTemp+"\\ALM", NULL);
	CreateDirectory(strTemp+"\\POS", NULL);
	CreateDirectory(strTemp+"\\XPV", NULL);
	CreateDirectory(strTemp+"\\RAN", NULL);
	//CreateDirectory(strTemp+"\\BDALM", NULL);
	//CreateDirectory(strTemp+"\\BDJAL", NULL);
	theApp.m_strSaveData = strTemp;
	WritePrivateProfileString("Product", "SaveData", theApp.m_strSaveData, theApp.m_strProjFile);
	WritePrivateProfileString("FILE", "SaveData", strText, theApp.m_strProjFile);
	theApp.m_winPrintApp.LoadConfig(theApp.m_strDatabase, theApp.m_strProjFile);
	m_btnStart.EnableWindow(FALSE);
	m_btnStop.EnableWindow(TRUE);
	theApp.m_winPrintApp.Start();
	m_startTime = CTime::GetCurrentTime();
	SetTimer(1, 1000, NULL);
}

void CSetFileDlg::OnBnClickedBtnStop()
{
	// TODO: Add your control notification handler code here
	m_btnStart.EnableWindow(TRUE);
	m_btnStop.EnableWindow(FALSE);
	theApp.m_winPrintApp.Stop();
	KillTimer(1);
}
