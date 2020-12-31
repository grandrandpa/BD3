// PlotSky.cpp : implementation file
//

#include "stdafx.h"
#include "PlotSky.h"


// CPlotSky
#define PI   (3.1415926535897932 )    //!< 180.0/PI
#define R2D   (57.295779513082320876798154814105)    //!< 180.0/PI
#define D2R   (0.017453292519943295769236907684886)  //!< PI/180.0
#define ELV_LIMIT 5.0

IMPLEMENT_DYNAMIC(CPlotSky, CWnd)

CPlotSky::CPlotSky()
{
	m_dwChNum = 0;
	m_bSingleChSel = FALSE;
	m_pCharData = NULL;
	m_pcsSetDat = new CCriticalSection;
	m_dwColorRef[0]=RGB(255,0,0);
	m_dwColorRef[1]=RGB(255,255,0);
	m_dwColorRef[2]=RGB(0,0,255);
	m_dwColorRef[3]=RGB(255,0,255);
	m_dwColorRef[4]=RGB(0,255,255);
	m_dwColorRef[5]=RGB(0,255,0);
	m_dwColorRef[6]=RGB(255,255,255);
	m_dwColorRef[7]=RGB(128,0,0);
	m_dwColorRef[8]=RGB(0,128,0);
	m_dwColorRef[9]=RGB(128,128,0);
	m_dwColorRef[10]=RGB(0,0,128);
	m_dwColorRef[11]=RGB(128,0,128);
	m_dwColorRef[12]=RGB(0,128,128);
	m_dwColorRef[13]=RGB(128,128,128);
	m_dwColorRef[14]=RGB(192,0,0);
	m_dwColorRef[15]=RGB(0,192,0);
	m_dwColorRef[16] = RGB(192,192,0);
	m_dwColorRef[17] = RGB(0,0,192);
	m_dwColorRef[18] = RGB(192,0,192);
	m_dwColorRef[19] = RGB(0,192,192);
	m_dwColorRef[20] = RGB(192,192,192);
	m_dwColorRef[21] = RGB(255,128,0);
	m_dwColorRef[22] = RGB(255,0,128);
	m_dwColorRef[23] = RGB(255,128,128);
	m_dwColorRef[24] = RGB(128,0,255);
	m_dwColorRef[25] = RGB(0,128,255);

	m_clrMainBGColor = RGB(0, 0, 0);
	m_dwGridLineColor = RGB(0,128,0);
	m_dwTextColor = RGB(0,255,255);//

	m_nRadiu = 0;
	m_ptCenterPoint.SetPoint(0, 0);
	m_GnsspenLine.CreatePen (PS_SOLID, 1,m_dwGridLineColor);
	m_GnssDotpenLine.CreatePen (PS_DOT, 1,m_dwGridLineColor);
}

CPlotSky::~CPlotSky()
{
	if(m_pCharData!= NULL)
	{
		delete m_pCharData;
		m_pCharData = NULL;
	}
	if(m_pcsSetDat!= NULL)
	{
		delete m_pcsSetDat;
		m_pcsSetDat = NULL;
	}
}

BEGIN_MESSAGE_MAP(CPlotSky, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()

bool CPlotSky::Create(const RECT &rect, DWORD dwStyle, CWnd *pParentWnd, UINT nControlID)
{
	if (GetSafeHwnd())
		return FALSE;
	BOOL bRes = CWnd::Create( NULL, NULL, dwStyle , rect, pParentWnd, nControlID );
	return bRes;
}

// CPlotSky message handlers
int CPlotSky::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_pMainFont = new CFont;
	m_pMainFont->CreateFont(
		12,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nCl ipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"宋体");

	return 0;
}

void CPlotSky::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	CRect rtClient;
	GetClientRect(rtClient);
	//双缓冲绘图
	CDC MemDC;
	CBitmap MemBitmap;
	MemDC.CreateCompatibleDC(NULL);//&dc
	MemBitmap.CreateCompatibleBitmap(&dc, rtClient.Width(), rtClient.Height());
	CBitmap *pOldBit = MemDC.SelectObject(&MemBitmap);
	MemDC.SetTextColor(m_dwTextColor);//
	MemDC.SetBkMode(TRANSPARENT);
	MemDC.SelectObject(m_pMainFont);
	ReDrawAll(&MemDC, rtClient);

	dc.BitBlt(0, 0, rtClient.Width(), rtClient.Height(), &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBit);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
}

void CPlotSky::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(IsWindow(m_hWnd))
		Invalidate();
}
void CPlotSky::ReDrawAll(CDC* pDc, CRect rect)
{
}
void CPlotSky::DrawPlotGrid(CDC* pDc, CRect rect)
{
	int num = 0;
	double R = 0;
	char DEGREE[4]="°";
	CString OutStr;
	m_ptCenterPoint.SetPoint((rect.left+rect.right)/2,(rect.top+rect.bottom)/2);
	m_nRadiu = min((rect.left+rect.right)/2,(rect.top+rect.bottom)/2)-15;
	if(m_nRadiu<15)
		m_nRadiu=10;

	int nOldBkMode=pDc->SetBkMode(TRANSPARENT);
	CBrush * pBrush =CBrush::FromHandle( (HBRUSH)::GetStockObject(NULL_BRUSH) );
	CBrush * pOldBrush = pDc->SelectObject( pBrush );	
	CPen* pOldPen = pDc->SelectObject (&m_GnsspenLine);
	COLORREF clrTextOld = pDc->SetTextColor (m_dwTextColor);    
	CFont* pOldFont=pDc->SelectObject(m_pMainFont);

	//画两条中心直线
	pDc->MoveTo(m_ptCenterPoint.x-m_nRadiu-15,m_ptCenterPoint.y);
	pDc->LineTo(m_ptCenterPoint.x+m_nRadiu+15,m_ptCenterPoint.y);
	pDc->MoveTo(m_ptCenterPoint.x,m_ptCenterPoint.y-m_nRadiu-15);
	pDc->LineTo(m_ptCenterPoint.x,m_ptCenterPoint.y+m_nRadiu+15);

	//0度
	pDc->Ellipse(m_ptCenterPoint.x-m_nRadiu,m_ptCenterPoint.y-m_nRadiu,m_ptCenterPoint.x+m_nRadiu,m_ptCenterPoint.y+m_nRadiu);	
	//30度
	pDc->Ellipse(m_ptCenterPoint.x-2*m_nRadiu/3,m_ptCenterPoint.y-2*m_nRadiu/3,m_ptCenterPoint.x+2*m_nRadiu/3,m_ptCenterPoint.y+2*m_nRadiu/3);
	//60度
	pDc->Ellipse(m_ptCenterPoint.x-m_nRadiu/3,m_ptCenterPoint.y-m_nRadiu/3,m_ptCenterPoint.x+m_nRadiu/3,m_ptCenterPoint.y+m_nRadiu/3);

	//画90度点	
	num=90;
	OutStr.Format("%2i%s",num,DEGREE);		
	pDc->TextOut(m_ptCenterPoint.x+m_nRadiu+3,m_ptCenterPoint.y-15,OutStr);
	//画180度点	
	num=180;
	OutStr.Format("%2i%s",num,DEGREE);		
	pDc->TextOut(m_ptCenterPoint.x+2,m_ptCenterPoint.y+m_nRadiu,OutStr);
	//画270度点	
	num=270;
	OutStr.Format("%2i%s",num,DEGREE);		
	pDc->TextOut(m_ptCenterPoint.x-m_nRadiu-30,m_ptCenterPoint.y-15,OutStr);
	//画360度点	
	num=0;
	OutStr.Format("%2i%s",num,DEGREE);		
	pDc->TextOut(m_ptCenterPoint.x,m_ptCenterPoint.y-m_nRadiu-15,OutStr);
	//画90度点	
	num=90;
	OutStr.Format("%2i%s",num,DEGREE);		
	pDc->TextOut(m_ptCenterPoint.x-8, m_ptCenterPoint.y-8,OutStr);
	pDc->SelectObject (pOldPen);
	pOldPen = pDc->SelectObject (&m_GnsspenLine);

	//画45度斜线
	pDc->MoveTo(m_ptCenterPoint);
	pDc->LineTo((int)(m_ptCenterPoint.x+m_nRadiu*0.707),(int)(m_ptCenterPoint.y-m_nRadiu*0.707));
	//画135度斜线
	pDc->MoveTo(m_ptCenterPoint);
	pDc->LineTo((int)(m_ptCenterPoint.x+m_nRadiu*0.707),(int)(m_ptCenterPoint.y+m_nRadiu*0.707));
	//画225度斜线
	pDc->MoveTo(m_ptCenterPoint);
	pDc->LineTo((int)(m_ptCenterPoint.x-m_nRadiu*0.707),(int)(m_ptCenterPoint.y-m_nRadiu*0.707));
	//画315度斜线
	pDc->MoveTo(m_ptCenterPoint);
	pDc->LineTo((int)(m_ptCenterPoint.x-m_nRadiu*0.707),(int)(m_ptCenterPoint.y+m_nRadiu*0.707));	   
	pDc->SelectObject (pOldPen);
	pDc->SelectObject( pOldBrush ); 
	pDc->SetTextColor (clrTextOld);
	clrTextOld=	pDc->SetTextColor(RGB(255,255,255));
	pOldPen=pDc->SelectObject(&m_GnsspenLine);
	DrawLegend(pDc, rect);
}
void CPlotSky::DrawLegend(CDC* pDc, CRect rect)//
{
	CString strOut;
	int x = 15, y = 15;

	CPen NewPen;
	NewPen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	CPen *pOldPen = pDc->SelectObject(&NewPen);

	CFont myfont;
	myfont.CreateFont(
		14,
		6,
		0,
		0,
		700,
		FALSE,
		TRUE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		"Arial");
	CFont *pOldFont = pDc->SelectObject(&myfont);

	int rBig = 7, rSmall = 2;
	pDc->MoveTo(x-rBig, y);
	pDc->LineTo(x-rSmall, y-rSmall);
	pDc->LineTo(x, y-rBig);
	pDc->LineTo(x+rSmall, y-rSmall);
	pDc->LineTo(x+rBig, y);
	pDc->LineTo(x+rSmall, y+rSmall);
	pDc->LineTo(x, y+rBig);
	pDc->LineTo(x-rSmall, y+rSmall);
	pDc->LineTo(x-rBig, y);
	strOut.Format("%s", "GPS");
	pDc->TextOut(x+10, y-7, strOut);

	y = y + 20;
	pDc->MoveTo(x, y-7);
	pDc->LineTo(x, y+7);
	pDc->MoveTo(x-7, y);
	pDc->LineTo(x+7, y);
	pDc->MoveTo(x-5, y-5);
	pDc->LineTo(x+6, y+6);
	pDc->MoveTo(x-5, y+5);
	pDc->LineTo(x+6, y-6);
	strOut.Format("%s", "GLN");
	pDc->TextOut(x+10, y-7, strOut);

	y = y + 20;
	int r = 7;
	pDc->MoveTo(int(x+r*cos(162*D2R)), int(y-r*sin(162*D2R)));
	pDc->LineTo(int(x+r*cos(18*D2R)), int(y-r*sin(18*D2R)));
	pDc->LineTo(int(x+r*cos(234*D2R)), int(y-r*sin(234*D2R)));
	pDc->LineTo(int(x+r*cos(90*D2R)), int(y-r*sin(90*D2R)));
	pDc->LineTo(int(x+r*cos(306*D2R)), int(y-r*sin(306*D2R)));
	pDc->LineTo(int(x+r*cos(162*D2R)), int(y-r*sin(162*D2R)));
	strOut.Format("%s", "BD2");
	pDc->TextOut(x+10, y-7, strOut);

	pDc->SelectObject(pOldPen);
	pDc->SelectObject(pOldFont);
	myfont.DeleteObject();
	NewPen.DeleteObject();
}
void CPlotSky::DrawPlot(CDC* pDc, CRect rect)
{
	CPoint pt;
	CString OutStr;
	int i=0, j=0,flag=0,id=0;
	double R=0, azi=0, elv=0;
	//glonass
	CBrush brGlonass (RGB (205, 75, 0));
	//gps
	CBrush brGPS (RGB (255, 0, 0));  
	//bd2
	CBrush brBD2(RGB (0, 155, 0)); 
	CBrush * pBrush =CBrush::FromHandle( (HBRUSH)::GetStockObject(NULL_BRUSH) );
	CBrush * pOldBrush = pDc->SelectObject( pBrush );	
	for (i=0; i<m_dwChNum; i++)
	{
		if (m_pCharData[i].m_bVisible == FALSE)
			continue;

		COLORREF clrCh = m_pCharData[i].dwColor;
		CPen pen(PS_SOLID, 1, clrCh);
		CPen *pOldPen =  pDc->SelectObject(&pen);
		for (j=0; j<m_pCharData[i].nSatNum; j++)
		{
			id = m_pCharData[i].nID[j];
			azi = m_pCharData[i].dAzi[j];
			elv = m_pCharData[i].dElev[j];
			flag = m_pCharData[i].Flag[i];
			if ((id>0&&id<65) && (azi>=0 && azi<=360) && (elv>=0 && elv<=90))
			{
				R=m_nRadiu*(1.0-elv/90.0);
				pt.x=m_ptCenterPoint.x+(int)(R*sin(azi*D2R));
				pt.y=m_ptCenterPoint.y-(int)(R*cos(azi*D2R));		
				DrawSatellite(pDc, pt.x, pt.y, id, i, flag);
			}
		}
		pDc->SelectObject (pOldPen);
	}
}
void CPlotSky::DrawSatellite(CDC* pDC, int x, int y, int SvNo, int SVType, int iFlag)
{
	CPen NewPen;
	CString strOut;
	DWORD dwColor = m_dwColorRef[20-SVType];
	if (0 == iFlag)//卫星健康
		NewPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	else
		NewPen.CreatePen(PS_SOLID, 1, dwColor);

	CPen *pOldPen = pDC->SelectObject(&NewPen);
	CFont myfont;
	myfont.CreateFont(
		14,
		6,
		0,
		0,
		700,
		FALSE,
		TRUE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		"Arial");
	CFont *pOldFont = pDC->SelectObject(&myfont);

	if (SVType == 0)//GPS
	{
		int rBig = 7, rSmall = 2;
		pDC->MoveTo(x-rBig, y);
		pDC->LineTo(x-rSmall, y-rSmall);
		pDC->LineTo(x, y-rBig);
		pDC->LineTo(x+rSmall, y-rSmall);
		pDC->LineTo(x+rBig, y);
		pDC->LineTo(x+rSmall, y+rSmall);
		pDC->LineTo(x, y+rBig);
		pDC->LineTo(x-rSmall, y+rSmall);
		pDC->LineTo(x-rBig, y);
		strOut.Format("%d", SvNo);
		pDC->TextOut(x+10, y-8, strOut);
	}
	else if (SVType == 1)//GLN
	{
		pDC->MoveTo(x, y-7);
		pDC->LineTo(x, y+7);
		pDC->MoveTo(x-7, y);
		pDC->LineTo(x+7, y);
		pDC->MoveTo(x-5, y-5);
		pDC->LineTo(x+6, y+6);
		pDC->MoveTo(x-5, y+5);
		pDC->LineTo(x+6, y-6);
		strOut.Format("%d", SvNo);
		pDC->TextOut(x+10, y-8, strOut);

	} 
	else if(SVType == 2)//BD
	{
		int r = 8;
		pDC->MoveTo(int(x+r*cos(162*D2R)), int(y-r*sin(162*D2R)));
		pDC->LineTo(int(x+r*cos(18*D2R)), int(y-r*sin(18*D2R)));
		pDC->LineTo(int(x+r*cos(234*D2R)), int(y-r*sin(234*D2R)));
		pDC->LineTo(int(x+r*cos(90*D2R)), int(y-r*sin(90*D2R)));
		pDC->LineTo(int(x+r*cos(306*D2R)), int(y-r*sin(306*D2R)));
		pDC->LineTo(int(x+r*cos(162*D2R)), int(y-r*sin(162*D2R)));
		strOut.Format("%d", SvNo);
		pDC->TextOut(x+10, y-8, strOut);
	}
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);
	myfont.DeleteObject();
	NewPen.DeleteObject();
}
int CPlotSky::CreatePlot(const RECT& rt, CWnd* pParentWnd, int nChannelNum, int nMaxPlotNum)
{
	return -1;
}
