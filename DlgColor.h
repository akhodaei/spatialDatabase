#if !defined(AFX_DLGCOLOR_H__C9C3C2E5_A6E1_11D3_BAAF_00A0C9A67FC8__INCLUDED_)
#define AFX_DLGCOLOR_H__C9C3C2E5_A6E1_11D3_BAAF_00A0C9A67FC8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgColor.h : header file
//

//RUICHEN create

/////////////////////////////////////////////////////////////////////////////
// CDlgColor dialog
class CIdbDoc;

class CDlgColor : public CDialog
{
// Construction
public:
	CDlgColor(CIdbDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgColor)
	enum { IDD = IDD_DLG_COLOR };
	CListBox	m_RangeList;
	CString	m_Cur_RangeList;
	//}}AFX_DATA

	CIdbDoc* m_pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgColor)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgColor)
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeRangeList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOLOR_H__C9C3C2E5_A6E1_11D3_BAAF_00A0C9A67FC8__INCLUDED_)
