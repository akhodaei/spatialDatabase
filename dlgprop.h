#include "afxwin.h"
#include "slist.h"
#include "db.h"
#include <fstream.h>
#include <io.h>
#include "idbDoc.h"
#if !defined(AFX_DLGPROP_H__8DE58534_554E_11D1_90C6_00A0C9392AD1__INCLUDED_)
#define AFX_DLGPROP_H__8DE58534_554E_11D1_90C6_00A0C9392AD1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgProp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProp dialog

class CDlgProp : public CDialog
{
// Construction
public: 
	CDlgProp(CIdbDoc* pDoc , CWnd* pParent = NULL);   // standard constructor
	CIdbDoc* pDocTemp;

// Dialog Data
	//{{AFX_DATA(CDlgProp)
	enum { IDD = IDD_DLG_PROPERTY };
	CString	m_strOut;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtntable();
	CButton TableBtn;
	CString RelName;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROP_H__8DE58534_554E_11D1_90C6_00A0C9392AD1__INCLUDED_)
