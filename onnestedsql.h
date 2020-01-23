#if !defined(AFX_ONNESTEDSQL_H__7425725A_B156_414C_B869_80F2018A5727__INCLUDED_)
#define AFX_ONNESTEDSQL_H__7425725A_B156_414C_B869_80F2018A5727__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OnNestedSql.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OnNestedSql dialog

class OnNestedSql : public CDialog
{
// Construction
public:
	OnNestedSql(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(OnNestedSql)
	enum { IDD = IDD_NESTED_SQL };
	CString	m_Create;
	CString	m_Select1;
	CString	m_From1;
	CString	m_Where1;
	CString	m_Select2;
	CString	m_From2;
	CString	m_Where2;
	CString	m_Operator;

	CString	m_strCreate;
	CString	m_strSelect1;
	CString	m_strFrom1;
	CString	m_strWhere1;
	CString	m_strSelect2;
	CString	m_strFrom2;
	CString	m_strWhere2;
	CString	m_strOperator;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OnNestedSql)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void FileSave(CString fullFileName);
	void FileRead(CString fullFileName);
	BOOL FindByKey(CString& key, CString& value, CString* pArrStr, int nLineNumber);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(OnNestedSql)
	afx_msg void OnSave();
	afx_msg void OnRead();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClear();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONNESTEDSQL_H__7425725A_B156_414C_B869_80F2018A5727__INCLUDED_)
