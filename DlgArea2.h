#if !defined(AFX_DLGAREA2_H__219A2EC3_2504_11D3_9CAC_00902744CE47__INCLUDED_)
#define AFX_DLGAREA2_H__219A2EC3_2504_11D3_9CAC_00902744CE47__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgArea2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgArea2 dialog

class CDlgArea2 : public CDialog
{
// Construction
public:
	CDlgArea2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgArea2)
	enum { IDD = IDD_DIALOG_AREA2 };
	double	m_Time;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgArea2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgArea2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAREA2_H__219A2EC3_2504_11D3_9CAC_00902744CE47__INCLUDED_)
