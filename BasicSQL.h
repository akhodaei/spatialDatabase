#if !defined(AFX_BASICSQL1_H__E402AACF_6B34_4F13_BB8F_C9CEC85EECEF__INCLUDED_)
#define AFX_BASICSQL1_H__E402AACF_6B34_4F13_BB8F_C9CEC85EECEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BasicSQL1.h : header file
//

#include <afx.h>

/////////////////////////////////////////////////////////////////////////////
// BasicSQL dialog

class BasicSQL : public CDialog
{
// Construction
public:
	BasicSQL(CWnd* pParent = NULL);   // standard constructor

public:
// Dialog Data
	//{{AFX_DATA(BasicSQL)
	enum { IDD = IDD_BASICSQL };
	CString m_strCreate;
	CString m_strSelect;
	CString m_strFrom;
	CString m_strWhere;

	CString	m_Create;
	CString	m_Select;
	CString	m_From;
	CString	m_Where;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BasicSQL)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

public:
	void FileSave(CString fullFileName);
	void FileRead(CString fullFileName);
	BOOL FindByKey(CString& key, CString& value, CString* pArrStr, int nLineNumber);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BasicSQL)
	afx_msg void OnSave();
	afx_msg void OnRead();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClear();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASICSQL1_H__E402AACF_6B34_4F13_BB8F_C9CEC85EECEF__INCLUDED_)
