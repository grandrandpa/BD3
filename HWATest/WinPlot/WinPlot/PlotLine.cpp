// PlotLine.cpp : implementation file
//

#include "stdafx.h"
#include "PlotLine.h"


// CPlotLine

IMPLEMENT_DYNAMIC(CPlotLine, CWnd)

CPlotLine::CPlotLine()
{
	InitPara();
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
	m_dwColorRef[22] = RGB(55,0,128);
	m_dwColorRef[23] = RGB(255,128,128);
	m_dwColorRef[24] = RGB(128,0,255);
	m_dwColorRef[25] = RGB(0,128,255);
	m_pcsSetDat = new CCriticalSection;
	m_pToolbar = new CPlotToolbar;

	m_dwDrawMode = DRAW_MODE_LINE;
	m_bShowCursor = FALSE;
	m_bDrawAxisValue = FALSE;
	m_bAxisMove = FALSE;
	m_bAutoZoomFit = TRUE;
	m_bPausePlot = FALSE;
	m_bDrawDot = TRUE;
	m_pFontAxisY = NULL;
	m_pToolbarFont = NULL;
	m_bToolBarShow = TRUE;
	m_bMouseInToolBarHotSpot = TRUE;

	m_strXUnit = "无";
	m_strYUnit = "无";
	m_dDotSpanX = 1.0;
	m_dDotSpanY = 1.0;
	//x轴名称
	CString m_strAxisXName = "X轴";
	//y轴名称
	CString m_strAxisYName = "Y轴";
	m_clrMainBGColor = RGB(0, 0, 0);
	m_dwGridLineColor = RGB(0,128,0);
	m_dwAxisColor = RGB(0,128,0);
	m_dwTextColor = RGB(0,255,255);//

	m_dMouseDownOnPlotX = 0.0;
	m_dMouseDownOnPlotY = 0.0;

	m_dUnitScaleX = 1.0;
	m_dUnitScaleY = 1.0;

	m_iNumSumAfterDot = 0;
	m_iNumSumAfterDotX = 0;
	m_iNumSumAfterDotY = 4;
	//Legeng相关参数
	m_iChLabelHei = 16;
	m_dwChNum = 0;
	m_dwChDatNum = 0;

	m_bSingleChSel = FALSE;
	m_bshowlegend = TRUE;

	m_strTitle.Empty();
}

CPlotLine::~CPlotLine()
{
	// modify by lpp 
	if(m_pToolbar!= NULL)
	{
		delete m_pToolbar;
		m_pToolbar = NULL;
	}
	if(m_pcsSetDat!= NULL)
	{
		delete m_pcsSetDat;
		m_pcsSetDat = NULL;
	}
	if(m_pMainFont!= NULL )
	{
		m_pMainFont->DeleteObject();
		delete m_pMainFont;
		m_pMainFont = NULL;
	}
	/*if(m_pToolbarFont!= NULL )
	{
		m_pToolbarFont->DeleteObject();
		delete m_pToolbarFont;
		m_pToolbarFont = NULL;
	}*/
	if(m_pFontAxisY!= NULL)
	{
		m_pFontAxisY->DeleteObject();
		delete m_pFontAxisY;
		m_pFontAxisY = NULL;
	}

	if(m_dwChNum > 0)
	{
		delete []m_pChDat;
		m_pChDat = NULL;
	}
}


BEGIN_MESSAGE_MAP(CPlotLine, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_ROOT_AXISMOVE, &CPlotLine::OnRootAxismove)
	ON_COMMAND(ID_ROOT_AXISZOOM, &CPlotLine::OnRootAxiszoom)
	ON_COMMAND(ID_ROOT_CHANNEL_ALL, &CPlotLine::OnRootChannelAll)
	ON_COMMAND(ID_ROOT_CHANNEL_SINGLE, &CPlotLine::OnRootChannelSingle)
	ON_COMMAND(ID_ROOT_CURVALUE, &CPlotLine::OnRootCurvalue)
	ON_COMMAND(ID_ROOT_MARK_POINTS, &CPlotLine::OnRootMarkPoints)
	ON_COMMAND(ID_ROOT_PAUSE, &CPlotLine::OnRootPause)
	ON_COMMAND(ID_ROOT_ZOOMFIT, &CPlotLine::OnRootZoomfit)
	ON_COMMAND(ID_ROOT_ZOOMIN, &CPlotLine::OnRootZoomin)
	ON_COMMAND(ID_ROOT_ZOOMOUT, &CPlotLine::OnRootZoomout)
	ON_COMMAND(ID_ROOT_CLEAN, &CPlotLine::OnRootClean)
	ON_COMMAND_RANGE(ID_ROOT_CHANNEL_0, ID_ROOT_CHANNEL_128, OnRootShowCh)
END_MESSAGE_MAP()

// CPlotLine message handlers
int CPlotLine::OnCreate(LPCREATESTRUCT lpCreateStruct)
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

	m_pFontAxisY = new CFont;
	m_pFontAxisY->CreateFont(
		12,                        // nHeight
		0,                         // nWidth
		900,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"宋体");

	m_pToolbarFont = new CFont;
	m_pToolbarFont->CreateFont(
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
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"宋体");
	m_pToolbar->CreateToolbar(m_rtToolBar, this);
	m_pToolbar->SetFont(m_pToolbarFont);
	m_pToolbar->CreateButton(ID_ROOT_AXISMOVE, "移动");
	m_pToolbar->CreateButton(ID_ROOT_ZOOMIN, "放大");
	m_pToolbar->CreateButton(ID_ROOT_ZOOMOUT, "缩小");
	m_pToolbar->CreateButton(ID_ROOT_ZOOMFIT, "自动缩放");
	m_pToolbar->CreateButton(ID_ROOT_CURVALUE, "测量");
	m_pToolbar->CreateButton(ID_ROOT_MARK_POINTS, "描点");
	//m_pToolbar->CreateButton(ID_ROOT_CHANNEL_SINGLE, "单通道");
	//m_pToolbar->CreateButton(ID_ROOT_CHANNEL_ALL, "全通道");
	//m_pToolbar->CreateButton(ID_ROOT_PAUSE, "暂定");
	m_pToolbar->CreateButton(ID_ROOT_CLEAN, "清除");

	m_pToolbar->SetBtnChecked(ID_ROOT_PAUSE, m_bPausePlot);
	m_pToolbar->SetBtnChecked(ID_ROOT_AXISMOVE, m_bAxisMove);
	m_pToolbar->SetBtnChecked(ID_ROOT_CURVALUE, m_bShowCursor);
	m_pToolbar->SetBtnChecked(ID_ROOT_MARK_POINTS, m_bDrawDot);
	m_pToolbar->SetBtnChecked(ID_ROOT_ZOOMFIT, m_bAutoZoomFit);
	m_pToolbar->SetBtnChecked(ID_ROOT_CHANNEL_ALL, !m_bSingleChSel);
	m_pToolbar->SetBtnChecked(ID_ROOT_CHANNEL_SINGLE, m_bSingleChSel);
	OnRootChannelSingle();

	return 0;
}
void CPlotLine::OnPaint()
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
	RecalcRect(rtClient);
	m_pToolbar->SetRect(m_rtToolBar);
	ReDrawAll(&MemDC, rtClient);

	dc.BitBlt(0, 0, rtClient.Width(), rtClient.Height(), &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBit);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
}

void CPlotLine::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(IsWindow(m_hWnd))
		Invalidate();
}
//////////////////////////////////////////////////////////////////////////
bool CPlotLine::Create(const RECT &rect, DWORD dwStyle, CWnd *pParentWnd, UINT nControlID)
{
	if (GetSafeHwnd())
		return FALSE;
	BOOL bRes = CWnd::Create( NULL, NULL, dwStyle , rect, pParentWnd, nControlID );
	return bRes;
}

//////////////////////////////////////////////////////////////////////////
void CPlotLine::ReDrawAll(CDC* pDc, CRect rect)
{
	CBrush brush(m_clrMainBGColor);
	pDc->FillRect(m_rtPlot, &brush);
	//自动缩放
	if(m_bAutoZoomFit)
		RecalcAutoZoomFit();

	switch (m_dwDrawMode)
	{
	case DRAW_MODE_LINE:
		DrawLines(pDc);//绘制曲线图
		break;
	case DRAW_MODE_POINTS:
		DrawPoints(pDc);//绘制曲线图
		break;
	default:
		break;
	}
	DrawTitle(pDc);
	if(m_bshowlegend)
		DrawLegend(pDc);
	if (m_bToolBarShow)
		m_pToolbar->DrawToolbar(pDc);
	DrawAxisX(pDc);
	DrawAxisY(pDc);

	CBrush brPlotBox(m_dwAxisColor);
	pDc->FrameRect(m_rtPlot, &brPlotBox);
	CRect rtFrame(rect.left+3, rect.top+3, rect.right-3, rect.bottom-3);
	CBrush brFrame(RGB(128,128,128));
	pDc->FrameRect(rtFrame, &brFrame);

	//显示坐标单位y轴/x轴
	CString strTmp;
	if (!m_strAxisXName.IsEmpty() && !m_strAxisYName.IsEmpty())
	{
		strTmp.Format("Y=%s", m_strAxisYName);
		CSize NameSize = pDc->GetTextExtent(strTmp);
		pDc->TextOut(m_rtAxisY.right-NameSize.cx, m_rtAxisY.top, strTmp);
		strTmp.Format("X=%s", m_strAxisXName);
		NameSize = pDc->GetTextExtent(strTmp);
		pDc->TextOut(m_rtLegend.left, m_rtAxisX.top - NameSize.cy, strTmp);
	}
	brush.DeleteObject();
	brPlotBox.DeleteObject();
	brFrame.DeleteObject();

}
void CPlotLine::DrawPoints(CDC* pDc)
{
	DWORD i=0, j=0;
	//绘制每一个通道
	double dx=0, dy=0;
	CRect rtClient = m_rtPlot;
	//绘图区左上角偏移
	int xd = rtClient.left;
	int yd = rtClient.top;

	DrawPlotGrid(pDc);//绘制网格
	if(m_bPausePlot)
		return;
	for (i=0;i<m_dwChNum;i++)
	{
		if (m_pChDat[i].m_bVisible == FALSE)
			continue;
		//20120722 当点数小于2时，跳过此通道 
		/*if (m_pChDat[i].m_dwMaxsize < 2)
			continue;*/

		CPen pen(PS_SOLID, 1, m_pChDat[i].m_clrCh);
		CPen *pOldPen;
		pOldPen =  pDc->SelectObject(&pen);
		m_pChDat[i].m_clrDot = m_dwColorRef[25-i%25];

		//X轴找到要绘制的第一个点和最后一个点
		DWORD iMaxSize = m_pChDat[i].m_dwMaxsize;
		DWORD iAxisXDotBegin = m_pChDat[i].m_dwFront;
		DWORD iAxisXDotEnd = m_pChDat[i].m_dwRear;
		/*for (j=0;j<m_pChDat[i].m_dwDotsNumCur-2;j++)
		{
			if(m_pChDat[i].m_pdX[j] < m_dAxisXMin)
			{
				if (m_pChDat[i].m_pdX[j+1]< m_dAxisXMin && m_pChDat[i].m_pdX[j+2] > m_dAxisXMin)
					iAxisXDotBegin = j+1;
			}
			if (m_pChDat[i].m_pdX[j] > m_dAxisXMax)
			{
				if (m_pChDat[i].m_pdX[j-1] < m_dAxisXMax)
					iAxisXDotEnd = j+1;
			}
		}
		if (iAxisXDotEnd > m_pChDat[i].m_dwDotsNum)iAxisXDotEnd = m_pChDat[i].m_dwDotsNum;*/

		double xs, ys;
		xs = m_pChDat[i].m_pdX[iAxisXDotBegin]- m_dAxisXMin;
		ys = m_dAxisYMax - m_pChDat[i].m_pdY[iAxisXDotBegin];

		pDc->MoveTo(int(xs*m_dXMul + xd), int(ys*m_dYMul + yd));
		//只绘制屏幕中X轴范围内的数据
		for (j = iAxisXDotBegin;j != iAxisXDotEnd; j=(j+1)%iMaxSize)
		{
			dx = m_pChDat[i].m_pdX[j];
			dy = m_pChDat[i].m_pdY[j];
			//conv(dx,dy, ym, xd, yd);

			xs = dx - m_dAxisXMin;
			ys = m_dAxisYMax - dy;
			if (!m_bDrawDot)
				DrawDot(pDc , xs*m_dXMul + xd, ys*m_dYMul + yd, 3, m_pChDat[i].m_clrDot);
			else
			{
				pDc->LineTo(int(xs*m_dXMul + xd), int(ys*m_dYMul + yd));
				DrawDot(pDc , xs*m_dXMul + xd, ys*m_dYMul + yd, 3, m_pChDat[i].m_clrDot);
			}
		}
		pDc->SelectObject(pOldPen);
	}
}
void CPlotLine::DrawLines(CDC* pDc)//绘制曲线图区
{
	DWORD i=0, j=0;
	//绘制每一个通道
	double dx=0, dy=0;
	CRect rtClient = m_rtPlot;
	//绘图区左上角偏移
	int xd = rtClient.left;
	int yd = rtClient.top;

	DrawPlotGrid(pDc);//绘制网格
	for (i=0;i<m_dwChNum;i++)
	{
		if (m_pChDat[i].m_bVisible == FALSE)
			continue;
		//20120722 当点数小于2时，跳过此通道 
		/*if (m_pChDat[i].m_dwDotsNumCur < 2)
			continue;*/

		COLORREF clrCh = m_pChDat[i].m_clrCh;
		CPen pen(PS_SOLID, 1, clrCh);
		CPen *pOldPen;
		pOldPen =  pDc->SelectObject(&pen);
		m_pChDat[i].m_clrDot = m_dwColorRef[25-i%25];

		//X轴找到要绘制的第一个点和最后一个点
		DWORD iMaxSize = m_pChDat[i].m_dwMaxsize;
		DWORD iAxisXDotBegin = m_pChDat[i].m_dwFront;
		DWORD iAxisXDotEnd = m_pChDat[i].m_dwRear;
		//for (j=0;j<m_pChDat[i].m_dwDotsNumCur-1;j++)
		//{
		//	if(m_pChDat[i].m_pdX[j] < m_dAxisXMin)
		//	{
		//		if (m_pChDat[i].m_pdX[j+1] > m_dAxisXMin)// && m_pChDat[i].m_pdX[j+1] > m_dAxisXMin)
		//			iAxisXDotBegin = j+1;
		//	}

		//	if (m_pChDat[i].m_pdX[j+1] > m_dAxisXMax)
		//	{
		//		if (m_pChDat[i].m_pdX[j] < m_dAxisXMax)
		//			iAxisXDotEnd = j+1;
		//	}
		//}

		double xs, ys;
		xs = m_dUnitScaleX;//m_pChDat[i].m_pdX[iAxisXDotBegin]- m_dAxisXMin;
		ys = m_dAxisYMax - m_pChDat[i].m_pdY[iAxisXDotBegin];

		//只绘制屏幕中X轴范围内的数据
		DWORD index=0;
		for (j=iAxisXDotBegin,index=0; j != iAxisXDotEnd; index++, j=(j+1)%iMaxSize)
		{
			/*dx = m_pChDat[i].m_pdX[j];
			dy = m_pChDat[i].m_pdY[j];
			if (m_dwDrawMode == DRAW_MODE_POINTS)
				dx = i*m_dUnitScaleX;*/

			dx = index*m_dUnitScaleX;
			dy = m_pChDat[i].m_pdY[j];
			//conv(dx,dy, ym, xd, yd);

			xs = dx - m_dAxisXMin;
			ys = m_dAxisYMax - dy;
			//dc.LineTo(sCh0.m_pdX[i], dytmp);

			//绘制第一个点坐标
			if (index == 0)
			{
				pDc->MoveTo(int(xs*m_dXMul + xd), int(ys*m_dYMul + yd));
			}
			pDc->LineTo(int(xs*m_dXMul + xd), int(ys*m_dYMul + yd));

			if (m_bDrawDot)//是否描点
			{
				double dxDot = xs*m_dXMul + xd;
				double dyDot = ys*m_dYMul + yd;

				DrawDot(pDc , dxDot, dyDot, 3, m_pChDat[i].m_clrDot);
				if (dxDot - m_poMouseCursorCur.x < 10 &&
					dxDot - m_poMouseCursorCur.x > -10 &&
					dyDot - m_poMouseCursorCur.y < 10 &&
					dyDot - m_poMouseCursorCur.y > -10)
				{
					CString strTmp;

					strTmp.Format("%.2f %.2f", m_pChDat[i].m_pdX[j], m_pChDat[i].m_pdY[j]);
					COLORREF clrOld = pDc->GetTextColor();
					pDc->SetTextColor(clrCh);
					pDc->TextOut(int(dxDot+4), int(dyDot-4), strTmp);
					pDc->SetTextColor(clrOld);
				}
			}
		}
	}
	//显示当前测量值
	if (m_bShowCursor && m_bDrawDot == FALSE)
	{
		if (m_rtPlot.PtInRect(m_poCursor) == TRUE)
		{
			CString strAxis;
			double x,y;
			x = (m_poCursor.x - m_rtPlot.left)/m_dXMul + m_dAxisXMin;
			y = m_dAxisYMax - (m_poCursor.y - m_rtPlot.top)/m_dYMul;
			strAxis.Format("X=%.2f,Y=%.2f", x*m_dUnitScaleX, y*m_dUnitScaleY);

			//pDc->TextOut(m_poCursor.x, m_poCursor.y-16 ,strAxis);
			pDc->TextOut(m_rtPlot.left+2, m_rtPlot.top+2 ,strAxis);
		}
	}
}
void CPlotLine::DrawAxisX(CDC* pDc)//绘制X轴
{
	int i=0, nFormat=0;
	CString strTmp;
	CString strFormat;

	ClearRect(pDc, &m_rtAxisX, m_clrMainBGColor);
	double dDivWid = (m_dAxisXMax - m_dAxisXMin) / 10;

	CPen pen(PS_SOLID, 0, RGB(64,255,64));
	CPen *pOldPen = pDc->SelectObject(&pen);

	pDc->MoveTo(m_rtAxisX.left, m_rtAxisX.top);
	pDc->LineTo(m_rtAxisX.right, m_rtAxisX.top);

	nFormat = int(m_iNumSumAfterDotX * m_dUnitScaleX);
	strFormat.Format("%%.%df",  nFormat);
	for (i= 0;i<10;i++)
	{
		pDc->MoveTo(int(dDivWid*i*m_dXMul + m_rtPlot.left), int(m_rtAxisX.top));
		pDc->LineTo(int(dDivWid*i*m_dXMul + m_rtPlot.left), int(m_rtAxisX.top + 5));

		double dDotVal = m_dAxisXMin + dDivWid*i;
		strTmp.Format(strFormat, dDotVal*m_dUnitScaleX);
		pDc->TextOut(int(dDivWid*i*m_dXMul + m_rtPlot.left), m_rtAxisX.top, strTmp);
	}
	strFormat.Format("单位：%s", m_strXUnit);
	CSize cs = pDc->GetTextExtent(strFormat);
	pDc->TextOut(int(dDivWid*10*m_dXMul + m_rtPlot.left), m_rtAxisX.top, strFormat);
	pDc->SelectObject(pOldPen);
	pen.DeleteObject();
	pOldPen->DeleteObject();
}
void CPlotLine::DrawAxisY(CDC* pDc)//绘制Y轴
{
	CSize cs;
	int i=0, nFormat=0;
	CString strTmp;
	CString strFormat;

	ClearRect(pDc, m_rtAxisY, m_clrMainBGColor);
	double dDivWid = (m_dAxisYMax - m_dAxisYMin) / 10;

	CPen pen(PS_SOLID, 0, RGB(64,255,64));
	CPen *pOldPen = pDc->SelectObject(&pen);
	pDc->MoveTo(m_rtAxisY.right -1, m_rtAxisY.top);
	pDc->LineTo(m_rtAxisY.right -1, m_rtAxisY.bottom);

	nFormat = int(m_iNumSumAfterDotY * m_dUnitScaleY);
	strFormat.Format("%%.%df", nFormat);
	for (i= 0;i<10;i++)
	{
		pDc->MoveTo(int(m_rtAxisY.right), int(m_rtPlot.bottom - dDivWid*i*m_dYMul));
		pDc->LineTo(int(m_rtAxisY.right-5), int(m_rtPlot.bottom - dDivWid*i*m_dYMul));

		strTmp.Format(strFormat, m_dAxisYMin + dDivWid*i);
		cs = pDc->GetTextExtent(strTmp);
		pDc->TextOut(int(m_rtAxisY.right - cs.cx - 2), int(m_rtPlot.bottom - dDivWid*i*m_dYMul-5), strTmp);
	}
	strFormat.Format("单位：%s", m_strYUnit);
	cs = pDc->GetTextExtent(strFormat);
	pDc->TextOut(m_rtAxisY.right, m_rtPlot.top - cs.cy, strFormat);
	pDc->SelectObject(pOldPen);
	pen.DeleteObject();
	pOldPen->DeleteObject();
}
void CPlotLine::DrawPlotGrid(CDC* pDc)//绘制网格
{
	DWORD i;
	int rtxBegin = m_rtPlot.left;
	int rtxEnd = m_rtPlot.right;
	int rtyBegin = m_rtPlot.top;
	int rtyEnd = m_rtPlot.bottom;

	double dGridWidX = (rtxEnd-rtxBegin)*1.0/10;
	double dGridWidY = (rtyEnd-rtyBegin)*1.0/10;

	CPen pen(PS_DOT, 1, m_dwGridLineColor);//PS_DOT,PS_DASHDOT,PS_DASHDOTDOT
	CPen *pOldPen = pDc->SelectObject(&pen);
	//绘制主要网格
	for (i=1;i<10;i++)
	{
		//画竖线
		pDc->MoveTo(int(rtxBegin + i*dGridWidX), m_rtPlot.top);
		pDc->LineTo(int(rtxBegin + i*dGridWidX), m_rtPlot.bottom);

		//画横线
		pDc->MoveTo(rtxBegin, int(rtyBegin + i*dGridWidY));
		pDc->LineTo(rtxEnd, int(rtyBegin + i*dGridWidY));
	}
	pDc->SelectObject(pOldPen);
	pen.DeleteObject();
	pOldPen->DeleteObject();
}
void CPlotLine::DrawLegend(CDC* pDc)//
{
	ClearRect(pDc, m_rtLegend, m_clrMainBGColor);
	//int i; // note by lpp
	DWORD i;
	CRect rtChLbe;
	CString strTmp;
	CBrush brFrame(RGB(0,255,0));
	CBrush brFrameIn(RGB(0,0,0));
	for (i=0;i<m_dwChNum;i++)
	{
		rtChLbe.top = i*m_iChLabelHei+m_rtLegend.top;
		rtChLbe.bottom = rtChLbe.top + m_iChLabelHei + 2;
		rtChLbe.left = m_rtLegend.left+2;
		rtChLbe.right = m_rtLegend.right-5;//rtChLbe.left+40;


		rtChLbe.right = rtChLbe.left + 10;
		rtChLbe.bottom = rtChLbe.top + 10;

		if (m_pChDat[i].strChName.IsEmpty())
			strTmp.Format("%d", i+1);
		else
			strTmp.Format("%s", m_pChDat[i].strChName);
		CSize cs = pDc->GetTextExtent(strTmp);
		pDc->TextOut(rtChLbe.right+3, int(rtChLbe.top-fabs((cs.cy - rtChLbe.Height())/2.0)), strTmp);

		if (m_pChDat[i].m_bVisible)
		{
			rtChLbe.right += 2;
			pDc->FrameRect(rtChLbe, &brFrame);
			rtChLbe.top += 1;
			rtChLbe.bottom -=1;
			rtChLbe.left+= 1;
			rtChLbe.right-=1;
			pDc->FrameRect(rtChLbe, &brFrameIn);
		}

		//绘制通道色块
		rtChLbe.top += 1;
		rtChLbe.bottom -=1;
		rtChLbe.left+= 1;
		rtChLbe.right-=1;
		CBrush brush(m_pChDat[i].m_clrCh);
		pDc->FillRect(rtChLbe, &brush);

	}
}
void CPlotLine::DrawTitle(CDC* pDc)//标题
{
	CFont* newFont=new CFont;
	CSize point = pDc->GetTextExtent(m_strTitle);
	ClearRect(pDc, &m_rtTitle, m_clrMainBGColor);
	newFont->CreateFont(
		24,                        // nHeight
		12,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_BOLD,                 // nWeight //FW_NORMAL //FW_BOLD
		FALSE,                     // bItalic
		TRUE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		"宋体");//宋体
	CFont* oldFont = pDc->SelectObject(newFont);
	pDc->TextOut((m_rtTitle.Width() +AXIS_Y_WIDTH +AXIS_LEGEND_WIDTH- point.cx)/2, (m_rtTitle.bottom + m_rtTitle.top)/2 - point.cy/2, m_strTitle);
	//pDc->MoveTo((m_rtTitle.Width() +AXIS_Y_WIDTH +AXIS_LEGEND_WIDTH- point.cx)/2, (m_rtTitle.bottom + m_rtTitle.top)/2 + point.cy/2);
	//pDc->LineTo((m_rtTitle.Width() +AXIS_Y_WIDTH +AXIS_LEGEND_WIDTH+ point.cx)/2, (m_rtTitle.bottom + m_rtTitle.top)/2 + point.cy/2);
	pDc->SelectObject(oldFont);
	newFont->DeleteObject();
	oldFont->DeleteObject();
}
void CPlotLine::ClearRect(CDC* pDc, LPRECT rt, COLORREF clr)//
{
	CBrush brBG(clr);
	pDc->FillRect(rt, &brBG);
	brBG.DeleteObject();
}
void CPlotLine::DrawDot(CDC *pDc, double x, double y,  int iDotSize, COLORREF clr)
{
	CBrush brDot(clr);
	int iFix = iDotSize/2+1;
	CBrush* pOldBr = pDc->SelectObject(&brDot);
	//pDc->FillRect(CRect(int(x-iFix),int(y-iFix),int(x+iDotSize),int(y+iDotSize)), &brDot);
	pDc->Ellipse(CRect(int(x-iFix),int(y-iFix),int(x+iDotSize),int(y+iDotSize)));
	pDc->SelectObject(pOldBr);
	brDot.DeleteObject();
	pOldBr->DeleteObject();
}
//////////////////////////////////////////////////////////////////////////////
void CPlotLine::InitPara()
{
	m_rtAxisX = CRect(1,1,1,1);
	m_rtAxisY = CRect(1,1,1,1);
	m_rtAxisY = CRect(1,1,1,1);
	m_rtPlot = CRect(1,1,1,1);
	m_rtLegend= CRect(1,1,1,1);
	m_rtToolBar= CRect(1,1,1,1);
	m_rtTitle= CRect(1,1,1,1);


	m_dAxisXMax = 100.0;
	m_dAxisYMax = 100.0;

	m_dAxisXMin = 0.0;
	m_dAxisYMin = 0.0;

	m_dXMul = 1.0;
	m_dYMul = 1.0;

	m_bLBtnDown = FALSE;
	m_ptMouseLast = CPoint(0,0);

	m_dwChNum = 0;

	m_bDrawDot = FALSE;
	m_bBoxZoomDrawRect = FALSE;

	m_dwMouseDragMode = MOUSE_DRAG_MOVE;
	//m_dwMouseDragMode = MOUSE_DRAG_ZOOM;
	//m_dwMouseDragMode = MOUSE_DRAG_BOX_ZOOM;
	m_pMainFont = NULL;
}

void CPlotLine::RecalcRect(CRect rect)//m_rtToolBar
{
	//工具栏
	m_rtToolBar.top = rect.top;
	m_rtToolBar.bottom = m_rtToolBar.top + TOOLBAR_HEIGH;
	m_rtToolBar.left = rect.left;
	m_rtToolBar.right = rect.right;
	//标题栏
	m_rtTitle.top = m_rtToolBar.bottom;
	m_rtTitle.bottom = rect.top + AXIS_TITLE_HEIGH;
	m_rtTitle.left = rect.left;
	m_rtTitle.right = rect.right;

	//X轴
	m_rtAxisX.bottom = rect.bottom;
	m_rtAxisX.top = rect.bottom-AXIS_X_HEIGH; //AxisX Height
	m_rtTitle.left = rect.left + AXIS_Y_WIDTH;
	m_rtTitle.right = rect.right - AXIS_LEGEND_WIDTH;

	//Y轴
	m_rtAxisY.top = m_rtTitle.bottom;
	m_rtAxisY.bottom = m_rtAxisX.top;
	m_rtAxisY.left = rect.left;
	m_rtAxisY.right = m_rtAxisY.left + AXIS_Y_WIDTH;// AxisY Width

	//图例
	m_rtLegend.top = m_rtTitle.bottom;
	m_rtLegend.bottom = m_rtAxisX.top;
	m_rtLegend.left = rect.right-AXIS_LEGEND_WIDTH; //legend Width
	m_rtLegend.right = rect.right;

	//Plot区域
	m_rtPlot.top = m_rtTitle.bottom;
	m_rtPlot.bottom = m_rtAxisX.top;
	m_rtPlot.left = m_rtAxisY.right;
	m_rtPlot.right = m_rtLegend.left;

	RecalcAxisRange();
}
//////////////////////////////////////////////////////////////////////////
void CPlotLine::RecalcAxisRange(BOOL bRefMul)
{
	//更新屏幕的最大坐标范围
	if (bRefMul)
	{//比率不变，更新实际坐标系的边界值。//用于plot Move。
		m_dAxisXMax = m_rtPlot.Width()	+ m_dAxisXMin;
		m_dAxisYMax = m_rtPlot.Height() + m_dAxisYMin;

		m_dAxisXMax = m_rtPlot.Width()/m_dXMul	+ m_dAxisXMin;
		m_dAxisYMax = m_rtPlot.Height()/m_dYMul + m_dAxisYMin;
	}
	else
	{//更新屏幕坐标与实际坐标系的比率。//用于plot zoom
		m_dXMul = m_rtPlot.Width()/(m_dAxisXMax		- m_dAxisXMin);
		m_dYMul = m_rtPlot.Height()/(m_dAxisYMax	- m_dAxisYMin);
	}
}

void CPlotLine::MouseDragMove(CPoint point)//
{
	double x = point.x - m_ptMouseLast.x;
	double y = point.y - m_ptMouseLast.y;

	m_dAxisXMin -= x/m_dXMul;
	m_dAxisXMax -= x/m_dXMul;

	m_dAxisYMin += y/m_dYMul;
	m_dAxisYMax = m_rtPlot.Height()/m_dYMul + m_dAxisYMin;
	//重绘
	Invalidate();
	m_ptMouseLast = point;
}
void CPlotLine::MouseDragZoom(CPoint point)//
{
	//先将鼠标的位置作为中心位置
	double x = point.x - m_ptLMouseDown.x;
	double y = point.y - m_ptLMouseDown.y;

	//double dTmpMulX;
	//double dTmpMulY;

	if (x>0)
		m_dXMul = m_dMulXMouseDown * (1+ 0.1*x);
	else if (x<0)
	{
		x*=-1;
		m_dXMul = m_dMulXMouseDown / (1+ 0.1*x);
		//m_dXMul*=(0.99);
	}

	if (y<0)
		m_dYMul = m_dMulYMouseDown * (1-0.1*y);
	else if (y>0)
		m_dYMul = m_dMulYMouseDown / (1+0.1*y);



	m_dAxisXMax = m_rtPlot.Width()/m_dXMul/2 + m_dMouseDownOnPlotX;
	m_dAxisXMin = m_dMouseDownOnPlotX - m_rtPlot.Width()/m_dXMul/2;
	m_dAxisYMax = m_rtPlot.Height()/m_dYMul/2 + m_dMouseDownOnPlotY;
	m_dAxisYMin = m_dMouseDownOnPlotY - m_rtPlot.Height()/m_dYMul/2;

	//重绘
	Invalidate();
	//RecalcAxisRange(FALSE);
	m_ptMouseLast = point;
}

void CPlotLine::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bLBtnDown && m_bAxisMove)
	{//drag
		/*switch(m_dwMouseDragMode)
		{
		case MOUSE_DRAG_MOVE:
			MouseDragMove(point);
			break;
		case MOUSE_DRAG_ZOOM:
			if(m_rtPlot.PtInRect(m_ptLMouseDown))
				MouseDragZoom(point);
			break;
		default:
			break;
		}*/
		//if(m_bAxisMove)
		MouseDragMove(point);
		if(IsWindow(m_hWnd))
			Invalidate();
	}
	if (m_bShowCursor)
	{
		m_poCursor = point;
		m_poMouseCursorCur = point;
		if(IsWindow(m_hWnd))
			Invalidate();
	}
	//if(m_bPausePlot)


	CWnd::OnMouseMove(nFlags, point);
}

void CPlotLine::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bLBtnDown = TRUE;
	m_ptMouseLast = point;
	m_ptLMouseDown = point;

	if (m_rtPlot.PtInRect(point))
	{	//获取鼠标下的 plot绘图区域中的点坐标
		m_dMouseDownOnPlotX = m_dAxisXMin + (point.x-m_rtPlot.left)/m_dXMul;
		m_dMouseDownOnPlotY = m_dAxisYMin + (m_rtPlot.bottom-point.y)/m_dYMul;

		m_dMulXMouseDown = m_dXMul;
		m_dMulYMouseDown = m_dYMul;
	}
	CheckMouseHitLegend(point);

	CWnd::OnLButtonDown(nFlags, point);
}

void CPlotLine::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bLBtnDown = FALSE;
	if (m_bToolBarShow)
	{
		m_pToolbar->CheckClick(point - CPoint(m_rtToolBar.left, m_rtToolBar.top));
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void CPlotLine::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	DWORD i = 0;
	CMenu menuPlot;
	menuPlot.CreatePopupMenu();
	menuPlot.AppendMenu(MF_STRING, ID_ROOT_CLEAN, "清除");			//0
	menuPlot.AppendMenu(MF_STRING, ID_ROOT_PAUSE, "暂定");			//1
	menuPlot.AppendMenu(MF_STRING, ID_ROOT_AXISMOVE, "轴移动");		//2
	//menuPlot.AppendMenu(MF_STRING, ID_ROOT_AXISZOOM, "轴缩放");	//
	menuPlot.AppendMenu(MF_STRING, ID_ROOT_ZOOMIN, "放大x2");		//4
	menuPlot.AppendMenu(MF_STRING, ID_ROOT_ZOOMOUT, "缩小x2");		//5
	menuPlot.AppendMenu(MF_STRING, ID_ROOT_ZOOMFIT, "自动缩放");	//6
	menuPlot.AppendMenu(MF_STRING, ID_ROOT_CURVALUE, "测量");		//7
	menuPlot.AppendMenu(MF_STRING, ID_ROOT_MARK_POINTS, "描点");	//8

	menuPlot.AppendMenu(MF_BYPOSITION|MF_POPUP|MF_STRING,(UINT)menuPlot.m_hMenu,"通道");//8
	CMenu* menuCH = menuPlot.GetSubMenu(8);
	menuCH->AppendMenu(MF_STRING, ID_ROOT_CHANNEL_SINGLE, "单选");
	menuCH->AppendMenu(MF_STRING, ID_ROOT_CHANNEL_ALL, "显示全部");
	for (i=0;i<m_dwChNum;i++)
	{
		CString strTmpCHName;
		strTmpCHName.Format("%s", m_pChDat[i].strChName);
		menuCH->AppendMenu(MF_STRING, ID_ROOT_CHANNEL_0 + i, strTmpCHName);
	}

	UpdateRClickMenuState(&menuPlot);

	CPoint pt;
	GetCursorPos(&pt);

	menuPlot.TrackPopupMenu(TPM_LEFTALIGN,pt.x, pt.y, this);
	menuPlot.DestroyMenu();

	CWnd::OnRButtonDown(nFlags, point);
}
void CPlotLine::UpdateRClickMenuState(CMenu* pMenu)
{
	//去掉多余的ch通道菜单
	DWORD i = 0;
	CString strTmp;
	//更显ch的显示状态
	for (i=0;i<m_dwChNum;i++)
	{
		if (m_pChDat[i].m_bVisible)
		{
			pMenu->GetSubMenu(8)->CheckMenuItem(i+2, MF_BYPOSITION|MF_CHECKED);
		}
		else
		{
			pMenu->GetSubMenu(8)->CheckMenuItem(i+2, MF_BYPOSITION| MF_UNCHECKED);
		}
	}
	if (m_bSingleChSel)
	{
	}
	pMenu->GetSubMenu(8)->CheckMenuItem(0, MF_BYPOSITION|(m_bSingleChSel? MF_CHECKED:MF_UNCHECKED));
	pMenu->GetSubMenu(8)->CheckMenuItem(1, MF_BYPOSITION|(m_bSingleChSel? MF_UNCHECKED:MF_CHECKED));

	/*int iCheckMenuItem = 0;
	switch(m_dwMouseDragMode)
	{
	case MOUSE_DRAG_MOVE:
		iCheckMenuItem = 1;
		break;
	case MOUSE_DRAG_ZOOM:
		iCheckMenuItem = 2;
		break;
	case MOUSE_DRAG_BOX_ZOOM:
		iCheckMenuItem = 3;
		break;
	}*/
	//pMenu->CheckMenuItem(1, m_bAxisMove?MF_BYPOSITION|MF_CHECKED:MF_BYPOSITION|MF_UNCHECKED);

	if (m_bPausePlot)
		pMenu->CheckMenuItem(1, MF_BYPOSITION|MF_CHECKED);
	if (m_bAxisMove)
		pMenu->CheckMenuItem(2, MF_BYPOSITION|MF_CHECKED);
	if (m_bAutoZoomFit)
		pMenu->CheckMenuItem(5, MF_BYPOSITION|MF_CHECKED);
	if(m_bShowCursor)
		pMenu->CheckMenuItem(6, MF_BYPOSITION|MF_CHECKED);
	if (m_bDrawDot)
		pMenu->CheckMenuItem(7, MF_BYPOSITION|MF_CHECKED);
}
//////////////////////////////////////////////////////////////////////////
//右键菜单处理函数
void CPlotLine::OnRootAxismove()
{
	// TODO: Add your command handler code here
	//m_dwMouseDragMode = MOUSE_DRAG_MOVE;
	m_bAxisMove = !m_bAxisMove;
	if(m_bAxisMove)
		m_bAutoZoomFit = FALSE;
	m_pToolbar->SetBtnChecked(ID_ROOT_AXISMOVE, m_bAxisMove);
	m_pToolbar->SetBtnChecked(ID_ROOT_ZOOMFIT, m_bAutoZoomFit);
}

void CPlotLine::OnRootAxiszoom()
{
	// TODO: Add your command handler code here
	m_dwMouseDragMode = MOUSE_DRAG_ZOOM;
	//Invalidate();
}

void CPlotLine::OnRootChannelAll()
{
	// TODO: Add your command handler code here
	DWORD i=0;
	if (m_bSingleChSel)
	{
		for (i=0;i<m_dwChNum;i++)
		{
			m_pChDat[i].m_bVisible = TRUE;
		}
		m_bSingleChSel = FALSE;
		m_pToolbar->SetBtnChecked(ID_ROOT_CHANNEL_ALL, TRUE);
		m_pToolbar->SetBtnChecked(ID_ROOT_CHANNEL_SINGLE, FALSE);
	} 
	else
	{
		for (i=0;i<m_dwChNum;i++)
		{
			m_pChDat[i].m_bVisible = FALSE;
		}
		m_bSingleChSel = TRUE;
		m_pChDat[0].m_bVisible = TRUE;
		m_pToolbar->SetBtnChecked(ID_ROOT_CHANNEL_ALL, FALSE);
		m_pToolbar->SetBtnChecked(ID_ROOT_CHANNEL_SINGLE, TRUE);
	}
}

void CPlotLine::OnRootChannelSingle()
{
	// TODO: Add your command handler code here
	DWORD i=0;
	if (m_bSingleChSel)
	{
		for (i=0;i<m_dwChNum;i++)
		{
			m_pChDat[i].m_bVisible = TRUE;
		}
		m_bSingleChSel = FALSE;
		m_pToolbar->SetBtnChecked(ID_ROOT_CHANNEL_ALL, TRUE);
		m_pToolbar->SetBtnChecked(ID_ROOT_CHANNEL_SINGLE, FALSE);
	} 
	else
	{
		for (i=0;i<m_dwChNum;i++)
		{
			m_pChDat[i].m_bVisible = FALSE;
		}
		m_bSingleChSel = TRUE;
		m_pChDat[0].m_bVisible = TRUE;
		m_pToolbar->SetBtnChecked(ID_ROOT_CHANNEL_ALL, FALSE);
		m_pToolbar->SetBtnChecked(ID_ROOT_CHANNEL_SINGLE, TRUE);
	}
}

void CPlotLine::OnRootCurvalue()
{
	// TODO: Add your command handler code here
	m_bShowCursor = !m_bShowCursor;
	m_pToolbar->SetBtnChecked(ID_ROOT_CURVALUE, m_bShowCursor);
}

void CPlotLine::OnRootMarkPoints()
{
	// TODO: Add your command handler code here
	m_bDrawDot = !m_bDrawDot;
	m_pToolbar->SetBtnChecked(ID_ROOT_MARK_POINTS, m_bDrawDot);
}

void CPlotLine::OnRootPause()
{
	// TODO: Add your command handler code here
	//m_bPausePlot = !m_bPausePlot;
	if (m_bPausePlot)
	{
		m_bPausePlot = FALSE;
		m_pToolbar->SetBtnChecked(ID_ROOT_PAUSE, FALSE);
	} 
	else
	{
		m_bPausePlot = TRUE;
		m_pToolbar->SetBtnChecked(ID_ROOT_PAUSE, TRUE);
	}
}

void CPlotLine::OnRootZoomfit()
{
	// TODO: Add your command handler code here
	m_bAutoZoomFit = !m_bAutoZoomFit;
	if(m_bAutoZoomFit)
		m_bAxisMove = FALSE;
	m_pToolbar->SetBtnChecked(ID_ROOT_AXISMOVE, m_bAxisMove);
	m_pToolbar->SetBtnChecked(ID_ROOT_ZOOMFIT, m_bAutoZoomFit);
	//重绘
	Invalidate();
}
void CPlotLine::RecalcAutoZoomFit()
{
	DWORD i=0, count=0;
	double dMaxY=0,dMinY=0,dMaxX=0,dMinX=0;
	m_dXMul = m_rtPlot.Width()*1.0/(m_pChDat[0].GetDotNum()+20);
	//m_dAxisXMin = 0;
	/*dMaxY = m_pChDat[0].m_dMaxY;
	dMinY = m_pChDat[0].m_dMinY;
	dMaxX = m_pChDat[0].m_dMaxX;
	dMinX = m_pChDat[0].m_dMinX;*/
	//int i;// note by lpp
	for (i=0;i<m_dwChNum;i++)
	{
		if (m_pChDat[i].m_bVisible)
		{
			if (count == 0)
			{
				count = 1;
				dMaxY = m_pChDat[i].m_dMaxY;
				dMinY = m_pChDat[i].m_dMinY;
				dMaxX = m_pChDat[i].m_dMaxX;
				dMinX = m_pChDat[i].m_dMinX;
			}
			if (dMaxY < m_pChDat[i].m_dMaxY) dMaxY = m_pChDat[i].m_dMaxY;
			if (dMinY > m_pChDat[i].m_dMinY) dMinY = m_pChDat[i].m_dMinY;

			if (dMaxX < m_pChDat[i].m_dMaxX) dMaxX = m_pChDat[i].m_dMaxX;
			if (dMinX > m_pChDat[i].m_dMinX) dMinX = m_pChDat[i].m_dMinX;
		}
	}

	double dYWid = dMaxY - dMinY;
	if (dYWid == 0)
	{
		dYWid = 5.0;
		m_dYMul = (m_rtPlot.Height()*0.9)/dYWid;
		m_dAxisYMin = dMinY -dYWid*0.05;
	}
	else
	{
		m_dYMul = (m_rtPlot.Height()*0.9)/dYWid;
		m_dAxisYMin = dMinY -dYWid*0.05;
	}

	if (m_dwDrawMode == DRAW_MODE_POINTS)
	{
		double dXWid = dMaxX - dMinX;
		if (dXWid == 0)
		{
			dXWid = 5.0;
			m_dXMul = (m_rtPlot.Width()*0.9)/dXWid;
			m_dAxisXMin = dMinX -dXWid*0.05;
		} 
		else
		{
			m_dXMul = (m_rtPlot.Width()*0.9)/dXWid;
			m_dAxisXMin = dMinX -dXWid*0.05;
		}
	} 

	RecalcAxisRange();
}

void CPlotLine::OnRootZoomin()
{
	// TODO: Add your command handler code here
	m_bAutoZoomFit = FALSE;
	m_dXMul*=1.1;
	m_dYMul*=1.1;
	RecalcAxisRange();
	m_pToolbar->SetBtnChecked(ID_ROOT_ZOOMFIT, m_bAutoZoomFit);
	//重绘
	Invalidate();
}

void CPlotLine::OnRootZoomout()
{
	// TODO: Add your command handler code here
	m_bAutoZoomFit = FALSE;
	m_dXMul/=1.1;
	m_dYMul/=1.1;
	RecalcAxisRange();
	m_pToolbar->SetBtnChecked(ID_ROOT_ZOOMFIT, m_bAutoZoomFit);
	//重绘
	Invalidate();
}
void CPlotLine::CheckMouseHitLegend(CPoint point)
{
	DWORD iIndex = (point.y - m_rtLegend.top)/m_iChLabelHei;

	if (FALSE == m_rtLegend.PtInRect(point))
		return;
	if (iIndex >=0 && iIndex < m_dwChNum)
		OnRootShowCh(iIndex + ID_ROOT_CHANNEL_0);
}
void CPlotLine::OnRootShowCh(UINT uiCH)
{
	uiCH -= ID_ROOT_CHANNEL_0;
	//if (m_bSingleChSel)
	//{
	//	//int i; // note by lpp
	//	DWORD i;
	//	for (i=0;i<m_dwChNum;i++)
	//	{
	//		m_pChDat[i].m_bVisible = FALSE;
	//	}
	//	m_pChDat[uiCH].m_bVisible = TRUE;
	//}
	//else
	//{
	//	m_pChDat[uiCH].m_bVisible = !(m_pChDat[uiCH].m_bVisible);
	//}
	m_pChDat[uiCH].m_bVisible = !(m_pChDat[uiCH].m_bVisible);
}
void CPlotLine::OnRootClean()
{
	// TODO: Add your command handler code here
	Clear();
}
//////右键菜单结束
//////////////////////////////////////////////////////////////////////////
//创建绘图区：
//rt: 控件产生区域，
//pParentWnd: 父窗口，
//dwMode: 设定当前绘图模式
//nChannelNum: 通道数，最大为8通道
//nMaxPlotNum: 每通道最大绘图点
//////////////////////////////////////////////////////////////////////////
int CPlotLine::CreatePlot(const RECT& rt, CWnd* pParentWnd, DWORD dwMode, int nChannelNum, int nMaxPlotNum)
{
	m_dwDrawMode = dwMode;
	if (m_dwDrawMode == DRAW_MODE_LINE)
	{
		m_iNumSumAfterDotX = 0;
	} 
	else if(m_dwDrawMode == DRAW_MODE_POINTS)
	{
		m_iNumSumAfterDotX = 4;
	}
	m_iNumSumAfterDotY = 4;
	SetChannelNum(nChannelNum, nMaxPlotNum);
	bool bRes = Create(rt, WS_CHILD|WS_VISIBLE|SS_BLACKFRAME|SS_NOTIFY, pParentWnd);
	//ShowWindow(SW_SHOW);
	if(bRes)
		return 1;
	return 0;
}
void CPlotLine::SetChannelNum(int nCh, int nMaxBufLen)
{
	DWORD i=0;
	if (m_dwChNum > 0)
	{
		delete[] m_pChDat;
		m_pChDat = NULL;
	}
	m_dwChNum = nCh;
	m_dwChDatNum = nMaxBufLen;
	m_pChDat = new PLOT_LINE_CHANNEL[m_dwChNum];
	for (i=0;i<m_dwChNum;i++)
	{
		m_pChDat[i].SetDotsNum(nMaxBufLen);
		m_pChDat[i].m_clrCh = m_dwColorRef[i];
	}
}
//设定通道名称//TODO
int CPlotLine::SetChannelName(int iCh, LPCTSTR lpstrName)
{
	if (iCh>=int(m_dwChNum))
	{
		return -1;
	}
	m_pChDat[iCh].SetChName(lpstrName);

	return 0;
}

//获取当前绘图模式//TODO
DWORD CPlotLine::GetPlotMode()
{
	return m_dwDrawMode;
}

//设定当前绘图模式//TODO
//模式为MODE_LINE 或者MODE_CONSTRLLATION（星座图）
void CPlotLine::SetPlotMode(DWORD dwMode)
{
	m_dwDrawMode = dwMode;
	if (m_dwDrawMode == DRAW_MODE_LINE)
	{
		m_iNumSumAfterDotX = 0;
	} 
	else if(m_dwDrawMode == DRAW_MODE_POINTS)
	{
		m_iNumSumAfterDotX = 4;
	}
	m_iNumSumAfterDotY = 4;
	Invalidate();
}
int CPlotLine::SetChColor(int iCh, DWORD dwColor)
{
	if (iCh >=int(m_dwChNum))return -1;
	m_pChDat[iCh].m_clrCh = dwColor;
	return 0;
}
void CPlotLine::AddChannelData(int iCh, double dy)
{
	m_pcsSetDat->Lock();
	m_pChDat[iCh].AddDot(m_pChDat[iCh].m_dwDotsNumCur, dy);
	m_pcsSetDat->Unlock();

	if (!m_bPausePlot)
		Invalidate();
}
//点增加模式时对通道设定点
void CPlotLine::AddChannelData(int iCh, double dx, double dy)
{
	m_pcsSetDat->Lock();
	m_pChDat[iCh].AddDot(dx, dy);

	if (!m_bPausePlot)
		Invalidate();
	m_pcsSetDat->Unlock();
}

//曲线模式时 为通道设定数据 //TODO
int CPlotLine::SetChannelDat(int iCh, double *dDat, int iDatCount)
{
	int i = 0;
	if (iCh >=int(m_dwChNum))
		return -1;

	m_pcsSetDat->Lock();
	for (i=0;i<iDatCount;i++)
	{
		m_pChDat[iCh].AddDot(i, dDat[i]);
	}
	if (!m_bPausePlot)
		Invalidate();
	m_pcsSetDat->Unlock();

	return 0;
}

//星图模式时 为通道设定数据 //TODO
int CPlotLine::SetChannelDat(int iCh, double* dDatX, double* dDatY, int iDatCount)
{
	int i = 0;
	if (iCh >=int(m_dwChNum))
		return -1;

	m_pcsSetDat->Lock();
	for (i=0;i<iDatCount;i++)
	{
		m_pChDat[iCh].AddDot(dDatX[i], dDatY[i]);
	}
	if (!m_bPausePlot)
		Invalidate();
	m_pcsSetDat->Unlock();

	return 0;
}

//设定Y轴名称 //TODO
void CPlotLine::SetYAxisName(LPCTSTR lpszYAxisName)
{
	m_strAxisYName = lpszYAxisName;
}
//设定X轴名称 //TODO
void CPlotLine::SetXAxisName(LPCTSTR lpszXAxisName)
{
	m_strAxisXName = lpszXAxisName;
}
//设定X轴区间，如0~100； //TODO
void CPlotLine::SetXSpan(double iStart, double Span)
{
	m_dAxisXMin = iStart;
	m_dAxisXMax = m_dAxisXMin + Span;
	RecalcAxisRange(FALSE);
}
//设定Y轴区间，如0~100； //TODO
void CPlotLine::SetYSpan(double iStart, double Span)
{
	m_dAxisYMin = iStart;
	m_dAxisYMax = m_dAxisYMin + Span;
	RecalcAxisRange(FALSE);
}
//复位空间变量 //TODO
void CPlotLine::Reset()
{
}

//清屏 //TODO
void CPlotLine::Clear()
{
	//int i;// note by lpp
	DWORD i;
	m_pcsSetDat->Lock();
	for (i=0;i<m_dwChNum;i++)
	{
		m_pChDat[i].m_dwFront = 0;
		m_pChDat[i].m_dwRear = 0;
		m_pChDat[i].m_dwDotsNumCur = 0;
	}
	m_pcsSetDat->Unlock();
	RedrawWindow();
	//Invalidate();
}

//横向放大
void CPlotLine::ZoomAxisX(double dZoom)
{
	if (dZoom > 0)
		m_dXMul *= dZoom;
	if (m_dXMul<0.1)m_dXMul = 0.1;
	RecalcAxisRange();
}

//纵向放大
void CPlotLine::ZoomAxisY(double dZoom)
{
	if (dZoom > 0)
		m_dYMul *= dZoom;
	if (m_dYMul<0.1)m_dYMul = 0.1;
	RecalcAxisRange();
}
//放大缩小
void CPlotLine::ZoomAxis(double dZoom)
{
	if (dZoom > 0)
	{
		m_dXMul *= dZoom;
		m_dYMul *= dZoom;
	}
	if (m_dXMul<0.1)m_dXMul = 0.1;
	if (m_dYMul<0.1)m_dYMul = 0.1;
	RecalcAxisRange();
}
//自动缩放
void CPlotLine::SetAutoZoomFit(bool bFit)
{
	m_bAutoZoomFit = bFit;
}
//设定显示区域名称[图例名称] //TODO
void CPlotLine::SetTitle(LPCTSTR lpszTitle)
{
	m_strTitle.Format("%s", lpszTitle);
}

//绘制某一通道，注意绘制前后加Lock操作！
void CPlotLine::RenderCh(int iCh ,BOOL bClear)
{
	m_pChDat[iCh].m_bVisible = bClear;
}
//设定背景颜色
void CPlotLine::SetBKColor(DWORD dwColor)
{
	m_clrMainBGColor = dwColor;
}
// 设定网格线颜色
void CPlotLine::SetGridLineColor(DWORD dwColor)
{
	m_dwGridLineColor = dwColor;
}
// //设定坐标轴颜色
void CPlotLine::SetAxisColor(DWORD dwColor)
{
	m_dwAxisColor = dwColor;
}
void CPlotLine::SetTextColor(DWORD dwColor)
{
	m_dwTextColor = dwColor;
}

//设定X轴单位
void CPlotLine::SetUintDotSpanX(LPCTSTR strUint)
{
	m_strXUnit = strUint;
}
//设定Y轴单位
void CPlotLine::SetUintDotSpanY(LPCTSTR strUint)
{
	m_strYUnit = strUint;
}
//设定X轴比例//这个比例用于显示坐标使用。例如0~1024表示0~3000MHz,dScale=实际值/点数
void CPlotLine::SetUnitScaleX(double dScale)
{
	m_dUnitScaleX = dScale;
}
//设定Y轴比例//这个比例用于显示坐标使用。例如0~1024表示0~3000MHz,dScale=实际值/点数
void CPlotLine::SetUnitScaleY(double dScale)
{
	m_dUnitScaleY = dScale;
}
//设定是否描点
void CPlotLine::SetDrawDot(BOOL bDraw)
{
	m_bDrawDot = bDraw;
}
//设定是否显示测量值
void CPlotLine::SetCurSor(BOOL bDraw)
{
	m_bShowCursor = bDraw;
}
//设置是否暂停
void CPlotLine::SetVisible(BOOL bPause)
{
	m_bPausePlot = bPause;
}
//是否显示图例
void CPlotLine::SetLegend(BOOL bDraw)
{
	m_bshowlegend = bDraw;
}
//X轴坐标后保留几位小数//-1表示自动无限长度,默认为0
void CPlotLine::SetAxisNumSumAfterDotX(int num)
{
	m_iNumSumAfterDotX = num;
}
//Y轴坐标后保留几位小数//-1表示自动无限长度,默认为0
void CPlotLine::SetAxisNumSumAfterDotY(int num)
{
	m_iNumSumAfterDotY = num;
}

