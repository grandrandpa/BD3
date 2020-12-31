// RadarPointView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "RadarPointView.h"


// RadarPointView

IMPLEMENT_DYNCREATE(RadarPointView, CBCGPFormView)

RadarPointView::RadarPointView()
	: CBCGPFormView(RadarPointView::IDD)
{
    //m_strCaption = _T("Radar Point Style");
	//m_bShowLabels = TRUE;

	//m_bShowAxisX = 1;
	//m_bShowAxisY = 1;
	//m_nMarkerType = 0;
	//m_nMarkerSize = 0;

	//m_bInterlaced = FALSE;

    m_bShowGP = TRUE;
    m_bShowBD = TRUE;
    m_bShowGL = TRUE;
    m_bShowGA = TRUE;

#ifdef _XTP_INCLUDE_TOOLKIT
	m_hBrush.CreateSolidBrush(RGB(227,239,255));
#else
	m_hBrush.CreateSolidBrush(RGB(255, 255, 255));
#endif
}

RadarPointView::~RadarPointView()
{
}

void RadarPointView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);

    //DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	//DDX_Check(pDX, IDC_CHECK_AXISX, m_bShowAxisX);
	//DDX_Check(pDX, IDC_CHECK_AXISY, m_bShowAxisY);
	//DDX_Check(pDX, IDC_CHECK_INTERLACED, m_bInterlaced);

    DDX_Check(pDX, IDC_CHECK_GPS, m_bShowGP);
	DDX_Check(pDX, IDC_CHECK_BD, m_bShowBD);
    DDX_Check(pDX, IDC_CHECK_GL, m_bShowGL);
	DDX_Check(pDX, IDC_CHECK_GA, m_bShowGA);

	//DDX_CBIndex(pDX, IDC_COMBO_MARKER_TYPE, m_nMarkerType);
	//DDX_CBIndex(pDX, IDC_COMBO_MARKER_SIZE, m_nMarkerSize);

    DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
}

BEGIN_MESSAGE_MAP(RadarPointView, CBCGPFormView)
	//ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnCheckShowLabels)

	//ON_CBN_SELCHANGE(IDC_COMBO_MARKER_SIZE, OnCbnSelchangeComboMarkerSize)
	//ON_CBN_SELCHANGE(IDC_COMBO_MARKER_TYPE, OnCbnSelchangeComboMarkerType)

	//ON_BN_CLICKED(IDC_CHECK_AXISX, OnCheckShowAxisX)
	//ON_BN_CLICKED(IDC_CHECK_AXISY, OnCheckShowAxisY)
	//ON_BN_CLICKED(IDC_CHECK_INTERLACED, OnCheckInterlaced)

	ON_WM_PAINT()
	ON_WM_CTLCOLOR()

    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_CHECK_BD, &RadarPointView::OnClickedCheckBd)
    ON_BN_CLICKED(IDC_CHECK_GA, &RadarPointView::OnClickedCheckGa)
    ON_BN_CLICKED(IDC_CHECK_GL, &RadarPointView::OnClickedCheckGl)
    ON_BN_CLICKED(IDC_CHECK_GPS, &RadarPointView::OnClickedCheckGps)
END_MESSAGE_MAP()


// RadarPointView diagnostics

#ifdef _DEBUG
void RadarPointView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

#ifndef _WIN32_WCE
void RadarPointView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}
#endif
#endif //_DEBUG

BOOL RadarPointView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CBCGPFormView::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	return TRUE;
}

// RadarPointView message handlers
void RadarPointView::OnCheckShowLabels() 
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartRadarPointSeriesStyle* pStyle = (CXTPChartRadarPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		//pStyle->GetLabel()->SetVisible(m_bShowLabels);
	}
}

void RadarPointView::OnCheckShowAxisX() 
{
	UpdateData();

	CXTPChartRadarDiagram* pDiagram = (CXTPChartRadarDiagram*)m_wndChartControl.GetContent()->GetPrimaryDiagram();

	//pDiagram->GetAxisX()->SetVisible(m_bShowAxisX);
}

void RadarPointView::OnCheckShowAxisY() 
{
	UpdateData();

	CXTPChartRadarDiagram* pDiagram = (CXTPChartRadarDiagram*)m_wndChartControl.GetContent()->GetPrimaryDiagram();

	//pDiagram->GetAxisY()->SetVisible(m_bShowAxisY);
}

void RadarPointView::OnCheckInterlaced() 
{
	UpdateData();

	CXTPChartRadarDiagram* pDiagram = (CXTPChartRadarDiagram*)m_wndChartControl.GetContent()->GetPrimaryDiagram();

	//pDiagram->GetAxisX()->SetInterlaced(m_bInterlaced);
}


void RadarPointView::OnCbnSelchangeComboMarkerSize()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartRadarPointSeriesStyle* pStyle = (CXTPChartRadarPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		//pStyle->GetMarker()->SetSize(8 + 2 * m_nMarkerSize);

		// Solid Mode
		// pStyle->GetMarker()->GetFillStyle()->SetFillMode(xtpChartFillSolid);
	}
}


void RadarPointView::OnCbnSelchangeComboMarkerType()
{
	UpdateData();

	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();

	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
	{
		CXTPChartRadarPointSeriesStyle* pStyle = (CXTPChartRadarPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();

		//pStyle->GetMarker()->SetType((XTPChartMarkerType)m_nMarkerType);
	}
}

void RadarPointView::Updata(int radar_input_buf_len, Radar_Input * radar_input_buf)
{
// 	pSeries_no->GetPoints()->RemoveAll();
// 	for(int i = 0; i < radar_input_buf_len; i++)
// 	{
// 		CXTPChartSeriesPoint* rpView = new CXTPChartSeriesPoint(radar_input_buf[i].x, radar_input_buf[i].y);
// 		pSeries_no->GetPoints()->Add(rpView);
// 		rpView->SetLabelText(radar_input_buf[i].prn);
// 	}
}

BOOL RadarPointView::CreateView(CWnd* pParent, CCreateContext* pContext)
{
    CRect rect(0,0,300,300);

    if (!Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
        rect, pParent, AFX_IDW_PANE_FIRST, pContext))
    {
        TRACE0("Warning: couldn't create RadarPointView!\n");
        return FALSE;
    }

    return TRUE;
}

void RadarPointView::OnInitialUpdate()
{
	CBCGPFormView::OnInitialUpdate();

	ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	m_wndGroupBoxLabels.SubclassDlgItem(IDC_STATIC_LABELS, this);	


	CXTPWindowRect rc(m_wndChartControl);//m_wndChartControl
	ScreenToClient(rc);
	m_nTopGap = rc.top;
	m_nLeftGap = rc.left;

    CreateChart();

    //int i;

	//CComboBox* pComboBoxSize = (CComboBox*)GetDlgItem(IDC_COMBO_MARKER_SIZE);
	//for (i = 8; i <= 30; i += 2)
	//{
	//	CString strSize;
	//	strSize.Format(_T("%d"), i);

	//	pComboBoxSize->AddString(strSize);
	//}
	//pComboBoxSize->SetCurSel(0);

	
#ifdef _XTP_INCLUDE_TOOLKIT
	m_wndGroupBoxLabels.SetTheme(xtpControlThemeResource);
#endif
}

void RadarPointView::CreateChart()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	pContent->GetLegend()->SetVisible(TRUE);
	//CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	//pTitle->SetText(_T("Constellation"));
	CString strPalette = "BLACK";
	m_wndChartControl.GetContent()->GetAppearance()->LoadPalette(_T("CHART_PALETTE_") + strPalette);
	m_wndChartControl.GetContent()->OnChartChanged();
	m_wndChartControl.GetContent()->GetAppearance()->LoadAppearance(_T("CHART_APPEARANCE_BLACK"));
	m_wndChartControl.GetContent()->OnChartChanged();

	pSeries_BD = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries_BD->SetArgumentScaleType(xtpChartScaleNumerical);
	pSeries_BD->SetName(_T("BD"));
	CXTPChartRadarPointSeriesStyle* BDstyle = new CXTPChartRadarPointSeriesStyle();
	BDstyle->SetColor(CXTPChartColor::Red);
	BDstyle->GetMarker()->SetType(xtpChartMarkerStar);
	BDstyle->GetMarker()->SetSize(18);
	BDstyle->GetLabel()->SetLineLength(-11);//-11
	BDstyle->GetLabel()->SetShowLines(FALSE);
	pSeries_BD->SetStyle(BDstyle);

	pSeries_GPS = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries_GPS->SetArgumentScaleType(xtpChartScaleNumerical);
	pSeries_GPS->SetName(_T("GPS"));
	CXTPChartRadarPointSeriesStyle* GPSstyle = new CXTPChartRadarPointSeriesStyle();
	GPSstyle->SetColor(CXTPChartColor::LimeGreen);
	GPSstyle->GetMarker()->SetType(xtpChartMarkerCircle);
	GPSstyle->GetMarker()->SetSize(18);
	GPSstyle->GetLabel()->SetLineLength(-11);
	GPSstyle->GetLabel()->SetShowLines(FALSE);
	pSeries_GPS->SetStyle(GPSstyle);

	pSeries_GLONASS = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries_GLONASS->SetArgumentScaleType(xtpChartScaleNumerical);
	pSeries_GLONASS->SetName(_T("GLONASS"));
	CXTPChartRadarPointSeriesStyle* GLstyle = new CXTPChartRadarPointSeriesStyle();
	GLstyle->SetColor(CXTPChartColor::Purple);
	GLstyle->GetMarker()->SetType(xtpChartMarkerPentagon);
	GLstyle->GetMarker()->SetSize(18);
	GLstyle->GetLabel()->SetLineLength(-11);
	GLstyle->GetLabel()->SetShowLines(FALSE);
	pSeries_GLONASS->SetStyle(GLstyle);

    pSeries_GA = pContent->GetSeries()->Add(new CXTPChartSeries());
	pSeries_GA->SetArgumentScaleType(xtpChartScaleNumerical);
	pSeries_GA->SetName(_T("Galileo"));
	CXTPChartRadarPointSeriesStyle* GAstyle = new CXTPChartRadarPointSeriesStyle();
	GAstyle->SetColor(CXTPChartColor::SteelBlue);
	GAstyle->GetMarker()->SetType(xtpChartMarkerDiamond);
	GAstyle->GetMarker()->SetSize(18);
	GAstyle->GetLabel()->SetLineLength(-11);
	GAstyle->GetLabel()->SetShowLines(FALSE);
	pSeries_GA->SetStyle(GAstyle);

	CXTPChartRadarDiagram* pDiagram = DYNAMIC_DOWNCAST(CXTPChartRadarDiagram, pSeries_BD->GetDiagram());
	ASSERT (pDiagram);

	pDiagram->GetAxisX()->SetInterlaced(FALSE);//m_bInterlaced
	pDiagram->GetAxisX()->GetRange()->SetMinValue(0);
	pDiagram->GetAxisX()->GetRange()->SetMaxValue(330);
	pDiagram->GetAxisX()->GetRange()->SetAutoRange(FALSE);

	pDiagram->GetAxisY()->GetRange()->SetMinValue(0);
	pDiagram->GetAxisY()->GetRange()->SetMaxValue(90);
	pDiagram->GetAxisY()->SetReversed(TRUE);
	pDiagram->GetAxisY()->GetRange()->SetAutoRange(FALSE);

    pDiagram->GetAxisX()->SetGridSpacing(30);
	pDiagram->GetAxisX()->SetGridSpacingAuto(FALSE);//FALSE

	pDiagram->SetBackgroundColor(CXTPChartColor::Black);//


// 	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();
// 	for (int i = 0; i < pSeriesCollection->GetCount(); i++)
// 	{
// 		CXTPChartRadarPointSeriesStyle* pStyle = (CXTPChartRadarPointSeriesStyle*)pSeriesCollection->GetAt(i)->GetStyle();
// 		pStyle->GetLabel()->SetBackColor(TRANSPARENT);
// 	}
}

void RadarPointView::BD_Radar(int  sat_num, Radar_Input * radar_input_buf)
{
		pSeries_BD->GetPoints()->RemoveAll();
		for(int i = 0; i < sat_num; i++)
		{
			if(radar_input_buf[i].soln == TRUE)
			{
				CXTPChartSeriesPoint* rpView = new CXTPChartSeriesPoint(radar_input_buf[i].az, radar_input_buf[i].elev);
				pSeries_BD->GetPoints()->Add(rpView);
				rpView->SetLabelText(radar_input_buf[i].prn);
			}
			else
			{
				CXTPChartSeriesPoint* rpView = new CXTPChartSeriesPoint(radar_input_buf[i].az, radar_input_buf[i].elev);
				pSeries_BD->GetPoints()->Add(rpView)->SetColor(CXTPChartColor::Transparent);//Transparent
				rpView->SetLabelText(radar_input_buf[i].prn);
			}		 	
		}
}

void RadarPointView::GPS_Radar(int  sat_num, Radar_Input * radar_input_buf)
{
	pSeries_GPS->GetPoints()->RemoveAll();
	for(int i = 0; i < sat_num; i++)
	{
		if(radar_input_buf[i].soln == TRUE)
		{
			CXTPChartSeriesPoint* rpView = new CXTPChartSeriesPoint(radar_input_buf[i].az, radar_input_buf[i].elev);
			pSeries_GPS->GetPoints()->Add(rpView);
			rpView->SetLabelText(radar_input_buf[i].prn);
		}
		else
		{
			CXTPChartSeriesPoint* rpView = new CXTPChartSeriesPoint(radar_input_buf[i].az, radar_input_buf[i].elev);
			pSeries_GPS->GetPoints()->Add(rpView)->SetColor(CXTPChartColor::Transparent);////LimeGreen
			rpView->SetLabelText(radar_input_buf[i].prn);
		}		 	
	}
}

void RadarPointView::GLONASS_Radar(int  sat_num, Radar_Input * radar_input_buf)
{
	pSeries_GLONASS->GetPoints()->RemoveAll();
	for(int i = 0; i < sat_num; i++)
	{
		if(radar_input_buf[i].soln == TRUE)
		{
			CXTPChartSeriesPoint* rpView = new CXTPChartSeriesPoint(radar_input_buf[i].az, radar_input_buf[i].elev);
			pSeries_GLONASS->GetPoints()->Add(rpView);
			rpView->SetLabelText(radar_input_buf[i].prn);
		}
		else
		{
			CXTPChartSeriesPoint* rpView = new CXTPChartSeriesPoint(radar_input_buf[i].az, radar_input_buf[i].elev);
			pSeries_GLONASS->GetPoints()->Add(rpView)->SetColor(CXTPChartColor::Transparent);////Purple
			rpView->SetLabelText(radar_input_buf[i].prn);
		}		 	
	}
}

void RadarPointView::GA_Radar(int sat_num, Radar_Input * radar_input_buf)
{
	pSeries_GA->GetPoints()->RemoveAll();
	for(int i = 0; i < sat_num; i++)
	{
		if(radar_input_buf[i].soln == TRUE)
		{
			CXTPChartSeriesPoint* rpView = new CXTPChartSeriesPoint(radar_input_buf[i].az, radar_input_buf[i].elev);
			pSeries_GA->GetPoints()->Add(rpView);
			rpView->SetLabelText(radar_input_buf[i].prn);
		}
		else
		{
			CXTPChartSeriesPoint* rpView = new CXTPChartSeriesPoint(radar_input_buf[i].az, radar_input_buf[i].elev);
			pSeries_GA->GetPoints()->Add(rpView)->SetColor(CXTPChartColor::Transparent);////SteelBlue
			rpView->SetLabelText(radar_input_buf[i].prn);
		}		 	
	}
}

void RadarPointView::ClearAllSat()
{
	pSeries_GLONASS->GetPoints()->RemoveAll();
	pSeries_GPS->GetPoints()->RemoveAll();
	pSeries_BD->GetPoints()->RemoveAll();
    pSeries_GA->GetPoints()->RemoveAll();
}

void RadarPointView::DealData(NmeaAllData* data)
{
    Radar_Input gps_bi[48] = {0};
	Radar_Input bd_bi[48] = {0};
	Radar_Input glonass_bi[48] = {0};
    Radar_Input ga_bi[48] = {0};

    int i = 0;
	int gp_gsv = data->GP_view_C;
	int bd_gsv = data->BD_view_C;
	int gl_gsv = data->GL_view_C;
    int ga_gsv = data->GA_view_C;

    UpdateData();

    if(gp_gsv>0)
	{
		for (i=0; i < gp_gsv; i++)
		{
			//sprintf(bi[i].prn, "%sGP", nmea_char_save.GP_view[i].PRN);
			int x = atof(data->GP_view[i].fangwei_cour);
			if (x>360 || x<0)
			{
				gps_bi[i].az = 0;
			} 
			else
			{
				gps_bi[i].az = x;
			}

			int y = atof(data->GP_view[i].yang_cour);
			if (y>90 || y<0)
			{
				gps_bi[i].elev = 0;
			} 
			else
			{
				gps_bi[i].elev = y;
			}

			gps_bi[i].soln = TRUE;//data->GP_SEQ[i];
			sprintf(gps_bi[i].prn, "%s", data->GP_view[i].PRN);
			//sprintf(gps_bi[i].freq_num, noavtel_char_save.GP_SignalType[i]);
			//gps_bi[i].state = noavtel_char_save.GP_soln[i];

		}
		if(m_bShowGP)
		{
			GPS_Radar(gp_gsv, gps_bi);
		}
			
	}
	else
	{
		gp_gsv = data->GP_view_C;
	}

    if(bd_gsv>0)
	{
		for (i=0; i < bd_gsv; i++)
		{
			//sprintf(bi[i].prn, "%sGP", nmea_char_save.GP_view[i].PRN);
			int x = atof(data->BD_view[i].fangwei_cour);
			if (x>360 || x<0)
			{
				bd_bi[i].az = 0;
			} 
			else
			{
				bd_bi[i].az = x;
			}

			int y = atof(data->BD_view[i].yang_cour);
			if (y>90 || y<0)
			{
				bd_bi[i].elev = 0;
			} 
			else
			{
				bd_bi[i].elev = y;
			}

			bd_bi[i].soln = TRUE;//data->BD_SEQ[i];
			sprintf(bd_bi[i].prn, "%s", data->BD_view[i].PRN);

		}
		if(m_bShowBD)
		{
			BD_Radar(bd_gsv, bd_bi);
		}
	}
	else
	{
		bd_gsv = data->BD_view_C;
	}


    if(gl_gsv>0)
	{
		for (i=0; i < gl_gsv; i++)
		{
			//sprintf(bi[i].prn, "%sGP", nmea_char_save.GP_view[i].PRN);
			int x = atof(data->GL_view[i].fangwei_cour);
			if (x>360 || x<0)
			{
				glonass_bi[i].az = 0;
			} 
			else
			{
				glonass_bi[i].az = x;
			}

			int y = atof(data->GL_view[i].yang_cour);
			if (y>90 || y<0)
			{
				glonass_bi[i].elev = 0;
			} 
			else
			{
				glonass_bi[i].elev = y;
			}

			glonass_bi[i].soln = TRUE;//data->GL_SEQ[i];
			sprintf(glonass_bi[i].prn, "%s", data->GL_view[i].PRN);

		}
		if(m_bShowGL)
		{
			GLONASS_Radar(gl_gsv, glonass_bi);
		}
	}
	else
	{
		gl_gsv = data->GL_view_C;
	}


    if(ga_gsv>0)
	{
		for (i=0; i < ga_gsv; i++)
		{
			//sprintf(bi[i].prn, "%sGP", nmea_char_save.GP_view[i].PRN);
			int x = atof(data->GA_view[i].fangwei_cour);
			if (x>360 || x<0)
			{
				ga_bi[i].az = 0;
			} 
			else
			{
				ga_bi[i].az = x;
			}

			int y = atof(data->GA_view[i].yang_cour);
			if (y>90 || y<0)
			{
				ga_bi[i].elev = 0;
			} 
			else
			{
				ga_bi[i].elev = y;
			}

			ga_bi[i].soln = TRUE;//data->GA_SEQ[i];
			sprintf(ga_bi[i].prn, "%s", data->GA_view[i].PRN);

		}
		if(m_bShowGA)
		{
			GA_Radar(ga_gsv, ga_bi);
		}
	}
	else
	{
		ga_gsv = data->GA_view_C;
	}
}


void RadarPointView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
// 	m_wndChartControl.GetContent()->GetAppearance()->LoadPalette(_T("CHART_PALETTE__BLACK"));
// 	m_wndChartControl.GetContent()->OnChartChanged();
// 	m_wndChartControl.GetContent()->GetAppearance()->LoadAppearance(_T("CHART_APPEARANCE_BLACK"));
// 
// 	m_wndChartControl.GetContent()->OnChartChanged();

	CRect   rect;  
	GetClientRect(rect);
	dc.FillSolidRect(rect,RGB(0,0,0));   //设置整个背景为黑色
}


HBRUSH RadarPointView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CBCGPFormView::OnCtlColor(pDC, pWnd, nCtlColor);
// 	m_wndChartControl.GetContent()->GetAppearance()->LoadPalette(_T("CHART_PALETTE__BLACK"));
// 	m_wndChartControl.GetContent()->OnChartChanged();
// 	m_wndChartControl.GetContent()->GetAppearance()->LoadAppearance(_T("CHART_APPEARANCE_BLACK"));
// 
// 	m_wndChartControl.GetContent()->OnChartChanged();

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_BTN)//
	{
		//pDC->SetTextColor(RGB(0,0,0));
		//pDC->SetBkColor(RGB(0,0,0));

 		//HBRUSH b=CreateSolidBrush(RGB(0,0,0));
 		//return b;

		//return m_hBrush;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

BOOL RadarPointView::OnEraseBkgnd(CDC* pDC)
{
	return CBCGPFormView::OnEraseBkgnd(pDC);
}

void RadarPointView::OnSize(UINT nType, int cx, int cy)
{
    CBCGPFormView::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here

    TRACE("----RadarPointView::OnSize cx:%d, cy:%d\n", cx, cy);

	if (!m_wndGroupBoxLabels.GetSafeHwnd())
		return;

	CXTPWindowRect rc(m_wndGroupBoxLabels);
	int nWidth = cx;//max(m_totalDev.cx, cx);
    int nHeight = cy;

    TRACE("----RadarPointView::OnSize RC--- nWidth:%d, m_nLeftGap:%d\n", nWidth ,m_nLeftGap);
	//max(m_totalDev.cy, cy);

    m_wndChartControl.SetWindowPos(0, 0, 0, nWidth - 2 * m_nLeftGap, nHeight - m_nTopGap - m_nLeftGap,  SWP_NOMOVE | SWP_NOZORDER);//
    m_wndGroupBoxLabels.SetWindowPos(0, 0, 0, nWidth - 2 * m_nLeftGap , rc.Height(),  SWP_NOMOVE | SWP_NOZORDER);//nWidth - 2 * m_nLeftGap //

}


void RadarPointView::OnClickedCheckBd()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    if(!m_bShowBD)
    {
        pSeries_BD->GetPoints()->RemoveAll();
    }

}


void RadarPointView::OnClickedCheckGa()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    if(!m_bShowGA)
    {
        pSeries_GA->GetPoints()->RemoveAll();
    }
}


void RadarPointView::OnClickedCheckGl()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    if(!m_bShowGL)
    {
        pSeries_GLONASS->GetPoints()->RemoveAll();
    }
}


void RadarPointView::OnClickedCheckGps()
{
    // TODO: Add your control notification handler code here
    UpdateData();
    if(!m_bShowGP)
    {
        pSeries_GPS->GetPoints()->RemoveAll();
    }
}
