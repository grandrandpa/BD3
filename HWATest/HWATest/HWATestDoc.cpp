// HWATestDoc.cpp : implementation of the CHWATestDoc class
//

#include "stdafx.h"
#include "HWATest.h"

#include "HWATestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHWATestDoc

IMPLEMENT_DYNCREATE(CHWATestDoc, CDocument)

BEGIN_MESSAGE_MAP(CHWATestDoc, CDocument)
END_MESSAGE_MAP()


// CHWATestDoc construction/destruction

CHWATestDoc::CHWATestDoc()
{
	// TODO: add one-time construction code here
}

CHWATestDoc::~CHWATestDoc()
{
}

BOOL CHWATestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CHWATestDoc serialization

void CHWATestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

// CHWATestDoc diagnostics
#ifdef _DEBUG
void CHWATestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHWATestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHWATestDoc commands
