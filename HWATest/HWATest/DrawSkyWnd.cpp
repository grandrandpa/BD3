// DrawSkyWnd.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "DrawSkyWnd.h"


// CDrawSkyWnd

IMPLEMENT_DYNAMIC(CDrawSkyWnd, CWnd)

CDrawSkyWnd::CDrawSkyWnd()
{
	ZeroMemory(&m_listSky, sizeof(BD2_GSV));

}

CDrawSkyWnd::~CDrawSkyWnd()
{
}


BEGIN_MESSAGE_MAP(CDrawSkyWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_COMMAND(ID_USER_CLEAR, &CDrawSkyWnd::OnUserClear)
	//ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CDrawSkyWnd message handlers
BOOL CDrawSkyWnd::Create(const RECT &rect, CWnd *pParentWnd, UINT nControlID)
{
	if (GetSafeHwnd())
		return FALSE;
	BOOL bRes = CWnd::Create( NULL, NULL,WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rect, pParentWnd,nControlID );
	return bRes;
}



void CDrawSkyWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	CBCGPMemDC memDC (dc, this);
	CDC* pDC = &memDC.GetDC ();	
	CRect rect; 	
	GetClientRect(&rect);
	pDC->FillSolidRect(&rect,clrBkFace);
	DrawSky(pDC, rect);
	ReleaseDC(pDC);
}

void CDrawSkyWnd::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CWnd::OnNcPaint() for painting messages
	DrawWindowsRect(this);
}

void CDrawSkyWnd::Clear(void)
{
	ZeroMemory(&m_listSky, sizeof(BD2_GSV));
	Reset();
}

void CDrawSkyWnd::RefreshView(BD2_GSV* data)
{
	memcpy(&m_listSky, data,sizeof(BD2_GSV));
}

void CDrawSkyWnd::Reset(void)
{
	if(IsWindow(m_hWnd))
		Invalidate();
}

void CDrawSkyWnd::DrawSky(CDC* pDC, CRect rect)
{
	int i=0,idErr=0,id=0;
	int Radiu,num=0,SvID=0;	
	char DEGREE[4]="°";
	CString OutStr;
	double R;
	double Azi,Elv;
	//glonass
	CBrush brGlonass (RGB (0, 200, 255));
	//gps
	CBrush brGPS (RGB (113, 240, 100));
	//bd3
	CBrush brBD2(RGB (77, 166, 247));
	GetClientRect(&rect);
	CPoint pt,CenterPoint((rect.left+rect.right)/2,(rect.top+rect.bottom)/2);
	Radiu=min((rect.left+rect.right)/2,(rect.top+rect.bottom)/2)-15;
	if(Radiu<15)
		Radiu=10;
	int nOldBkMode=pDC->SetBkMode(TRANSPARENT);
	CBrush * pBrush =CBrush::FromHandle( (HBRUSH)::GetStockObject(NULL_BRUSH) );
	CBrush * pOldBrush = pDC->SelectObject( pBrush );	
	CPen* pOldPen = pDC->SelectObject (&m_GnsspenLine);
	COLORREF clrTextOld = pDC->SetTextColor (clrTextFace);    
	CFont* pOldFont=pDC->SelectObject(&m_GnssfontNormal);
	//画两条中心直线
	pDC->MoveTo(CenterPoint.x-Radiu-15,CenterPoint.y);
	pDC->LineTo(CenterPoint.x+Radiu+15,CenterPoint.y);
	pDC->MoveTo(CenterPoint.x,CenterPoint.y-Radiu-15);
	pDC->LineTo(CenterPoint.x,CenterPoint.y+Radiu+15);
	//0度
	pDC->Ellipse(CenterPoint.x-Radiu,CenterPoint.y-Radiu,CenterPoint.x+Radiu,CenterPoint.y+Radiu);	
	//30度
	pDC->Ellipse(CenterPoint.x-2*Radiu/3,CenterPoint.y-2*Radiu/3,CenterPoint.x+2*Radiu/3,CenterPoint.y+2*Radiu/3);
	//60度
	pDC->Ellipse(CenterPoint.x-Radiu/3,CenterPoint.y-Radiu/3,CenterPoint.x+Radiu/3,CenterPoint.y+Radiu/3);
	//画0度点	
	//OutStr.Format("%2i%s",num,DEGREE);		
	//pDC->TextOut(CenterPoint.x+Radiu+3,CenterPoint.y+3,OutStr);
	//画90度点	
	num=90;
	OutStr.Format("%2i%s",num,DEGREE);		
	pDC->TextOut(CenterPoint.x+Radiu+3,CenterPoint.y-15,OutStr);
	//画180度点	
	num=180;
	OutStr.Format("%2i%s",num,DEGREE);		
	pDC->TextOut(CenterPoint.x+2,CenterPoint.y+Radiu,OutStr);
	//画270度点	
	num=270;
	OutStr.Format("%2i%s",num,DEGREE);		
	pDC->TextOut(CenterPoint.x-Radiu-30,CenterPoint.y-15,OutStr);
	//画360度点	
	num=0;
	OutStr.Format("%2i%s",num,DEGREE);		
	pDC->TextOut(CenterPoint.x,CenterPoint.y-Radiu-15,OutStr);
	//画30度点	
	num=30;
	OutStr.Format("%2i%s",num,DEGREE);		
	pDC->TextOut(CenterPoint.x, CenterPoint.y-Radiu*2/3-15,OutStr);
	//画中心60度点	
	num=60;
	OutStr.Format("%2i%s",num,DEGREE);		
	pDC->TextOut(CenterPoint.x, CenterPoint.y-Radiu/3-15,OutStr);
	pDC->SelectObject (pOldPen);
	pOldPen = pDC->SelectObject (&m_GnsspenLine);
	//15度
	//pDC->Ellipse(CenterPoint.x-5*Radiu/6,CenterPoint.y-5*Radiu/6,CenterPoint.x+5*Radiu/6,CenterPoint.y+5*Radiu/6);
	//45度
	//pDC->Ellipse(CenterPoint.x-1*Radiu/2,CenterPoint.y-1*Radiu/2,CenterPoint.x+1*Radiu/2,CenterPoint.y+1*Radiu/2);
	//75度
	//pDC->Ellipse(CenterPoint.x-Radiu/6,CenterPoint.y-Radiu/6,CenterPoint.x+Radiu/6,CenterPoint.y+Radiu/6);
	//画45度斜线
	pDC->MoveTo(CenterPoint);
	pDC->LineTo((int)(CenterPoint.x+Radiu*0.707),(int)(CenterPoint.y-Radiu*0.707));
	//画135度斜线
	pDC->MoveTo(CenterPoint);
	pDC->LineTo((int)(CenterPoint.x+Radiu*0.707),(int)(CenterPoint.y+Radiu*0.707));
	//画225度斜线
	pDC->MoveTo(CenterPoint);
	pDC->LineTo((int)(CenterPoint.x-Radiu*0.707),(int)(CenterPoint.y-Radiu*0.707));
	//画315度斜线
	pDC->MoveTo(CenterPoint);
	pDC->LineTo((int)(CenterPoint.x-Radiu*0.707),(int)(CenterPoint.y+Radiu*0.707));	   
	pDC->SelectObject (pOldPen);
	pDC->SelectObject( pOldBrush ); 
	pDC->SetTextColor (clrTextOld);
	clrTextOld=	pDC->SetTextColor(RGB(0,0,0));  //编号字体颜色
	pOldPen=pDC->SelectObject(&m_GnsspenLine);

    //m_listSky.id[0] = 1;
    //m_listSky.num = 1;
    //m_listSky.elv[0] = 66.0;
    //m_listSky.azi[0] = 5.0; 

	for(i=0;i<m_listSky.num;i++)
	{
		SvID = m_listSky.id[i];
		//id = (SvID>40)?(SvID-40):SvID;
#ifdef _DRAW_IDErr
		idErr = m_listSky.idErr[SvID-1];
#endif
		Azi  = m_listSky.azi[i];
		Elv  = m_listSky.elv[i];
		if(SvID>0 && SvID < 200  && //SvID <65
			Elv>=0 && Elv <= 90 &&
			Azi >=0 && Azi <= 360)
		{
//			if(Elv <= ELV_LIMIT)//仰角限制
//				pOldBrush=pDC->SelectObject (&brGPS);
//#ifdef _DRAW_IDErr
//			else if(idErr == 0)//表示此星在定位过程中被剔除了
//				pOldBrush=pDC->SelectObject (&brGlonass);
//#endif
//			else
//				pOldBrush=pDC->SelectObject (&brBD2);

            if(m_listSky.system_type == BD)
            {
                pOldBrush=pDC->SelectObject (&brBD2);
            }
            else if(m_listSky.system_type == GP)
            {
                pOldBrush=pDC->SelectObject (&brGPS);
            }
            else if(m_listSky.system_type == GL)
            {
                pOldBrush=pDC->SelectObject (&brGlonass);
            }
            else if(m_listSky.system_type == GA)
            {
                pOldBrush=pDC->SelectObject (&brBD2);
            }

			OutStr.Format("%d", SvID);
			R=Radiu*(1.0-Elv/90.0);
			pt.x=CenterPoint.x+(int)(R*sin(Azi*D2R));
			pt.y=CenterPoint.y-(int)(R*cos(Azi*D2R));		
			pDC->Ellipse(pt.x-5,pt.y-5,pt.x+10,pt.y+10);//FillEllipse //Ellipse
			if (SvID>= 10)
				pDC->TextOut(pt.x-5,pt.y-8,OutStr,OutStr.GetLength());
			else
				pDC->TextOut(pt.x-3,pt.y-6,OutStr,OutStr.GetLength());			
			pDC->SelectObject( pOldBrush );
		}
	}

	pDC->SelectObject (pOldPen);
	pDC->SetTextColor (clrTextOld);
	pDC->SelectObject(pOldFont);
	pDC->SetBkMode( nOldBkMode );
}

void CDrawSkyWnd::OnUserClear()
{
	// TODO: Add your command handler code here
	Clear();
}

void CDrawSkyWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
		//CPoint pt;
		//CMenu menu;
		//GetCursorPos(&pt);
		//menu.CreatePopupMenu();
		//menu.AppendMenu(MF_STRING, ID_USER_CLEAR, "清除");
		////UpdateRClickMenuState(&menuPlot);
		//menu.TrackPopupMenu(TPM_LEFTALIGN,pt.x, pt.y, this);
		//menu.DestroyMenu();

	CWnd::OnRButtonDown(nFlags, point);
}
