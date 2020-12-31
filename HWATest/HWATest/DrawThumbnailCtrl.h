#pragma once


// CDrawThumbnailCtrl
#define MAX_DRAW_RAN_NUM 3
#define CHART_THUMBNAIL_NUM	3

class CDrawThumbnailCtrl : public CWnd
{
	DECLARE_DYNAMIC(CDrawThumbnailCtrl)

public:
	CDrawThumbnailCtrl();
	virtual ~CDrawThumbnailCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL Create(const RECT &rect, CWnd *pParentWnd, UINT nControlID, int type);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg LRESULT OnChartMouseDown(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnChartMouseUp(WPARAM wp, LPARAM lp);
	void Repos();
	void UpdateChartColorTheme(int nTheme);
private:
	CBCGPVisualContainerCtrl m_wndContainer;
	CBCGPChartVisualObject*	m_pCharts[CHART_THUMBNAIL_NUM];
	CBCGPChartSeries*	m_arSeries[CHART_THUMBNAIL_NUM];
	double				m_maxValue[CHART_THUMBNAIL_NUM];
	double				m_minValue[CHART_THUMBNAIL_NUM];
	CBCGPChartAxis*		m_pAxisY[CHART_THUMBNAIL_NUM];
	bool				m_bFirstUpdate;
	CBCGPChartVisualObject*	m_pClickedChart;
	CBCGPChartVisualObject*	m_pExpandedChart;
	CRITICAL_SECTION m_Lock;//ÁÙ½çÇø
	int					m_nType;

	CBCGPTextGaugeImpl*		m_pInfoText;
	// Attributes
	virtual CBCGPBaseVisualCtrl* GetCtrl()
	{
		return &m_wndContainer;
	}
public:
	void Redraw();
	void Clear();
	void AddChartData(PackageXYZ xyz);
};


