#if !defined(AFX_DLGAPPROXIMATION_H__C90D8A12_EEE0_4DE6_8F95_AA184699269A__INCLUDED_)
#define AFX_DLGAPPROXIMATION_H__C90D8A12_EEE0_4DE6_8F95_AA184699269A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgApproximation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgApproximation dialog

class CDlgApproximation : public CDialog
{
// Construction
public:
	CDlgApproximation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgApproximation)
	enum { IDD = IDD_APPROXIMATION };
	BOOL	m_UseApproximation;
	long	m_ApproxValue;
	int		m_ApproxType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgApproximation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgApproximation)
	afx_msg void OnApproxChecked();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAPPROXIMATION_H__C90D8A12_EEE0_4DE6_8F95_AA184699269A__INCLUDED_)
