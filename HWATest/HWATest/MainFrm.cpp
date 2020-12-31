// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "HWATest.h"

#include "ChildFrm.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CBCGPMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPMDIFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_WINDOW_MANAGER, OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_COMMAND(ID_MDI_MOVE_TO_NEXT_GROUP, OnMdiMoveToNextGroup)
	ON_COMMAND(ID_MDI_MOVE_TO_PREV_GROUP, OnMdiMoveToPrevGroup)
	ON_COMMAND(ID_MDI_NEW_HORZ_TAB_GROUP, OnMdiNewHorzTabGroup)
	ON_COMMAND(ID_MDI_NEW_VERT_GROUP, OnMdiNewVertGroup)
	ON_COMMAND(ID_MDI_CANCEL, OnMdiCancel)
	ON_COMMAND(ID_MENU_SHOW_TXT, &CMainFrame::OnMenuShowTxt)
	//////////////////////////////////////////////////////////////////////////
	ON_COMMAND(ID_MENU_PROJ_NEW, &CMainFrame::OnMenuProjNew)
	ON_UPDATE_COMMAND_UI(ID_MENU_PROJ_NEW, &CMainFrame::OnUpdateMenuProjNew)
	ON_COMMAND(ID_MENU_PROJ_OPEN, &CMainFrame::OnMenuProjOpen)
	ON_UPDATE_COMMAND_UI(ID_MENU_PROJ_OPEN, &CMainFrame::OnUpdateMenuProjOpen)
	ON_COMMAND(ID_MENU_PROJ_CLOSE, &CMainFrame::OnMenuProjClose)
	ON_UPDATE_COMMAND_UI(ID_MENU_PROJ_CLOSE, &CMainFrame::OnUpdateMenuProjClose)
	ON_COMMAND(ID_MENU_SHOW_ALM, &CMainFrame::OnMenuShowAlm)
	ON_COMMAND(ID_MENU_SHOW_EPH, &CMainFrame::OnMenuShowEph)
	ON_COMMAND(ID_MENU_SHOW_ION, &CMainFrame::OnMenuShowIon)
	ON_COMMAND(ID_MENU_SHOW_JAL, &CMainFrame::OnMenuShowJal)
	ON_COMMAND(ID_MENU_SHOW_POS, &CMainFrame::OnMenuShowPos)
	ON_COMMAND(ID_MENU_SHOW_RAN, &CMainFrame::OnMenuShowRan)
	ON_COMMAND(ID_MENU_SHOW_TIM, &CMainFrame::OnMenuShowTim)
	ON_COMMAND(ID_MENU_LINE_POS, &CMainFrame::OnMenuLinePos)
	ON_COMMAND(ID_MENU_LINE_RAN, &CMainFrame::OnMenuLineRan)
	ON_COMMAND(ID_MENU_SETUP_CHA, &CMainFrame::OnMenuSetup)
	ON_COMMAND(ID_MENU_DEV_CONNECT, &CMainFrame::OnMenuDevConnect)
	ON_COMMAND(ID_MENU_DEV_DISCONNECT, &CMainFrame::OnMenuDevDisconnect)
	ON_COMMAND(ID_MENU_DEV_INITIAL, &CMainFrame::OnMenuDevInitial)
	ON_COMMAND(ID_MENU_DEV_FACTORY, &CMainFrame::OnMenuDevFactory)
	ON_COMMAND(ID_MENU_POSMOD_HOST, &CMainFrame::OnMenuPosmodHost)
	ON_COMMAND(ID_MENU_POSMOD_CONSOLE, &CMainFrame::OnMenuPosmodConsole)
	ON_COMMAND(ID_MENU_PLAY_START, &CMainFrame::OnMenuPlayStart)
	ON_UPDATE_COMMAND_UI(ID_MENU_PLAY_START, &CMainFrame::OnUpdateMenuPlayStart)
	ON_COMMAND(ID_MENU_PLAY_PAUSE, &CMainFrame::OnMenuPlayPause)
	ON_UPDATE_COMMAND_UI(ID_MENU_PLAY_PAUSE, &CMainFrame::OnUpdateMenuPlayPause)
	ON_COMMAND(ID_MENU_PLAY_STOP, &CMainFrame::OnMenuPlayStop)
	ON_UPDATE_COMMAND_UI(ID_MENU_PLAY_STOP, &CMainFrame::OnUpdateMenuPlayStop)
	ON_COMMAND(ID_MENU_PLAY_FORWARD, &CMainFrame::OnMenuPlayForward)
	ON_UPDATE_COMMAND_UI(ID_MENU_PLAY_FORWARD, &CMainFrame::OnUpdateMenuPlayForward)
	ON_COMMAND(ID_MENU_PLAY_SLIDER, &CMainFrame::OnMenuPlaySlider)
	ON_UPDATE_COMMAND_UI(ID_MENU_PLAY_SLIDER, &CMainFrame::OnUpdateMenuPlaySlider)
	ON_UPDATE_COMMAND_UI(ID_MENU_POSMOD_HOST, &CMainFrame::OnUpdateMenuPosmodHost)
	ON_UPDATE_COMMAND_UI(ID_MENU_POSMOD_CONSOLE, &CMainFrame::OnUpdateMenuPosmodConsole)
	ON_UPDATE_COMMAND_UI(ID_MENU_DEV_CONNECT, &CMainFrame::OnUpdateMenuDevConnect)
	ON_UPDATE_COMMAND_UI(ID_MENU_DEV_DISCONNECT, &CMainFrame::OnUpdateMenuDevDisconnect)
	ON_COMMAND(ID_MENU_PROJ_PROPERTY, &CMainFrame::OnMenuProjProperty)
	ON_COMMAND(ID_MENU_VIEW_POSMOD, &CMainFrame::OnMenuViewPosmod)
	ON_UPDATE_COMMAND_UI(ID_MENU_VIEW_POSMOD, &CMainFrame::OnUpdateMenuViewPosmod)
	ON_COMMAND(ID_MENU_VIEW_SKY, &CMainFrame::OnMenuViewSky)
	ON_UPDATE_COMMAND_UI(ID_MENU_VIEW_SKY, &CMainFrame::OnUpdateMenuViewSky)
	ON_COMMAND(ID_MENU_VIEW_SNR, &CMainFrame::OnMenuViewSnr)
	ON_UPDATE_COMMAND_UI(ID_MENU_VIEW_SNR, &CMainFrame::OnUpdateMenuViewSnr)
	ON_COMMAND(ID_MENU_SHOW_SIV, &CMainFrame::OnMenuShowSiv)
	ON_COMMAND(ID_MENU_SHOW_GBS, &CMainFrame::OnMenuShowGbs)
	ON_UPDATE_COMMAND_UI(ID_MENU_DEV_INITIAL, &CMainFrame::OnUpdateMenuDevInitial)
	ON_UPDATE_COMMAND_UI(ID_MENU_DEV_FACTORY, &CMainFrame::OnUpdateMenuDevFactory)
	ON_UPDATE_COMMAND_UI(ID_MENU_SETUP_CHA, &CMainFrame::OnUpdateMenuSetup)
	ON_COMMAND(ID_MENU_SHOW_XPV, &CMainFrame::OnMenuShowXpv)

    ON_COMMAND(ID_MENU_SHOW_GGA, &CMainFrame::OnMenuShowGga)
    ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_GGA, &CMainFrame::OnUpdateMenuShowGga)
	//////////////////////////////消息处理////////////////////////////////////////////
	ON_MESSAGE(MSG_ANSWER_INFORMATION_COD, &CMainFrame::OnAnswerInfoCOD)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_EPH, &CMainFrame::OnAnswerInfoEPH)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_ION, &CMainFrame::OnAnswerInfoION)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_ALM, &CMainFrame::OnAnswerInfoALM)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_JAL, &CMainFrame::OnAnswerInfoJAL)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_COM, &CMainFrame::OnAnswerInfoCOM)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_MOD, &CMainFrame::OnAnswerInfoMOD)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_POS, &CMainFrame::OnAnswerInfoPOS)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_RAN, &CMainFrame::OnAnswerInfoRAN)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_REF, &CMainFrame::OnAnswerInfoREF)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_SIV, &CMainFrame::OnAnswerInfoGSV)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_STA, &CMainFrame::OnAnswerInfoSTA)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_TIM, &CMainFrame::OnAnswerInfoTIM)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_XPV, &CMainFrame::OnAnswerInfoXPV)//
	ON_MESSAGE(MSG_ANSWER_INFORMATION_SRC, &CMainFrame::OnAnswerInfoSRC)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_FRAME, &CMainFrame::OnAnswerInfoFrame)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_SNR, &CMainFrame::OnAnswerInfoSNR)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_GBS, &CMainFrame::OnAnswerInfoGBS)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_SIM, &CMainFrame::OnAnswerInfoSIM)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_VER, &CMainFrame::OnAnswerInfoVER)
	ON_MESSAGE(MSG_ANSWER_POSITION_POS, &CMainFrame::OnAnswerCalPositionPOS)
	ON_MESSAGE(MSG_ANSWER_INFORMATION_TEST, &CMainFrame::OnAnswerInfoPAO)	//add by cy 20180714
	ON_MESSAGE(MSG_ANSWER_INFORMATION_CHD, &CMainFrame::OnAnswerInfoCHD)

    //短报文设置
    ON_MESSAGE(MSG_SHOW_CMD_VIEW, &CMainFrame::OnShowCmdInfo)

    ON_MESSAGE(MSG_SHOW_GGA_POS_INFO, &CMainFrame::OnUpdateGGAPOSInfo)
	//////////////////////////////////////////////////////////////////////////
	ON_MESSAGE(MSG_EMULATOR_SETUP_MOD, &CMainFrame::OnEmulatorSetupMOD)
	ON_MESSAGE(MSG_EMULATOR_SETUP_LOG, &CMainFrame::OnEmulatorSetupLOG)
	ON_MESSAGE(MSG_EMULATOR_SETUP_STA, &CMainFrame::OnEmulatorSetupSTA)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_MENU_PLAY_BACKWARD, &CMainFrame::OnMenuPlayBackward)
	ON_UPDATE_COMMAND_UI(ID_MENU_PLAY_BACKWARD, &CMainFrame::OnUpdateMenuPlayBackward)
	ON_COMMAND(ID_MENU_PROJ_SAVE, &CMainFrame::OnMenuProjSave)
	ON_UPDATE_COMMAND_UI(ID_MENU_PROJ_SAVE, &CMainFrame::OnUpdateMenuProjSave)
	ON_UPDATE_COMMAND_UI(ID_MENU_PROJ_PROPERTY, &CMainFrame::OnUpdateMenuProjProperty)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_ALM, &CMainFrame::OnUpdateMenuShowAlm)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_EPH, &CMainFrame::OnUpdateMenuShowEph)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_GBS, &CMainFrame::OnUpdateMenuShowGbs)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_ION, &CMainFrame::OnUpdateMenuShowIon)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_POS, &CMainFrame::OnUpdateMenuShowPos)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_JAL, &CMainFrame::OnUpdateMenuShowJal)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_RAN, &CMainFrame::OnUpdateMenuShowRan)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_SIV, &CMainFrame::OnUpdateMenuShowSiv)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_TIM, &CMainFrame::OnUpdateMenuShowTim)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_TXT, &CMainFrame::OnUpdateMenuShowTxt)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_XPV, &CMainFrame::OnUpdateMenuShowXpv)
	ON_UPDATE_COMMAND_UI(ID_MENU_LINE_POS, &CMainFrame::OnUpdateMenuLinePos)
	ON_UPDATE_COMMAND_UI(ID_MENU_LINE_RAN, &CMainFrame::OnUpdateMenuLineRan)
	ON_COMMAND(ID_MENU_ABOUT_INSTRUCTION, &CMainFrame::OnMenuAboutInstruction)
	ON_COMMAND(ID_MENU_ABOUT_DEV, &CMainFrame::OnMenuAboutDev)
	ON_COMMAND(ID_MENU_SHOW_VEL, &CMainFrame::OnMenuShowVel)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_VEL, &CMainFrame::OnUpdateMenuShowVel)
	ON_COMMAND(ID_MENU_SHOW_CHA, &CMainFrame::OnMenuShowCha)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_CHA, &CMainFrame::OnUpdateMenuShowCha)
	ON_COMMAND(ID_MENU_VIEW_CLOSE, &CMainFrame::OnMenuViewClose)
	ON_UPDATE_COMMAND_UI(ID_MENU_VIEW_CLOSE, &CMainFrame::OnUpdateMenuViewClose)
	ON_COMMAND(ID_MENU_TEST_START, &CMainFrame::OnMenuTestStart)
	ON_UPDATE_COMMAND_UI(ID_MENU_TEST_START, &CMainFrame::OnUpdateMenuTestStart)
	ON_COMMAND(ID_MENU_TEST_STOP, &CMainFrame::OnMenuTestStop)
	ON_UPDATE_COMMAND_UI(ID_MENU_TEST_STOP, &CMainFrame::OnUpdateMenuTestStop)
	ON_COMMAND(ID_MENU_CLEAR_ALL, &CMainFrame::OnMenuClearAll)
	ON_UPDATE_COMMAND_UI(ID_MENU_CLEAR_ALL, &CMainFrame::OnUpdateMenuClearAll)
	ON_COMMAND(ID_MENU_SHOW_TEST, &CMainFrame::OnMenuShowTest)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_TEST, &CMainFrame::OnUpdateMenuShowTest)
	ON_COMMAND(ID_MENU_SHOW_CHD, &CMainFrame::OnMenuShowChd)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_CHD, &CMainFrame::OnUpdateMenuShowChd)
    ON_COMMAND(ID_MENU_EPQ, &CMainFrame::OnMenuEpq)
    ON_COMMAND(ID_SEND_TCQ, &CMainFrame::OnSendTcq)
    ON_COMMAND(ID_Menu_QRQ, &CMainFrame::OnMenuQrq)
    ON_COMMAND(ID_MENU_SHOW_CMD, &CMainFrame::OnMenuShowCmd)

    ON_COMMAND(ID_MENU_VIEW_GPS_SNR, &CMainFrame::OnMenuViewGpsSnr)
    ON_UPDATE_COMMAND_UI(ID_MENU_VIEW_GPS_SNR, &CMainFrame::OnUpdateMenuViewGpsSnr)
    ON_COMMAND(ID_MENU_VIEW_GL_SNR, &CMainFrame::OnMenuViewGlSnr)
    ON_UPDATE_COMMAND_UI(ID_MENU_VIEW_GL_SNR, &CMainFrame::OnUpdateMenuViewGlSnr)
    ON_COMMAND(ID_MENU_VIEW_GA_SNR, &CMainFrame::OnMenuViewGaSnr)
    ON_UPDATE_COMMAND_UI(ID_MENU_VIEW_GA_SNR, &CMainFrame::OnUpdateMenuViewGaSnr)
    ON_COMMAND(ID_MENU_SEND_CMD, &CMainFrame::OnMenuSendCmd)
    ON_UPDATE_COMMAND_UI(ID_MENU_SEND_CMD, &CMainFrame::OnUpdateMenuSendCmd)
    END_MESSAGE_MAP()

static UINT indicators[] =
{
	IDS_STATUS_NAME,           // status line indicator
	IDS_STATUS_PRJT,
	IDS_STATUS_TIM,
	IDS_STATUS_MOD,
	IDS_STATUS_CONNECT,
	IDS_STATUS_VERSION,
	IDS_STATUS_CPU,
	IDS_STATUS_SOFT,
	IDS_STATUS_CLOCK,
	IDS_STATUS_PPS
};

static SPlaySpeedBar PlayStep[] = 
{
	1000,
	500,
	250,
	200,
	100,
	50,
	20,
	10
};
const int StepSize = sizeof(PlayStep)/sizeof(SPlaySpeedBar);
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
: m_bPosMode(true)
, m_bPlayStart(false)
, m_bPlayPause(false)
, m_nInterval(1)
, m_nPlayStatus(2)
{
	// TODO: add member initialization code here 
	m_nglobalWeek = 0;
	m_nglobalTow = 0;
	m_bTestMode = false;
	m_nCurLeap = 15;
	m_bAllVisible = true;
	m_bCustomTooltipText = false;
	m_nProjStatus = 0;
	m_arPackSRC.clear();
	m_arrayViews.RemoveAll();
	m_dPosTimeCount = 0;
	for (int i=0; i<MAX_VIEWS; i++)
	{
		m_arrayViews.Add(NULL);
	}

	InitializeCriticalSection(&m_Lock);
	InitializeCriticalSection(&m_csPlayer);
	InitializeCriticalSection(&m_csSaveFile);
}

CMainFrame::~CMainFrame()
{
	m_bPosMode = false;
	m_bPlayStart = false;
	m_bPlayPause = false;
	m_nProjStatus = 0;
	m_bTestMode = false;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CString strText;
	char buf[MAX_PATH];
	ZeroMemory(buf, sizeof(MAX_PATH));
	if (CBCGPMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CBCGPToolBar::EnableQuickCustomization ();

	/*CBCGPMDITabParams mdiTabParams;
	mdiTabParams.m_bFlatFrame = FALSE;
	mdiTabParams.m_bEnableTabSwap = FALSE;
	mdiTabParams.m_nTabBorderSize = 4;
	mdiTabParams.m_bAutoColor = TRUE;
	mdiTabParams.m_bTabIcons = TRUE;
	mdiTabParams.m_bDocumentMenu = TRUE;
	mdiTabParams.m_style = CBCGPTabWnd::STYLE_3D_VS2005;
	mdiTabParams.m_closeButtonMode = CBCGPTabWnd::TAB_CLOSE_BUTTON_NONE;
	EnableMDITabbedGroups (TRUE, mdiTabParams);*/
	EnableMDITabs(TRUE, TRUE, CBCGPTabWnd::LOCATION_TOP, TRUE, CBCGPTabWnd::STYLE_3D_ONENOTE);
	GetMDITabs().EnableAutoColor (TRUE);
	GetMDITabs().EnableTabDocumentsMenu (FALSE);
	GetMDITabs().EnableTabSwap (FALSE);
	GetMDITabs().SetTabBorderSize (2);
	GetMDITabs().SetFlatFrame (FALSE);
	GetMDITabs().EnableCustomToolTips (TRUE);
	GetMDITabs().SetTabCloseButtonMode(CBCGPTabWnd::TAB_CLOSE_BUTTON_ACTIVE);
	GetMDITabs().SetCaptionFont(FALSE);
	//CBCGPPopupMenu::SetForceMenuFocus (FALSE);

	const UINT uiLoadImageFlags = LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS;
	if (m_bmpRed.GetSafeHandle () == NULL)
	{
		HBITMAP hbmp = (HBITMAP) ::LoadImage (
			AfxGetResourceHandle (),
			MAKEINTRESOURCE(IDB_BITMAP_RED),
			IMAGE_BITMAP,
			10, 10,
			uiLoadImageFlags);
		m_bmpRed.Attach (hbmp);
	}
	if (m_bmpGreen.GetSafeHandle () == NULL)
	{
		HBITMAP hbmp = (HBITMAP) ::LoadImage (
			AfxGetResourceHandle (),
			MAKEINTRESOURCE(IDB_BITMAP_GREEN),
			IMAGE_BITMAP,
			10, 10,
			uiLoadImageFlags);
		m_bmpGreen.Attach (hbmp);
	}
	// Menu will not take the focus on activation:
	CBCGPPopupMenu::SetForceMenuFocus (FALSE);

	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP;
	if (!m_wndMenuBar.Create (this, dwStyle))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	// Detect color depth. 256 color toolbars can be used in the
	dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, dwStyle))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.LoadToolBar(IDR_USER_TOOLBAR, 0, 0, TRUE, 0, 0, IDB_BITMAP_BAR);

	GetPrivateProfileString("Product", "Version", "0", buf, MAX_PATH, theApp.m_strConfigPath);
	strText = "V1.0";//CString(buf);
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	m_wndStatusBar.SetPaneInfo(0, IDS_STATUS_NAME, SBPS_OWNERDRAW, 60);
	m_wndStatusBar.SetPaneInfo(1, IDS_STATUS_PRJT, SBPS_OWNERDRAW, 200);
	m_wndStatusBar.SetPaneInfo(2, IDS_STATUS_TIM, SBPS_OWNERDRAW, 240);
	m_wndStatusBar.SetPaneInfo(3, IDS_STATUS_MOD, SBPS_OWNERDRAW, 150);
	m_wndStatusBar.SetPaneInfo(4, IDS_STATUS_CONNECT, SBPS_STRETCH | SBPS_OWNERDRAW, 150);
	m_wndStatusBar.SetPaneInfo(5, IDS_STATUS_VERSION, SBPS_STRETCH | SBPS_OWNERDRAW, 100);
	m_wndStatusBar.SetPaneInfo(6, IDS_STATUS_CPU, SBPS_STRETCH | SBPS_OWNERDRAW, 45);
	m_wndStatusBar.SetPaneInfo(7, IDS_STATUS_SOFT, SBPS_STRETCH | SBPS_OWNERDRAW, 45);
	m_wndStatusBar.SetPaneInfo(8, IDS_STATUS_CLOCK, SBPS_STRETCH | SBPS_OWNERDRAW, 45);
	m_wndStatusBar.SetPaneInfo(9, IDS_STATUS_PPS, SBPS_STRETCH | SBPS_OWNERDRAW, 45);
	m_wndStatusBar.SetPaneIcon(4, m_bmpRed);
	m_wndStatusBar.SetPaneIcon(5, m_bmpRed);
	m_wndStatusBar.SetPaneIcon(6, m_bmpRed);
	m_wndStatusBar.SetPaneIcon(7, m_bmpRed);
	m_wndStatusBar.SetPaneIcon(8, m_bmpRed);
	m_wndStatusBar.SetPaneIcon(9, m_bmpRed);
	m_wndStatusBar.SetPaneText(0, strText);

    //m_wndStatusBar.SetPaneTextColor(0, RGB(255, 255, 255));
    //m_wndStatusBar.SetPaneTextColor(2, RGB(255, 255, 255));

	// Load control bar icons:
	CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize (CSize (16, 16));
	imagesWorkspace.SetTransparentColor (RGB (255, 0, 255));
	imagesWorkspace.Load (IDB_WORKSPACE);
	imagesWorkspace.SmoothResize(globalData.GetRibbonImageScale());

	//if (!m_wndWorkSpace.Create (_T("上位机定位模式"), this, CRect (0, 0, 200, 200), TRUE, ID_VIEW_WORKSPACE, 
	//	WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	//{
	//	TRACE0("Failed to create Workspace bar\n");
	//	return -1;      // fail to create
	//}
	//m_wndWorkSpace.SetIcon (imagesWorkspace.ExtractIcon (0), FALSE);

	//星空图
	//if (!m_wndSkyView.Create (_T("星空图"), this, CSize (300, 150),
	//	TRUE, IDD_SHOW_VIEW_SKY, 
 //       //WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_SIZE_DYNAMIC))
 //       WS_CHILD | WS_VISIBLE | CBRS_SIZE_DYNAMIC | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	//{
	//	TRACE0("Failed to create output bar\n");
	//	return -1;      // fail to create
	//}
	//m_wndSkyView.SetIcon (imagesWorkspace.ExtractIcon (2), FALSE);


	//信号强度
	//if (!m_wndSnrView.Create (_T("BD信号强度"), this, CSize (300, 150), TRUE, 
	//	IDD_SHOW_VIEW_SNR,
 //       //WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_SIZE_DYNAMIC | WS_CAPTION))//| CBRS_GRIPPER))
 //       WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
 //       //WS_CHILD | WS_VISIBLE| WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI | WS_CAPTION| CBRS_HIDE_INPLACE))
	//{
	//	TRACE0("Failed to create output bar\n");
	//	return -1;      // fail to create 
	//}
	//m_wndSnrView.SetIcon (imagesWorkspace.ExtractIcon (2), FALSE);

 //   if (!m_wndGPSnrView.Create (_T("GPS信号强度"), this, CSize (300, 150), TRUE, 
	//	IDD_SHOW_VIEW_GPS_SNR,
 //       //WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_SIZE_DYNAMIC | WS_CAPTION))//| CBRS_GRIPPER))
 //       WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
 //       //WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI | WS_CAPTION | CBRS_HIDE_INPLACE))
	//{
	//	TRACE0("Failed to create output bar\n");
	//	return -1;      // fail to create 
	//}
	//m_wndGPSnrView.SetIcon (imagesWorkspace.ExtractIcon (2), FALSE);

 //   if (!m_wndGASnrView.Create (_T("GA信号强度"), this, CSize (300, 150), TRUE, 
	//	IDD_SHOW_VIEW_GA_SNR,
 //       //WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_SIZE_DYNAMIC | WS_CAPTION))//| CBRS_GRIPPER))
 //       WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
 //       //WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI | WS_CAPTION | CBRS_HIDE_INPLACE))
	//{
	//	TRACE0("Failed to create output bar\n");
	//	return -1;      // fail to create 
	//}
	//m_wndGASnrView.SetIcon (imagesWorkspace.ExtractIcon (2), FALSE);

 //   if (!m_wndGLSnrView.Create (_T("GL信号强度"), this, CSize (300, 150), TRUE, 
	//	IDD_SHOW_VIEW_GL_SNR,
 //       //WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_SIZE_DYNAMIC | WS_CAPTION))//| CBRS_GRIPPER))
 //       WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
 //       //WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI | WS_CAPTION | CBRS_HIDE_INPLACE))
	//{
	//	TRACE0("Failed to create output bar\n");
	//	return -1;      // fail to create 
	//}
	//m_wndGLSnrView.SetIcon (imagesWorkspace.ExtractIcon (2), FALSE);


    if (!m_wndOutputView.Create (_T("命令"), this, CRect (0, 0, 100, 100),
		TRUE, 
		ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create output bar\n");
		return FALSE;      // fail to create
	}

	//m_wndWorkSpace.EnableDocking(CBRS_ALIGN_ANY);
	//m_wndMenuBar.EnableDocking(CBRS_ALIGN_TOP);
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
    EnableAutoHideBars(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndSkyView);
	DockControlBar(&m_wndSnrView);
    DockControlBar(&m_wndGPSnrView);
    DockControlBar(&m_wndGASnrView);
    DockControlBar(&m_wndGLSnrView);
	m_wndSnrView.DockToWindow (&m_wndSkyView, CBRS_ALIGN_BOTTOM);
    //m_wndGPSnrView.DockToWindow (&m_wndSnrView, CBRS_ALIGN_LEFT);//CBRS_ALIGN_BOTTOM//CBRS_ALIGN_RIGHT

	m_wndSkyView.EnableDocking(CBRS_ALIGN_ANY);
    m_wndSnrView.EnableDocking(CBRS_ALIGN_ANY);
    m_wndGPSnrView.EnableDocking(CBRS_ALIGN_ANY);

	CBCGPDockingControlBar* pTabbedBar = NULL;
    //m_wndSnrView.AttachToTabWnd (&m_wndSkyView, BCGP_DM_SHOW, TRUE, &pTabbedBar);//type2
	//m_wndGPSnrView.AttachToTabWnd (pTabbedBar, BCGP_DM_SHOW, TRUE, &pTabbedBar);
    m_wndGPSnrView.AttachToTabWnd (&m_wndSnrView, BCGP_DM_SHOW, TRUE, &pTabbedBar);
    m_wndGASnrView.AttachToTabWnd (pTabbedBar, BCGP_DM_SHOW, TRUE, &pTabbedBar);
    m_wndGLSnrView.AttachToTabWnd (pTabbedBar, BCGP_DM_SHOW, TRUE, &pTabbedBar);

	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBar);
	//DockControlBar(&m_wndWorkSpace);

    DockControlBar(&m_wndOutputView);
    m_wndOutputView.EnableDocking(CBRS_ALIGN_ANY);

	//if (!m_wndCaptionBar.Create (WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | CBRS_TOP, this, ID_VIEW_CAPTIONBAR, -1))
	//{
	//	TRACE0("Failed to create caption bar\n");
	//	return -1;      // fail to create
	//}
	//m_wndCaptionBar.SetFlatBorder();

	// Enable windows manager:
	EnableWindowsDialog (ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE);
	//CBCGPDockManager::SetDockMode (BCGP_DT_SMART);

	//添加监听者对象
	CWinGlobal::SetMainWndHandle(this->m_hWnd);
	m_Listener.Add((CBasicListener*)&theApp.m_winCalPosApp);
	m_PrintListener.Add((CBasicListener*)&theApp.m_winPrintApp);//m_winLinkApp//
	theApp.m_winCalPosApp.GetListener()->Add(this->m_hWnd);
	//theApp.m_winPlayerApp.GetListener()->Add(this->m_hWnd);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CBCGPMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers


void CMainFrame::OnViewCustomize()
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
}

afx_msg LRESULT CMainFrame::OnToolbarReset(WPARAM wp,LPARAM lp)
{
	// TODO: reset toolbar with id = (UINT) wp to its initial state:
	//
	 UINT uiToolBarId = (UINT) wp;
	 if (uiToolBarId == IDR_USER_TOOLBAR)
	 {
		 m_btnSlider.m_nID = ID_MENU_PLAY_SLIDER;
		 //CBCGPSliderButton btnSlider(ID_MENU_PLAY_SLIDER);
		 m_btnSlider.SetRange (0, 100);
		 m_wndToolBar.ReplaceButton(ID_MENU_PLAY_SLIDER, m_btnSlider);
		 m_btnSlider.SetValue(0);
	 }

	return 0;
}

void CMainFrame::OnWindowManager() 
{
	ShowWindowsDialog ();
}

BOOL CMainFrame::OnShowMDITabContextMenu (CPoint point, DWORD dwAllowedItems, BOOL bDrop)
{
	/*
	CMenu menu;
	VERIFY(menu.LoadMenu (bDrop ? IDR_POPUP_DROP_MDITABS : IDR_POPUP_MDITABS));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	if ((dwAllowedItems & BCGP_MDI_CREATE_HORZ_GROUP) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_NEW_HORZ_TAB_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CREATE_VERT_GROUP) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_NEW_VERT_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_MOVE_NEXT) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_MOVE_TO_NEXT_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_MOVE_PREV) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_MOVE_TO_PREV_GROUP, MF_BYCOMMAND);
	}
	//取消文档右键菜单(save and close)
	CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	pPopupMenu->SetAutoDestroy (FALSE);
	pPopupMenu->Create (this, point.x, point.y, pPopup->GetSafeHmenu ());
*/
	return TRUE;
}

void CMainFrame::OnMdiMoveToNextGroup() 
{
	//MDITabMoveToNextGroup ();
}

void CMainFrame::OnMdiMoveToPrevGroup() 
{
	//MDITabMoveToNextGroup (FALSE);
}

void CMainFrame::OnMdiNewHorzTabGroup() 
{
	//MDITabNewGroup (FALSE);
}

void CMainFrame::OnMdiNewVertGroup() 
{
	//MDITabNewGroup ();
}

void CMainFrame::OnMdiCancel() 
{
	// TODO: Add your command handler code here
	
}

CBCGPMDIChildWnd* CMainFrame::CreateDocumentWindow (LPCTSTR lpcszDocName, CObject* /*pObj*/)
{
	if (lpcszDocName != NULL && lpcszDocName [0] != '\0')
	{
		CDocument* pDoc = AfxGetApp()->OpenDocumentFile (lpcszDocName);

		if (pDoc != NULL)
		{
			POSITION pos = pDoc->GetFirstViewPosition();

			if (pos != NULL)
			{
				CView* pView = pDoc->GetNextView (pos);
				if (pView == NULL)
				{
					return NULL;
				}

				return DYNAMIC_DOWNCAST (CBCGPMDIChildWnd, pView->GetParent ());
			}   
		}
	}

	return NULL;
}

void CMainFrame::OnClose() 
{
	if (BCGPMessageBox("请确认是否要退出应用程序？", MB_OKCANCEL) == IDOK)
	{
		OnMenuProjClose();
		WritePrivateProfileString("POSMOD", "Tester", "0", "config.ini");
		SaveMDIState (theApp.GetRegSectionPath ());
		CBCGPMDIFrameWnd::OnClose();
	}
}

BOOL CMainFrame::OnEraseMDIClientBackground(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	ASSERT_VALID (pDC);

	CRect rect;
	m_wndClientArea.GetClientRect (rect);

	CBCGPDrawManager dm(*pDC);
	dm.FillGradient2 (rect, RGB(227,239,255), RGB(177,211,255), 45);

	pDC->SelectObject (&m_GnssfontNormal25);
	pDC->SetBkMode (TRANSPARENT);
	CString strText = _T("北斗多频试验验证终端测试系统");
	CSize sizeText = pDC->GetTextExtent (strText);
	CPoint ptText (rect.right/2 - sizeText.cx/2, rect.bottom/2 - sizeText.cy - 10);
	pDC->SetTextColor (RGB (0, 45, 85));
	pDC->TextOut (ptText.x, ptText.y, strText);
	ptText.x -= 2;
	ptText.y -= 2;
	pDC->SetTextColor (RGB (255, 255, 255));
	pDC->TextOut (ptText.x, ptText.y, strText);

	pDC->SelectObject (&m_GnssfontBold);
	pDC->SetBkMode (TRANSPARENT);
	strText = _T("");//北京华力创通科技股份有限公司技术研究中心
	sizeText = pDC->GetTextExtent (strText);
	CPoint ptTxt (rect.right - sizeText.cx - 10, rect.bottom - sizeText.cy - 10);
	pDC->SetTextColor (RGB (0, 45, 85));
	pDC->TextOut (ptTxt.x, ptTxt.y, strText);
	ptTxt.x -= 2;
	ptTxt.y -= 2;
	pDC->SetTextColor (RGB (255, 255, 255));
	pDC->TextOut (ptTxt.x, ptTxt.y, strText);

	return TRUE;
}

void CMainFrame::OnSizeMDIClient (const CRect& rectOld, const CRect& rectNew)
{
	m_wndClientArea.RedrawWindow ();
}

BOOL CMainFrame::OnMenuButtonToolHitTest (CBCGPToolbarButton* pButton, TOOLINFO* pTI)
{
	ASSERT_VALID (pButton);
	ASSERT (pTI != NULL);

	if (pButton->m_nID == 0 || 
		pButton->m_nID == (UINT)-1)
	{
		return FALSE;
	}

	CString strText = pButton->m_strTextCustom;
	strText.Remove (_T('&'));

	if (m_bCustomTooltipText)
	{
		strText = _T("提示信息:");
	}

	if (strText.IsEmpty ())
	{
		return FALSE;
	}

	pTI->lpszText = (LPTSTR) ::calloc ((strText.GetLength () + 1), sizeof (TCHAR));
	lstrcpy (pTI->lpszText, strText);

	return TRUE;
}

BOOL CMainFrame::GetToolbarButtonToolTipText (CBCGPToolbarButton* pButton, CString& strTTText)
{
	ASSERT_VALID (pButton);

	if (pButton->m_nID == 0 || 
		pButton->m_nID == (UINT)-1)
	{
		return FALSE;
	}

	strTTText = _T("功能:");

	return TRUE;
}

 // UI_TYPE_RIBBON
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	//m_wndHwaView.SubclassWindow(m_wndHwaView.m_hWnd);
	double x=0,y=0,z=0;
	m_wndSaveFile.Create(IDD_SET_FILE_DIALOG, this);
	m_wndSaveFile.CenterWindow();
	m_wndSetSystem.Create(IDD_SET_SYSTEM_DIALOG, this);
	m_wndSetSystem.CenterWindow();
	m_wndCheckDlg.Create(IDD_ABOUT_DIALOG, this);
	m_wndCheckDlg.CenterWindow();
	/*m_wndProperty.Create(IDD_PROJPROPERTY, this);
	m_wndProperty.CenterWindow();*/
	//SetTimer(2, 2000, NULL);


    CBCGPToolBarImages imagesWorkspace;
	imagesWorkspace.SetImageSize (CSize (16, 16));
	imagesWorkspace.SetTransparentColor (RGB (255, 0, 255));
	imagesWorkspace.Load (IDB_WORKSPACE);
	imagesWorkspace.SmoothResize(globalData.GetRibbonImageScale());

	if (!m_wndSkyView.Create (_T("星空图"), this, CSize (300, 150),
		TRUE, IDD_SHOW_VIEW_SKY, 
        //WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_SIZE_DYNAMIC))
        WS_CHILD | WS_VISIBLE | CBRS_SIZE_DYNAMIC | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create
	}
	m_wndSkyView.SetIcon (imagesWorkspace.ExtractIcon (2), FALSE);
    m_wndSkyView.SetContext(pContext);


    if (!m_wndSnrView.Create (_T("BD信号强度"), this, CSize (300, 150), TRUE, 
		IDD_SHOW_VIEW_SNR,
        //WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_SIZE_DYNAMIC | WS_CAPTION))//| CBRS_GRIPPER))
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
        //WS_CHILD | WS_VISIBLE| WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI | WS_CAPTION| CBRS_HIDE_INPLACE))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create 
	}
    m_wndSnrView.SetIcon (imagesWorkspace.ExtractIcon (2), FALSE);
    m_wndSnrView.SetContext(pContext);

    if (!m_wndGPSnrView.Create (_T("GPS信号强度"), this, CSize (300, 150), TRUE, 
		IDD_SHOW_VIEW_GPS_SNR,
        //WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_SIZE_DYNAMIC | WS_CAPTION))//| CBRS_GRIPPER))
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
        //WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI | WS_CAPTION | CBRS_HIDE_INPLACE))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create 
	}
	m_wndGPSnrView.SetIcon (imagesWorkspace.ExtractIcon (2), FALSE);
    m_wndGPSnrView.SetContext(pContext);

    if (!m_wndGASnrView.Create (_T("GA信号强度"), this, CSize (300, 150), TRUE, 
		IDD_SHOW_VIEW_GA_SNR,
        //WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_SIZE_DYNAMIC | WS_CAPTION))//| CBRS_GRIPPER))
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
        //WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI | WS_CAPTION | CBRS_HIDE_INPLACE))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create 
	}
	m_wndGASnrView.SetIcon (imagesWorkspace.ExtractIcon (2), FALSE);
    m_wndGASnrView.SetContext(pContext);

    if (!m_wndGLSnrView.Create (_T("GL信号强度"), this, CSize (300, 150), TRUE, 
		IDD_SHOW_VIEW_GL_SNR,
        //WS_CHILD | WS_VISIBLE | CBRS_RIGHT | CBRS_SIZE_DYNAMIC | WS_CAPTION))//| CBRS_GRIPPER))
        WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
        //WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI | WS_CAPTION | CBRS_HIDE_INPLACE))
	{
		TRACE0("Failed to create output bar\n");
		return -1;      // fail to create 
	}
	m_wndGLSnrView.SetIcon (imagesWorkspace.ExtractIcon (2), FALSE);
    m_wndGLSnrView.SetContext(pContext);


	return CBCGPMDIFrameWnd::OnCreateClient(lpcs, pContext);
}
void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CBCGPMDIFrameWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndClientArea.RedrawWindow ();
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	int pos = 0;
	CString strText;
	if (nIDEvent == 1)//定时器，控制文件读取速度
	{
		if (m_nProjStatus == 2)
		{
			EnterCriticalSection(&m_csPlayer);
			if(theApp.m_winPlayerApp.GetPauseStatus() && theApp.m_winPlayerApp.GetPlayStatus())//当文件播放线程开启后，并且处于暂停状态时，才可执行
				theApp.m_winPlayerApp.startPlay();
			LeaveCriticalSection(&m_csPlayer);
			pos = theApp.m_winPlayerApp.GetPos();
			if(pos > m_btnSlider.GetPos(ID_MENU_PLAY_SLIDER))
				m_btnSlider.SetValue(pos);
			if(pos == 100)
			{
				m_bPlayStart = false;
				m_btnSlider.SetValue(0);
				/*theApp.m_winPlayerApp.stopPlay();
				KillTimer(1);*/
				OnMenuPlayStop();
			}
		}
	}
	else if (nIDEvent == 2)
	{

	}
	CBCGPMDIFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::SelectView(int nID)
{
    TRACE("SelectView %d\n", nID);
	switch (nID)
	{
	case IDD_SHOW_VIEW_SRC:
		SwitchToView(nID, theApp.m_pSrcTemplate, RUNTIME_CLASS(CShowSrcView));
		break;
	case IDD_SHOW_VIEW_ALM:
		SwitchToView(nID, theApp.m_pAlmTemplate, RUNTIME_CLASS(CShowAlmView));
		break;
	case IDD_SHOW_VIEW_EPH:
		SwitchToView(nID, theApp.m_pEphTemplate, RUNTIME_CLASS(CShowEphView));
		break;
	case IDD_SHOW_VIEW_ION:
		SwitchToView(nID, theApp.m_pIonTemplate, RUNTIME_CLASS(CShowIonView));
		break;
	case IDD_SHOW_VIEW_JAL:
		SwitchToView(nID, theApp.m_pJalTemplate, RUNTIME_CLASS(CShowJalView));
		break;
	case IDD_SHOW_VIEW_POS:
		SwitchToView(nID, theApp.m_pPosTemplate, RUNTIME_CLASS(CShowPosView));
		break;
	case IDD_SHOW_VIEW_RAN:
		SwitchToView(nID, theApp.m_pRanTemplate, RUNTIME_CLASS(CShowRanView));
		break;
	case IDD_SHOW_VIEW_TIM:
		SwitchToView(nID, theApp.m_pTimTemplate, RUNTIME_CLASS(CShowTimView));
		break;
	case IDD_SHOW_VIEW_SIV:
		SwitchToView(nID, theApp.m_pSivTemplate, RUNTIME_CLASS(CShowSivView));
		break;
	case IDD_DRAW_VIEW_POS:
		SwitchToView(nID, theApp.m_pDrawPosTemplate, RUNTIME_CLASS(CDrawPosView));
		break;
	case IDD_DRAW_VIEW_RAN:
		SwitchToView(nID, theApp.m_pDrawRanTemplate, RUNTIME_CLASS(CDrawRanView));
		break;
	case IDD_SHOW_VIEW_GBS:
		SwitchToView(nID, theApp.m_pGbsTemplate, RUNTIME_CLASS(CShowGbsView));
		break;
	case IDD_SHOW_VIEW_XPV:
		SwitchToView(nID, theApp.m_pXpvTemplate, RUNTIME_CLASS(CShowXpvView));
		break;
	case IDD_SHOW_VIEW_VEL:
		SwitchToView(nID, theApp.m_pVelTemplate, RUNTIME_CLASS(CShowVelView));
		break;
	case IDD_SHOW_VIEW_CHA:
		SwitchToView(nID, theApp.m_pChaTemplate, RUNTIME_CLASS(CShowChaView));
		break;

    case IDD_SHOW_VIEW_GGA_POS:
        SwitchToView(nID, theApp.m_pGgaPosTemplate, RUNTIME_CLASS(CShowGgaPosView));
        break;

	case IDD_SHOW_VIEW_TEST:
		SwitchToView(nID, theApp.m_pPAOrderTemplate, RUNTIME_CLASS(CDrawPAOrderView));
		break;
	case IDD_SHOW_VIEW_CHD:
		SwitchToView(nID, theApp.m_pChDecodeTemplate, RUNTIME_CLASS(ChDecodeView));
		break;	


	default:
		break;
	}
}

void CMainFrame::SwitchToView(int nID, CDocTemplate * pTemplate, CRuntimeClass * pViewClass)
{
	CView *pView = NULL;
	CDocument *pDoc = NULL;
	int index = nID - IDD_USER_BASE;
	CMDIChildWnd *pMDIActive = MDIGetActive();//获得活动子窗口
	if (pMDIActive == NULL)
	{
		pDoc = new CHWATestDoc;
	}
	else
	{
		pDoc = pMDIActive->GetActiveDocument();//获得活动doc 
	}
	if (pDoc == NULL)
		return;

	POSITION pos = pDoc->GetFirstViewPosition();//查询此doc下的所有已创建view
	while (pos != NULL)
	{
		pView = pDoc->GetNextView(pos);
		if (pView->IsKindOf(pViewClass))//如果已创建此view 则设其为活动
		{
			pView->GetParentFrame()->ActivateFrame();//视图激活
			return;
		}
	}
	//如果没有创建，则创建此view的childframe及view
	CMDIChildWnd *pNewFrame = (CMDIChildWnd *)(pTemplate->CreateNewFrame(pDoc, NULL));
	if (pNewFrame == NULL)
		return;
	ASSERT_KINDOF(CMDIChildWnd, pNewFrame);
	pTemplate->InitialUpdateFrame(pNewFrame, pDoc);

	//将已经创建好的view保存到m_arrayViews
	pos = pDoc->GetFirstViewPosition();//查询此doc下的所有已创建view
	while (pos != NULL)
	{
		pView = pDoc->GetNextView(pos);
		if (pView->IsKindOf(pViewClass))//如果已创建此view 则设其为活动
		{
			EnterCriticalSection(&m_Lock);
			m_arrayViews.SetAt(index, pView);
			LeaveCriticalSection(&m_Lock);
		}
	}
}
void CMainFrame::CloseAllView()
{
	CView *pView = NULL;
	CDocument *pDoc = NULL;
	m_bAllVisible = false;
	CMDIChildWnd *pMDIActive = MDIGetActive();//获得活动子窗口
	if (pMDIActive == NULL)
	{
		pDoc = new CHWATestDoc;
	}
	else
	{
		pDoc = pMDIActive->GetActiveDocument();//获得活动doc 
	}
	if (pDoc == NULL)
		return;

	POSITION pos = pDoc->GetFirstViewPosition();//查询此doc下的所有已创建view
	while (pos != NULL)
	{
		pView = pDoc->GetNextView(pos); 
		if (pView->IsWindowVisible())//如果已创建此view 则设其为活动
		{
			pView->ShowWindow(SW_HIDE);
			pView->GetParentFrame()->DestroyWindow();
		}
	}
}
/************************************************************************************************/
/////////////////////////////////////////菜单栏///////////////////////////////////////////////////
/************************************************************************************************/
void CMainFrame::OnMenuProjNew()
{
	// TODO: Add your command handler code here 
	CProjNewPage   dlg(_T("新建项目"));
	dlg.SetWizardMode();
	if(dlg.DoModal() == ID_WIZFINISH)
	{
		m_nProjStatus = 1;
		theApp.m_bConnectFlag = OnLinkToDevice();
		if (theApp.m_bConnectFlag)
		{
			m_wndStatusBar.SetPaneIcon(4, m_bmpGreen);
			m_wndStatusBar.SetPaneText(1, "新建项目："+theApp.m_strProjName + ".xproj");
			theApp.m_winPrintApp.LoadConfig(theApp.m_strDatabase, theApp.m_strProjFile);
			theApp.m_winCalPosApp.LoadConfig(theApp.m_strProjFile);
		}
		else
			m_wndStatusBar.SetPaneText(1, "新建项目：创建失败。");
	}
}

void CMainFrame::OnUpdateMenuProjNew(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_nProjStatus);
}

void CMainFrame::OnMenuClearAll()
{
	// TODO: Add your command handler code here
	int i=0,length=0;
	m_wndSkyView.Clear();
	m_wndSnrView.Clear();
    m_wndGPSnrView.Clear();
	theApp.m_winCalPosApp.Clear();

	/*length = m_arrayViews.GetSize();
	for (i=0; i<length; i++)
	{
		CHWATestView* pNewView = DYNAMIC_DOWNCAST(CHWATestView, m_arrayViews[i]);
		if(pNewView != NULL && ::IsWindow(pNewView->m_hWnd))
		{
			if(pNewView->IsWindowVisible())
				pNewView->Clear();
		}
	}*/
}

void CMainFrame::OnUpdateMenuClearAll(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnMenuProjOpen()
{
	// TODO: Add your command handler code here
	char buf[MAX_PATH];
	CProjOpenPage dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_nInterval = 1;
		m_nProjStatus = 2;
		theApp.m_strProjFile = dlg.m_strProjFileName;
		ZeroMemory(buf, sizeof(char)*MAX_PATH);
		GetPrivateProfileString("Product", "ProjPath", "", buf, MAX_PATH, theApp.m_strProjFile);
		theApp.m_strProjPath = CString(buf);
		ZeroMemory(buf, sizeof(char)*MAX_PATH);
		GetPrivateProfileString("Product", "ProjName", "", buf, MAX_PATH, theApp.m_strProjFile);
		theApp.m_strProjName = CString(buf);
		ZeroMemory(buf, sizeof(char)*MAX_PATH);
		GetPrivateProfileString("Product", "ProjData", "", buf, MAX_PATH, theApp.m_strProjFile);
		theApp.m_strDatabase = CString(buf);
		ZeroMemory(buf, sizeof(char)*MAX_PATH);
		GetPrivateProfileString("Product", "ProjOrigin", "", buf, MAX_PATH, theApp.m_strProjFile);
		theApp.m_strOriginData = CString(buf);
		ZeroMemory(buf, sizeof(char)*MAX_PATH);
		GetPrivateProfileString("Product", "ProjImage", "", buf, MAX_PATH, theApp.m_strProjFile);
		theApp.m_strPictures = CString(buf);
		ZeroMemory(buf, sizeof(char)*MAX_PATH);
		GetPrivateProfileString("Product", "ProjType", "0", buf, MAX_PATH, theApp.m_strProjFile);
		theApp.m_nProjectType = atoi(buf);
		ZeroMemory(buf, sizeof(char)*MAX_PATH);
		GetPrivateProfileString("Product", "Protocol", "1", buf, MAX_PATH, theApp.m_strProjFile);
		theApp.m_nProtocol = atoi(buf);
		theApp.m_winPlayerApp.CreatePlayer(theApp.m_nProtocol);
		theApp.m_winPlayerApp.GetListener()->Add(this->m_hWnd);
		theApp.m_winPlayerApp.GetListener()->Add((CBasicListener*)&theApp.m_winPrintApp);//
		theApp.m_winCalPosApp.LoadConfig(theApp.m_strProjFile);
		if(!theApp.m_winPlayerApp.Open(theApp.m_strOriginData))
		{
			OnMenuProjClose();
			BCGPMessageBox("打开项目失败");
			m_wndStatusBar.SetPaneText(1, "打开项目失败");
			return;
		}
		m_wndStatusBar.SetPaneText(1, "打开项目："+theApp.m_strProjName + ".xproj");
	}
}

void CMainFrame::OnUpdateMenuProjOpen(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(!m_nProjStatus);
}

void CMainFrame::OnMenuProjClose()
{
	// TODO: Add your command handler code here 
	int i=0,length=0;
	if (m_nProjStatus == 1)
	{
		theApp.m_winPrintApp.Stop();
		OnDLinkFromDevice();
	} 
	else if (m_nProjStatus == 2)
	{
		theApp.m_winPlayerApp.GetListener()->Remove(this->m_hWnd);
		theApp.m_winPlayerApp.GetListener()->Remove((CBasicListener*)&theApp.m_winPrintApp);
		OnMenuPlayStop();
		theApp.m_winPlayerApp.Close();
	}
	m_nProjStatus = 0;
	theApp.Clear();
	OnMenuClearAll();
	m_wndSaveFile.Reset();
	CloseAllView();
}

void CMainFrame::OnUpdateMenuProjClose(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnMenuProjProperty()
{
	// TODO: Add your command handler code here
	//m_wndProperty.ShowWindow(SW_SHOW);
	CProjPropertyPage dlg;
	dlg.DoModal();
}

void CMainFrame::OnUpdateMenuProjProperty(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnMenuProjSave()
{
	// TODO: Add your command handler code here
	m_wndSaveFile.ShowWindow(SW_SHOW);
	m_wndSaveFile.SetProjectPath(theApp.m_strProjPath);
}

void CMainFrame::OnUpdateMenuProjSave(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus == 1);//m_nProjStatus == 1
}

//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnMenuShowAlm()
{
	// TODO: Add your command handler code here
	SelectView(IDD_SHOW_VIEW_ALM);
}

void CMainFrame::OnMenuShowEph()
{
	// TODO: Add your command handler code here
	SelectView(IDD_SHOW_VIEW_EPH);
}

void CMainFrame::OnMenuShowIon()
{
	// TODO: Add your command handler code here
	SelectView(IDD_SHOW_VIEW_ION);
}

void CMainFrame::OnMenuShowJal()
{
	// TODO: Add your command handler code here
	SelectView(IDD_SHOW_VIEW_JAL);
}

void CMainFrame::OnMenuShowPos()
{
	// TODO: Add your command handler code here
	SelectView(IDD_SHOW_VIEW_POS);
}

void CMainFrame::OnMenuShowXpv()
{
	// TODO: Add your command handler code here
	SelectView(IDD_SHOW_VIEW_XPV);
}

void CMainFrame::OnMenuShowRan()
{
	// TODO: Add your command handler code here
	SelectView(IDD_SHOW_VIEW_RAN);
}

void CMainFrame::OnMenuShowTim()
{
	// TODO: Add your command handler code here
	SelectView(IDD_SHOW_VIEW_TIM);
}

void CMainFrame::OnMenuShowTxt()
{
	// TODO: Add your command handler code here
	SelectView(IDD_SHOW_VIEW_SRC);
}

void CMainFrame::OnMenuShowSiv()
{
	// TODO: Add your command handler code here
	SelectView(IDD_SHOW_VIEW_SIV);
}

void CMainFrame::OnMenuShowGbs()
{
	// TODO: Add your command handler code here
	SelectView(IDD_SHOW_VIEW_GBS);
}

void CMainFrame::OnMenuShowVel()
{
	// TODO: Add your command handler code here
	//SelectView(IDD_SHOW_VIEW_VEL);
}

void CMainFrame::OnMenuShowCha()
{
	// TODO: Add your command handler code here
	SelectView(IDD_SHOW_VIEW_CHA);
}

void CMainFrame::OnUpdateMenuShowCha(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnUpdateMenuShowVel(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnUpdateMenuShowAlm(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnUpdateMenuShowEph(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnUpdateMenuShowGbs(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnUpdateMenuShowIon(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnUpdateMenuShowPos(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnUpdateMenuShowJal(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnUpdateMenuShowRan(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnUpdateMenuShowSiv(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnUpdateMenuShowTim(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnUpdateMenuShowTxt(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnUpdateMenuShowXpv(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}
//////////////////////////////////////////////////////////////////////////

void CMainFrame::OnMenuLinePos()
{
	// TODO: Add your command handler code here
	SelectView(IDD_DRAW_VIEW_POS);
}

void CMainFrame::OnMenuLineRan()
{
	// TODO: Add your command handler code here
	SelectView(IDD_DRAW_VIEW_RAN);
}

void CMainFrame::OnUpdateMenuLinePos(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnUpdateMenuLineRan(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}

///////////////////////////////////////////////
void CMainFrame::OnMenuSetup()
{
	// TODO: Add your command handler code here
	m_wndSetSystem.ShowWindow(SW_SHOW);
}
void CMainFrame::OnUpdateMenuSetup(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(theApp.m_bConnectFlag && m_nProjStatus);// == 1
}

//////////////////////////////////////////////////////////////////////////
bool CMainFrame::OnLinkToDevice()
{
	SETCOM com;
	SETSOCKET skt;
	CWinConfigApp config;
	CString str = "端口：未连接设备。";
	theApp.m_nConnectType = config.GetLinkConfig(&skt, &com, theApp.m_strConfigPath);
	theApp.m_nProtocol = com.protocol;
	if (theApp.m_nConnectType == 0)
	{
		theApp.m_bConnectFlag = theApp.m_winLinkApp.CreateComm(com.com, com.baud, com.protocol);
		if (theApp.m_bConnectFlag)
		{
			str.Format("端口：COM%d, %d, %s", com.com, com.baud, (com.protocol == 1)?"ASCII":(com.protocol == 2 ? "binary" : "BD3"));
			theApp.m_winLinkApp.GetListener()->Add(this->m_hWnd);//
			theApp.m_winLinkApp.GetListener()->Add((CBasicListener*)&theApp.m_winPrintApp);
			//测试代码
			theApp.m_winCalPosApp.LoadConfig(theApp.m_strProjFile);
		}
		else
		{
			BCGPMessageBox("设备连接失败，请重新建立连接！");
		}
	}
	else if (theApp.m_nConnectType == 1)
	{
		theApp.m_bConnectFlag = theApp.m_winLinkApp.CreateSocket(skt.port, skt.dwIP, skt.protocol);
		if (theApp.m_bConnectFlag)
		{
			str.Format("端口：%d.%d.%d.%d, %d, %s", (skt.dwIP>>24)&0xFF, (skt.dwIP>>16)&0xFF, (skt.dwIP>>8)&0xFF, skt.dwIP&0xFF, skt.port, (skt.protocol == 1)?"ASCII":"binary");
			theApp.m_winLinkApp.GetListener()->Add(this->m_hWnd);
			theApp.m_winLinkApp.GetListener()->Add((CBasicListener*)&theApp.m_winPrintApp);
			//测试代码
			theApp.m_winCalPosApp.LoadConfig(theApp.m_strProjFile);
		}
		else
		{
			BCGPMessageBox("设备连接失败，请重新建立连接！");
		}
	}
	m_wndStatusBar.SetPaneText(4, str);

	return theApp.m_bConnectFlag;
}
void CMainFrame::OnMenuDevConnect()
{
	// TODO: Add your command handler code here
	CSetPortDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
#ifdef _HWA_DEBUG
		m_nProjStatus = 1;
#endif
		theApp.m_bConnectFlag = OnLinkToDevice();
		if (theApp.m_bConnectFlag)
			m_wndStatusBar.SetPaneIcon(4, m_bmpGreen);
	}

}
void CMainFrame::OnDLinkFromDevice()
{
	if(theApp.m_winLinkApp.GetStatus())
	{
		theApp.m_bConnectFlag = false;
		theApp.m_winLinkApp.GetListener()->Remove(this->m_hWnd);
		theApp.m_winLinkApp.GetListener()->Remove((CBasicListener*)&theApp.m_winPrintApp);
		m_wndStatusBar.SetPaneIcon(4, m_bmpRed);
		theApp.m_winLinkApp.Close();
	}
}
void CMainFrame::OnMenuDevDisconnect()
{
	// TODO: Add your command handler code here
	if (BCGPMessageBox("请确认是否要断开设备连接？", MB_OKCANCEL) == IDOK)
	{
		OnDLinkFromDevice();
		m_wndStatusBar.SetPaneText(4, "端口：已断开...");
	}
}

void CMainFrame::OnUpdateMenuDevConnect(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifdef _HWA_DEBUG
	pCmdUI->Enable(!theApp.m_bConnectFlag);
#else
	pCmdUI->Enable(!theApp.m_bConnectFlag && m_nProjStatus == 1);
#endif
}

void CMainFrame::OnUpdateMenuDevDisconnect(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifdef _HWA_DEBUG
	pCmdUI->Enable(theApp.m_bConnectFlag);
#else
	pCmdUI->Enable(theApp.m_bConnectFlag && m_nProjStatus == 1);
#endif
}

void CMainFrame::OnMenuDevInitial()
{
	// TODO: Add your command handler code here
	CSetBDIDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnMenuDevFactory() //软件复位
{
	// TODO: Add your command handler code here
	BCGPMessageBox("软件复位成功");
}
void CMainFrame::OnUpdateMenuDevInitial(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(theApp.m_bConnectFlag && m_nProjStatus == 1);
}

void CMainFrame::OnUpdateMenuDevFactory(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(theApp.m_bConnectFlag && m_nProjStatus == 1);
}

//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnMenuPosmodHost()
{
	// TODO: Add your command handler code here
	m_bPosMode = true;
}

void CMainFrame::OnMenuPosmodConsole()
{
	// TODO: Add your command handler code here
	m_bPosMode = false;
}
void CMainFrame::OnUpdateMenuPosmodHost(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bPosMode);
	pCmdUI->Enable(m_nProjStatus);
}

void CMainFrame::OnUpdateMenuPosmodConsole(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!m_bPosMode);
	pCmdUI->Enable(m_nProjStatus);
}

//////////////////////////////数据回放功能////////////////////////////////////////////
void CMainFrame::OnMenuPlayStart()
{
	// TODO: Add your command handler code here
	m_nPlayStatus = 0;
	EnterCriticalSection(&m_csPlayer);
	theApp.m_winPlayerApp.startPlay();
	SetTimer(1, PlayStep[2].nFreq, NULL);
	LeaveCriticalSection(&m_csPlayer);
}

void CMainFrame::OnUpdateMenuPlayStart(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->SetCheck(m_bPlayStart);
	pCmdUI->Enable(m_nPlayStatus && (m_nProjStatus == 2));
}

void CMainFrame::OnMenuPlayPause()
{
	// TODO: Add your command handler code here
	m_nPlayStatus = 1;
	EnterCriticalSection(&m_csPlayer);
	KillTimer(1);
	Sleep(5);
	theApp.m_winPlayerApp.pausePlay();
	LeaveCriticalSection(&m_csPlayer);
}

void CMainFrame::OnUpdateMenuPlayPause(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->SetCheck(m_bPlayPause && m_bPlayStart);
	pCmdUI->Enable(!m_nPlayStatus  && (m_nProjStatus == 2));
}

void CMainFrame::OnMenuPlayStop()
{
	// TODO: Add your command handler code here
	m_nPlayStatus = 2;
	EnterCriticalSection(&m_csPlayer);
	KillTimer(1);
	Sleep(5);
	theApp.m_winPlayerApp.stopPlay();
	LeaveCriticalSection(&m_csPlayer);
}

void CMainFrame::OnUpdateMenuPlayStop(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->SetCheck(!m_bPlayStart);
	pCmdUI->Enable(!m_nPlayStatus  && (m_nProjStatus == 2));
}

void CMainFrame::OnMenuPlayForward()
{
	// TODO: Add your command handler code here
	m_nInterval = (m_nInterval+1)%StepSize;
	EnterCriticalSection(&m_csPlayer);
	if(theApp.m_winPlayerApp.GetPlayStatus())//当文件播放线程开启后，才可执行
		SetTimer(1, PlayStep[m_nInterval].nFreq, NULL);
	LeaveCriticalSection(&m_csPlayer);
}

void CMainFrame::OnUpdateMenuPlayForward(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((m_nProjStatus == 2));
}

void CMainFrame::OnMenuPlayBackward()
{
	// TODO: Add your command handler code here
	m_nInterval = (m_nInterval - 1 + StepSize)%StepSize;
	EnterCriticalSection(&m_csPlayer);
	if(theApp.m_winPlayerApp.GetPlayStatus())//当文件播放线程开启后，才可执行
		SetTimer(1, PlayStep[m_nInterval].nFreq, NULL);
	LeaveCriticalSection(&m_csPlayer);
}

void CMainFrame::OnUpdateMenuPlayBackward(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((m_nProjStatus == 2));
}

void CMainFrame::OnMenuPlaySlider() 
{
	int pos = 0;
	CString str;
	EnterCriticalSection(&m_csPlayer);
	if (GetAsyncKeyState (VK_LBUTTON) == 0)
	{
		/*str.Format (_T("Moved to: %d"), CBCGPSliderButton::GetPos(ID_MENU_PLAY_SLIDER));
		BCGPMessageBox (str);*/
		//先关闭定时器，暂停播放；然后移动进度条；最后再开始播放，开启定时器
		KillTimer(1);
		Sleep(5);
		theApp.m_winPlayerApp.pausePlay();
		pos = CBCGPSliderButton::GetPos(ID_MENU_PLAY_SLIDER);
		theApp.m_winPlayerApp.Seek(pos);
		Sleep(5);
		theApp.m_winPlayerApp.startPlay();
		SetTimer(1, PlayStep[m_nInterval].nFreq, NULL);
	}
	LeaveCriticalSection(&m_csPlayer);
}
void CMainFrame::OnUpdateMenuPlaySlider(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((m_nProjStatus == 2));
}
/////////////////////////////////////////////////////////////
void CMainFrame::OnMenuViewPosmod()
{
	// TODO: Add your command handler code here
	//m_wndWorkSpace.ShowControlBar(!m_wndWorkSpace.IsVisible(), FALSE, TRUE);
}

void CMainFrame::OnUpdateMenuViewPosmod(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(FALSE);//m_wndWorkSpace.IsVisible()
	pCmdUI->Enable(FALSE);
}

void CMainFrame::OnMenuViewSky()
{
	// TODO: Add your command handler code here
	m_wndSkyView.ShowControlBar(!m_wndSkyView.IsVisible(), FALSE, TRUE);
}

void CMainFrame::OnUpdateMenuViewSky(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_wndSkyView.IsVisible());
}

void CMainFrame::OnMenuViewSnr()
{
	// TODO: Add your command handler code here
	m_wndSnrView.ShowControlBar(!m_wndSnrView.IsVisible(), FALSE, TRUE);
}

void CMainFrame::OnUpdateMenuViewSnr(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_wndSnrView.IsVisible());
}

void CMainFrame::OnMenuViewClose()
{
	// TODO: Add your command handler code here
	CloseAllView();
}

void CMainFrame::OnUpdateMenuViewClose(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
}

//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnMenuAboutInstruction()
{
	// TODO: Add your command handler code here
	ShellExecute(NULL, "open",  "北斗多频试验验证终端监控软件-使用手册.CHM", NULL, NULL, SW_SHOW);
	//BCGPMessageBox("暂时尚未制作帮助文档");
}

void CMainFrame::OnMenuAboutDev()
{
	// TODO: Add your command handler code here
	SETACK data;
	data.ID = OUT_BDSIM;
	theApp.m_winLinkApp.SetupACKRequest(data);
	Sleep(500);
	m_wndCheckDlg.ShowWindow(SW_SHOW);
	//m_wndCheckDlg.InitPropListPRM();
}

/////////////////////////////消息处理/////////////////////////////////////////////
void CMainFrame::OnUpdateInformation(int nID, CGlobalVariant* data)
{
	int index = nID - IDD_USER_BASE;//
	if(index < 0 || index >= m_arrayViews.GetSize())
		return;

	CHWATestView* pNewView = DYNAMIC_DOWNCAST(CHWATestView, m_arrayViews[index]);
	if(pNewView != NULL && ::IsWindow(pNewView->m_hWnd))
	{
		if(pNewView->IsWindowVisible())
			pNewView->OnUpdateAllViews(data, nID);
	}
}

//////////////////////////////////////////////////////////////////////////
//接收消息，然后计算结果
LRESULT CMainFrame::OnAnswerInfoCOD(WPARAM wParam, LPARAM lParam)
{
	return 0; 
}//卫星原始导航电文
LRESULT CMainFrame::OnAnswerInfoEPH(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	CGlobalVariant* pData = new CGlobalVariant();
	BD2_EPH* result = (BD2_EPH*)wParam;
	count = sizeof(BD2_EPH);
	m_nglobalWeek = result->week;
	m_nglobalTow = result->tow;
	pData->length = count;
	pData->buffer = (unsigned char*)malloc(count+1);
	memcpy(pData->buffer, result, sizeof(BD2_EPH));
	try
	{
		OnUpdateInformation(IDD_SHOW_VIEW_EPH, pData);
		if (pData->buffer)
			free(pData->buffer);
		delete pData;
		//开始上位机定位
		if(m_bPosMode)
		{
			m_Listener.OnAnswerCalPositionEPH((WPARAM)result, 0);
		}
	}
	catch (...)
	{
	}

	return 0; 
}//卫星星历信息
LRESULT CMainFrame::OnAnswerInfoION(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	CGlobalVariant* pData = new CGlobalVariant();
	BD2_ION* result = (BD2_ION*)wParam;
	count = sizeof(BD2_ION);
	m_nglobalWeek = result->week;
	m_nglobalTow = result->tow;
	pData->length = count;
	pData->buffer = (unsigned char*)malloc(count+1);
	memcpy(pData->buffer, result, sizeof(BD2_ION));
	try
	{
		OnUpdateInformation(IDD_SHOW_VIEW_ION, pData);
		if (pData->buffer)
			free(pData->buffer);
		delete pData;
		//开始上位机定位
		if(m_bPosMode)
		{
			m_Listener.OnAnswerCalPositionION((WPARAM)result, 0);
		}
	}
	catch (...)
	{
	}

	return 0; 
}//卫星电离层参数
LRESULT CMainFrame::OnAnswerInfoALM(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	CGlobalVariant* pData = new CGlobalVariant();
	BD2_ALM* result = (BD2_ALM*)wParam;
	count = sizeof(BD2_ALM);
	pData->length = count;
	pData->buffer = (unsigned char*)malloc(count+1);
	memcpy(pData->buffer, result, sizeof(BD2_ALM));
	try
	{
		OnUpdateInformation(IDD_SHOW_VIEW_ALM, pData);
		if (pData->buffer)
			free(pData->buffer);
		delete pData;

		//开始上位机定位
		if(m_bPosMode)
		{
			m_Listener.OnAnswerCalPositionALM((WPARAM)result, 0);
		}
	}
	catch (...)
	{
	}

	return 0; 
}//卫星历书信息
LRESULT CMainFrame::OnAnswerInfoJAL(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	CGlobalVariant* pData = new CGlobalVariant();
	BD2_JAL* result = (BD2_JAL*)wParam;
	count = sizeof(BD2_JAL);
	pData->length = count;
	pData->buffer = (unsigned char*)malloc(count+1);
	memcpy(pData->buffer, result, sizeof(BD2_JAL));
	try
	{
		OnUpdateInformation(IDD_SHOW_VIEW_JAL, pData);
		if (pData->buffer)
			free(pData->buffer);
		delete pData;
		//开始上位机定位
		if(m_bPosMode)
		{
			m_Listener.OnAnswerCalPositionJAL((WPARAM)result, 0);
		}
	}
	catch (...)
	{
	}

	return 0; 
}//卫星简约历书信息
LRESULT CMainFrame::OnAnswerInfoCOM(WPARAM wParam, LPARAM lParam)
{
	return 0;
}//端口速率信息
LRESULT CMainFrame::OnAnswerInfoMOD(WPARAM wParam, LPARAM lParam)
{
	CString str;
	UINT8 i=0, mode=0;
	try
	{
		SETMOD* output = (SETMOD*)wParam;
		str.Format("%d", output->BD2Pos);
		WritePrivateProfileString("GNMOD", "BD2Pos", str, theApp.m_strConfigPath);
		str.Format("%d", output->BD1Pos);
		WritePrivateProfileString("GNMOD", "BD1Pos", str, theApp.m_strConfigPath);
		str.Format("%d", output->GPSPos);
		WritePrivateProfileString("GNMOD", "GPSPos", str, theApp.m_strConfigPath);
		str.Format("%d", output->GaliPos);
		WritePrivateProfileString("GNMOD", "GaliPos", str, theApp.m_strConfigPath);
		str.Format("%d", output->ComPos);
		WritePrivateProfileString("GNMOD", "ComPos", str, theApp.m_strConfigPath);
		str.Format("%d", output->BD2Time);
		WritePrivateProfileString("GNMOD", "BD2Time", str, theApp.m_strConfigPath);
		str.Format("%d", output->BD1Time);
		WritePrivateProfileString("GNMOD", "BD1Time", str, theApp.m_strConfigPath);
		str.Format("%d", output->GPSTime);
		WritePrivateProfileString("GNMOD", "GPSTime", str, theApp.m_strConfigPath);
		str.Format("%d", output->GaliTime);
		WritePrivateProfileString("GNMOD", "GaliTime", str, theApp.m_strConfigPath);
		for (i=0; i<14; i++)
		{
			if (((output->BD2Pos >> i) & 0x01) || ((output->BD1Pos >> i) & 0x01))
			{
				if (i<7)
				{
					mode = i+1;
				}
				else
				{
					mode = i;
				}
			}
		}
		if (((output->BD2Pos >> 2) & 0x01) && ((output->BD2Pos >> 10) & 0x01))//B1CB3C
		{
			mode = 21;
		}
		else if (((output->BD1Pos >> 1) & 0x01) && ((output->BD1Pos >> 9) & 0x01))//B1QB3Q
		{
			mode = 22;
		}
		else if (((output->BD2Pos >> 3) & 0x01) && ((output->BD2Pos >> 11) & 0x01))//B1AB3A
		{
			mode = 23;
		}
		else if (((output->BD2Pos >> 3) & 0x01) && ((output->BD2Pos >> 13) & 0x01))//B1AB3AE
		{
			mode = 27;
		}
		else if (((output->BD2Pos >> 12) & 0x01) && ((output->BD2Pos >> 11) & 0x01))//BsB3A
		{
			mode = 24;
		}
		else if (((output->BD2Pos >> 12) & 0x01) && ((output->BD2Pos >> 13) & 0x01))//BsB3AE
		{
			mode = 28;
		}
		else if (((output->BD2Pos >> 2) & 0x01) && ((output->BD2Pos >> 4) & 0x01))//B1CB2a
		{
			mode = 26;
		}
		else if (((output->BD2Pos >> 2) & 0x01) && ((output->BD2Pos >> 6) & 0x01) && ((output->BD2Pos >> 10) & 0x01))//B1CB2B3C
		{
			mode = 25;
		}
		str.Format("%d", mode);
		WritePrivateProfileString("GNMOD", "mode", str, theApp.m_strConfigPath);
		int index = ModeToItem(mode);
		if(index < 21 && index >= 0)
		{
			str.Format("当前定位模式：%s", strMODE[index]);
			BCGPMessageBox(str);
		}
	}
	catch (...)
	{
	}

	return 0;
}//定位授时模式信息
LRESULT CMainFrame::OnAnswerInfoPOS(WPARAM wParam, LPARAM lParam)
{
	CString strText;
	int mode=0, index=0, count=0;
	CGlobalVariant* pData = new CGlobalVariant();
	BD2_POS* pos = (BD2_POS*)wParam;

	pos->flag = false;
	count = sizeof(BD2_POS);
	m_nglobalWeek = pos->week;
	m_nglobalTow = pos->tow;
	pData->length = count;
	pData->buffer = (unsigned char*)malloc(count+1);
	memcpy(pData->buffer, pos, sizeof(BD2_POS));
	memcpy(&theApp.m_CurPosition, &pos->blh, sizeof(BD2_USER_BLH));
	try
	{
		OnUpdateInformation(IDD_SHOW_VIEW_POS, pData);//显示数据
		OnUpdateInformation(IDD_DRAW_VIEW_POS, pData);//显示数据
		if (pData->buffer)
			free(pData->buffer);
		delete pData;

		mode = pos->mode;
		index = ModeToItem(mode);
		if(index <= -1 || index >= 24)
		{
			m_wndStatusBar.SetPaneText(3, "当前定位模式：NONE", TRUE);
		}
		else
		{
			m_wndStatusBar.SetPaneText(3, "当前定位模式：" + strMODE[index], TRUE);
		}
	}
	catch (...)
	{
	}

	return 0;
}//定位、测速结果信息
LRESULT CMainFrame::OnAnswerCalPositionPOS(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	BD2_POS temp;
	CGlobalVariant* pData = new CGlobalVariant();
	BD2_POS* pos = (BD2_POS*)wParam;

	pos->flag = true;
	count = sizeof(BD2_POS);
	pData->length = count;
	pData->buffer = (unsigned char*)malloc(count+1);
	memcpy(pData->buffer, pos, sizeof(BD2_POS));
	try
	{
		m_PrintListener.OnAnswerInfoXPV((WPARAM)pos, count);
		OnUpdateInformation(IDD_SHOW_VIEW_XPV, pData);//显示数据
		OnUpdateInformation(IDD_DRAW_VIEW_POS, pData);//显示数据
		if (pData->buffer)
			free(pData->buffer);
		delete pData;

		if (m_bTestMode)
		{
			memcpy(&temp, pos, sizeof(BD2_POS));
			theApp.m_LinkTestApp.AnswerPOSRequest(temp);
		}
	}
	catch (...)
	{
	}

	return 0;
}
LRESULT CMainFrame::OnAnswerInfoRAN(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	int branch = 0;
	double total = sizeof(BD2_RAN);
	CGlobalVariant* pData = new CGlobalVariant();
	BD2_RAN* result = (BD2_RAN*)wParam;
	count = sizeof(BD2_RAN);
	m_nglobalWeek = result->week;
	m_nglobalTow = result->tow;
	pData->length = count;
	pData->buffer = (unsigned char*)malloc(count+1);
	memcpy(pData->buffer, result, sizeof(BD2_RAN));
	try
	{
		OnUpdateInformation(IDD_DRAW_VIEW_RAN, pData);//显示数据
		OnUpdateInformation(IDD_SHOW_VIEW_RAN, pData);//显示数据
		OnUpdateInformation(IDD_SHOW_VIEW_CHA, pData);
		if (pData->buffer)
			free(pData->buffer);
		delete pData;
		//////////////////////////////////////////////////////////////////////////
		//开始上位机定位
		if(m_bPosMode)
		{
			m_Listener.OnAnswerCalPositionRAN((WPARAM)result, m_nCurLeap);
		}
		if(m_nProjStatus == 2)//选择打开项目，播放文件时启用
		{
			if(theApp.m_winPlayerApp.GetPlayStatus())
				theApp.m_winPlayerApp.pausePlay();
		}
	}
	catch (...)
	{
	}

	return 0;
}//伪距、载波、多普勒信息
LRESULT CMainFrame::OnAnswerInfoREF(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	return 0;
}//时空参考信息

LRESULT CMainFrame::OnAnswerInfoGSV(WPARAM wParam, LPARAM lParam)
{
	CGlobalVariant* pData = new CGlobalVariant();

    NmeaAllData* result = (NmeaAllData*)wParam;

	//BD2_GSV* result = (BD2_GSV*)wParam;
	pData->length = sizeof(BD2_GSV);
	pData->buffer = (unsigned char*)malloc(sizeof(BD2_GSV)+1);

    BD2_GSV packGSV;
    int id=0;
	double elv=0,azi=0;
    int count = strtod(result->GSV_in_use, NULL);//save_GSV.satellite_view

    BD2_GSV	GSVPack;
    GSVPack.num = count;
    for (int i=0; i<count; i++)
	{
        id = atoi(result->GA_view[i].PRN);
        elv = strtod(result->GA_view[i].yang_cour, NULL);
        azi = strtod(result->GA_view[i].fangwei_cour, NULL);

		GSVPack.id[i] = id;
		GSVPack.elv[i] = elv;
		GSVPack.azi[i] = azi;
        GSVPack.snr[i] = strtod(result->GA_view[i].CN0, NULL);

	}
    GSVPack.system_type = result->sys;	


	memcpy(pData->buffer, &packGSV, sizeof(BD2_GSV));
	try
	{
		OnUpdateInformation(IDD_SHOW_VIEW_SIV, pData);
		if (pData->buffer)
			free(pData->buffer);
		delete pData;

		m_wndSkyView.RefreshView(result);
		//delete result;
	}
	catch (...)
	{
	}

	return 0; 
}//卫星信息

LRESULT CMainFrame::OnAnswerInfoPAO(WPARAM wParam, LPARAM lParam)//add by cy 20180714
{
	int count=0;
	CGlobalVariant* pData = new CGlobalVariant();
	BD2_PAORDER* result = (BD2_PAORDER*)wParam;
	count = sizeof(BD2_PAORDER);
	pData->length = count;
	pData->buffer = (unsigned char*)malloc(count+1);
	memcpy(pData->buffer, result, sizeof(BD2_PAORDER));
	try
	{
		OnUpdateInformation(IDD_SHOW_VIEW_TEST, pData);
		if (pData->buffer)
			free(pData->buffer);
		delete pData;

		//m_wndSkyView.RefreshView(result);
		//delete result;
	}
	catch (...)
	{
	}

	return 0; 
}
LRESULT CMainFrame::OnAnswerInfoCHD(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	CGlobalVariant* pData = new CGlobalVariant();
	BD2_CHD* result = (BD2_CHD*)wParam;
	count = sizeof(BD2_CHD);
	pData->length = count;
	pData->buffer = (unsigned char*)malloc(count+1);
	memcpy(pData->buffer, result, sizeof(BD2_CHD));
	try
	{
		OnUpdateInformation(IDD_SHOW_VIEW_CHD, pData);
		if (pData->buffer)
			free(pData->buffer);
		delete pData;

		//m_wndSkyView.RefreshView(result);
		//delete result;
	}
	catch (...)
	{
	}

	return 0; 
}

LRESULT CMainFrame::OnShowCmdInfo(WPARAM wParam, LPARAM lParam)
{
    CString str;
    char *info = (char*)wParam;
    str = info;

    m_wndOutputView.ShowDataToWindow(str);
    //TRACE("Show Cmd info:%s\n", info);
    return 0;
}

LRESULT CMainFrame::OnUpdateGGAPOSInfo(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	//BD2_POS temp;
	CGlobalVariant* pData = new CGlobalVariant();
	//BD2_POS* pos = (BD2_POS*)wParam;
    NmeaAllData* pos = (NmeaAllData*)wParam;

	//pos->flag = true;
	count = sizeof(NmeaAllData);
	pData->length = count;
	pData->buffer = (unsigned char*)malloc(count+1);
	memcpy(pData->buffer, pos, count);
	try
	{
		//m_PrintListener.OnAnswerInfoXPV((WPARAM)pos, count);
		//OnUpdateInformation(IDD_SHOW_VIEW_XPV, pData);//显示数据
		OnUpdateInformation(IDD_SHOW_VIEW_GGA_POS, pData);//显示数据
		if (pData->buffer)
			free(pData->buffer);
		delete pData;

		if (m_bTestMode)
		{
			//memcpy(&temp, pos, sizeof(BD2_POS));
			//theApp.m_LinkTestApp.AnswerPOSRequest(temp);
		}
	}
	catch (...)
	{
	}

    return 0;
}

LRESULT CMainFrame::OnAnswerInfoSTA(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	int data = 0;
	CString strText = "序列号：";
	BD2_STA* result = (BD2_STA*)wParam;
	try
	{
		data = result->number;
		if (data & 0x01)
		{
			strText += "01";
		}
		if (data & 0x02)
		{
			strText += "02";
		}
		if (data & 0x04)
		{
			strText += "03";
		}
		if (data & 0x08)
		{
			strText += "04";
		}
		m_wndStatusBar.SetPaneText(5, strText);
		if ((data&0x01)&&(data&0x02)&&(data&0x04)&&(data&0x08))
		{
			m_wndStatusBar.SetPaneIcon(5, m_bmpGreen);
		}
		else
		{
			m_wndStatusBar.SetPaneIcon(5, m_bmpRed);
		}

		m_wndStatusBar.SetPaneIcon(6, (result->cpu)?m_bmpGreen:m_bmpRed);
		m_wndStatusBar.SetPaneIcon(7, (result->soft)?m_bmpGreen:m_bmpRed);
		m_wndStatusBar.SetPaneIcon(8, (result->clock)?m_bmpGreen:m_bmpRed);
		m_wndStatusBar.SetPaneIcon(9, (result->pps)?m_bmpGreen:m_bmpRed);
	}
	catch (...)
	{
	}

	return 0; 
}//终端工作状态信息
LRESULT CMainFrame::OnAnswerInfoTIM(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	CString str;
	int index=0, mode=0;
	CGlobalVariant* pData = new CGlobalVariant();
	BD2_TIME* result = (BD2_TIME*)wParam;
	m_nCurLeap = result->Leap;
	count = sizeof(BD2_TIME);
	pData->length = count;
	pData->buffer = (unsigned char*)malloc(count+1);
	memcpy(pData->buffer, result, sizeof(BD2_TIME));
	try
	{
		OnUpdateInformation(IDD_SHOW_VIEW_TIM, pData);
		if (pData->buffer)
			free(pData->buffer);
		delete pData;

		str.Format("当前时刻：%04d/%02d/%02d %02d:%02d:%02d, 闰秒：%02d", 
			result->year,result->month,result->day,result->hour,result->minute,result->second,result->Leap);
		m_wndStatusBar.SetPaneText(2, str);
	}
	catch (...)
	{
	}

	return 0; 
}//授时结果信息
LRESULT CMainFrame::OnAnswerInfoXPV(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	int mode=0, index=0;
/*	CGlobalVariant* pData = new CGlobalVariant();
	BD2_POS* pos = (BD2_POS*)wParam;
	count = sizeof(BD2_POS);
	pData->length = count;
	pData->buffer = (unsigned char*)malloc(count+1);
	memcpy(pData->buffer, pos, sizeof(BD2_POS));
	try
	{
		OnUpdateInformation(IDD_SHOW_VIEW_POS, pData);//显示数据
		free(pData->buffer);
		delete pData;

		mode = pos->mode;
		index = ModeToItem(mode);
		if(index <= -1 || index >= 24)
		{
			m_wndStatusBar.SetPaneText(3, "当前定位模式：NONE", TRUE);
		}
		else
		{
			m_wndStatusBar.SetPaneText(3, "当前定位模式：" + strMODE[index], TRUE);
		}
	}
	catch (...)
	{
	}*/

	return 0; 
}//笛卡尔坐标定位、测速结果信息
LRESULT CMainFrame::OnAnswerInfoSRC(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	UTCTime obsTime;
	CString strText,strPath;
	CGlobalVariant* pData = new CGlobalVariant();
	BD2_SRC* result = (BD2_SRC*)wParam;
	count = sizeof(BD2_SRC);
	pData->length = count;
	pData->buffer = (unsigned char*)malloc(count+1);
	memcpy(pData->buffer, result, sizeof(BD2_SRC));
	memset(&obsTime, 0, sizeof(UTCTime));
	try
	{
		OnUpdateInformation(IDD_SHOW_VIEW_SRC, pData);
		if (pData->buffer)
			free(pData->buffer);
		delete pData;

		if(m_nProjStatus == 1 && m_nglobalWeek != 0)//新建工程，才具有存储功能
		{
			obsTime.week = m_nglobalWeek;
			obsTime.tow = m_nglobalTow;
			obsTime.leap = 0;
			BDTime2UTC(&obsTime);
			strText.Empty();
			strPath.Empty();
			strText.Format("%04d%02d%02d.ori", obsTime.year, obsTime.month, obsTime.day);
			strPath = theApp.m_strOriginData + strText;
			RecordFile(result->Buffer, result->length, strPath, theApp.m_nProtocol);//原始存储
		}
	}
	catch (...)
	{
	}

	return 0;
}//原始数据
LRESULT CMainFrame::OnAnswerInfoFrame(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	BD2_SRC* result = (BD2_SRC*)wParam;
	try
	{
	}
	catch (...)
	{
	}

	return 0;
}
LRESULT CMainFrame::OnAnswerInfoSNR(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	int branch = (int)lParam;
	//BD2_GSV* result = (BD2_GSV*)wParam;

    NmeaAllData* data = (NmeaAllData*)wParam;

	try
	{
        switch(data->sys)
        {
        case GP:
            m_wndGPSnrView.RefreshView(data, branch);
            break;

        case BD:
            m_wndSnrView.RefreshView(data, branch);
            break;

        case GL:
            m_wndGLSnrView.RefreshView(data, branch);
            break;

        case GA:
            m_wndGASnrView.RefreshView(data, branch);
            break;
        }
	}
	catch (...)
	{
	}

	return 0;
}//信号强度
LRESULT CMainFrame::OnAnswerInfoGBS(WPARAM wParam, LPARAM lParam)
{
	int count=0;
	CGlobalVariant* pData = new CGlobalVariant();
	BD2_GBS* result = (BD2_GBS*)wParam;
	count = sizeof(BD2_GBS);
	m_nglobalWeek = result->week;
	m_nglobalTow = result->tow;
	pData->length = count;
	pData->buffer = (unsigned char*)malloc(count+1);
	memcpy(pData->buffer, result, sizeof(BD2_GBS));
	try
	{
		OnUpdateInformation(IDD_SHOW_VIEW_GBS, pData);
		if (pData->buffer)
			free(pData->buffer);
		delete pData;
	}
	catch (...)
	{
	}

	return 0; 
}//自主完好性
LRESULT CMainFrame::OnAnswerInfoSIM(WPARAM wParam, LPARAM lParam)//SIM卡信息
{
	CString strText,strAppName;
	BD2_SIM* pData = (BD2_SIM*)wParam;
	int branch = pData->branch;

	switch (branch)
	{
	case CH_B1Q:
		strAppName = "PRM_B1Q";
		WritePrivateProfileString(strAppName, "Flag", "1", theApp.m_strProjFile);
		strText.Format("%d", pData->prmFlag);
		WritePrivateProfileString(strAppName, "prmFlag", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->prmWeek0);
		WritePrivateProfileString(strAppName, "prmStartTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->prmWeek1);
		WritePrivateProfileString(strAppName, "prmDeadTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdFlag);
		WritePrivateProfileString(strAppName, "simFlag", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdWeek0);
		WritePrivateProfileString(strAppName, "simStartTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdWeek1);
		WritePrivateProfileString(strAppName, "simDeadTime", strText, theApp.m_strProjFile);
		break;
	case CH_B1A:
		strAppName = "PRM_B1A";
		WritePrivateProfileString(strAppName, "Flag", "1", theApp.m_strProjFile);
		strText.Format("%d", pData->prmFlag);
		WritePrivateProfileString(strAppName, "prmFlag", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->prmWeek0);
		WritePrivateProfileString(strAppName, "prmStartTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->prmWeek1);
		WritePrivateProfileString(strAppName, "prmDeadTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdFlag);
		WritePrivateProfileString(strAppName, "simFlag", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdWeek0);
		WritePrivateProfileString(strAppName, "simStartTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdWeek1);
		WritePrivateProfileString(strAppName, "simDeadTime", strText, theApp.m_strProjFile);
		break;
	case CH_B3Q:
		strAppName = "PRM_B3Q";
		WritePrivateProfileString(strAppName, "Flag", "1", theApp.m_strProjFile);
		strText.Format("%d", pData->prmFlag);
		WritePrivateProfileString(strAppName, "prmFlag", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->prmWeek0);
		WritePrivateProfileString(strAppName, "prmStartTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->prmWeek1);
		WritePrivateProfileString(strAppName, "prmDeadTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdFlag);
		WritePrivateProfileString(strAppName, "simFlag", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdWeek0);
		WritePrivateProfileString(strAppName, "simStartTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdWeek1);
		WritePrivateProfileString(strAppName, "simDeadTime", strText, theApp.m_strProjFile);
		break;
	case CH_B3A:
		strAppName = "PRM_B3A";
		WritePrivateProfileString(strAppName, "Flag", "1", theApp.m_strProjFile);
		strText.Format("%d", pData->prmFlag);
		WritePrivateProfileString(strAppName, "prmFlag", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->prmWeek0);
		WritePrivateProfileString(strAppName, "prmStartTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->prmWeek1);
		WritePrivateProfileString(strAppName, "prmDeadTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdFlag);
		WritePrivateProfileString(strAppName, "simFlag", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdWeek0);
		WritePrivateProfileString(strAppName, "simStartTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdWeek1);
		WritePrivateProfileString(strAppName, "simDeadTime", strText, theApp.m_strProjFile);
		break;
	case CH_B3AE:
		strAppName = "PRM_B3AE";
		WritePrivateProfileString(strAppName, "Flag", "1", theApp.m_strProjFile);
		strText.Format("%d", pData->prmFlag);
		WritePrivateProfileString(strAppName, "prmFlag", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->prmWeek0);
		WritePrivateProfileString(strAppName, "prmStartTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->prmWeek1);
		WritePrivateProfileString(strAppName, "prmDeadTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdFlag);
		WritePrivateProfileString(strAppName, "simFlag", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdWeek0);
		WritePrivateProfileString(strAppName, "simStartTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdWeek1);
		WritePrivateProfileString(strAppName, "simDeadTime", strText, theApp.m_strProjFile);
		break;
	case CH_Bs:
		strAppName = "PRM_Bs";
		WritePrivateProfileString(strAppName, "Flag", "1", theApp.m_strProjFile);
		strText.Format("%d", pData->prmFlag);
		WritePrivateProfileString(strAppName, "prmFlag", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->prmWeek0);
		WritePrivateProfileString(strAppName, "prmStartTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->prmWeek1);
		WritePrivateProfileString(strAppName, "prmDeadTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdFlag);
		WritePrivateProfileString(strAppName, "simFlag", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdWeek0);
		WritePrivateProfileString(strAppName, "simStartTime", strText, theApp.m_strProjFile);
		strText.Format("%d", pData->mpdWeek1);
		WritePrivateProfileString(strAppName, "simDeadTime", strText, theApp.m_strProjFile);
		break;
	default:
		break;
	}
	//m_wndCheckDlg.InitPropListPRM();

	return 0;
}
LRESULT CMainFrame::OnAnswerInfoVER(WPARAM wParam, LPARAM lParam)//版本信息
{
	CString strText,strAppName;
	BD2_VER* pData = (BD2_VER*)wParam;
	int type = pData->type;
	strAppName = "VERSION";
	if (type == 0)
	{
		strText.Format("V%d.%d.%d.%d", pData->dsp.ver[0], pData->dsp.ver[1],pData->dsp.ver[2],pData->dsp.ver[3]);
		WritePrivateProfileString(strAppName, "DSPVer", strText, theApp.m_strProjFile);
		strText.Format("%04d/%02d/%02d-%02d:%02d:%02d", pData->dsp.year, pData->dsp.month,pData->dsp.day,pData->dsp.hour,pData->dsp.minute,pData->dsp.second);
		WritePrivateProfileString(strAppName, "DSPTime", strText, theApp.m_strProjFile);
	} 
	else if (type == 1)
	{
		strText.Format("V%d.%d.%d.%d", pData->dsp.ver[0], pData->dsp.ver[1],pData->dsp.ver[2],pData->dsp.ver[3]);
		WritePrivateProfileString(strAppName, "DSPB1Ver", strText, theApp.m_strProjFile);
		strText.Format("%04d/%02d/%02d-%02d:%02d:%02d", pData->dsp.year, pData->dsp.month,pData->dsp.day,pData->dsp.hour,pData->dsp.minute,pData->dsp.second);
		WritePrivateProfileString(strAppName, "DSPB1Time", strText, theApp.m_strProjFile);

		strText.Format("V%d.%d.%d.%d", pData->fpga.ver[0], pData->fpga.ver[1],pData->fpga.ver[2],pData->fpga.ver[3]);
		WritePrivateProfileString(strAppName, "FPGAB1Ver", strText, theApp.m_strProjFile);
		strText.Format("%04d/%02d/%02d-%02d:%02d:%02d", pData->fpga.year, pData->fpga.month,pData->fpga.day,pData->fpga.hour,pData->fpga.minute,pData->fpga.second);
		WritePrivateProfileString(strAppName, "FPGAB1Time", strText, theApp.m_strProjFile);
	}
	else if (type == 2)
	{
		strText.Format("V%d.%d.%d.%d", pData->dsp.ver[0], pData->dsp.ver[1],pData->dsp.ver[2],pData->dsp.ver[3]);
		WritePrivateProfileString(strAppName, "DSPB2Ver", strText, theApp.m_strProjFile);
		strText.Format("%04d/%02d/%02d-%02d:%02d:%02d", pData->dsp.year, pData->dsp.month,pData->dsp.day,pData->dsp.hour,pData->dsp.minute,pData->dsp.second);
		WritePrivateProfileString(strAppName, "DSPB2Time", strText, theApp.m_strProjFile);

		strText.Format("V%d.%d.%d.%d", pData->fpga.ver[0], pData->fpga.ver[1],pData->fpga.ver[2],pData->fpga.ver[3]);
		WritePrivateProfileString(strAppName, "FPGAB2Ver", strText, theApp.m_strProjFile);
		strText.Format("%04d/%02d/%02d-%02d:%02d:%02d", pData->fpga.year, pData->fpga.month,pData->fpga.day,pData->fpga.hour,pData->fpga.minute,pData->fpga.second);
		WritePrivateProfileString(strAppName, "FPGAB2Time", strText, theApp.m_strProjFile);
	}
	else if (type == 3)
	{
		strText.Format("V%d.%d.%d.%d", pData->dsp.ver[0], pData->dsp.ver[1],pData->dsp.ver[2],pData->dsp.ver[3]);
		WritePrivateProfileString(strAppName, "DSPB3Ver", strText, theApp.m_strProjFile);
		strText.Format("%04d/%02d/%02d-%02d:%02d:%02d", pData->dsp.year, pData->dsp.month,pData->dsp.day,pData->dsp.hour,pData->dsp.minute,pData->dsp.second);
		WritePrivateProfileString(strAppName, "DSPB3Time", strText, theApp.m_strProjFile);

		strText.Format("V%d.%d.%d.%d", pData->fpga.ver[0], pData->fpga.ver[1],pData->fpga.ver[2],pData->fpga.ver[3]);
		WritePrivateProfileString(strAppName, "FPGAB3Ver", strText, theApp.m_strProjFile);
		strText.Format("%04d/%02d/%02d-%02d:%02d:%02d", pData->fpga.year, pData->fpga.month,pData->fpga.day,pData->fpga.hour,pData->fpga.minute,pData->fpga.second);
		WritePrivateProfileString(strAppName, "FPGAB3Time", strText, theApp.m_strProjFile);
	}
	else if (type == 4)
	{
		strText.Format("V%d.%d.%d.%d", pData->dsp.ver[0], pData->dsp.ver[1],pData->dsp.ver[2],pData->dsp.ver[3]);
		WritePrivateProfileString(strAppName, "DSPBsVer", strText, theApp.m_strProjFile);
		strText.Format("%04d/%02d/%02d-%02d:%02d:%02d", pData->dsp.year, pData->dsp.month,pData->dsp.day,pData->dsp.hour,pData->dsp.minute,pData->dsp.second);
		WritePrivateProfileString(strAppName, "DSPBsTime", strText, theApp.m_strProjFile);

		strText.Format("V%d.%d.%d.%d", pData->fpga.ver[0], pData->fpga.ver[1],pData->fpga.ver[2],pData->fpga.ver[3]);
		WritePrivateProfileString(strAppName, "FPGABsVer", strText, theApp.m_strProjFile);
		strText.Format("%04d/%02d/%02d-%02d:%02d:%02d", pData->fpga.year, pData->fpga.month,pData->fpga.day,pData->fpga.hour,pData->fpga.minute,pData->fpga.second);
		WritePrivateProfileString(strAppName, "FPGABsTime", strText, theApp.m_strProjFile);
	}
	//m_wndCheckDlg.InitPropListSIM();

	return 0;
}
//////////////////////////////////////////////////////////////////////////
//					测试平台对接，新增代码
//////////////////////////////////////////////////////////////////////////
LRESULT CMainFrame::OnEmulatorSetupMOD(WPARAM wParam, LPARAM lParam)
{
	SETMOD data;
	memcpy(&data, &wParam, sizeof(SETMOD));
	//开始上位机定位
	if(m_bPosMode)
	{
		//theApp.m_winLinkApp.SetupMODRequest(data);
		m_Listener.OnAnswerCalPositionMOD((WPARAM)wParam, m_nCurLeap);
	}
	return 0;
}

LRESULT CMainFrame::OnEmulatorSetupLOG(WPARAM wParam, LPARAM lParam)//设置输出
{
	SETLOG data;
	SETLOG* pData= (SETLOG*)wParam;
	memcpy(&data, &wParam, sizeof(SETLOG));
	if (theApp.m_bConnectFlag && m_bPosMode)
	{
		theApp.m_winLinkApp.SetupLOGRequest(data);
	}

	return 0;
}
LRESULT CMainFrame::OnEmulatorSetupSTA(WPARAM wParam, LPARAM lParam)//设置调制方式
{
	SETSTA data;
	SETSTA* pData= (SETSTA*)wParam;
	memcpy(&data, &wParam, sizeof(SETSTA));
	if (theApp.m_bConnectFlag && m_bPosMode)
	{
		theApp.m_winLinkApp.SetupSTARequest(data);
	}

	return 0;
}
void CMainFrame::OnMenuTestStart()
{
	// TODO: Add your command handler code here
	CTestDlg dlg;
	int port=0;
	DWORD baud=0;
    int protocol = 2;
	if(m_bTestMode)
		return;

	if (dlg.DoModal() == IDOK)
	{
		port = dlg.m_nPort;
		baud = dlg.m_nBaud;
		if(theApp.m_LinkTestApp.CreateComm(port, baud, 2))
		{
			m_bTestMode = true;
			theApp.m_LinkTestApp.GetListener()->Add(this->m_hWnd);
			WritePrivateProfileString("POSMOD", "Tester", "1", "config.ini");
		}
	}
}

void CMainFrame::OnUpdateMenuTestStart(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here 
#ifdef _HWA_DEBUG
	pCmdUI->Enable(m_nProjStatus);
#endif
	pCmdUI->SetCheck(m_bTestMode && m_nProjStatus);//m_bTestMode
}

void CMainFrame::OnMenuTestStop()
{
	// TODO: Add your command handler code here
	if (m_bTestMode)
	{
		m_bTestMode = false;
		WritePrivateProfileString("POSMOD", "Tester", "0", "config.ini");
		theApp.m_LinkTestApp.GetListener()->Remove(this->m_hWnd);
		theApp.m_LinkTestApp.Close();
	}
}

void CMainFrame::OnUpdateMenuTestStop(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
#ifdef _HWA_DEBUG
	pCmdUI->Enable(m_nProjStatus);
#endif
	pCmdUI->SetCheck(!m_bTestMode && m_nProjStatus);//m_bTestMode
}


void CMainFrame::OnMenuShowTest()
{
	// TODO: Add your command handler code here
	SelectView(IDD_SHOW_VIEW_TEST);
}


void CMainFrame::OnUpdateMenuShowTest(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}


void CMainFrame::OnMenuShowChd()
{
	// TODO: Add your command handler code here
	SelectView(IDD_SHOW_VIEW_CHD);
}


void CMainFrame::OnUpdateMenuShowChd(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_nProjStatus);
}


void CMainFrame::OnMenuEpq()
{
    // TODO: Add your command handler code here

    //CSetEPQDialog dlg;
	//if (dlg.DoModal() == IDOK)
	//{

	//}

    CSetEPQDialog *m_wndSetEPQDlg = NULL;

    // 创建非模态对话框实例   
    m_wndSetEPQDlg = new CSetEPQDialog();
    m_wndSetEPQDlg->Create(IDD_SET_EPQ_DIALOG, this);

    m_wndSetEPQDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnSendTcq()
{
    // TODO: Add your command handler code here
 //   CSetTcqDig dlg;
	//if (dlg.DoModal() == IDOK)
	//{}

    CSetTcqDig *m_wndSetTCQDlg = NULL;

    // 创建非模态对话框实例   
    m_wndSetTCQDlg = new CSetTcqDig();
    m_wndSetTCQDlg->Create(IDD_SET_TCQ_DIALOG, this);

    m_wndSetTCQDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnMenuQrq()
{
    // TODO: Add your command handler code here
 //   CSetQRQDig dlg;
	//if (dlg.DoModal() == IDOK)
	//{}
    CSetQRQDig *m_wndSetQRQDlg = NULL;

    // 创建非模态对话框实例   
    m_wndSetQRQDlg = new CSetQRQDig();
    m_wndSetQRQDlg->Create(IDD_SET_QRQ_DIALOG, this);

    m_wndSetQRQDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnMenuShowCmd()
{
    // TODO: Add your command handler code here
    m_wndOutputView.ShowControlBar (!m_wndOutputView.IsVisible (), FALSE, TRUE);
}


void CMainFrame::OnMenuShowGga()
{
    SelectView(IDD_SHOW_VIEW_GGA_POS);
}


void CMainFrame::OnUpdateMenuShowGga(CCmdUI *pCmdUI)
{
    pCmdUI->Enable(m_nProjStatus);
}


void CMainFrame::OnMenuViewGpsSnr()
{
    // TODO: Add your command handler code here
    m_wndGPSnrView.ShowControlBar(!m_wndGPSnrView.IsVisible(), FALSE, TRUE);
}


void CMainFrame::OnUpdateMenuViewGpsSnr(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(m_wndGPSnrView.IsVisible());
}


void CMainFrame::OnMenuViewGlSnr()
{
    // TODO: Add your command handler code here
    m_wndGLSnrView.ShowControlBar(!m_wndGLSnrView.IsVisible(), FALSE, TRUE);
}


void CMainFrame::OnUpdateMenuViewGlSnr(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(m_wndGLSnrView.IsVisible());
}


void CMainFrame::OnMenuViewGaSnr()
{
    // TODO: Add your command handler code here
    m_wndGASnrView.ShowControlBar(!m_wndGASnrView.IsVisible(), FALSE, TRUE);
}


void CMainFrame::OnUpdateMenuViewGaSnr(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->SetCheck(m_wndGASnrView.IsVisible());
}


void CMainFrame::OnMenuSendCmd()
{
    // TODO: Add your command handler code here
    if(m_nProjStatus == 0)
    {
        return;
    }

   CSendCmdDig *sendCmdDlg = NULL;

    // 创建非模态对话框实例   
    sendCmdDlg = new CSendCmdDig();
    sendCmdDlg->Create(IDD_SEND_CMD, this);

    sendCmdDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnUpdateMenuSendCmd(CCmdUI *pCmdUI)
{
    // TODO: Add your command update UI handler code here
    pCmdUI->Enable(m_nProjStatus);
}
