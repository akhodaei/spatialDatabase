#if !defined(AFX_DLGMAXMIN_H__77010B21_CED5_11D4_90B7_00A0C9392ACC__INCLUDED_)
#define AFX_DLGMAXMIN_H__77010B21_CED5_11D4_90B7_00A0C9392ACC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgMaxMin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMaxMin dialog

class CDlgMaxMin : public CDialog
{
// Construction
public:
	CDlgMaxMin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMaxMin)
	enum { IDD = IDD_MAXMIN_DLG };
	CString	m_maxmin_name;
	CString	m_maxmin_function;
	float	m_maxmin_constant;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMaxMin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMaxMin)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMAXMIN_H__77010B21_CED5_11D4_90B7_00A0C9392ACC__INCLUDED_)
