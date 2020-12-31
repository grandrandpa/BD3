#pragma once

#include "BaseView.h"

// CBarView form view

class CBarView : public CBCGPFormView//CFormView
{
	DECLARE_DYNCREATE(CBarView)

protected:
	CBarView();           // protected constructor used by dynamic creation
	virtual ~CBarView();

public:
	enum { IDD = IDD_FORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
    CXTPChartSeries* pSeries_L1;
	CXTPChartSeries* pSeries_L2;
	CXTPChartSeries* pSeries_L5;
	CXTPChartSeries* pSeries_B1;
	CXTPChartSeries* pSeries_B2;
	CXTPChartSeries* pSeries_B3;
	CXTPChartSeries* pSeries_G1;
	CXTPChartSeries* pSeries_G2;
    CXTPChartSeries* pSeries_E1;
	CXTPChartSeries* pSeries_E5;
	CXTPChartSeriesPoint* rpView;

    int m_nTopGap;
	int m_nLeftGap;
    CBrush m_hBrush;
    CChartBorder<CXTPChartControl> m_wndChartControl;
	CResizeGroupBox m_wndGroupBoxLabels;

public:
    BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
    void CreateChartGPS();
	void CreateChartBD();
	void CreateChartGL();
    void CreateChartGA();

	void GPS_BarSeries(int sat_num, Bar_Input * bar_input_buf);
	void BD_BarSeries(int sat_num, Bar_Input * bar_input_buf);
	void GL_BarSeries(int sat_num, Bar_Input * bar_input_buf);
    void GA_BarSeries(int sat_num, Bar_Input * bar_input_buf);

	void GPS_BarSeries_Nov(int sat_num, Bar_Input * bar_input_buf);
	void BD_BarSeries_Nov(int sat_num, Bar_Input * bar_input_buf);
	void GL_BarSeries_Nov(int sat_num, Bar_Input * bar_input_buf);

    void DealData(NmeaAllData* data);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    virtual void OnInitialUpdate();
    afx_msg void OnPaint();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnSize(UINT nType, int cx, int cy);
};


