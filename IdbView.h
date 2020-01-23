#if !defined(AFX_IDBVIEW_H__E009B502_428E_11D1_BDBF_00A0C96C8766__INCLUDED_)
#define AFX_IDBVIEW_H__E009B502_428E_11D1_BDBF_00A0C96C8766__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// IdbView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIdbView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

const int cnColor = 12;

class COwnListBox;
class CIdbView : public CFormView
{
protected:
	CIdbView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CIdbView)

// Form Data
public:
	//{{AFX_DATA(CIdbView)
	enum { IDD = IDD_DLG_REL_LIST };
	COwnListBox	m_listRecord;
	//}}AFX_DATA

// Attributes
public:
	CIdbDoc* GetDocument();

	static COLORREF colorList[cnColor];
	static COLORREF GetDrawColor(int i)
		{	return colorList[i % cnColor];	}

// Operations
public:
	void callSelChange();
	void callColorRelation();
	void SetupList();
	void SetMatrixColor(Relation* pR);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIdbView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CIdbView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CIdbView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeList1();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnOpIntersection();
	afx_msg void OnOpUnion();
	afx_msg void OnOpArea();
	afx_msg void OnBuffer();
	afx_msg void OnOpComplement();
	afx_msg void OnOpMinus();
	afx_msg void OnOpBlock();
	afx_msg void OnOpCollide();
	afx_msg void OnColorRelation();
	afx_msg void OnUpdateColorRelation(CCmdUI* pCmdUI);
	afx_msg void OnOpColor();
	afx_msg void OnUpdateOpComplement(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOpMinus(CCmdUI* pCmdUI);
	afx_msg void OnRegresion();
	afx_msg void OnDel_Relations();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in idbView.cpp
inline CIdbDoc* CIdbView::GetDocument()
   { return (CIdbDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDBVIEW_H__E009B502_428E_11D1_BDBF_00A0C96C8766__INCLUDED_)
