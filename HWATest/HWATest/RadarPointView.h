#pragma once

#include "BaseView.h"

template <class TBase>
class CChartBorder : public TBase
{
public:
	CChartBorder()
	{
#ifdef _XTP_INCLUDE_TOOLKIT
		CXTPChartColor color;
		color.SetFromCOLORREF(0xcf9365);

		GetContent()->GetBorder()->SetColor(color);
#endif
	}

};
// RadarPointView form view

class RadarPointView : public CBCGPFormView//CFormView
{
	DECLARE_DYNCREATE(RadarPointView)

protected:
	RadarPointView();           // protected constructor used by dynamic creation
	virtual ~RadarPointView();

public:
	enum { IDD = IDD_BASEVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

    afx_msg void OnCheckShowLabels();
	afx_msg void OnCbnSelchangeComboMarkerSize();
	afx_msg void OnCbnSelchangeComboMarkerType();
	afx_msg void OnCheckShowAxisX();
	afx_msg void OnCheckShowAxisY();
	afx_msg void OnCheckInterlaced();

	DECLARE_MESSAGE_MAP()

    //CString m_strCaption;
 //   BOOL m_bShowLabels;
	//int m_nMarkerType;
	//int m_nMarkerSize;

	//BOOL m_bShowAxisX;
	//BOOL m_bShowAxisY;
	//BOOL m_bInterlaced;

    BOOL m_bShowBD;
	BOOL m_bShowGP;
    BOOL m_bShowGL;
	BOOL m_bShowGA;

private:
	CXTPChartSeries* pSeries_GPS;
	CXTPChartSeries* pSeries_BD;
	CXTPChartSeries* pSeries_GLONASS;
    CXTPChartSeries* pSeries_GA;

    CBrush m_hBrush;
	CChartBorder<CXTPChartControl> m_wndChartControl;

	CResizeGroupBox m_wndGroupBoxLabels;

	int m_nTopGap;
	int m_nLeftGap;

public:
    BOOL CreateView(CWnd* pParent, CCreateContext* pContext);
    void Updata(int radar_input_buf_len, Radar_Input * radar_input_buf);

    void CreateChart();
	void OnInitialUpdate();

    void BD_Radar(int sat_num, Radar_Input * radar_input_buf);
	void GPS_Radar(int sat_num, Radar_Input * radar_input_buf);
	void GLONASS_Radar(int sat_num, Radar_Input * radar_input_buf);
    void GA_Radar(int sat_num, Radar_Input * radar_input_buf);
	void ClearAllSat();

    void DealData(NmeaAllData* data);

    afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnClickedCheckBd();
    afx_msg void OnClickedCheckGa();
    afx_msg void OnClickedCheckGl();
    afx_msg void OnClickedCheckGps();
};


