#if !defined(AFX_DLGAREA_H__6E99A084_64FD_11D1_90D6_00A0C9392AD1__INCLUDED_)
#define AFX_DLGAREA_H__6E99A084_64FD_11D1_90D6_00A0C9392AD1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgArea.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgArea dialog

class CDlgArea : public CDialog
{
// Construction
public:
	CDlgArea(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgArea)
	enum { IDD = IDD_DLG_AREA };
	double	m_dMaxX;
	double	m_dMinX;
	double	m_dStep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgArea)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgArea)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAREA_H__6E99A084_64FD_11D1_90D6_00A0C9392AD1__INCLUDED_)
