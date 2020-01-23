#if !defined(AFX_DLGINSR_H__84E02BC3_4BE1_11D1_90BF_00A0C9392AD1__INCLUDED_)
#define AFX_DLGINSR_H__84E02BC3_4BE1_11D1_90BF_00A0C9392AD1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgInsR.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInsR dialog

class CDlgInsR : public CDialog
{
// Construction
public:
	CDlgInsR(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgInsR)
	enum { IDD = IDD_DLG_INSRELATION };
	CString	m_strText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInsR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void FileSave(CString fullFileName);
	void FileRead(CString fullFileName);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInsR)
	afx_msg void OnSave();
	afx_msg void OnRead();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINSR_H__84E02BC3_4BE1_11D1_90BF_00A0C9392AD1__INCLUDED_)
