#if !defined(AFX_DLGBLOCK_H__DB1B92E3_1F9A_11D3_B569_00A0C9934E86__INCLUDED_)
#define AFX_DLGBLOCK_H__DB1B92E3_1F9A_11D3_B569_00A0C9934E86__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgBlock.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBlock dialog

class CDlgBlock : public CDialog
{
// Construction
public:
	CDlgBlock(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBlock)
	enum { IDD = IDD_DIALOG_BLOCK };
	CString	m_strName;
	long	m_Time;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBlock)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBlock)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBLOCK_H__DB1B92E3_1F9A_11D3_B569_00A0C9934E86__INCLUDED_)
