#pragma once


// CDrawChartBar
class CDrawChartBar : public CWnd
{
	DECLARE_DYNAMIC(CDrawChartBar)

public:
	CDrawChartBar();
	virtual ~CDrawChartBar();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnUserClear();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
private:
	void DrawChart(CDC* pDC, int chartType, int l, int w, int h, int top);
	//afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	void ReDrawAll(CDC* pDC, CRect rect);
private:
	int			m_nVisibleWindowType;
	BD2_GSV		m_arPackSNR[4];
	CString		m_strChartTitle[4];

    CXTPChartSeries* pSeries_GPS;
public:
	BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nControlID, int nType=4);
	void SetChartTitle(int index, CString strTitle);
	void SetChartData(int index, BD2_GSV* data);
	void ClearChartData(int index);
	void Reset(void);
	void Clean();
	void Clear(void);
};


