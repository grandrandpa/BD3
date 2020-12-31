// HWATest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "HWATest.h"

#include "ChildFrm.h"
#include "HWATestDoc.h"
#include "HWATestView.h"
#include "afxwin.h"
#include "DrawTestView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About
class CAboutDlg : public CBCGPDialog
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_editTips;
};

CAboutDlg::CAboutDlg() : CBCGPDialog(CAboutDlg::IDD)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TIPS, m_editTips);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBCGPDialog)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

const int  iMaxUserToolbars		= 10;
const UINT uiFirstUserToolBarId	= AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId	= uiFirstUserToolBarId + iMaxUserToolbars - 1;

// CHWATestApp

BEGIN_MESSAGE_MAP(CHWATestApp, CBCGPWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CBCGPWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CBCGPWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CBCGPWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CHWATestApp construction

CHWATestApp::CHWATestApp()
: m_nProjectType(0)
, m_strConfigPath(_T(""))
, m_bConnectFlag(false)
, m_nConnectType(0)
, m_bStaticMeasure(false)
{
	/*AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2000, ID_VIEW_APPLOOK_2000);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_XP, ID_VIEW_APPLOOK_XP);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2003, ID_VIEW_APPLOOK_2003);
	AddVisualTheme(BCGP_VISUAL_THEME_VS_2005, ID_VIEW_APPLOOK_VS2005);
	AddVisualTheme(BCGP_VISUAL_THEME_VS_2008, ID_VIEW_APPLOOK_VS2008);
	AddVisualTheme(BCGP_VISUAL_THEME_VS_2010, ID_VIEW_APPLOOK_VS2010);
	AddVisualTheme(BCGP_VISUAL_THEME_VS_2012_LIGHT, ID_VIEW_APPLOOK_VS2012_LIGHT);
	AddVisualTheme(BCGP_VISUAL_THEME_VS_2012_DARK, ID_VIEW_APPLOOK_VS2012_DARK);
	AddVisualTheme(BCGP_VISUAL_THEME_VS_2012_BLUE, ID_VIEW_APPLOOK_VS2012_BLUE);
	AddVisualTheme(BCGP_VISUAL_THEME_DEFAULT, ID_VIEW_APPLOOK_WINDOWS_NATIVE);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2007_BLUE, ID_VIEW_APPLOOK_2007);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2007_BLACK, ID_VIEW_APPLOOK_2007_1);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2007_SILVER, ID_VIEW_APPLOOK_2007_2);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2007_AQUA, ID_VIEW_APPLOOK_2007_3);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2010_BLUE, ID_VIEW_APPLOOK_2010_1);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2010_BLACK, ID_VIEW_APPLOOK_2010_2);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2010_SILVER, ID_VIEW_APPLOOK_2010_3);
	AddVisualTheme(BCGP_VISUAL_THEME_SCENIC, ID_VIEW_APPLOOK_WIN7);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2013_WHITE, ID_VIEW_APPLOOK_2013_1);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2013_GRAY, ID_VIEW_APPLOOK_2013_2);
	AddVisualTheme(BCGP_VISUAL_THEME_OFFICE_2013_DARK_GRAY, ID_VIEW_APPLOOK_2013_3);*/
    //AddVisualTheme(BCGP_VISUAL_THEME_VS_2013_LIGHT, ID_VIEW_APPLOOK_2013_1);
	SetVisualTheme(BCGP_VISUAL_THEME_OFFICE_2013_GRAY);//BCGP_VISUAL_THEME_OFFICE_2013_GRAY

	/*CBCGPToolbarOptions toolbarOptions;
	toolbarOptions.m_nViewToolbarsMenuEntryID = ID_VIEW_TOOLBARS;
	toolbarOptions.m_nCustomizeCommandID = ID_VIEW_CUSTOMIZE;
	toolbarOptions.m_strCustomizeCommandLabel = _T("Customize...");
	SetToolbarOptions(toolbarOptions);*/

	// TODO: add construction code here
	m_nProtocol = 0;
	m_strPictures.Empty();
	m_strOriginData.Empty();
	ZeroMemory(&m_CurPosition, sizeof(BD2_USER_BLH));
	// Setup custom color theme:// Setup custom color theme:
	CBCGPChartTheme::InitChartColors(m_CustomColorTheme, 
		CBCGPColor::White,		// Fill color
		CBCGPColor::Chocolate,	// Outline color
		CBCGPColor::Maroon,		// Text color
		CBCGPColor(), 
		CBCGPColor::SeaShell, .08);

	InitSeriesColors(m_CustomColorTheme.m_seriesColors[0], CBCGPColor::Crimson);
	InitSeriesColors(m_CustomColorTheme.m_seriesColors[1], CBCGPColor::BlueViolet);
	InitSeriesColors(m_CustomColorTheme.m_seriesColors[2], CBCGPColor::CornflowerBlue);
	InitSeriesColors(m_CustomColorTheme.m_seriesColors[3], CBCGPColor::DarkGreen);
	InitSeriesColors(m_CustomColorTheme.m_seriesColors[4], CBCGPColor::Coral);

	// Create custom texture theme:
	CBCGPChartTheme::InitChartColors(m_CustomTexturedTheme, 
		CBCGPColor::White,	// Fill color
		CBCGPColor::CadetBlue,	// Outline color
		CBCGPColor::CadetBlue,		// Text color
		CBCGPColor(), 
		CBCGPColor::SeaShell, .08);
	// TODO: add construction code here
}


// The one and only CHWATestApp object

CHWATestApp theApp;


// CHWATestApp initialization

BOOL CHWATestApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CBCGPWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

	//用户登录设置
	/*CLoginDlg  loginDlg;
	if(loginDlg.DoModal()!=IDOK)
		return FALSE;*/
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("北京华力创通科技股份有限公司技术研究中心"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	SetRegistryBase(_T("Settings"));

	//////////////////////////////////////////////////////////////////////////
	CString strText;
	char buff[MAX_PATH];
	GetCurrentDirectory(255, buff);
	strText = CString(buff);
	m_strConfigPath = strText + "\\config.ini";

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CHWATestView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	/////////////////////////////创建模板/////////////////////////////////////////////
	if (!CreateDocTemplate())
		return FALSE;

	//////////////////////////////////////////////////////////////////////////
	clrBarFace = RGB(101,147,207);
	clrTextFace = RGB(247,66,0);//RGB(21,66,139);//
	clrBkFace = RGB(231,241,254);//RGB(0,0,0);//
	m_GnsspenLine.CreatePen (PS_SOLID, 1,clrBarFace);
	m_GnssDotpenLine.CreatePen (PS_DOT, 1,clrBarFace);
	LOGFONT lfIcon;
	VERIFY(::SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(lfIcon), &lfIcon, 0));
	lfIcon.lfWeight = FW_NORMAL;
	lfIcon.lfItalic = FALSE;
	m_GnssfontNormal.CreateFontIndirect(&lfIcon);
	lfIcon.lfHeight = 20;
	lfIcon.lfWeight = FW_BOLD;
	m_GnssfontBold.CreateFontIndirect(&lfIcon);
	lfIcon.lfHeight = 50;
	lfIcon.lfWeight = FW_BOLD;
	m_GnssfontNormal25.CreateFontIndirect(&lfIcon);
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	// call DragAcceptFiles only if there's a suffix
	// In an MDI app, this should occur immediately after setting m_pMainWnd

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
	{
		if (!pMainFrame->LoadMDIState(GetRegSectionPath()) || 
			DYNAMIC_DOWNCAST(CMDIChildWnd, pMainFrame->GetActiveFrame()) == NULL)
		{
			if (!ProcessShellCommand(cmdInfo))
				return FALSE;
		}
	}
	else
	{
		// Dispatch commands specified on the command line
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;
	}
	// The main window has been initialized, so show and update it
	GetPrivateProfileString("Product", "Name", "北斗多频试验验证终端测试系统", buff, MAX_PATH, m_strConfigPath);
	strText = CString(buff);
	pMainFrame->SetWindowText(strText);
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	return TRUE;
}

// CHWATestApp message handlers 
BOOL CHWATestApp::CreateDocTemplate()
{
	m_pChaTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CShowChaView));
	if (!m_pChaTemplate)
		return FALSE;
	AddDocTemplate(m_pChaTemplate);

	m_pVelTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CShowVelView));
	if (!m_pVelTemplate)
		return FALSE;
	AddDocTemplate(m_pVelTemplate);

	m_pXpvTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CShowXpvView));
	if (!m_pXpvTemplate)
		return FALSE;
	AddDocTemplate(m_pXpvTemplate);

	m_pGbsTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CShowGbsView));
	if (!m_pGbsTemplate)
		return FALSE;
	AddDocTemplate(m_pGbsTemplate);

	m_pSivTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CShowSivView));
	if (!m_pSivTemplate)
		return FALSE;
	AddDocTemplate(m_pSivTemplate);

	m_pPAOrderTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // test
		RUNTIME_CLASS(CDrawPAOrderView));
	if (!m_pPAOrderTemplate)
		return FALSE;
	AddDocTemplate(m_pPAOrderTemplate);
	

	m_pSrcTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CShowSrcView));
	if (!m_pSrcTemplate)
		return FALSE;
	AddDocTemplate(m_pSrcTemplate);

	m_pTimTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CShowTimView));
	if (!m_pTimTemplate)
		return FALSE;
	AddDocTemplate(m_pTimTemplate);

	m_pEphTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CShowEphView));
	if (!m_pEphTemplate)
		return FALSE;
	AddDocTemplate(m_pEphTemplate);

	m_pIonTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CShowIonView));
	if (!m_pIonTemplate)
		return FALSE;
	AddDocTemplate(m_pIonTemplate);

	m_pJalTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CShowJalView));
	if (!m_pJalTemplate)
		return FALSE;
	AddDocTemplate(m_pJalTemplate);

	m_pPosTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CShowPosView));
	if (!m_pPosTemplate)
		return FALSE;
	AddDocTemplate(m_pPosTemplate);

	m_pRanTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CShowRanView));
	if (!m_pRanTemplate)
		return FALSE;
	AddDocTemplate(m_pRanTemplate);

	m_pChDecodeTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom ChDecode child frame
		RUNTIME_CLASS(ChDecodeView));
	if (!m_pChDecodeTemplate)
		return FALSE;
	AddDocTemplate(m_pChDecodeTemplate);
	

	m_pAlmTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CShowAlmView));
	if (!m_pAlmTemplate)
		return FALSE;
	AddDocTemplate(m_pAlmTemplate);

	m_pDrawPosTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CDrawPosView));
	if (!m_pDrawPosTemplate)
		return FALSE;
	AddDocTemplate(m_pDrawPosTemplate);

	m_pDrawRanTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CDrawRanView));
	if (!m_pDrawRanTemplate)
		return FALSE;
	AddDocTemplate(m_pDrawRanTemplate);

    m_pGgaPosTemplate = new CMultiDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CHWATestDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CShowGgaPosView));
	if (!m_pGgaPosTemplate)
		return FALSE;
	AddDocTemplate(m_pGgaPosTemplate);

	return TRUE;
}

int CHWATestApp::ExitInstance() 
{
	Reset();
	Clear();

	return CBCGPWinApp::ExitInstance();
}

void CHWATestApp::UpdateChartColorTheme(int nTheme)
{

}
void CHWATestApp::Reset()
{
	delete m_pSrcTemplate;
	delete m_pAlmTemplate;
	delete m_pEphTemplate;
	delete m_pIonTemplate;
	delete m_pJalTemplate;
	delete m_pPosTemplate;
	delete m_pRanTemplate;
	delete m_pTimTemplate;
	delete m_pSivTemplate;
	delete m_pGbsTemplate;
	delete m_pDrawPosTemplate;
	delete m_pDrawRanTemplate;
	delete m_pPAOrderTemplate;
	delete m_pChDecodeTemplate;
    delete m_pGgaPosTemplate;

	m_pSrcTemplate = NULL;
	m_pAlmTemplate = NULL;
	m_pEphTemplate = NULL;
	m_pIonTemplate = NULL;
	m_pJalTemplate = NULL;
	m_pPosTemplate = NULL;
	m_pRanTemplate = NULL;
	m_pTimTemplate = NULL;
	m_pSivTemplate = NULL;
	m_pGbsTemplate = NULL;
	m_pDrawPosTemplate = NULL;
	m_pDrawRanTemplate = NULL;
	m_pPAOrderTemplate = NULL;
	m_pChDecodeTemplate = NULL;
    m_pGgaPosTemplate = NULL;
}

void CHWATestApp::Clear()
{
	m_nProtocol = 0;
	m_nConnectType = 0;
	m_nProjectType = 0;
	m_bConnectFlag = false;
	m_bStaticMeasure = false;
	m_strProjPath.Empty();
	m_strProjName.Empty();
	m_strProjFile.Empty();
	m_strDatabase.Empty();
	m_strPictures.Empty();
	m_strProjPath.Empty();
	m_strProjPath.Empty();
	m_strSaveData.Empty();
	m_strSatPath.Empty();
	memset(&m_CurPosition, 0, sizeof(BD2_USER_BLH));
	m_winLinkApp.Close();
	m_LinkTestApp.Close();
	m_winPlayerApp.stopPlay();
	m_winPrintApp.Stop();
}

// App command to run the dialog
void CHWATestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CHWATestApp message handlers


void CHWATestApp::PreLoadState()
{

	//GetContextMenuManager()->AddMenu(_T("My menu"), IDR_CONTEXT_MENU);

	// TODO: add another context menus here
}

BOOL CHWATestApp::SaveAllModified()
{
	if (!CBCGPWinApp::SaveAllModified())
	{
		return FALSE;
	}

	CBCGPMDIFrameWnd* pMainFrame = DYNAMIC_DOWNCAST(CBCGPMDIFrameWnd, m_pMainWnd);
	if (pMainFrame != NULL)
	{
		pMainFrame->SaveMDIState(GetRegSectionPath());
	}

	return TRUE;
}

void InitSeriesColors(BCGPSeriesColors& sc, const CBCGPColor& color, UINT nTextureResID)
{
	CBCGPColor colorGradient = color;
	colorGradient.MakeLighter(.5);

	if (nTextureResID != 0)
	{
		CBCGPColor colorAlt = color;
		colorAlt.MakeLighter(.2);

		sc.m_brElementFillColor.SetTextureImage(CBCGPImage(nTextureResID), colorAlt);
	}
	else
	{
		sc.m_brElementFillColor.SetColors(color, colorGradient, (CBCGPBrush::BCGP_GRADIENT_TYPE)-1);
	}

	CBCGPColor colorOutline = color;
	colorOutline.MakeDarker(.1);

	sc.m_brElementLineColor.SetColor(colorOutline);
	sc.m_brMarkerFillColor.SetColors(color, colorGradient, CBCGPBrush::BCGP_GRADIENT_DIAGONAL_LEFT);
	sc.m_brMarkerFillColor.MakeLighter(.15);

	sc.m_brMarkerLineColor.SetColor(colorOutline);
	sc.m_brDataLabelLineColor.SetColor(colorOutline);

	sc.m_brDataLabelFillColor.SetColor(color);
	sc.m_brDataLabelFillColor.MakePale();

	CBCGPColor colorText = color;
	colorText.MakeDarker(.2);

	sc.m_brDataLabelTextColor.SetColor(colorText);
}
