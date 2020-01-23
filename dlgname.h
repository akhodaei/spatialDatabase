#if !defined(AFX_DLGNAME_H__1FA5E000_EE29_11D2_A630_00104BECD389__INCLUDED_)
#define AFX_DLGNAME_H__1FA5E000_EE29_11D2_A630_00104BECD389__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgName dialog

class CDlgName : public CDialog
{
// Construction
public:
	CDlgName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgName)
	enum { IDD = IDD_DIALOG_NAME };
	CString	m_newRelName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgName)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNAME_H__1FA5E000_EE29_11D2_A630_00104BECD389__INCLUDED_)
