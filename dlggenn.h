#if !defined(AFX_DLGGENN_H__065E91E4_61EC_11D1_90D4_00A0C9392AD1__INCLUDED_)
#define AFX_DLGGENN_H__065E91E4_61EC_11D1_90D4_00A0C9392AD1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgGenN.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGenN dialog

class CIdbDoc;
class CDlgGenN : public CDialog
{
// Construction
public:
	CDlgGenN(CIdbDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGenN)
	enum { IDD = IDD_DLG_GEN_REL };
	CComboBox	m_combRel;
	CString	m_strRel;
	CString	m_strID;
	//}}AFX_DATA
	CIdbDoc* m_pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGenN)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGenN)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGENN_H__065E91E4_61EC_11D1_90D4_00A0C9392AD1__INCLUDED_)
