#if !defined(AFX_DLGRELNAME_H__C9BFEDD3_CEE5_11D1_B528_00A0C9934E86__INCLUDED_)
#define AFX_DLGRELNAME_H__C9BFEDD3_CEE5_11D1_B528_00A0C9934E86__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgRelName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRelName dialog
class CIdbDoc;

class CDlgRelName : public CDialog
{
// Construction
public:
	CDlgRelName(CIdbDoc* pDoc,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRelName)
	enum { IDD = IDD_DLG_GEN_REL1 };
	CComboBox	m_combRel;
	CString	m_strRel;
	//}}AFX_DATA
	CIdbDoc* m_pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRelName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRelName)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRELNAME_H__C9BFEDD3_CEE5_11D1_B528_00A0C9934E86__INCLUDED_)
