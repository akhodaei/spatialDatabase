#if !defined(AFX_DLGEXPORT_H__4FD91323_87C7_11D2_B523_00A0C9934E86__INCLUDED_)
#define AFX_DLGEXPORT_H__4FD91323_87C7_11D2_B523_00A0C9934E86__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgExport.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgExport dialog

class CDlgExport : public CDialog
{
// Construction
public:
	CDlgExport(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgExport)
	enum { IDD = IDD_EXPORT_FILE };
	CString	m_sDescriptive;
	CString	m_sSpatial;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgExport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgExport)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEXPORT_H__4FD91323_87C7_11D2_B523_00A0C9934E86__INCLUDED_)
