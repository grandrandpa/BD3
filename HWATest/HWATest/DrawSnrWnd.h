#pragma once


// CDrawSnrWnd

class CDrawSnrWnd : public CWnd
{
	DECLARE_DYNAMIC(CDrawSnrWnd)

public:
	CDrawSnrWnd();
	virtual ~CDrawSnrWnd();

protected:
	DECLARE_MESSAGE_MAP()
private:
	PackageSNR		m_listSnr;
public:
	BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nControlID);
	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	void Reset(void);
	void Clear(void);
	void RefreshView(PackageSNR* data);
	void DrawAllSnr(CDC* pDC, int l, int w, int h, int top);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


