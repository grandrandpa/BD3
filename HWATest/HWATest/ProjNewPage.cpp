// ProjNewPage.cpp : implementation file
//

#include "stdafx.h"
#include "HWATest.h"
#include "ProjNewPage.h"


// CProjNewPage

IMPLEMENT_DYNAMIC(CProjNewPage, CBCGPPropertySheet)

CProjNewPage::CProjNewPage(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CBCGPPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	EnableVisualManagerStyle();
	AddPage(&m_pageFiles);
	AddPage(&m_pageConfig);
	AddPage(&m_pageLink);
}

CProjNewPage::CProjNewPage(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CBCGPPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	EnableVisualManagerStyle();
	AddPage(&m_pageFiles);
	AddPage(&m_pageConfig);
	AddPage(&m_pageLink);
}

CProjNewPage::~CProjNewPage()
{
}


BEGIN_MESSAGE_MAP(CProjNewPage, CBCGPPropertySheet)
END_MESSAGE_MAP()


// CProjNewPage message handlers

//BOOL CProjNewPage::OnInitDialog()
//{
//	BOOL bResult = CBCGPPropertySheet::OnInitDialog();
//
//	// TODO:  Add your specialized code here
//
//	return bResult;
//}
