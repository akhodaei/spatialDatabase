#if !defined(AFX_DLGNTIME_H__576F40E4_097E_11D3_A417_00A0C9A6613A__INCLUDED_)
#define AFX_DLGNTIME_H__576F40E4_097E_11D3_A417_00A0C9A6613A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgNtime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNtime dialog

class CDlgNtime : public CDialog
{
// Construction
public:
	CDlgNtime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNtime)
	enum { IDD = IDD_DIALOG_TIME };
	double	m_Start;
	double	m_End;
	double	m_Speed;
	double	m_NoOfStep;
	double	m_Step;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNtime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNtime)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNTIME_H__576F40E4_097E_11D3_A417_00A0C9A6613A__INCLUDED_)
