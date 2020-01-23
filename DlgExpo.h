#if !defined(AFX_DLGEXPO_H__A6A62540_C075_11D4_90B7_00A0C9392ACC__INCLUDED_)
#define AFX_DLGEXPO_H__A6A62540_C075_11D4_90B7_00A0C9392ACC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgExpo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgExpo dialog

class CDlgExpo : public CDialog
{
// Construction
public:
	CDlgExpo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgExpo)
	enum { IDD = IDD_EXPO_DLG };
	double	m_Speed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgExpo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgExpo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEXPO_H__A6A62540_C075_11D4_90B7_00A0C9392ACC__INCLUDED_)
