#if !defined(AFX_BARVIEW_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_)
#define AFX_BARVIEW_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// CDrawSkyWnd

class CDrawSkyWnd : public CWnd
{
	DECLARE_DYNAMIC(CDrawSkyWnd)

public:
	CDrawSkyWnd();
	virtual ~CDrawSkyWnd();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnUserClear();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
private:
	BD2_GSV	m_listSky;
public:
	BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nControlID);
	afx_msg void OnPaint();
	afx_msg void OnNcPaint();
	void Clear(void);
	void RefreshView(BD2_GSV* data);
	void Reset(void);
	void DrawSky(CDC* pDC, CRect rect);

//private:
    //CXTPChartSeries* pSeries_GPS;

};

#endif // !defined(AFX_BARVIEW_H__F31A2B31_B7F8_49D2_B748_57B38AF51C5F__INCLUDED_)
