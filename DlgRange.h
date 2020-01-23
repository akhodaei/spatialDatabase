#if !defined(AFX_DLGRANGE_H__C9C3C2E6_A6E1_11D3_BAAF_00A0C9A67FC8__INCLUDED_)
#define AFX_DLGRANGE_H__C9C3C2E6_A6E1_11D3_BAAF_00A0C9A67FC8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgRange.h : header file
//

//RUICHEN create

/////////////////////////////////////////////////////////////////////////////
// CDlgRange dialog

class CDlgRange : public CDialog
{
// Construction
public:
	CDlgRange(CWnd* pParent = NULL);   // standard constructor
	COLORREF m_SelectColor;

// Dialog Data
	//{{AFX_DATA(CDlgRange)
	enum { IDD = IDD_DLG_RANGE };
	float	m_RangeLeft;
	float	m_RangeRight;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRange)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRange)
	afx_msg void OnRangeColorSelect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRANGE_H__C9C3C2E6_A6E1_11D3_BAAF_00A0C9A67FC8__INCLUDED_)
