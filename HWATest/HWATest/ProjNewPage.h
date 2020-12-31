#pragma once
#include "ProjFilesPage.h"
#include "ProjConfigPage.h"
#include "ProjLinkPage.h"


// CProjNewPage

class CProjNewPage : public CBCGPPropertySheet
{
	DECLARE_DYNAMIC(CProjNewPage)

public:
	CProjNewPage(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CProjNewPage(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CProjNewPage();

protected:
	DECLARE_MESSAGE_MAP()
private:
	CProjFilesPage		m_pageFiles;
	CProjConfigPage		m_pageConfig;
	CProjLinkPage		m_pageLink;
};


