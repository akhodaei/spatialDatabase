#if !defined(AFX_MATRIXVIEW_H__AD687993_3CF6_11D1_BDC2_00A0C96EF3EF__INCLUDED_)
#define AFX_MATRIXVIEW_H__AD687993_3CF6_11D1_BDC2_00A0C96EF3EF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MatrixView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatrixView view

class CMatrixView : public CScrollView
{
protected:
	CMatrixView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMatrixView)

// Attributes
public:
	CIdbDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatrixView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMatrixView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMatrixView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in idbView.cpp
inline CIdbDoc* CMatrixView::GetDocument()
   { return (CIdbDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATRIXVIEW_H__AD687993_3CF6_11D1_BDC2_00A0C96EF3EF__INCLUDED_)
