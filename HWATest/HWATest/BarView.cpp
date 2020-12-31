// BarView.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "BarView.h"


// CBarView

IMPLEMENT_DYNCREATE(CBarView, CBCGPFormView)

CBarView::CBarView()
	: CBCGPFormView(CBarView::IDD)
{
#ifdef _XTP_INCLUDE_TOOLKIT
	m_hBrush.CreateSolidBrush(RGB(227,239,255));
#else
	m_hBrush.CreateSolidBrush(RGB(255, 255, 255));
#endif
}

CBarView::~CBarView()
{
}

void CBarView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_CHARTCONTROL, m_wndChartControl);
}

BEGIN_MESSAGE_MAP(CBarView, CFormView)
    ON_WM_PAINT()
    ON_WM_CTLCOLOR()
    ON_WM_SIZE()
END_MESSAGE_MAP()


// CBarView diagnostics

#ifdef _DEBUG
void CBarView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBarView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBarView message handlers


void CBarView::OnInitialUpdate()
{
    CFormView::OnInitialUpdate();

    // TODO: Add your specialized code here and/or call the base class
    ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	//m_wndGroupBoxLabels.SubclassDlgItem(IDC_STATIC_LABELS, this);	


	CXTPWindowRect rc(m_wndChartControl);
	ScreenToClient(rc);
	m_nTopGap = rc.top;
	m_nLeftGap = rc.left;

    //CreateChartGPS(); //just test
	
#ifdef _XTP_INCLUDE_TOOLKIT
	m_wndGroupBoxLabels.SetTheme(xtpControlThemeResource);
#endif
}

BOOL CBarView::CreateView(CWnd* pParent, CCreateContext* pContext)
{
    CRect rect(0,0,300,300);

    if (!Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
        rect, pParent, AFX_IDW_PANE_FIRST, pContext))
    {
        TRACE0("Warning: couldn't create CBarView!\n");
        return FALSE;
    }

    return TRUE;
}


void CBarView::CreateChartGPS()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	pContent->GetLegend()->SetVisible(TRUE);
	//CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	//pTitle->SetText(_T("GPS"));
	CString strPalette = "BLACK";
	m_wndChartControl.GetContent()->GetAppearance()->LoadPalette(_T("CHART_PALETTE_") + strPalette);
	m_wndChartControl.GetContent()->OnChartChanged();
	m_wndChartControl.GetContent()->GetAppearance()->LoadAppearance(_T("CHART_APPEARANCE_BLACK"));
	m_wndChartControl.GetContent()->OnChartChanged();

	pSeries_L1 = pContent->GetSeries()->Add(new CXTPChartSeries()); //L1 频点的柱状图
	pSeries_L1->SetName(_T("L1"));
	CXTPChartBarSeriesStyle* L1style = new CXTPChartBarSeriesStyle();
	L1style->SetColor(CXTPChartColor::DeepSkyBlue);
	pSeries_L1->SetStyle(L1style);
// 	for(int i=0;i<12;i++)
// 	{
// 		pSeries_L1->GetPoints()->Add(new CXTPChartSeriesPoint(i+1,0));
// 	}
	

	pSeries_L2 = pContent->GetSeries()->Add(new CXTPChartSeries()); //L2 频点的柱状图
	pSeries_L2->SetName(_T("L2"));
	CXTPChartBarSeriesStyle* L2style = new CXTPChartBarSeriesStyle();
	L2style->SetColor(CXTPChartColor::Purple);
	pSeries_L2->SetStyle(L2style);
// 	for(int i=0;i<12;i++)
// 	{
// 		pSeries_L2->GetPoints()->Add(new CXTPChartSeriesPoint(i+1,0));
// 	}

	pSeries_L5 = pContent->GetSeries()->Add(new CXTPChartSeries()); //L5 频点的柱状图
	pSeries_L5->SetName(_T("L5"));
	CXTPChartBarSeriesStyle* L5style = new CXTPChartBarSeriesStyle();
	L5style->SetColor(CXTPChartColor::HotPink);
	pSeries_L5->SetStyle(L5style);
// 	for(int i=0;i<12;i++)
// 	{
// 		pSeries_L5->GetPoints()->Add(new CXTPChartSeriesPoint(i+1,0));
// 	}

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries_L1->GetDiagram());
	ASSERT (pDiagram);
	pDiagram->GetAxisX()->GetLabel()->SetFont(CXTPChartFont::GetTahoma12());
	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("PRN"));
	pDiagram->GetAxisY()->GetLabel()->SetFont(CXTPChartFont::GetTahoma12());
	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("CN0"));
	pDiagram->GetAxisY()->GetRange()->SetAutoRange(FALSE);
	pDiagram->GetAxisY()->GetRange()->SetMaxValue(60);
	pDiagram->GetAxisY()->GetRange()->SetMinValue(0);
	pDiagram->GetAxisX()->GetInterlacedFillStyle()->SetFillMode(xtpChartFillEmpty);
}

void CBarView::CreateChartBD()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	pContent->GetLegend()->SetVisible(TRUE);
	//CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	//pTitle->SetText(_T("BD"));
	CString strPalette = "BLACK";
	m_wndChartControl.GetContent()->GetAppearance()->LoadPalette(_T("CHART_PALETTE_") + strPalette);
	m_wndChartControl.GetContent()->OnChartChanged();
	m_wndChartControl.GetContent()->GetAppearance()->LoadAppearance(_T("CHART_APPEARANCE_BLACK"));

	m_wndChartControl.GetContent()->OnChartChanged();

	pSeries_B1 = pContent->GetSeries()->Add(new CXTPChartSeries()); //B1 频点的柱状图
	pSeries_B1->SetName(_T("B1"));
	CXTPChartBarSeriesStyle* B1style = new CXTPChartBarSeriesStyle();
	B1style->SetColor(CXTPChartColor::DeepSkyBlue);
	pSeries_B1->SetStyle(B1style);


	pSeries_B2 = pContent->GetSeries()->Add(new CXTPChartSeries()); //B2 频点的柱状图
	pSeries_B2->SetName(_T("B2"));
	CXTPChartBarSeriesStyle* B2style = new CXTPChartBarSeriesStyle();
	B2style->SetColor(CXTPChartColor::Purple);
	pSeries_B2->SetStyle(B2style);

	pSeries_B3 = pContent->GetSeries()->Add(new CXTPChartSeries()); //B2 频点的柱状图
	pSeries_B3->SetName(_T("B3"));
	CXTPChartBarSeriesStyle* B3style = new CXTPChartBarSeriesStyle();
	B3style->SetColor(CXTPChartColor::Red);
	pSeries_B3->SetStyle(B3style);

	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries_B1->GetDiagram());
	ASSERT (pDiagram);
	pDiagram->GetAxisX()->GetLabel()->SetFont(CXTPChartFont::GetTahoma12());
	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("PRN"));
	pDiagram->GetAxisY()->GetLabel()->SetFont(CXTPChartFont::GetTahoma12());
	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("CN0"));
	pDiagram->GetAxisY()->GetRange()->SetAutoRange(FALSE);
	pDiagram->GetAxisY()->GetRange()->SetMaxValue(60);
	pDiagram->GetAxisY()->GetRange()->SetMinValue(0);
	pDiagram->GetAxisX()->GetInterlacedFillStyle()->SetFillMode(xtpChartFillEmpty);
// 	pDiagram->GetAxisY()->SetInterlaced(FALSE);
// 	pDiagram->GetAxisX()->SetInterlaced(FALSE);
}

void CBarView::CreateChartGL()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	pContent->GetLegend()->SetVisible(TRUE);
	//CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	//pTitle->SetText(_T("GLONASS"));
	CString strPalette = "BLACK";
	m_wndChartControl.GetContent()->GetAppearance()->LoadPalette(_T("CHART_PALETTE_") + strPalette);
	m_wndChartControl.GetContent()->OnChartChanged();
	m_wndChartControl.GetContent()->GetAppearance()->LoadAppearance(_T("CHART_APPEARANCE_BLACK"));

	m_wndChartControl.GetContent()->OnChartChanged();

	pSeries_G1 = pContent->GetSeries()->Add(new CXTPChartSeries()); //B1 频点的柱状图
	pSeries_G1->SetName(_T("G1"));
	CXTPChartBarSeriesStyle* G1style = new CXTPChartBarSeriesStyle();
	G1style->SetColor(CXTPChartColor::DeepSkyBlue);
	pSeries_G1->SetStyle(G1style);


	pSeries_G2 = pContent->GetSeries()->Add(new CXTPChartSeries()); //B2 频点的柱状图
	pSeries_G2->SetName(_T("G2"));
	CXTPChartBarSeriesStyle* G2style = new CXTPChartBarSeriesStyle();
	G2style->SetColor(CXTPChartColor::Purple);
	pSeries_G2->SetStyle(G2style);


	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries_G1->GetDiagram());
	ASSERT (pDiagram);
	pDiagram->GetAxisX()->GetLabel()->SetFont(CXTPChartFont::GetTahoma12());
	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("PRN"));
	pDiagram->GetAxisY()->GetLabel()->SetFont(CXTPChartFont::GetTahoma12());
	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("CN0"));
	pDiagram->GetAxisY()->GetRange()->SetAutoRange(FALSE);
	pDiagram->GetAxisY()->GetRange()->SetMaxValue(60);
	pDiagram->GetAxisY()->GetRange()->SetMinValue(0);
	pDiagram->GetAxisX()->GetInterlacedFillStyle()->SetFillMode(xtpChartFillEmpty);
}

void CBarView::CreateChartGA()
{
	CXTPChartContent* pContent = m_wndChartControl.GetContent();
	pContent->GetLegend()->SetVisible(TRUE);
	//CXTPChartTitle* pTitle = pContent->GetTitles()->Add(new CXTPChartTitle());
	//pTitle->SetText(_T("Galileo"));
	CString strPalette = "BLACK";
	m_wndChartControl.GetContent()->GetAppearance()->LoadPalette(_T("CHART_PALETTE_") + strPalette);
	m_wndChartControl.GetContent()->OnChartChanged();
	m_wndChartControl.GetContent()->GetAppearance()->LoadAppearance(_T("CHART_APPEARANCE_BLACK"));

	m_wndChartControl.GetContent()->OnChartChanged();

	pSeries_E1 = pContent->GetSeries()->Add(new CXTPChartSeries()); //E1 频点的柱状图
	pSeries_E1->SetName(_T("E1"));
	CXTPChartBarSeriesStyle* E1style = new CXTPChartBarSeriesStyle();
	E1style->SetColor(CXTPChartColor::DeepSkyBlue);
	pSeries_E1->SetStyle(E1style);


	pSeries_E5 = pContent->GetSeries()->Add(new CXTPChartSeries()); //E5 频点的柱状图
	pSeries_E5->SetName(_T("E5"));
	CXTPChartBarSeriesStyle* E5style = new CXTPChartBarSeriesStyle();
	E5style->SetColor(CXTPChartColor::Purple);
	pSeries_E5->SetStyle(E5style);


	CXTPChartDiagram2D* pDiagram = DYNAMIC_DOWNCAST(CXTPChartDiagram2D, pSeries_E1->GetDiagram());
	ASSERT (pDiagram);
	pDiagram->GetAxisX()->GetLabel()->SetFont(CXTPChartFont::GetTahoma12());
	pDiagram->GetAxisX()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisX()->GetTitle()->SetText(_T("PRN"));
	pDiagram->GetAxisY()->GetLabel()->SetFont(CXTPChartFont::GetTahoma12());
	pDiagram->GetAxisY()->GetTitle()->SetVisible(TRUE);
	pDiagram->GetAxisY()->GetTitle()->SetText(_T("CN0"));
	pDiagram->GetAxisY()->GetRange()->SetAutoRange(FALSE);
	pDiagram->GetAxisY()->GetRange()->SetMaxValue(60);
	pDiagram->GetAxisY()->GetRange()->SetMinValue(0);
	pDiagram->GetAxisX()->GetInterlacedFillStyle()->SetFillMode(xtpChartFillEmpty);
}

void CBarView::GPS_BarSeries(int sat_num, Bar_Input * bar_input_buf)
{
/*	char unused[5];*/
	
	pSeries_L1->GetPoints()->RemoveAll();
	pSeries_L2->GetPoints()->RemoveAll();
	pSeries_L5->GetPoints()->RemoveAll();
	for(int i = 0; i < sat_num; i++)
	{
		if(!strcmp(bar_input_buf[i].freq_num,"L1"))
		{
			if(bar_input_buf[i].state == TRUE)
			{
				pSeries_L1->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));
			}
			else
			{
				pSeries_L1->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
			}
		}

	}

	
// 	for(int i=0;i<(12-sat_num);i++)
// 	{
// 		sprintf(unused, "n/a%d", i);
// 		pSeries_L1->GetPoints()->Add(new CXTPChartSeriesPoint(unused,0));
// 		pSeries_L2->GetPoints()->Add(new CXTPChartSeriesPoint(unused,0));
// 		pSeries_L5->GetPoints()->Add(new CXTPChartSeriesPoint(unused,0));
// 	}

}

void CBarView::BD_BarSeries(int sat_num, Bar_Input * bar_input_buf)
{
	pSeries_B1->GetPoints()->RemoveAll();
	pSeries_B2->GetPoints()->RemoveAll();
	pSeries_B3->GetPoints()->RemoveAll();

	for(int i = 0; i < sat_num; i++)
	{
		if(!strcmp(bar_input_buf[i].freq_num,"B1"))
		{
			if(bar_input_buf[i].state == TRUE)
			{
				pSeries_B1->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));
			}
			else
			{
				pSeries_B1->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
			}
		}
// 		else if(!strcmp(bar_input_buf[i].freq_num,"B2"))
// 		{
// 			if(bar_input_buf[i].state == TRUE)
// 			{
// 				pSeries_B2->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));
// 			}
// 			else
// 			{
// 				pSeries_B2->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
// 			}
// 		}

	}

}

void CBarView::GL_BarSeries(int sat_num, Bar_Input * bar_input_buf)
{
	pSeries_G1->GetPoints()->RemoveAll();
	pSeries_G2->GetPoints()->RemoveAll();

	for(int i = 0; i < sat_num; i++)
	{
		if(!strcmp(bar_input_buf[i].freq_num,"G1"))
		{
			if(bar_input_buf[i].state == TRUE)
			{
				pSeries_G1->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));
			}
			else
			{
				pSeries_G1->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
			}
		}
// 		else if(!strcmp(bar_input_buf[i].freq_num,"G2"))
// 		{
// 			if(bar_input_buf[i].state == TRUE)
// 			{
// 				pSeries_G2->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));
// 			}
// 			else
// 			{
// 				pSeries_G2->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
// 			}
// 		}
	}

}

void CBarView::GA_BarSeries(int sat_num, Bar_Input * bar_input_buf)
{
	pSeries_E1->GetPoints()->RemoveAll();
	pSeries_E5->GetPoints()->RemoveAll();

	for(int i = 0; i < sat_num; i++)
	{
		if(!strcmp(bar_input_buf[i].freq_num,"E1"))
		{
			if(bar_input_buf[i].state == TRUE)
			{
				pSeries_E1->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));
			}
			else
			{
				pSeries_E1->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
			}
		}
// 		else if(!strcmp(bar_input_buf[i].freq_num,"G2"))
// 		{
// 			if(bar_input_buf[i].state == TRUE)
// 			{
// 				pSeries_G2->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));
// 			}
// 			else
// 			{
// 				pSeries_G2->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
// 			}
// 		}
	}

}


void CBarView::GPS_BarSeries_Nov(int sat_num, Bar_Input * bar_input_buf)
{
	pSeries_L1->GetPoints()->RemoveAll();
	pSeries_L2->GetPoints()->RemoveAll();
	pSeries_L5->GetPoints()->RemoveAll();
	if(sat_num>0)
	{
		for(int i = 0; i < sat_num; i++)
		{
			if(!strcmp(bar_input_buf[i].freq_num,"GPS_L1"))
			{
				if(bar_input_buf[i].state == TRUE)
				{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_L1->GetPoints()->Add(rpView);
					//pSeries_L1->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));			
				}
				else
				{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_L1->GetPoints()->Add(rpView)->SetColor(CXTPChartColor::Transparent);
					//pSeries_L1->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
				}
			}
			else if(!strcmp(bar_input_buf[i].freq_num,"GPS_L2"))
			{
			 	if(bar_input_buf[i].state == TRUE)
			 	{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_L2->GetPoints()->Add(rpView);
			 		//pSeries_L2->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));
			 	}
			 	else
			 	{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_L2->GetPoints()->Add(rpView)->SetColor(CXTPChartColor::Transparent);
			 		//pSeries_L2->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
			 	}
			}
			else if(!strcmp(bar_input_buf[i].freq_num,"GPS_L5"))
			{
			 	if(bar_input_buf[i].state == TRUE)
			 	{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_L5->GetPoints()->Add(rpView);
			 		//pSeries_L5->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));
			 	}
			 	else
			 	{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_L5->GetPoints()->Add(rpView)->SetColor(CXTPChartColor::Transparent);
			 		//pSeries_L5->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
			 	}
			}
			else
			{
					pSeries_L1->GetPoints()->RemoveAll();
					pSeries_L2->GetPoints()->RemoveAll();
					pSeries_L5->GetPoints()->RemoveAll();
			}
		}
	}


// 	for(int i=0;i<(12-sat_num);i++)
// 	{
// 		sprintf(unused, "n/a%d", i);
// 		pSeries_L1->GetPoints()->Add(new CXTPChartSeriesPoint(unused,0));
// 		pSeries_L2->GetPoints()->Add(new CXTPChartSeriesPoint(unused,0));
// 		pSeries_L5->GetPoints()->Add(new CXTPChartSeriesPoint(unused,0));
// 	}

}


void CBarView::BD_BarSeries_Nov(int sat_num, Bar_Input * bar_input_buf)
{
	pSeries_B1->GetPoints()->RemoveAll();
	pSeries_B2->GetPoints()->RemoveAll();
	pSeries_B3->GetPoints()->RemoveAll();
	// 	pSeries_L2->GetPoints()->RemoveAll();
	// 	pSeries_L5->GetPoints()->RemoveAll();
	if(sat_num>0)
	{
		for(int i = 0; i < sat_num; i++)
		{
			if(!strcmp(bar_input_buf[i].freq_num,"BD_B1"))
			{
				if(bar_input_buf[i].state == TRUE)
				{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_B1->GetPoints()->Add(rpView);
					//pSeries_L1->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));			
				}
				else
				{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_B1->GetPoints()->Add(rpView)->SetColor(CXTPChartColor::Transparent);
					//pSeries_L1->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
				}
			}
			else if(!strcmp(bar_input_buf[i].freq_num,"BD_B2"))
			{
				if(bar_input_buf[i].state == TRUE)
				{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_B2->GetPoints()->Add(rpView);
					//pSeries_L2->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));
				}
				else
				{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_B2->GetPoints()->Add(rpView)->SetColor(CXTPChartColor::Transparent);
					//pSeries_L2->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
				}
			}
			else if(!strcmp(bar_input_buf[i].freq_num,"BD_B3"))
			{
				if(bar_input_buf[i].state == TRUE)
				{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_B3->GetPoints()->Add(rpView);
					//pSeries_L2->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));
				}
				else
				{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_B3->GetPoints()->Add(rpView)->SetColor(CXTPChartColor::Transparent);
					//pSeries_L2->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
				}
			}
			else
			{
				pSeries_B1->GetPoints()->RemoveAll();
				pSeries_B2->GetPoints()->RemoveAll();
				pSeries_B3->GetPoints()->RemoveAll();
			}
		}
	}


}

void CBarView::GL_BarSeries_Nov(int sat_num, Bar_Input * bar_input_buf)
{
	pSeries_G1->GetPoints()->RemoveAll();
	pSeries_G2->GetPoints()->RemoveAll();
	// 	pSeries_L2->GetPoints()->RemoveAll();
	// 	pSeries_L5->GetPoints()->RemoveAll();
	if(sat_num>0)
	{
		for(int i = 0; i < sat_num; i++)
		{
			if(!strcmp(bar_input_buf[i].freq_num,"GL_G1"))
			{
				if(bar_input_buf[i].state == TRUE)
				{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_G1->GetPoints()->Add(rpView);
					//pSeries_L1->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));			
				}
				else
				{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_G1->GetPoints()->Add(rpView)->SetColor(CXTPChartColor::Transparent);
					//pSeries_L1->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
				}
			}
			else if(!strcmp(bar_input_buf[i].freq_num,"GL_G2"))
			{
				if(bar_input_buf[i].state == TRUE)
				{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_G2->GetPoints()->Add(rpView);
					//pSeries_L2->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0));
				}
				else
				{
					rpView = new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0);
					pSeries_G2->GetPoints()->Add(rpView)->SetColor(CXTPChartColor::Transparent);
					//pSeries_L2->GetPoints()->Add(new CXTPChartSeriesPoint(bar_input_buf[i].prn, bar_input_buf[i].cn0))->SetColor(CXTPChartColor::Transparent);
				}
			}
			else
			{
				pSeries_G1->GetPoints()->RemoveAll();
				pSeries_G2->GetPoints()->RemoveAll();
			}
		}
	}

}

void CBarView::DealData(NmeaAllData* data)
{
    CBarView*	gps_View  = NULL;
	CBarView*	bd_View  = NULL;
	CBarView*	gl_View  = NULL;
    CBarView*	ga_View  = NULL;
	
    Bar_Input gps_bi[24] = {0};
	Bar_Input bd_bi[24] = {0};
	Bar_Input gl_bi[24] = {0};
    Bar_Input ga_bi[24] = {0};

    int i = 0;
	int gp_gsv = data->GP_view_C;
	int bd_gsv = data->BD_view_C;
	int gl_gsv = data->GL_view_C;
    int ga_gsv = data->GA_view_C;

    UpdateData();

    if(gp_gsv>0)
    {
		for (i=0; i<gp_gsv; i++)
		{
			//sprintf(bi[i].prn, "%sGP", nmea_char_save.GP_view[i].PRN);
			double cno_num = atof(data->GP_view[i].CN0);
			sprintf(gps_bi[i].prn, "%s", data->GP_view[i].PRN);
			sprintf(gps_bi[i].freq_num, "L1");
			if (cno_num>60 || cno_num<0)
			{
				gps_bi[i].cn0 = 0;
			} 
			else
			{
				gps_bi[i].cn0 = cno_num;
			}

            //TODO 后续加入
			//if(data->GP_SEQ[i] == FALSE)
			{
				//gps_bi[i].state = false;
			}
			//else
			{
				gps_bi[i].state = true;
			}
		}

		//if(NMEA_NOVATEL_SHOW)
		{
			GPS_BarSeries(gp_gsv,/*gp_num, gp_gsv-gp_num, bd_num, bd_gsv-bd_num,*/gps_bi);
		}    
    }


    if(bd_gsv>0)
	{
		for (int j=0; j<bd_gsv; j++,i++)
		{
			//sprintf(bi[i].prn, "%sBD", nmea_char_save.BD_view[j].PRN);
			sprintf(bd_bi[i].prn, "%s", data->BD_view[i].PRN);
			double cno_num = atof(data->BD_view[j].CN0);
			sprintf(bd_bi[i].freq_num, "B1");

			if (cno_num>60 || cno_num<0)
			{
				bd_bi[i].cn0 = 0;
			} 
			else
			{
				bd_bi[i].cn0 = cno_num;
			}

            //TODO 后续加入
			//if(data->BD_SEQ[i] == FALSE)
			//{
			//	bd_bi[i].state = false;
			//}
			//else
			//{
				bd_bi[i].state = true;
			//}
		}
		//if(NMEA_NOVATEL_SHOW)
		{
			BD_BarSeries(bd_gsv,/*gp_num, gp_gsv-gp_num, bd_num, bd_gsv-bd_num,*/bd_bi);
		}
	}


    if(gl_gsv>0)
	{
		for (int j=0; j<gl_gsv; j++,i++)
		{
			//sprintf(bi[i].prn, "%sBD", nmea_char_save.BD_view[j].PRN);
			sprintf(gl_bi[i].prn, "%s", data->GL_view[i].PRN);
			double cno_num = atof(data->GL_view[j].CN0);
			sprintf(gl_bi[i].freq_num, "G1");

			if (cno_num>60 || cno_num<0)
			{
				gl_bi[i].cn0 = 0;
			} 
			else
			{
				gl_bi[i].cn0 = cno_num;
			}

            gl_bi[i].state = true;
			//if(data->GL_SEQ[i] == FALSE)
			//{
			//	gl_bi[i].state = false;
			//}
			//else
			//{
			//	gl_bi[i].state = true;
			//}
		}
		//if(NMEA_NOVATEL_SHOW)
		{
			GL_BarSeries(gl_gsv,/*gp_num, gp_gsv-gp_num, bd_num, bd_gsv-bd_num,*/gl_bi);
		}
	}


    if(ga_gsv>0)
	{
		for (int j=0; j<ga_gsv; j++,i++)
		{
			//sprintf(bi[i].prn, "%sBD", nmea_char_save.BD_view[j].PRN);
			sprintf(ga_bi[i].prn, "%s", data->GA_view[i].PRN);
			double cno_num = atof(data->GA_view[j].CN0);
			sprintf(ga_bi[i].freq_num, "E1");

			if (cno_num>60 || cno_num<0)
			{
				ga_bi[i].cn0 = 0;
			} 
			else
			{
				ga_bi[i].cn0 = cno_num;
			}


            ga_bi[i].state = true;
			//if(data->GL_SEQ[i] == FALSE)
			//{
			//	gl_bi[i].state = false;
			//}
			//else
			//{
			//	gl_bi[i].state = true;
			//}
		}
		//if(NMEA_NOVATEL_SHOW)
		{
			GA_BarSeries(ga_gsv,/*gp_num, gp_gsv-gp_num, bd_num, bd_gsv-bd_num,*/ga_bi);
		}
	}
}


void CBarView::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    // TODO: Add your message handler code here
    // Do not call CFormView::OnPaint() for painting messages
}


HBRUSH CBarView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CBCGPFormView::OnCtlColor(pDC, pWnd, nCtlColor);

    // TODO:  Change any attributes of the DC here
    if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_BTN)
	{
		pDC->SetBkMode(TRANSPARENT);
		return m_hBrush;
	}
    // TODO:  Return a different brush if the default is not desired
    return hbr;
}


void CBarView::OnSize(UINT nType, int cx, int cy)
{
    CFormView::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
    if (!m_wndChartControl.GetSafeHwnd())
		return;

	CXTPWindowRect rc(m_wndChartControl);

	int nWidth = cx;//max(m_totalDev.cx, cx);
	//m_wndGroupBoxLabels.SetWindowPos(0, 0, 0, nWidth - 2 * m_nLeftGap, rc.Height(), SWP_NOMOVE | SWP_NOZORDER);

	int nHeight = cy;//max(m_totalDev.cy, cy);
	m_wndChartControl.SetWindowPos(0, 0, 0, nWidth - 2 * m_nLeftGap, nHeight - m_nTopGap - m_nLeftGap, SWP_NOMOVE | SWP_NOZORDER);
}
