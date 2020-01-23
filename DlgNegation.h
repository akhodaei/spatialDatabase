#if !defined(AFX_DLGNEGATION_H__F0148EBC_98F2_4FD9_B0B4_18947D429901__INCLUDED_)
#define AFX_DLGNEGATION_H__F0148EBC_98F2_4FD9_B0B4_18947D429901__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNegation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNegation dialog

class CDlgNegation : public CDialog
{
// Construction
public:
	CDlgNegation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNegation)
	enum { IDD = IDD_DLG_NEGATION };
	CString	m_XRange;
	CString	m_YRange;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNegation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNegation)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNEGATION_H__F0148EBC_98F2_4FD9_B0B4_18947D429901__INCLUDED_)
