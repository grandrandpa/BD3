// ShowSnrView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ShowSnrView.h"
#include "BarView.h"


// CShowSnrView

IMPLEMENT_DYNAMIC(CShowSnrView, CBCGPDockingControlBar)

CShowSnrView::CShowSnrView()
: m_nCurrentTime(0)
{
	//Clear();
	m_dwRecvFlag = 0;

#if 1
    m_pContext = NULL;
    CRuntimeClass* pFactory = RUNTIME_CLASS(CBarView);
    m_pFormView = (CBarView *)(pFactory->CreateObject());
#endif
}

CShowSnrView::~CShowSnrView()
{
	Clear();
}


BEGIN_MESSAGE_MAP(CShowSnrView, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CShowSnrView message handlers

void CShowSnrView::OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL /*bDisableIfNoHndler*/)
{
}


int CShowSnrView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
# if 1
	// TODO:  Add your specialized creation code here
    if (m_pFormView != NULL)
	{
		m_pFormView->CreateView(this, m_pContext);
	}

    m_pFormView->CreateChartBD();
    RecalcLayout();

#else


	CRect rectDummy;
	rectDummy.SetRectEmpty ();
	if (!m_wndTabs.Create (CBCGPTabWnd::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("Failed to create output tab window\n");
		return -1;      // fail to create
	}
	// 创建输出窗格:
	m_wndSnrB2.SetChartTitle(0, "B2a 信号强度");
	m_wndSnrB2.SetChartTitle(1, "B2b_I 信号强度");
	m_wndSnrB2.SetChartTitle(2, "B2b_Q 信号强度");
	m_wndSnrB3.SetChartTitle(0, "B3I 信号强度");
	m_wndSnrB3.SetChartTitle(1, "B3Q 信号强度");
	m_wndSnrB3.SetChartTitle(2, "B3C 信号强度");
	m_wndSnrB3.SetChartTitle(3, "B3A 信号强度");
	//m_wndSnrBs.SetChartTitle(0, "Bs 信号强度");
	m_wndSnrBs.SetChartTitle(1, "B3AE 信号强度");
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	if (!m_wndSnrB1.Create(rectDummy, &m_wndTabs, 1, 4) ||
		!m_wndSnrB2.Create(rectDummy, &m_wndTabs, 2, 3) ||
		!m_wndSnrB3.Create(rectDummy, &m_wndTabs, 3, 4) )
        //||!m_wndSnrBs.Create(rectDummy, &m_wndTabs, 4, 2))
	{
		TRACE0("未能创建柱状图视图\n");
		return -1;      // 未能创建
	}
	// 将列表窗口附加到选项卡:
	m_wndTabs.AddTab(&m_wndSnrB1,  "B1 信号强度", 123);
	m_wndTabs.AddTab(&m_wndSnrB2,  "B2 信号强度", 124);
	m_wndTabs.AddTab(&m_wndSnrB3,  "B3 信号强度", 125);
	//m_wndTabs.AddTab(&m_wndSnrBs,  "Bs 信号强度", 126);
#endif

	return 0;
}


void CShowSnrView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
#if 1
    if (m_pFormView->GetSafeHwnd ())
	{
		m_pFormView->SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

#else
	m_wndTabs.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	Reset();
#endif
}

void CShowSnrView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
#if 1
    CRect rect;
	GetClientRect (rect);

	dc.FillSolidRect (rect, ::GetSysColor (COLOR_3DFACE));
#else
	 //Do not call CBCGPDockingControlBar::OnPaint() for painting messages
	CBCGPMemDC memDC (dc, this);
	//memDC.IsMemDC();
	CDC* pDC = &memDC.GetDC();	
	CRect rectClient; 	
	GetClientRect(&rectClient);	
	pDC->FillSolidRect(&rectClient,RGB(231,241,254));

#endif
}

void CShowSnrView::RefreshView(NmeaAllData* data, int branch)
{

    try{
        m_pFormView->DealData(data);
    } 
    catch(...)
    {
    }


#if 0
    if (data->sys != BD)
    {
        return ;
    }

    int id=0;
	double elv=0,azi=0;

    int count = strtod(data->GSV_in_use, NULL);//save_GSV.satellite_view

    BD2_GSV	GSVPack;
    GSVPack.num = count;
    for (int i=0; i<count; i++)
	{
        id = atoi(data->BD_view[i].PRN);
        elv = strtod(data->BD_view[i].yang_cour, NULL);
        azi = strtod(data->BD_view[i].fangwei_cour, NULL);

		GSVPack.id[i] = id;
		GSVPack.elv[i] = elv;
		GSVPack.azi[i] = azi;
        GSVPack.snr[i] = strtod(data->BD_view[i].CN0, NULL);

	}
    GSVPack.system_type = data->sys;

	double curTime = data->week*SECONDS_IN_WEEK+int(data->tow);
	try
	{
		if (curTime - m_nCurrentTime > 0)//保证时间往前推进
		{
			if ((m_dwRecvFlag & 0x01) == 0)
				m_wndSnrB1.ClearChartData(0);
			if (((m_dwRecvFlag >> 1) & 0x01) == 0)
				m_wndSnrB1.ClearChartData(1);
			if (((m_dwRecvFlag >> 2) & 0x01) == 0)
				m_wndSnrB1.ClearChartData(2);
			if (((m_dwRecvFlag >> 3) & 0x01) == 0)
				m_wndSnrB1.ClearChartData(3);
			if (((m_dwRecvFlag >> 4) & 0x01) == 0)
				m_wndSnrB2.ClearChartData(0);
			if (((m_dwRecvFlag >> 5) & 0x01) == 0)
				m_wndSnrB2.ClearChartData(1);
			if (((m_dwRecvFlag >> 6) & 0x01) == 0)
				m_wndSnrB2.ClearChartData(2);
			if (((m_dwRecvFlag >> 7) & 0x01) == 0)
				m_wndSnrB3.ClearChartData(0);
			if (((m_dwRecvFlag >> 8) & 0x01) == 0)
				m_wndSnrB3.ClearChartData(1);
			if (((m_dwRecvFlag >> 9) & 0x01) == 0)
				m_wndSnrB3.ClearChartData(2);
			if (((m_dwRecvFlag >> 10) & 0x01) == 0)
				m_wndSnrB3.ClearChartData(3);
			if (((m_dwRecvFlag >> 11) & 0x01) == 0)
				m_wndSnrBs.ClearChartData(0);
			if (((m_dwRecvFlag >> 12) & 0x01) == 0)
				m_wndSnrBs.ClearChartData(1);
			m_dwRecvFlag = 0;
		}
		m_nCurrentTime = curTime;
		switch (branch)
		{
		case CH_B1I:
			m_dwRecvFlag |= (1 << 0)&0xFFFF;
			m_wndSnrB1.SetChartData(0, &GSVPack);
			break;
		case CH_B1Q:
			m_dwRecvFlag |= (1 << 1)&0xFFFF;
			m_wndSnrB1.SetChartData(1, &GSVPack);
			break;
		case CH_B1C:
			m_dwRecvFlag |= (1 << 2)&0xFFFF;
			m_wndSnrB1.SetChartData(2, &GSVPack);
			break;
		case CH_B1A:
			m_dwRecvFlag |= (1 << 3)&0xFFFF;
			m_wndSnrB1.SetChartData(3, &GSVPack);
			break;
		case CH_B2a:
			m_dwRecvFlag |= (1 << 4)&0xFFFF;
			m_wndSnrB2.SetChartData(0, &GSVPack);
			break;
		case CH_B2b:
			m_dwRecvFlag |= (1 << 5)&0xFFFF;
			m_wndSnrB2.SetChartData(1, &GSVPack);
			break;
		case CH_B2:
			m_dwRecvFlag |= (1 << 6)&0xFFFF;
			m_wndSnrB2.SetChartData(2, &GSVPack);
			break;
		case CH_B3I:
			m_dwRecvFlag |= (1 << 7)&0xFFFF;
			m_wndSnrB3.SetChartData(0, &GSVPack);
			break;
		case CH_B3Q:
			m_dwRecvFlag |= (1 << 8)&0xFFFF;
			m_wndSnrB3.SetChartData(1, &GSVPack);
			break;
		case CH_B3C:
			m_dwRecvFlag |= (1 << 9)&0xFFFF;
			m_wndSnrB3.SetChartData(2, &GSVPack);
			break;
		case CH_B3A:
			m_dwRecvFlag |= (1 << 10)&0xFFFF;
			m_wndSnrB3.SetChartData(3, &GSVPack);
			break;
		case CH_Bs:
			m_dwRecvFlag |= (1 << 11)&0xFFFF;
			m_wndSnrBs.SetChartData(0, &GSVPack);
			break;
		case CH_B3AE:
			m_dwRecvFlag |= (1 << 12)&0xFFFF;
			m_wndSnrBs.SetChartData(1, &GSVPack);
			break;
		default:
			break;
		}
		Reset();
	}
	catch (...)
	{
	}
#endif

}

void CShowSnrView::Reset(void)
{
	//m_wndSnrB1.Reset();
	//m_wndSnrB2.Reset();
	//m_wndSnrB3.Reset();
	//m_wndSnrBs.Reset();
}
void CShowSnrView::Clear()
{
	//m_wndSnrB1.Clear();
	//m_wndSnrB2.Clear();
	//m_wndSnrB3.Clear();
	//m_wndSnrBs.Clear();
}
void CShowSnrView::Clean()
{
	//m_wndSnrB1.Clean();
	//m_wndSnrB2.Clean();
	//m_wndSnrB3.Clean();
	//m_wndSnrBs.Clean();
}

