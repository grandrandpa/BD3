// DrawGraphsWnd.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "DrawThumbnailCtrl.h"


// CDrawThumbnailCtrl

IMPLEMENT_DYNAMIC(CDrawThumbnailCtrl, CWnd)

CDrawThumbnailCtrl::CDrawThumbnailCtrl()
{
	for (int i = 0; i < CHART_THUMBNAIL_NUM; i++)
	{
		m_maxValue[i] = 0;
		m_minValue[i] = 0;
		m_pCharts[i] = NULL;
		m_arSeries[i] = NULL;
	}
	m_nType = 0;
	m_bFirstUpdate = true;
	m_pClickedChart = NULL;
	m_pExpandedChart = NULL;
	m_pInfoText = NULL;
	InitializeCriticalSection(&m_Lock);

}

CDrawThumbnailCtrl::~CDrawThumbnailCtrl()
{
}


BEGIN_MESSAGE_MAP(CDrawThumbnailCtrl, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(BCGM_ON_CHART_MOUSE_DOWN, OnChartMouseDown)
	ON_REGISTERED_MESSAGE(BCGM_ON_CHART_MOUSE_UP, OnChartMouseUp)
END_MESSAGE_MAP()



static BCGPChartCategory categories[] =
{
	BCGPChartLine,
	BCGPChartPie,
	BCGPChartPyramid,
	BCGPChartColumn,
	BCGPChartBar,
	BCGPChartArea,
	BCGPChartBubble,
	BCGPChartDoughnut,
	BCGPChartColumn3D,
	BCGPChartBar3D,
	BCGPChartArea3D,
};

static CString arChartTitle[] = 
{
	"纬度/伪距曲线",
	"经度/载波相位曲线",
	"高程/多普勒曲线"
};
// CDrawThumbnailCtrl message handlers

BOOL CDrawThumbnailCtrl::Create(const RECT &rect, CWnd *pParentWnd, UINT nControlID, int type)
{
	if (GetSafeHwnd())
		return FALSE;
	m_nType = type;
	BOOL bRes = CWnd::Create( NULL, NULL,WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rect, pParentWnd,nControlID );
	return bRes;
}

int CDrawThumbnailCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CString str;
	CRect rect;
	rect.SetRectEmpty();
	// TODO:  Add your specialized creation code here ID_DRAW_THUMNAILS_CONTAINER
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_SIZE_DYNAMIC;
	if (!m_wndContainer.Create(rect, this, 2, dwStyle))
	{
		return -1;
	}

	//初始化Container
	CBCGPVisualContainer* pContainer = m_wndContainer.GetVisualContainer();
	ASSERT_VALID(pContainer);

	m_pInfoText = new CBCGPTextGaugeImpl(_T(""), CBCGPColor::DarkGreen, pContainer);
	m_pInfoText->SetFillBrush(CBCGPBrush(CBCGPColor::LightBlue));

	CBCGPTextFormat tf = m_pInfoText->GetTextFormat();
	tf.SetTextAlignment(CBCGPTextFormat::BCGP_TEXT_ALIGNMENT_LEADING);

	m_pInfoText->SetTextFormat(tf);

	for (int i = 0; i < CHART_THUMBNAIL_NUM; i++)
	{
		m_pCharts[i] = new CBCGPChartVisualObject(pContainer);
		m_pCharts[i]->SetThumbnailMode();

		/*m_pCharts[i]->SetChartType(BCGPChartLine);*/
		m_pCharts[i]->SetChartTitle(arChartTitle[i]);
		//m_pCharts[i]->ShowAxisIntervalInterlacing(BCGP_CHART_X_PRIMARY_AXIS, FALSE);
		m_pCharts[i]->SetChartType (BCGPChartHistoricalLine, BCGP_CT_SIMPLE, FALSE);
		m_pCharts[i]->SetLegendPosition(BCGPChartLayout::LP_NONE);
		CBCGPChartAxis* pXAxis = m_pCharts[i]->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
		ASSERT_VALID(pXAxis);
		pXAxis->m_axisLabelType = CBCGPChartAxis::ALT_NO_LABELS;
		pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_NO_TICKS;
		pXAxis->SetFixedIntervalWidth(20, 5);
		m_pCharts[i]->ShowAxisIntervalInterlacing(BCGP_CHART_Y_PRIMARY_AXIS);
		m_arSeries[i] = m_pCharts[i]->CreateSeries(arChartTitle[i]);
	}
	m_pAxisY[0] = m_pCharts[0]->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	m_pAxisY[1] = m_pCharts[1]->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	m_pAxisY[2] = m_pCharts[2]->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	if(m_nType == 2)
		m_pAxisY[0]->SetFixedDisplayRange(20000000., 40000000.);
	else
	{
		m_pAxisY[0]->SetDisplayUnits(0.5);
		m_pAxisY[1]->SetDisplayUnits(0.5);
		m_pAxisY[2]->SetDisplayUnits(0.5);
	}
	

	Repos();
	UpdateChartColorTheme(21);//21 = CT_BLACK_AND_BLUE

	return 0;
}

void CDrawThumbnailCtrl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_wndContainer.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	Repos();
}
void CDrawThumbnailCtrl::Redraw()
{
	m_pCharts[0]->SetDirty(TRUE, TRUE);
	m_pCharts[1]->SetDirty(TRUE, TRUE);
	m_pCharts[2]->SetDirty(TRUE, TRUE);
	m_pCharts[0]->Redraw();
	m_pCharts[1]->Redraw();
	m_pCharts[2]->Redraw();
}
void CDrawThumbnailCtrl::Clear()
{
	EnterCriticalSection(&m_Lock);
	m_bFirstUpdate = true;
	m_arSeries[0]->RemoveAllDataPoints();
	m_arSeries[1]->RemoveAllDataPoints();
	m_arSeries[2]->RemoveAllDataPoints();
	Redraw();
	LeaveCriticalSection(&m_Lock);
}
void CDrawThumbnailCtrl::AddChartData(PackageXYZ xyz)
{
	EnterCriticalSection(&m_Lock);
	m_arSeries[0]->AddDataPoint(xyz.x);
	m_arSeries[1]->AddDataPoint(xyz.y);
	m_arSeries[2]->AddDataPoint(xyz.z);
	Redraw();
	LeaveCriticalSection(&m_Lock);
}
void CDrawThumbnailCtrl::UpdateChartColorTheme(int nTheme)
{
	CBCGPBrush brFill;

	for (int i = 0; i < CHART_THUMBNAIL_NUM; i++)
	{
		if (m_pCharts[i] != NULL)
		{
			if (nTheme < 0)
			{
				m_pCharts[i]->SetColors(theApp.GetCustomTheme(nTheme));
			}
			else
			{
				m_pCharts[i]->SetColors((CBCGPChartTheme::ChartTheme)nTheme);
			}

			if (brFill.IsEmpty())
			{
				brFill = m_pCharts[i]->GetDiagramFillColor();
			}
		}
	}

	m_wndContainer.GetVisualContainer()->SetFillBrush(brFill);
	m_wndContainer.RedrawWindow();
}

void CDrawThumbnailCtrl::Repos()
{
	CBCGPVisualContainer* pContainer = m_wndContainer.GetVisualContainer();
	ASSERT_VALID(pContainer);

	if (pContainer == NULL || pContainer->GetCount() == 0)
	{
		return;
	}

	const double cx = 400;
	const double cy = 300;
	const double margin = 10;
	const double captionHeight = 10;

	CBCGPRect rect = pContainer->GetRect();

	CBCGPRect rectCaption = rect;
	rectCaption.bottom = rectCaption.top + captionHeight + margin;

	m_pInfoText->SetRect(rectCaption);

	rect.top = rectCaption.bottom;

	if (m_pExpandedChart != NULL)
	{
		ASSERT_VALID(m_pExpandedChart);
		m_pExpandedChart->SetRect(rect);

		m_pInfoText->SetText(_T("Click chart to return back to the thumbnail view."));
	}
	else
	{
		m_pInfoText->SetText(_T("Click thumbnail to see a full-size chart."));
	}

	double x = rect.left;
	double y = rect.top;

	for (int i = 0; i < CHART_THUMBNAIL_NUM; i++)
	{
		if (m_pExpandedChart != NULL)
		{
			if (m_pCharts[i] != m_pExpandedChart)
			{
				m_pCharts[i]->SetVisible(FALSE);
			}
		}
		else
		{
			m_pCharts[i]->SetVisible();

			CBCGPRect rectChart(x, y, x + cx, y + cy);
			rectChart.DeflateRect(margin / 2, margin / 2);

			m_pCharts[i]->SetRect(rectChart);

			x += cx;

			if (x + cx > rect.right)
			{
				x = rect.left;
				y += cy;
			}
		}
	}

	m_wndContainer.RedrawWindow();
}

LRESULT CDrawThumbnailCtrl::OnChartMouseDown(WPARAM /*wp*/, LPARAM lp)
{
	if (m_pExpandedChart != NULL)
	{
		ASSERT_VALID(m_pExpandedChart);

		m_pExpandedChart->SetThumbnailMode();
		m_pExpandedChart = NULL;
		Repos();

		return 0;
	}

	CBCGPVisualContainer* pContainer = m_wndContainer.GetVisualContainer();
	ASSERT_VALID(pContainer);

	BCGPChartHitInfo* pHitInfo = (BCGPChartHitInfo*)lp;
	if (pHitInfo->m_nMouseButton != 0)
	{
		return 0;
	}

	m_pClickedChart = DYNAMIC_DOWNCAST(CBCGPChartVisualObject, pContainer->GetFromPoint(pHitInfo->m_ptHit));
	return 1;
}

LRESULT CDrawThumbnailCtrl::OnChartMouseUp(WPARAM /*wp*/, LPARAM lp)
{
	CBCGPVisualContainer* pContainer = m_wndContainer.GetVisualContainer();
	ASSERT_VALID(pContainer);

	BCGPChartHitInfo* pHitInfo = (BCGPChartHitInfo*)lp;
	if (pHitInfo->m_nMouseButton != 0)
	{
		return 0;
	}

	CBCGPChartVisualObject* pClickedChart = DYNAMIC_DOWNCAST(CBCGPChartVisualObject, pContainer->GetFromPoint(pHitInfo->m_ptHit));

	if (m_pClickedChart != pClickedChart || pClickedChart == NULL)
	{
		m_pClickedChart = NULL;
		return 0;
	}

	m_pExpandedChart = m_pClickedChart;
	m_pExpandedChart->SetThumbnailMode(FALSE);

	m_pClickedChart = NULL;

	Repos();

	return 1;
}
