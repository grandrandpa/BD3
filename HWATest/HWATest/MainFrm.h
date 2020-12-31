// MainFrm.h : interface of the CMainFrame class
//


#pragma once
#include "WorkSpaceBar.h"
#include "HWATestView.h"
#include "ProjNewPage.h"
#include "SetSYSDlg.h"
#include "ProjOpenPage.h"
#include "SetBDIDlg.h"
#include "BCGPSliderButton.h"

#include "OutputBar.h"

#include "ShowSkyView.h"
#include "ShowSnrView.h"
#include "ShowSnrGAView.h"
#include "ShowSnrGLView.h"
#include "ShowSnrGPView.h"
#include "SetPortDlg.h"
#include "SetFileDlg.h"
#include "CheckDevDlg.h"
#include "ProjPropertyPage.h"
#include "TestDlg.h"
#include "SetEPQDialog.h"
#include "SetTcqDig.h"
#include "SetQRQDig.h"
#include "SendCmdDig.h"

#include "RadarPointView.h"

#include "TransFunc.h"
#define MAX_VIEWS 24
#define UPDATE_BEGIN 1

class CMainFrame : public CBCGPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPMenuBar			m_wndMenuBar;
	CBCGPToolBar			m_wndToolBar;
	CWorkSpaceBar			m_wndWorkSpace;
	CBCGPCaptionBar			m_wndCaptionBar;
	CBCGPStatusBar			m_wndStatusBar;

	CShowSnrView			m_wndSnrView;
    CShowSnrGPView			m_wndGPSnrView;
    CShowSnrGLView			m_wndGLSnrView;
    CShowSnrGAView			m_wndGASnrView;

	CShowSkyView			m_wndSkyView;
	CSetFileDlg				m_wndSaveFile;
	CSetSYSDlg				m_wndSetSystem;
	//CProjPropertyPage		m_wndProperty;
	CBCGPSliderButton		m_btnSlider;
	CCheckDevDlg			m_wndCheckDlg;

    //CSetEPQDialog           *m_wndSetEPQDlg;
    //CSetTcqDig              *m_wndSetTCQDlg;
    //CSetQRQDig              *m_wndSetQRQDlg;

public:
    COutputBar              m_wndOutputView;

// Generated message map functions
private:
	CBitmap		m_bmpRed;
	CBitmap		m_bmpGreen;
	double		m_totalSecond;
	CRITICAL_SECTION m_Lock;//�ٽ���
	CRITICAL_SECTION m_csPlayer;//�ٽ���
	CArray<CView*, CView*> m_arrayViews;
	list<ComPackageData*>	m_arPackSRC;
	CRITICAL_SECTION m_csSaveFile;//�ٽ���
	CCalPosListener m_Listener;//���߳�����λ����λ����ģ�鷢������
	CHostListener	m_PrintListener;
private:
	bool		m_bTestMode;
	bool		m_bAllVisible;
	bool		m_bPosMode;
	bool		m_bPlayStart;
	bool		m_bPlayPause;
	int			m_nInterval;
	int			m_nPlayStatus;
	int			m_nProjStatus;
	bool		m_bCustomTooltipText;
	int			m_nCurLeap; //��ǰ����
	double		m_dPosTimeCount;
	int			m_nglobalWeek;
	double		m_nglobalTow;
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarReset(WPARAM wp,LPARAM lp);
	afx_msg void OnWindowManager();
	afx_msg void OnMdiMoveToNextGroup();
	afx_msg void OnMdiMoveToPrevGroup();
	afx_msg void OnMdiNewHorzTabGroup();
	afx_msg void OnMdiNewVertGroup();
	afx_msg void OnMdiCancel();
	afx_msg void OnClose();
	virtual BOOL OnEraseMDIClientBackground(CDC* pDC);
	virtual void OnSizeMDIClient (const CRect& rectOld, const CRect& rectNew);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnShowMDITabContextMenu (CPoint point, DWORD dwAllowedItems, BOOL bDrop);
	virtual CBCGPMDIChildWnd* CreateDocumentWindow (LPCTSTR lpcszDocName, CObject* /*pObj*/);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnMenuButtonToolHitTest (CBCGPToolbarButton* pButton, TOOLINFO* pTI);
	virtual BOOL GetToolbarButtonToolTipText (CBCGPToolbarButton* pButton, CString& strTTText);
public:
	void CloseAllView();
	void SelectView(int nID);
	void SwitchToView(int nID, CDocTemplate * pTemplate, CRuntimeClass * pViewClass);
	afx_msg void OnMenuProjNew();
	afx_msg void OnUpdateMenuProjNew(CCmdUI *pCmdUI);
	afx_msg void OnMenuProjOpen();
	afx_msg void OnUpdateMenuProjOpen(CCmdUI *pCmdUI);
	afx_msg void OnMenuProjClose();
	afx_msg void OnUpdateMenuProjClose(CCmdUI *pCmdUI);
	afx_msg void OnMenuProjProperty();
	afx_msg void OnUpdateMenuProjProperty(CCmdUI *pCmdUI);
	afx_msg void OnMenuProjSave();
	afx_msg void OnUpdateMenuProjSave(CCmdUI *pCmdUI);
	//////////////////////////////////////////////////////////////////////////
	afx_msg void OnMenuShowAlm();
	afx_msg void OnMenuShowEph();
	afx_msg void OnMenuShowIon();
	afx_msg void OnMenuShowJal();
	afx_msg void OnMenuShowPos();
	afx_msg void OnMenuShowRan();
	afx_msg void OnMenuShowTim();
	afx_msg void OnMenuShowTxt();
	afx_msg void OnMenuShowXpv();
	afx_msg void OnMenuShowSiv();
	afx_msg void OnMenuShowGbs();
	afx_msg void OnMenuShowVel();
	afx_msg void OnMenuShowCha();
	afx_msg void OnUpdateMenuShowCha(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuShowVel(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuShowAlm(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuShowEph(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuShowGbs(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuShowIon(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuShowPos(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuShowJal(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuShowRan(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuShowSiv(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuShowTim(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuShowTxt(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuShowXpv(CCmdUI *pCmdUI);
	//////////////////////////////////////////////////////////////////////////
	afx_msg void OnMenuLinePos();
	afx_msg void OnMenuLineRan();
	afx_msg void OnUpdateMenuLinePos(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuLineRan(CCmdUI *pCmdUI);
	//////////////////////////////////////////////////////////////////////////
	afx_msg void OnMenuSetup();
	afx_msg void OnUpdateMenuSetup(CCmdUI *pCmdUI);
	//////////////////////////////////////////////////////////////////////////
	bool OnLinkToDevice();
	void OnDLinkFromDevice();
	afx_msg void OnMenuDevConnect();
	afx_msg void OnMenuDevDisconnect();
	afx_msg void OnUpdateMenuDevConnect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuDevDisconnect(CCmdUI *pCmdUI);
	afx_msg void OnMenuDevInitial();
	afx_msg void OnMenuDevFactory();
	afx_msg void OnUpdateMenuDevInitial(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuDevFactory(CCmdUI *pCmdUI);
	//////////////////////////////////////////////////////////////////////////
	afx_msg void OnMenuPosmodHost();
	afx_msg void OnMenuPosmodConsole();
	afx_msg void OnUpdateMenuPosmodHost(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuPosmodConsole(CCmdUI *pCmdUI);
	//////////////////////////////////////////////////////////////////////////
	afx_msg void OnMenuPlayStart();
	afx_msg void OnUpdateMenuPlayStart(CCmdUI *pCmdUI);
	afx_msg void OnMenuPlayPause();
	afx_msg void OnUpdateMenuPlayPause(CCmdUI *pCmdUI);
	afx_msg void OnMenuPlayStop();
	afx_msg void OnUpdateMenuPlayStop(CCmdUI *pCmdUI);
	afx_msg void OnMenuPlayForward();
	afx_msg void OnUpdateMenuPlayForward(CCmdUI *pCmdUI);
	afx_msg void OnMenuPlayBackward();
	afx_msg void OnUpdateMenuPlayBackward(CCmdUI *pCmdUI);
	afx_msg void OnMenuPlaySlider();
	afx_msg void OnUpdateMenuPlaySlider(CCmdUI *pCmdUI);
public:
	afx_msg void OnMenuViewPosmod();
	afx_msg void OnUpdateMenuViewPosmod(CCmdUI *pCmdUI);
	afx_msg void OnMenuViewSky();
	afx_msg void OnUpdateMenuViewSky(CCmdUI *pCmdUI);
	afx_msg void OnMenuViewSnr();
	afx_msg void OnUpdateMenuViewSnr(CCmdUI *pCmdUI);
	afx_msg void OnMenuViewClose();
	afx_msg void OnUpdateMenuViewClose(CCmdUI *pCmdUI);
	//////////////////////////////////////////////////////////////////////////
	afx_msg void OnMenuAboutInstruction();
	afx_msg void OnMenuAboutDev();
	afx_msg void OnMenuClearAll();
	afx_msg void OnUpdateMenuClearAll(CCmdUI *pCmdUI);
	//////////////////////////////////////////////////////////////////////////
	void OnUpdateInformation(int nID, CGlobalVariant* data);
public:
	virtual LRESULT OnAnswerInfoCOD(WPARAM wParam, LPARAM lParam);//����ԭʼ��������
	virtual LRESULT OnAnswerInfoEPH(WPARAM wParam, LPARAM lParam);//����������Ϣ
	virtual LRESULT OnAnswerInfoION(WPARAM wParam, LPARAM lParam);//���ǵ�������
	virtual LRESULT OnAnswerInfoALM(WPARAM wParam, LPARAM lParam);//����������Ϣ
	virtual LRESULT OnAnswerInfoJAL(WPARAM wParam, LPARAM lParam);//���Ǽ�Լ������Ϣ
	virtual LRESULT OnAnswerInfoCOM(WPARAM wParam, LPARAM lParam);//�˿�������Ϣ
	virtual LRESULT OnAnswerInfoMOD(WPARAM wParam, LPARAM lParam);//��λ��ʱģʽ��Ϣ
	virtual LRESULT OnAnswerInfoPOS(WPARAM wParam, LPARAM lParam);//��λ�����ٽ����Ϣ
	virtual LRESULT OnAnswerInfoRAN(WPARAM wParam, LPARAM lParam);//α�ࡢ�ز�����������Ϣ
	virtual LRESULT OnAnswerInfoREF(WPARAM wParam, LPARAM lParam);//ʱ�ղο���Ϣ
	virtual LRESULT OnAnswerInfoGSV(WPARAM wParam, LPARAM lParam);//������Ϣ
	virtual LRESULT OnAnswerInfoSTA(WPARAM wParam, LPARAM lParam);//�ն˹���״̬��Ϣ
	virtual LRESULT OnAnswerInfoTIM(WPARAM wParam, LPARAM lParam);//��ʱ�����Ϣ
	virtual LRESULT OnAnswerInfoXPV(WPARAM wParam, LPARAM lParam);//�ѿ������궨λ�����ٽ����Ϣ
	virtual LRESULT OnAnswerInfoSRC(WPARAM wParam, LPARAM lParam);//ԭʼ����
	virtual LRESULT OnAnswerInfoSNR(WPARAM wParam, LPARAM lParam);//�ź�ǿ��
	virtual LRESULT OnAnswerInfoGBS(WPARAM wParam, LPARAM lParam);//���������
	virtual LRESULT OnAnswerInfoFrame(WPARAM wParam, LPARAM lParam);//һ֡ԭʼ����
	virtual LRESULT OnAnswerInfoSIM(WPARAM wParam, LPARAM lParam);//SIM����Ϣ
	virtual LRESULT OnAnswerInfoVER(WPARAM wParam, LPARAM lParam);//�汾��Ϣ
	virtual LRESULT OnAnswerInfoPAO(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnAnswerInfoCHD(WPARAM wParam, LPARAM lParam);//�ŵ�������Ϣ

    //�̱�������
    virtual LRESULT OnShowCmdInfo(WPARAM wParam, LPARAM lParam);

    virtual LRESULT OnUpdateGGAPOSInfo(WPARAM wParam, LPARAM lParam);
	//////////////////////////////////////////////////////////////////////////
	virtual LRESULT OnAnswerCalPositionPOS(WPARAM wParam, LPARAM lParam);//��λ����λ��������Ϣ
	afx_msg void OnMenuTestStart();
	afx_msg void OnUpdateMenuTestStart(CCmdUI *pCmdUI);
	afx_msg void OnMenuTestStop();
	afx_msg void OnUpdateMenuTestStop(CCmdUI *pCmdUI);
	//////////////////////////////////////////////////////////////////////////
	virtual LRESULT OnEmulatorSetupMOD(WPARAM wParam, LPARAM lParam);//���ö�λģʽ
	virtual LRESULT OnEmulatorSetupLOG(WPARAM wParam, LPARAM lParam);//�������
	virtual LRESULT OnEmulatorSetupSTA(WPARAM wParam, LPARAM lParam);//���õ��Ʒ�ʽ
	afx_msg void OnMenuShowTest();
	afx_msg void OnUpdateMenuShowTest(CCmdUI *pCmdUI);
	afx_msg void OnMenuShowChd();
	afx_msg void OnUpdateMenuShowChd(CCmdUI *pCmdUI);
    afx_msg void OnMenuEpq();
    afx_msg void OnSendTcq();
    afx_msg void OnMenuQrq();
    afx_msg void OnMenuShowCmd();
    afx_msg void OnMenuShowGga();
    afx_msg void OnUpdateMenuShowGga(CCmdUI *pCmdUI);
    afx_msg void OnMenuViewGpsSnr();
    afx_msg void OnUpdateMenuViewGpsSnr(CCmdUI *pCmdUI);
    afx_msg void OnMenuViewGlSnr();
    afx_msg void OnUpdateMenuViewGlSnr(CCmdUI *pCmdUI);
    afx_msg void OnMenuViewGaSnr();
    afx_msg void OnUpdateMenuViewGaSnr(CCmdUI *pCmdUI);
    afx_msg void OnMenuSendCmd();
    afx_msg void OnUpdateMenuSendCmd(CCmdUI *pCmdUI);
};

typedef struct SPlaySpeedBar
{
	int nFreq;
}SPlaySpeedBar;