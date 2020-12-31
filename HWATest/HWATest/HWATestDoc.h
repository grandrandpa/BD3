// HWATestDoc.h : interface of the CHWATestDoc class
//


#pragma once


class CHWATestDoc : public CDocument
{
public: // create from serialization only
	CHWATestDoc();
	DECLARE_DYNCREATE(CHWATestDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CHWATestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


