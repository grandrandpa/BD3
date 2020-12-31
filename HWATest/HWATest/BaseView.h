#pragma once


#ifndef _XTP_INCLUDE_TOOLKIT
#define CXTPButton CButton
#endif

class CResizeGroupBox : public CXTPButton
{
	DECLARE_DYNAMIC(CResizeGroupBox)
		
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPResizeGroupBox object
	//-----------------------------------------------------------------------
	CResizeGroupBox();
	
	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CXTPResizeGroupBox object, handles cleanup and
	//     deallocation
	//-----------------------------------------------------------------------
	virtual ~CResizeGroupBox();
	
protected:
	//-----------------------------------------------------------------------
	// Summary:
	//     Called during paint operations to exclude the control windows
	//     that are grouped by this control.
	// Parameters:
	//     pDC      - Pointer to device context.
	//     rcClient - Client area of group box.
	//-----------------------------------------------------------------------
	virtual void Exclude(CDC* pDC, CRect& rcClient);

protected:
//{{AFX_CODEJOCK_PRIVATE
	DECLARE_MESSAGE_MAP()
		
	//{{AFX_VIRTUAL(CXTPResizeGroupBox)
	//}}AFX_VIRTUAL
		
	//{{AFX_MSG(CXTPResizeGroupBox)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
//}}AFX_CODEJOCK_PRIVATE
};





